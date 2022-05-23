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
			virtual void OnExecute() = 0;
		};

		struct OnlinePacket_Rupees: public OnlinePacket {
			uint16_t rupeeAmountChanged;
			void OnExecute() override;
		};

		class Server {
		private:
			ENetEvent event;
			ENetHost* server;

			uint8_t player_count;

			std::thread onlineThread;

		public:
			int port;

			Server();

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

			Client();

			void SendPacketMessage(Ship::Online::OnlinePacket_Rupees* packet);
			void ConnectToServer();
			void RunClient();
		};
	}
}