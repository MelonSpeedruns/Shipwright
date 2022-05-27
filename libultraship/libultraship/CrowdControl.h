#pragma once

#include <SDL2/SDL_net.h>
#include <cstdint>
#include <thread>
#include <memory>
#include <map>
#include <vector>

namespace Ship {
    namespace CrowdControl {

        struct Command
        {
        public:
            uint32_t id = 0;
            std::string command;
            std::string viewer;
            int type;
            long long time;
        };

        typedef struct CCPacket {
            char recvbuf[512];
        } CCPacket;

        class CrowdControl {
        private:
            std::thread ccThreadRun;
            std::thread ccThreadReceive;

            TCPsocket tcpsock;
            IPaddress ip;

            std::map<uint32_t, std::shared_ptr<Command>> command_map;

            bool connected;
            uint8_t sendId;

            char received[512];

            std::vector<CCPacket> commandsInQueue;
            CCPacket receivedPacket;

            void RunCrowdControl();
            void ReceiveFromCrowdControl();

            std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();

            std::string socketBuffer = "";
            std::vector<std::string> BufferSocketResponse(const char* buf, size_t buf_size);

            long long GetElapsedTime();
            long long GetElapsedTime(std::chrono::steady_clock::time_point time);

        public:
            void InitCrowdControl();
        };
    }
}