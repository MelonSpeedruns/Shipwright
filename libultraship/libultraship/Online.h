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
			time_t timestamp;
		};

		struct OnlinePacket_Rupees {
			uint16_t rupeeAmountChanged;
		};

		class Server {
		private:
			ENetEvent event;
			ENetHost* server;

			uint8_t player_count;

			std::thread onlineThread;

		public:
			int port;

			bool isEnabled = false;

			Server();

			void ReceiveRupees(ENetPacket* packet);
			void SendPacketMessage(Ship::Online::OnlinePacket_Rupees* packet);
			void GetPlayerInfo(ENetPeer* peer);
			void CreateServer();
			void RunServer();
		};

		class Client {
		private:
			ENetHost* client = { 0 };
			ENetEvent event = { ENetEventType::ENET_EVENT_TYPE_NONE };
			ENetPeer* peer = { 0 };

			uint8_t disconnected = false;

			std::thread onlineThread;

		public:
			std::string ipAddress;
			int port;

			bool isEnabled = false;

			Client();

			void ReceiveRupees(ENetPacket* packet);
			void SendPacketMessage(Ship::Online::OnlinePacket_Rupees* packet);
			void ConnectToServer();
			void RunClient();
		};
	}
}