#include "Online.h"
#include <spdlog/spdlog.h>

namespace Ship {
    namespace Online {
        Server::Server() {
            port = 25565;
        }

        void Server::RunServer() {
            while (true) {
                client = SDLNet_TCP_Accept(server);

                if (client && server)
                {
                    break;
                }
            }

            const char* message = "HELLO CLIENT";

            while (client && server)
            {
                SDLNet_TCP_Send(client, message, strlen(message) + 1);

                char text[1000];

                SDLNet_TCP_Recv(client, text, 1000);
                SPDLOG_INFO(text);
            }

            SDLNet_TCP_Close(server);
            SDLNet_TCP_Close(client);
            SDLNet_Quit();
        }

        void Server::CreateServer() {
            SDLNet_Init();

            SDLNet_ResolveHost(&ip, NULL, port);

            server = SDLNet_TCP_Open(&ip);

            onlineThread = std::thread(&Server::RunServer, this);
        }

        void Client::RunClient()
        {
            const char* message = "HELLO SERVER";
            client = SDLNet_TCP_Open(&ip);

            while (client) {
                SDLNet_TCP_Send(client, message, strlen(message) + 1);

                char text[1000];

                SDLNet_TCP_Recv(client, text, 1000);
                SPDLOG_INFO(text);
            }

            SDLNet_TCP_Close(client);
            SDLNet_Quit();
        }

        void Client::ConnectToServer() {
            SDLNet_Init();

            SDLNet_ResolveHost(&ip, ipAddress.c_str(), port);

            onlineThread = std::thread(&Client::RunClient, this);
        }

        Client::Client() {
            ipAddress = "127.0.0.1";
            port = 25565;
        }
    }
}