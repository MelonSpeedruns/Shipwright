#pragma once

#include <iostream>
#include <thread>
#include <SDL_net.h>

#define MAX_PLAYERS 4

typedef struct {
    float_t x, y, z;
} Vec3float; // size = 0x0C

typedef struct {
    int16_t x, y, z;
} Vec3short; // size = 0x0C

typedef struct {
    Vec3float pos;
    Vec3short rot;
} PosRotOnline;

typedef struct PuppetPacket {
    uint8_t packet_type;

    uint8_t player_id;

    PosRotOnline posRot;
    uint8_t biggoron_broken;
    uint16_t scene_id;
    uint16_t sound_id[4];
    uint8_t puppet_age;

    // SkelAnime Data
    Vec3short jointTable[24];

    uint8_t sheathType;
    uint8_t shieldType;
    uint8_t leftHandType;
    uint8_t rightHandType;

    int16_t faceType;
    uint8_t tunicType;
    uint8_t bootsType;

    uint8_t damageEffect;
    uint8_t damageValue;
} PuppetPacket;

typedef struct {
    /* 0x00 */ uint8_t items[24];
    /* 0x18 */ int8_t ammo[16];
    /* 0x28 */ uint16_t equipment; // a mask where each nibble corresponds to a type of equipment `EquipmentType`, and
                                   // each bit to an owned piece `EquipInv*`
    /* 0x2C */ uint32_t upgrades;
    /* 0x30 */ uint32_t questItems;
    /* 0x34 */ uint8_t dungeonItems[20];
    /* 0x48 */ int8_t dungeonKeys[19];
    /* 0x5B */ int8_t defenseHearts;
    /* 0x5C */ int16_t gsTokens;
} InventoryZ64; // size = 0x5E

typedef struct InventoryPacket {
    uint8_t packet_type;
    InventoryZ64 inventory;
} InventoryPacket;

typedef struct ConnectionPacket {
    uint8_t packet_type;
    uint8_t player_id;
} ConnectionPacket;

class OnlineClient {
  public:
    bool running = false;

    void InitClient(char* ipAddr, int port);
    void SendPuppetPacketMessage(PuppetPacket* packet);

    void CloseClient();

  private:
    void RunClientReceive();
};