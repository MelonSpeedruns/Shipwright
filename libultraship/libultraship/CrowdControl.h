#pragma once

#include <SDL2/SDL_net.h>
#include <cstdint>
#include <thread>

namespace Ship {
    namespace CrowdControl {

        typedef struct CCPacket {
            uint8_t effectType;
            uint32_t effectData;
        } CCPacket;

        class CrowdControl {
        private:
            std::thread ccThread;

            TCPsocket tcpsock;
            IPaddress ip;

            CCPacket* receivedPacket;

            bool connected;

            void RunCrowdControl();

        public:
            void InitCrowdControl();
        };
    }
}