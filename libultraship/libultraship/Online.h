#pragma once

#include "SDL_net.h"
#include <thread>
#include <mutex>

namespace Ship {
	namespace Online {
		class Server {
		private:
			bool done;
			bool stopThreads;

			UDPsocket udpsock;
			UDPpacket* recv_packet;
			SDLNet_SocketSet socketset;
			int numused;
			const int MAX_PACKET_SIZE = 512;

			std::thread onlineThread;

			TCPsocket server;
			TCPsocket client;
			TCPsocket tcpsock;

			std::mutex OnlineMutex;

		public:
			int port;

			Server();
			~Server();

			void Stop();

			void CreateServer();
			void RunServer();
		};

		class Client {
		private:
			bool done;
			bool stopThreads;

			UDPsocket udpsock;
			UDPpacket* recv_packet;
			SDLNet_SocketSet socketset;
			int numused;
			const int MAX_PACKET_SIZE = 512;

			std::thread onlineThread;

			TCPsocket client;
			TCPsocket tcpsock;

			std::mutex OnlineMutex;

		public:
			std::string ipAddress;
			int port;

			Client();
			~Client();

			void Stop();

			void ConnectToServer();
			void RunClient();
		};
	}
}