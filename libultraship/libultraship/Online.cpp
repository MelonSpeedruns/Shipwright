#include "Online.h"
#include <spdlog/spdlog.h>

namespace Ship {
    namespace Online {
        Server::Server() {
            port = 25565;
        }

        Server::~Server() {
            SPDLOG_INFO("destruct Server");
            Stop();
        }

        void Server::Stop() {
            {
                const std::lock_guard<std::mutex> OnlineLock(OnlineMutex);
                stopThreads = true;
            }

            onlineThread.join();

            SDLNet_TCP_Close(tcpsock);
            SDLNet_TCP_Close(client);
            SDLNet_TCP_Close(server);

            SDLNet_Quit();
        }

        void Server::RunServer() {
            while (!done) {
                /* try to accept a connection */
                client = SDLNet_TCP_Accept(server);
                if (!client) { /* no connection accepted */
                  /*SPDLOG_INFO("SDLNet_TCP_Accept: %s\n",SDLNet_GetError()); */
                    SDL_Delay(100); /*sleep 1/10th of a second */
                    continue;
                }

                /* get the clients IP and port number */
                IPaddress* remoteip;
                remoteip = SDLNet_TCP_GetPeerAddress(client);
                if (!remoteip) {
                    SPDLOG_INFO("SDLNet_TCP_GetPeerAddress: {}\n", SDLNet_GetError());
                    continue;
                }

                /* print out the clients IP and port number */
                Uint32 ipaddr;
                ipaddr = SDL_SwapBE32(remoteip->host);
                SPDLOG_INFO("Accepted a connection from {}.{}.{}.{} port {}\n", ipaddr >> 24,
                    (ipaddr >> 16) & 0xff, (ipaddr >> 8) & 0xff, ipaddr & 0xff,
                    remoteip->port);
            }

            while (true) {
                const std::lock_guard<std::mutex> OnlineLock(OnlineMutex);

                if (stopThreads) {
                    return;
                }

                /* read the buffer from client */
                char message[1024];
                int len = SDLNet_TCP_Recv(client, message, 1024);
                if (!len) {
                    SPDLOG_INFO("SDLNet_TCP_Recv: {}\n", SDLNet_GetError());
                    break;
                }
                /* print out the message */
                SPDLOG_INFO("Received: {}\n", message);
                if (message[0] == 'q') {
                    SPDLOG_INFO("Disconecting on a q\n");
                    break;
                }
                if (message[0] == 'Q') {
                    SPDLOG_INFO("Closing server on a Q.\n");
                    done = true;
                    break;
                }
            }
        }

        void Server::CreateServer() {
            if (SDLNet_Init() == -1) {
                SPDLOG_INFO("SDLNet_Init: {}\n", SDLNet_GetError());
                exit(2);
            }

            SPDLOG_INFO("Starting server...\n");
            IPaddress ip;
            if (SDLNet_ResolveHost(&ip, NULL, 25565) == -1) {
                SPDLOG_INFO("SDLNet_ResolveHost: {}\n", SDLNet_GetError());
                exit(1);
            }

            server = SDLNet_TCP_Open(&ip);

            if (!server) {
                SPDLOG_INFO("SDLNet_TCP_Open: {}\n", SDLNet_GetError());
                exit(2);
            }

            onlineThread = std::thread(&Server::RunServer, this);
        }

        void Client::RunClient()
        {
            while (true) {
                const std::lock_guard<std::mutex> OnlineLock(OnlineMutex);

                if (stopThreads) {
                    return;
                }

                SPDLOG_INFO("message: ");

                int len = strlen("hello world!");

                /* strip the newline */
                int result;

                /* print out the message */
                SPDLOG_INFO("Sending: {}\n", "hello world!");

                result = SDLNet_TCP_Send(tcpsock, "hello world!", len); /* add 1 for the NULL */

                if (result < len)
                    SPDLOG_INFO("SDLNet_TCP_Send: {}\n", SDLNet_GetError());
            }
        }

        void Client::ConnectToServer() {
            if (SDLNet_Init() == -1) {
                SPDLOG_INFO("SDLNet_Init: {}\n", SDLNet_GetError());
                exit(2);
            }

            SPDLOG_INFO("Starting client...\n");
            IPaddress ip;

            if (SDLNet_ResolveHost(&ip, "127.0.0.1", 25565) == -1) {
                SPDLOG_INFO("SDLNet_ResolveHost: {}\n", SDLNet_GetError());
                exit(1);
            }

            tcpsock = SDLNet_TCP_Open(&ip);
            if (!tcpsock) {
                SPDLOG_INFO("SDLNet_TCP_Open: {}\n", SDLNet_GetError());
                exit(2);
            }

            onlineThread = std::thread(&Client::RunClient, this);
        }

        Client::Client() {
            ipAddress = "127.0.0.1";
            port = 25565;
        }

        Client::~Client() {
            SPDLOG_INFO("destruct Client");
            Stop();
        }

        void Client::Stop() {
            {
                const std::lock_guard<std::mutex> OnlineLock(OnlineMutex);
                stopThreads = true;
            }

            onlineThread.join();

            SDLNet_TCP_Close(tcpsock);
            SDLNet_TCP_Close(client);

            SDLNet_Quit();
        }
    }
}