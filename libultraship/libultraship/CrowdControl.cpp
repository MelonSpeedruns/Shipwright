#include "CrowdControl.h"
#include "Cvar.h"

extern "C" void SetCrowdControlData(Ship::CrowdControl::CCPacket * packet);

namespace Ship {
    namespace CrowdControl {
        void CrowdControl::InitCrowdControl() {
            if (SDLNet_ResolveHost(&ip, "127.0.0.1", 25565) == -1) {
                printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
                exit(1);
            }

            ccThread = std::thread(&CrowdControl::RunCrowdControl, this);
        }

        void CrowdControl::RunCrowdControl()
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

            while (connected && CVar_GetS32("gCrowdControl", 0) == 1) {
                int len = SDLNet_TCP_Recv(tcpsock, &receivedPacket, sizeof(CCPacket));

                if (!len) {
                    printf("SDLNet_TCP_Recv: %s\n", SDLNet_GetError());
                    break;
                }

                if (len > 0) {
                    SetCrowdControlData(receivedPacket);
                    printf("Received: %.*s\n", len, receivedPacket->effectType);
                }
            }

            if (connected) {
                SDLNet_TCP_Close(tcpsock);
                connected = false;
            }
        }
    }
}