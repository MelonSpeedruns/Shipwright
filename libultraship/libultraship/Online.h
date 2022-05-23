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

		struct PlayerInfo {
			uint8_t player_id;
		};

		struct OnlinePacket {
			uint8_t client_id;
			uint16_t packet_id;
			int player_id;
			time_t timestamp;
			uint16_t rupeeAmountChanged;
			float posX;
			float posY;
			float posZ;
		};

		void ReceiveData(ENetPacket* packet, ENetPeer* peer);
		void SendPacketMessage(OnlinePacket* packet);
			
		ENetHost* host = { 0 };

		class Server {
		private:
			ENetEvent event;

			uint8_t player_count;

			std::thread onlineThread;

		public:
			int port;

			bool isEnabled = false;

			Server();

			void GetPlayerInfo(ENetPeer* peer);
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

			bool isEnabled = false;

			Client();

			void ConnectToServer();
			void RunClient();
		};
	}
}