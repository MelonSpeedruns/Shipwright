#pragma once

#define ENET_IMPLEMENTATION

#include "enet.h"
#include <thread>
#include <mutex>

namespace Ship {
	namespace Online {
		enum PACKET_ID {
			CHANGE_RUPEES = 0,
			LINK_UPDATE = 1,
		};

		struct OnlinePacket {
			uint8_t player_id;
			uint16_t rupeeAmountChanged;
			float posX;
			float posY;
			float posZ;
		};

		void ReceiveData(ENetPacket* packet, ENetPeer* peer, ENetHost* host);
		void SendPacketMessage(OnlinePacket* packet, ENetHost* host);
			
		class Server {
		private:
			ENetEvent event;

			std::thread onlineThread;

		public:
			int port;

			ENetHost* server = { 0 };

			uint8_t my_player_id = 0;

			bool isEnabled = false;

			Server();

			void CreateServer();
			void RunServer();
		};

		class Client {
		private:
			ENetEvent event = { ENetEventType::ENET_EVENT_TYPE_NONE };
			ENetPeer* peer = { 0 };

			uint8_t disconnected = false;

			std::thread onlineThread;

		public:
			std::string ipAddress;
			int port;

			ENetHost* client = { 0 };

			uint8_t my_player_id = 0;

			bool isEnabled = false;

			Client();

			void ConnectToServer();
			void RunClient();
		};
	}
}