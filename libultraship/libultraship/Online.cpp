#include "Online.h"
#include <spdlog/spdlog.h>
#include <PR/ultra64/gbi.h>

extern "C" void Rupees_ChangeBy(s16 rupeeChange);

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
                ReceivePacketMessage();
            }

            SDLNet_TCP_Close(server);
            SDLNet_TCP_Close(client);
            SDLNet_Quit();
        }

        void Server::ReceivePacketMessage()
        {
            OnlinePacket* packet;
            int len = SDLNet_TCP_Recv(client, &packet, sizeof(OnlinePacket));

            if (len) {
                Rupees_ChangeBy(1);
            }
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

            }

            SDLNet_TCP_Close(client);
            SDLNet_Quit();
        }

        void Client::SendPacketMessage(OnlinePacket* packet)
        {
            SDLNet_TCP_Send(client, packet, sizeof(OnlinePacket));
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

        void OnlinePacket::OnExecute()
        {
            Rupees_ChangeBy(rupeeAmountChanged);
        }
    }
}