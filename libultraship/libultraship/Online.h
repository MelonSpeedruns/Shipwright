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

			const char* text = "HELLO CLIENT!\n";

			IPaddress ip;

			TCPsocket server;
			TCPsocket client;

		public:
			int port;

			Server();

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

			TCPsocket server;
			TCPsocket client;

		public:
			IPaddress ip;
			std::string ipAddress;
			int port;

			Client();

			void ConnectToServer();
			void RunClient();
		};
	}
}