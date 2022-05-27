#include "CrowdControl.h"
#include "Cvar.h"
#include "Lib/json.hpp"
#include <spdlog/spdlog.h>

extern "C" u8 ExecuteCommand(const char* effectId, uint32_t value);

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
                if (commandsInQueue.size() > 0) {
                    u8 returnSuccess = ExecuteCommand(commandsInQueue[0].effectType, commandsInQueue[0].effectValue);

                    nlohmann::json data2;
                    data2["id"] = commandsInQueue[0].packetId;
                    data2["status"] = returnSuccess;

                    std::string data3 = data2.dump();

                    SDLNet_TCP_Send(tcpsock, &data3, sizeof(data3) + 1);

                    sendId++;
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

            ccThreadRun = std::thread(&CrowdControl::RunCrowdControl, this);

            while (connected && CVar_GetS32("gCrowdControl", 0) == 1 && tcpsock) {
                int len = SDLNet_TCP_Recv(tcpsock, &received, 512);

                if (!len || !tcpsock) {
                    printf("SDLNet_TCP_Recv: %s\n", SDLNet_GetError());
                    break;
                }

                CCPacket* packet = new CCPacket();
                nlohmann::json data = nlohmann::json::parse(received);

                packet->packetId = data["id"];
                memcpy(&packet->effectType, data["code"].get<std::string>().c_str(), 64);
                packet->effectValue = data["type"];

                commandsInQueue.push_back(*packet);
            }

            if (connected) {
                SDLNet_TCP_Close(tcpsock);
                SDLNet_Quit();
                connected = false;
            }
        }
    }
}