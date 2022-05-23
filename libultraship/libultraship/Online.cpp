#include "Online.h"
#include <spdlog/spdlog.h>
#include <PR/ultra64/gbi.h>
#include "SohImGuiImpl.h"

#define MAX_CLIENTS 32

extern "C" void Rupees_ChangeBy(s16 rupeeChange);
extern "C" u8 rupeesReceived;

namespace Ship {
    namespace Online {
        Server::Server() {
            port = 25565;
        }

        void Server::GetPlayerInfo(ENetPeer* peer) {
            PlayerInfo* player_info = new PlayerInfo();
            player_info->player_id = player_count;
            peer->data = player_info;
            player_count++;
        }

        void Server::SendPacketMessage(Ship::Online::OnlinePacket_Rupees* packet) {
            ENetPacket* packetToSend = enet_packet_create(packet, sizeof(packet), ENET_PACKET_FLAG_RELIABLE);

            for (int i = 0; i < server->connectedPeers; i++) {
                enet_peer_send(&server->peers[i], 0, packetToSend);
            }
        }

        void Server::ReceiveRupees(ENetPacket* packet) {
            if (server != nullptr) {
                Ship::Online::OnlinePacket_Rupees* rupees = (Ship::Online::OnlinePacket_Rupees*)packet->data;
                rupeesReceived = 1;
                Rupees_ChangeBy(rupees->rupeeAmountChanged);
            }
        }

        void Server::RunServer() {
            /* Wait up to 1000 milliseconds for an event. (WARNING: blocking) */
            while (true) {
                while (enet_host_service(server, &event, 1000) > 0) {
                    switch (event.type) {
                    case ENET_EVENT_TYPE_CONNECT:
                        SohImGui::overlay->TextDrawNotification(5.0f, true, "A new client connected from %x:%u.\n", event.peer->address.host, event.peer->address.port);
                        /* Store any relevant client information here. */
                        GetPlayerInfo(event.peer);
                        break;

                    case ENET_EVENT_TYPE_RECEIVE:
                        SohImGui::overlay->TextDrawNotification(5.0f, true, "A packet has been received!",
                            event.packet->dataLength,
                            event.packet->data,
                            event.peer->data,
                            event.channelID);
                        /* Clean up the packet now that we're done using it. */
                        ReceiveRupees(event.packet);
                        enet_packet_destroy(event.packet);
                        break;

                    case ENET_EVENT_TYPE_DISCONNECT:
                        SohImGui::overlay->TextDrawNotification(5.0f, true, "%s disconnected.\n", event.peer->data);
                        /* Reset the peer's client information. */
                        event.peer->data = NULL;
                        break;

                    case ENET_EVENT_TYPE_DISCONNECT_TIMEOUT:
                        SohImGui::overlay->TextDrawNotification(5.0f, true, "%s disconnected due to timeout.\n", event.peer->data);
                        /* Reset the peer's client information. */
                        event.peer->data = NULL;
                        break;

                    case ENET_EVENT_TYPE_NONE:
                        break;
                    }
                }
            }

            player_count = 0;
            enet_host_destroy(server);
            enet_deinitialize();
        }

        void Server::CreateServer() {
            if (enet_initialize() != 0) {
                SohImGui::overlay->TextDrawNotification(5.0f, true, "An error occurred while initializing ENet.\n");
                return;
            }

            ENetAddress address = { 0 };

            address.host = ENET_HOST_ANY; /* Bind the server to the default localhost.     */
            address.port = port; /* Bind the server to port 7777. */

            /* create a server */
            server = enet_host_create(&address, MAX_CLIENTS, 2, 0, 0);

            if (server == NULL) {
                SohImGui::overlay->TextDrawNotification(5.0f, true, "An error occurred while trying to create an ENet server host.\n");
                return;
            }

            SohImGui::overlay->TextDrawNotification(5.0f, true, "Started a server!\n");

            onlineThread = std::thread(&Server::RunServer, this);
        }

        void Client::RunClient()
        {
            /* Allow up to 3 seconds for the disconnect to succeed
             * and drop any packets received packets.
             */
            while (true) {
                while (enet_host_service(client, &event, 3000) > 0) {
                    switch (event.type) {
                    case ENET_EVENT_TYPE_RECEIVE:
                        enet_packet_destroy(event.packet);
                        ReceiveRupees(event.packet);
                        break;
                    case ENET_EVENT_TYPE_DISCONNECT:
                        puts("Disconnection succeeded.");
                        disconnected = true;
                        break;
                    }
                }
            }

            // Drop connection, since disconnection didn't successed
            if (!disconnected) {
                enet_peer_reset(peer);
            }

            enet_host_destroy(client);
            enet_deinitialize();
        }

        void Client::SendPacketMessage(Ship::Online::OnlinePacket_Rupees* packet) {
            if (client != nullptr) {
                ENetPacket* packetToSend = enet_packet_create(packet, sizeof(packet), ENET_PACKET_FLAG_RELIABLE);

                for (int i = 0; i < client->connectedPeers; i++) {
                    enet_peer_send(&client->peers[i], 0, packetToSend);
                }
            }
        }

        void Client::ReceiveRupees(ENetPacket* packet) {
            Ship::Online::OnlinePacket_Rupees* rupees = (Ship::Online::OnlinePacket_Rupees*)packet->data;
            rupeesReceived = 1;
            Rupees_ChangeBy(rupees->rupeeAmountChanged);
        }

        void Client::ConnectToServer() {
            if (enet_initialize() != 0) {
                SohImGui::overlay->TextDrawNotification(5.0f, true, "An error occurred while initializing ENet.\n");
                return;
            }

            client = enet_host_create(NULL /* create a client host */,
                1 /* only allow 1 outgoing connection */,
                1 /* allow up 2 channels to be used, 0 and 1 */,
                0 /* assume any amount of incoming bandwidth */,
                0 /* assume any amount of outgoing bandwidth */);

            if (client == NULL) {
                SohImGui::overlay->TextDrawNotification(5.0f, true, "An error occurred while trying to create an ENet client host.\n");
                exit(EXIT_FAILURE);
            }

            ENetAddress address = { 0 };

            /* Connect to some.server.net:1234. */
            enet_address_set_host(&address, ipAddress.c_str());
            address.port = port;
            /* Initiate the connection, allocating the two channels 0 and 1. */
            peer = enet_host_connect(client, &address, 2, 0);
            if (peer == NULL) {
                SohImGui::overlay->TextDrawNotification(5.0f, true, "No available peers for initiating an ENet connection.\n");
                exit(EXIT_FAILURE);
            }
            /* Wait up to 5 seconds for the connection attempt to succeed. */
            if (enet_host_service(client, &event, 5000) > 0 &&
                event.type == ENET_EVENT_TYPE_CONNECT) {
                puts("Connection to some.server.net:1234 succeeded.");
                onlineThread = std::thread(&Client::RunClient, this);
            }
            else {
                /* Either the 5 seconds are up or a disconnect event was */
                /* received. Reset the peer in the event the 5 seconds   */
                /* had run out without any significant event.            */
                enet_peer_reset(peer);
                puts("Connection to some.server.net:1234 failed.");
            }
        }

        Client::Client() {
            ipAddress = "127.0.0.1";
            port = 25565;
        }
    }
}