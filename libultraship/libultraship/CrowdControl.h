#pragma once

#include <SDL2/SDL_net.h>
#include <cstdint>
#include <thread>
#include <memory>
#include <map>
#include <vector>

namespace Ship {
    namespace CrowdControl {
        typedef struct CCPacket {
            uint32_t packetId;
            char effectType[64];
            uint32_t effectValue;
        } CCPacket;

        class CrowdControl {
        private:
            std::thread ccThreadRun;
            std::thread ccThreadReceive;

            TCPsocket tcpsock;
            IPaddress ip;

            bool connected;
            uint8_t sendId;

            char received[512];

            std::vector<CCPacket> commandsInQueue;

            void RunCrowdControl();
            void ReceiveFromCrowdControl();

            std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();

            std::string socketBuffer = "";

        public:
            void InitCrowdControl();
        };
    }
}