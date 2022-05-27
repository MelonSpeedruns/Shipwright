#include "CrowdControl.h"
#include "Cvar.h"
#include "Lib/json.hpp"
#include <spdlog/spdlog.h>

extern "C" u8 SetCrowdControlData(const char* code);

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
                    nlohmann::json data = nlohmann::json::parse(commandsInQueue[0].recvbuf);
                    u8 returnSuccess = SetCrowdControlData(data["code"].get<std::string>().c_str());

                    nlohmann::json data2;
                    data2["id"] = sendId;

                    if (returnSuccess == 0) {
                        data2["status"] = 1;
                    }
                    else {
                        data2["status"] = 0;
                    }

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
                int len = SDLNet_TCP_Recv(tcpsock, &receivedPacket, 512);

                if (!len) {
                    printf("SDLNet_TCP_Recv: %s\n", SDLNet_GetError());
                    break;
                }

                commandsInQueue.push_back(receivedPacket);
            }

            if (connected) {
                SDLNet_TCP_Close(tcpsock);
                SDLNet_Quit();
                connected = false;
            }
        }
    }
}