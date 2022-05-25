#pragma once

#include <thread>
#include <mutex>

#define ENET_IMPLEMENTATION
#include <enet.h>

namespace Ship {
	namespace Online {
		typedef struct {
			float x, y, z;
		} Vec3float; // size = 0x0C

		typedef struct {
			int16_t x, y, z;
		} Vec3short; // size = 0x0C

		typedef struct {
			Vec3float pos;
			Vec3short rot;
		} PosRotOnline;

		typedef struct OnlinePacket {
			uint8_t player_id;
			uint16_t rupeeAmountChanged;
			PosRotOnline posRot;
			uint8_t biggoron_broken;

			//SkelAnime Data
			Vec3short jointTable[0x16];
			
			uint8_t sheathType;
			uint8_t shieldType;
			uint8_t leftHandType;
			uint8_t rightHandType;
		} OnlinePacket;

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

#define ENET_IMPLEMENTATION_DONE