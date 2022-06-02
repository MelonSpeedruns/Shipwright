#include "CrowdControl.h"
#include "Cvar.h"
#include "Lib/json.hpp"
#include <spdlog/spdlog.h>
#include <regex>

extern "C" u8 ExecuteCommand(const char* effectId, uint32_t value);
extern "C" u8 ExecuteTimedCommands();

namespace Ship {
    namespace CrowdControl {
        void CrowdControl::InitCrowdControl() {
            SDLNet_Init();

            if (SDLNet_ResolveHost(&ip, "127.0.0.1", 43384) == -1) {
                printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
            }

            ccThreadReceive = std::thread(&CrowdControl::ReceiveFromCrowdControl, this);
        }

        void CrowdControl::RunCrowdControl() {
            while (connected) {
                u8 returnSuccess = ExecuteTimedCommands();
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

            ccThreadRun = std::thread(&CrowdControl::RunCrowdControl, this);

            while (connected && CVar_GetS32("gCrowdControl", 0) == 1 && tcpsock) {
                int len = SDLNet_TCP_Recv(tcpsock, &received, 512);

                if (!len || !tcpsock) {
                    printf("SDLNet_TCP_Recv: %s\n", SDLNet_GetError());
                    break;
                }

                CCPacket packet;
                nlohmann::json dataReceived = nlohmann::json::parse(received);

                packet.packetId = dataReceived["id"];
                packet.effectValue = dataReceived["type"];

                u8 returnSuccess = ExecuteCommand(dataReceived["code"].get<std::string>().c_str(), packet.effectValue);

                nlohmann::json dataSend;
                dataSend["id"] = packet.packetId;
                dataSend["status"] = returnSuccess == 1 ? EffectResult::Success : EffectResult::Retry;
                dataSend["timeRemaining"] = 0;
                dataSend["type"] = 0;

                std::string jsonResponse = dataSend.dump();
                SDLNet_TCP_Send(tcpsock, const_cast<char*> (jsonResponse.data()), jsonResponse.size() + 1);
            }

            if (connected) {
                SDLNet_TCP_Close(tcpsock);
                SDLNet_Quit();
                connected = false;
                ccThreadRun.join();
            }
        }
    }
}