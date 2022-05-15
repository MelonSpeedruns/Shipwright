#pragma once

#include "SDL_net.h"
#include <thread>
#include <mutex>

namespace Ship {
	namespace Online {
		enum PACKET_ID {
			CHANGE_RUPEES = 0,
			LINK_UPDATE = 1,
		};

		struct OnlinePacket {
			uint8_t client_id;
			uint16_t packet_id;
			time_t timestamp;
			virtual void OnExecute() = 0;
		};

		struct OnlinePacket_Rupees: public OnlinePacket {
			uint16_t rupeeAmountChanged;
			void OnExecute() override;
		};

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

			void ReceivePacketMessage();
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

			void SendPacketMessage(OnlinePacket* packet);
			void ConnectToServer();
			void RunClient();
		};
	}
}