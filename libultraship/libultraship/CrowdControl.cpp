#include "CrowdControl.h"
#include "Cvar.h"
#include "Lib/json.hpp"
#include <spdlog/spdlog.h>
#include <regex>

extern "C" u8 ExecuteEffect(const char* effectId, uint32_t value);
extern "C" void RemoveEffect(const char* effectId);

namespace Ship {
    namespace CrowdControl {
        void CrowdControl::InitCrowdControl() {
            SDLNet_Init();

            if (SDLNet_ResolveHost(&ip, "127.0.0.1", 43384) == -1) {
                printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
            }

            ccThreadReceive = std::thread(&CrowdControl::ReceiveFromCrowdControl, this);
        }

        void CrowdControl::RunCrowdControl(CCPacket* packet) {
            u8 paused = 0;

            while (connected) {
                nlohmann::json dataSend;

                dataSend["id"] = packet->packetId;
                dataSend["type"] = 0;

                dataSend["timeRemaining"] = packet->timeRemaining;

                u8 returnSuccess = ExecuteEffect(packet->effectType.c_str(), packet->effectValue);
                dataSend["status"] = returnSuccess == 1 ? EffectResult::Success : returnSuccess == 2 ? EffectResult::Failure : EffectResult::Retry;

                std::string jsonResponse = dataSend.dump();
                SDLNet_TCP_Send(tcpsock, const_cast<char*> (jsonResponse.data()), jsonResponse.size() + 1);

                if (returnSuccess == 2) {
                    return;
                }

                if (returnSuccess == 1) {
                    if (paused && packet->timeRemaining > 0) {
                        paused = 0;
                        nlohmann::json dataSend;
                        dataSend["id"] = packet->packetId;
                        dataSend["type"] = 0;
                        dataSend["timeRemaining"] = packet->timeRemaining;
                        dataSend["status"] = EffectResult::Resumed;

                        std::string jsonResponse = dataSend.dump();
                        SDLNet_TCP_Send(tcpsock, const_cast<char*> (jsonResponse.data()), jsonResponse.size() + 1);
                    }

                    if (packet->timeRemaining <= 0) {
                        RemoveEffect(packet->effectType.c_str());
                        return;
                    }

                    packet->timeRemaining -= 500;

                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                }
                else if (returnSuccess == 0 && paused == 0 && packet->timeRemaining > 0) {
                    paused = 1;

                    nlohmann::json dataSend;
                    dataSend["id"] = packet->packetId;
                    dataSend["type"] = 0;
                    dataSend["timeRemaining"] = packet->timeRemaining;
                    dataSend["status"] = EffectResult::Paused;

                    std::string jsonResponse = dataSend.dump();
                    SDLNet_TCP_Send(tcpsock, const_cast<char*> (jsonResponse.data()), jsonResponse.size() + 1);

                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }
                else {
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                }
            }
        }

        void CrowdControl::ReceiveFromCrowdControl()
        {
            printf("Waiting for a connection from Crowd Control...");

            while (!connected && CVar_GetS32("gCrowdControl", 0) == 1) {
                tcpsock = SDLNet_TCP_Open(&ip);

                if (tcpsock) {
                    connected = true;
                    printf("Connected to Crowd Control!");
                    break;
                }
            }

            while (connected && CVar_GetS32("gCrowdControl", 0) == 1 && tcpsock) {
                int len = SDLNet_TCP_Recv(tcpsock, &received, 512);

                if (!len || !tcpsock || len == -1) {
                    printf("SDLNet_TCP_Recv: %s\n", SDLNet_GetError());
                    break;
                }

                nlohmann::json dataReceived = nlohmann::json::parse(received);

                CCPacket* packet = new CCPacket();
                packet->packetId = dataReceived["id"];
                packet->effectValue = dataReceived["type"];
                packet->effectType = dataReceived["code"].get<std::string>();

                if (strcmp(packet->effectType.c_str(), "defense_modifier") == 0 ||
                    strcmp(packet->effectType.c_str(), "iron_boots") == 0 ||
                    strcmp(packet->effectType.c_str(), "giant_link") == 0 ||
                    strcmp(packet->effectType.c_str(), "high_gravity") == 0) {
                    packet->timeRemaining = 30000;
                }
                else {
                    packet->timeRemaining = 0;
                }

                std::thread t = std::thread(&CrowdControl::RunCrowdControl, this, packet);
                t.detach();
            }

            if (connected) {
                SDLNet_TCP_Close(tcpsock);
                SDLNet_Quit();
                connected = false;
            }
        }
    }
}