#include "global.h"
#include "objects/gameplay_keep/gameplay_keep.h"
#include "objects/object_link_boy/object_link_boy.h"
#include "objects/object_link_child/object_link_child.h"
#include "objects/object_triforce_spot/object_triforce_spot.h"
#include "overlays/actors/ovl_Demo_Effect/z_demo_effect.h"

#include "overlays/actors/ovl_Obj_Syokudai/z_obj_syokudai.h"

typedef struct {
    /* 0x00 */ u8 flag;
    /* 0x02 */ u16 textId;
} TextTriggerEntry; // size = 0x04

typedef struct {
    /* 0x00 */ void* dList;
    /* 0x04 */ Vec3f pos;
} BowStringData; // size = 0x10

FlexSkeletonHeader* gPlayerSkelHeaders[] = { &gLinkAdultSkel, &gLinkChildSkel };

s16 sBootData[PLAYER_BOOTS_MAX][17] = {
    { 200, 1000, 300, 700, 550, 270, 600, 350, 800, 600, -100, 600, 590, 750, 125, 200, 130 },
    { 200, 1000, 300, 700, 550, 270, 1000, 0, 800, 300, -160, 600, 590, 750, 125, 200, 130 },
    { 200, 1000, 300, 700, 550, 270, 600, 600, 800, 550, -100, 600, 540, 270, 25, 0, 130 },
    { 200, 1000, 300, 700, 380, 400, 0, 300, 800, 500, -100, 600, 590, 750, 125, 200, 130 },
    { 80, 800, 150, 700, 480, 270, 600, 50, 800, 550, -40, 400, 540, 270, 25, 0, 80 },
    { 200, 1000, 300, 800, 500, 400, 800, 400, 800, 550, -100, 600, 540, 750, 125, 400, 200 },
};

// Used to map action params to model groups
u8 sActionModelGroups[] = {
    3,  15, 10, 2,  2,  5,  10, 11, 6,  6, 6, 6, 6, 6, 6, 6, 9, 9, 7, 7, 8, 3, 3, 6, 3, 3, 3, 3, 12, 13, 14, 14, 14, 14,
    14, 14, 14, 14, 14, 14, 14, 14, 14, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,  3,  3,  3,  3,
};

TextTriggerEntry sTextTriggers[] = {
    { 1, 0x3040 },
    { 2, 0x401D },
    { 0, 0x0000 },
    { 2, 0x401D },
};

// Used to map model groups to model types for [animation, left hand, right hand, sheath, waist]
u8 gPlayerModelTypes[][5] = {
    { 2, 0, 10, 16, 20 }, { 1, 2, 9, 19, 20 },  { 1, 2, 10, 17, 20 }, { 0, 0, 8, 18, 20 },
    { 0, 0, 8, 18, 20 },  { 3, 4, 9, 19, 20 },  { 4, 1, 11, 18, 20 }, { 5, 0, 8, 18, 20 },
    { 0, 6, 8, 18, 20 },  { 4, 0, 15, 18, 20 }, { 3, 1, 9, 18, 20 },  { 3, 5, 9, 18, 20 },
    { 0, 0, 13, 18, 20 }, { 0, 0, 14, 18, 20 }, { 0, 7, 8, 18, 20 },  { 0, 2, 8, 19, 20 },
};

Gfx* D_80125CE8[] = {
    gLinkAdultRightHandClosedNearDL,
    gLinkChildRightHandClosedNearDL,
    gLinkAdultRightHandClosedFarDL,
    gLinkChildRightHandClosedFarDL,
    gLinkAdultRightHandClosedNearDL,
    gLinkChildRightFistAndDekuShieldNearDL,
    gLinkAdultRightHandClosedFarDL,
    gLinkChildRightFistAndDekuShieldFarDL,
    gLinkAdultRightHandHoldingHylianShieldNearDL,
    gLinkChildRightHandClosedNearDL,
    gLinkAdultRightHandHoldingHylianShieldFarDL,
    gLinkChildRightHandClosedFarDL,
    gLinkAdultRightHandHoldingMirrorShieldNearDL,
    gLinkChildRightHandClosedNearDL,
    gLinkAdultRightHandHoldingMirrorShieldFarDL,
    gLinkChildRightHandClosedFarDL,
};

Gfx* D_80125D28[] = {
    gLinkAdultMasterSwordAndSheathNearDL,       gLinkChildSwordAndSheathNearDL,
    gLinkAdultMasterSwordAndSheathFarDL,        gLinkChildSwordAndSheathFarDL,
    gLinkAdultMasterSwordAndSheathNearDL,       gLinkChildDekuShieldSwordAndSheathNearDL,
    gLinkAdultMasterSwordAndSheathFarDL,        gLinkChildDekuShieldSwordAndSheathFarDL,
    gLinkAdultHylianShieldSwordAndSheathNearDL, gLinkChildHylianShieldSwordAndSheathNearDL,
    gLinkAdultHylianShieldSwordAndSheathFarDL,  gLinkChildHylianShieldSwordAndSheathFarDL,
    gLinkAdultMirrorShieldSwordAndSheathNearDL, gLinkChildSwordAndSheathNearDL,
    gLinkAdultMirrorShieldSwordAndSheathFarDL,  gLinkChildSwordAndSheathFarDL,
    NULL,                                       NULL,
    NULL,                                       NULL,
    NULL,                                       gLinkChildDekuShieldWithMatrixDL,
    NULL,                                       gLinkChildDekuShieldWithMatrixDL,
};

Gfx* D_80125D88[] = {
    gLinkAdultSheathNearDL,
    gLinkChildSheathNearDL,
    gLinkAdultSheathFarDL,
    gLinkChildSheathFarDL,
    gLinkAdultSheathNearDL,
    gLinkChildDekuShieldAndSheathNearDL,
    gLinkAdultSheathFarDL,
    gLinkChildDekuShieldAndSheathFarDL,
    gLinkAdultHylianShieldAndSheathNearDL,
    gLinkChildHylianShieldAndSheathNearDL,
    gLinkAdultHylianShieldAndSheathFarDL,
    gLinkChildHylianShieldAndSheathFarDL,
    gLinkAdultMirrorShieldAndSheathNearDL,
    gLinkChildSheathNearDL,
    gLinkAdultMirrorShieldAndSheathFarDL,
    gLinkChildSheathFarDL,
    NULL,
    NULL,
    NULL,
    NULL,
    gLinkAdultSheathNearDL,
    gLinkChildDekuShieldWithMatrixDL,
    gLinkAdultSheathNearDL,
    gLinkChildDekuShieldWithMatrixDL,
};

Gfx* D_80125DE8[] = {
    gLinkAdultLeftHandHoldingBgsNearDL,          gLinkChildLeftHandHoldingMasterSwordDL,
    gLinkAdultLeftHandHoldingBgsFarDL,           gLinkChildLeftHandHoldingMasterSwordDL,
    gLinkAdultHandHoldingBrokenGiantsKnifeDL,    gLinkChildLeftHandHoldingMasterSwordDL,
    gLinkAdultHandHoldingBrokenGiantsKnifeFarDL, gLinkChildLeftHandHoldingMasterSwordDL,
};

Gfx* D_80125E08[] = {
    gLinkAdultLeftHandNearDL,
    gLinkChildLeftHandNearDL,
    gLinkAdultLeftHandFarDL,
    gLinkChildLeftHandFarDL,
};

Gfx* D_80125E18[] = {
    gLinkAdultLeftHandClosedNearDL,
    gLinkChildLeftFistNearDL,
    gLinkAdultLeftHandClosedFarDL,
    gLinkChildLeftFistFarDL,
};

Gfx* D_80125E28[] = {
    gLinkAdultLeftHandHoldingMasterSwordNearDL,
    gLinkChildLeftFistAndKokiriSwordNearDL,
    gLinkAdultLeftHandHoldingMasterSwordFarDL,
    gLinkChildLeftFistAndKokiriSwordFarDL,
};

Gfx* D_80125E38[] = {
    gLinkAdultLeftHandHoldingMasterSwordNearDL,
    gLinkChildLeftFistAndKokiriSwordNearDL,
    gLinkAdultLeftHandHoldingMasterSwordFarDL,
    gLinkChildLeftFistAndKokiriSwordFarDL,
};

Gfx* D_80125E48[] = {
    gLinkAdultRightHandNearDL,
    gLinkChildRightHandNearDL,
    gLinkAdultRightHandFarDL,
    gLinkChildRightHandFarDL,
};

Gfx* D_80125E58[] = {
    gLinkAdultRightHandClosedNearDL,
    gLinkChildRightHandClosedNearDL,
    gLinkAdultRightHandClosedFarDL,
    gLinkChildRightHandClosedFarDL,
};

Gfx* D_80125E68[] = {
    gLinkAdultRightHandHoldingBowNearDL,
    gLinkChildRightHandHoldingSlingshotNearDL,
    gLinkAdultRightHandHoldingBowFarDL,
    gLinkChildRightHandHoldingSlingshotFarDL,
};

Gfx* D_80125E78[] = {
    gLinkAdultMasterSwordAndSheathNearDL,
    gLinkChildSwordAndSheathNearDL,
    gLinkAdultMasterSwordAndSheathFarDL,
    gLinkChildSwordAndSheathFarDL,
};

Gfx* D_80125E88[] = {
    gLinkAdultSheathNearDL,
    gLinkChildSheathNearDL,
    gLinkAdultSheathFarDL,
    gLinkChildSheathFarDL,
};

Gfx* D_80125E98[] = {
    gLinkAdultWaistNearDL,
    gLinkChildWaistNearDL,
    gLinkAdultWaistFarDL,
    gLinkChildWaistFarDL,
};

Gfx* D_80125EA8[] = {
    gLinkAdultRightHandHoldingBowNearDL,
    gLinkChildRightHandHoldingSlingshotNearDL,
    gLinkAdultRightHandHoldingBowFarDL,
    gLinkChildRightHandHoldingSlingshotFarDL,
};

Gfx* D_80125EB8[] = {
    gLinkAdultRightHandHoldingOotNearDL,
    gLinkChildRightHandHoldingFairyOcarinaNearDL,
    gLinkAdultRightHandHoldingOotFarDL,
    gLinkChildRightHandHoldingFairyOcarinaFarDL,
};

Gfx* D_80125EC8[] = {
    gLinkAdultRightHandHoldingOotNearDL,
    gLinkChildRightHandAndOotNearDL,
    gLinkAdultRightHandHoldingOotFarDL,
    gLinkChildRightHandHoldingOOTFarDL,
};

Gfx* D_80125ED8[] = {
    gLinkAdultRightHandHoldingHookshotNearDL,
    gLinkChildRightHandNearDL,
    gLinkAdultRightHandHoldingHookshotNearDL, // The 'far' display list exists but is not used
    gLinkChildRightHandFarDL,
};

Gfx* D_80125EE8[] = {
    gLinkAdultLeftHandHoldingHammerNearDL,
    gLinkChildLeftHandNearDL,
    gLinkAdultLeftHandHoldingHammerFarDL,
    gLinkChildLeftHandFarDL,
};

Gfx* D_80125EF8[] = {
    gLinkAdultLeftHandNearDL,
    gLinkChildLeftFistAndBoomerangNearDL,
    gLinkAdultLeftHandFarDL,
    gLinkChildLeftFistAndBoomerangFarDL,
};

Gfx* D_80125F08[] = {
    gLinkAdultLeftHandOutNearDL,
    gLinkChildLeftHandUpNearDL,
    gLinkAdultLeftHandOutNearDL,
    gLinkChildLeftHandUpNearDL,
};

Gfx* sArmOutDLs[] = {
    gLinkAdultRightArmOutNearDL,
    NULL,
};

Gfx* sHandOutDLs[] = {
    gLinkAdultRightHandOutNearDL,
    NULL,
};

Gfx* sRightShoulderNearDLs[] = {
    gLinkAdultRightShoulderNearDL,
    gLinkChildRightShoulderNearDL,
};

Gfx* D_80125F30[] = {
    gLinkAdultLeftArmOutNearDL,
    NULL,
};

Gfx* sHoldingFirstPersonWeaponDLs[] = {
    gLinkAdultRightHandHoldingBowFirstPersonDL,
    gLinkChildRightArmStretchedSlingshotDL,
};

// Indexed by model types (left hand, right hand, sheath or waist)
Gfx** sPlayerDListGroups[] = {
    D_80125E08, D_80125E18, D_80125E38, D_80125E28, D_80125DE8, D_80125EE8, D_80125EF8,
    D_80125F08, D_80125E48, D_80125E58, D_80125CE8, D_80125E68, D_80125EA8, D_80125EB8,
    D_80125EC8, D_80125ED8, D_80125E78, D_80125E88, D_80125D28, D_80125D88, D_80125E98,
};

Gfx gCullBackDList[] = {
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};

Gfx gCullFrontDList[] = {
    gsSPSetGeometryMode(G_CULL_FRONT),
    gsSPEndDisplayList(),
};

Vec3f* D_80160000;
s32 sDListsLodOffset;
Vec3f sGetItemRefPos;
s32 D_80160014;
s32 D_80160018;

void Player_SetBootData(GlobalContext* globalCtx, Player* this) {
    s32 currentBoots;
    s16* bootRegs;

    REG(27) = 2000;
    REG(48) = 370;

    currentBoots = this->currentBoots;
    if (currentBoots == PLAYER_BOOTS_KOKIRI) {
        if (!LINK_IS_ADULT) {
            currentBoots = PLAYER_BOOTS_KOKIRI_CHILD;
        }
    } else if (currentBoots == PLAYER_BOOTS_IRON) {
        if (this->stateFlags1 & 0x8000000) {
            currentBoots = PLAYER_BOOTS_IRON_UNDERWATER;
        }
        REG(27) = 500;
        REG(48) = 100;
    }

    bootRegs = sBootData[currentBoots];
    REG(19) = bootRegs[0];
    REG(30) = bootRegs[1];
    REG(32) = bootRegs[2];
    REG(34) = bootRegs[3];
    REG(35) = bootRegs[4];
    REG(36) = bootRegs[5];
    REG(37) = bootRegs[6];
    REG(38) = bootRegs[7];
    REG(43) = bootRegs[8];
    REG(45) = bootRegs[9];
    REG(68) = bootRegs[10];
    REG(69) = bootRegs[11];
    IREG(66) = bootRegs[12];
    IREG(67) = bootRegs[13];
    IREG(68) = bootRegs[14];
    IREG(69) = bootRegs[15];
    MREG(95) = bootRegs[16];

    if (globalCtx->roomCtx.curRoom.unk_03 == 2) {
        REG(45) = 500;
    }
}

s32 Player_InBlockingCsMode(GlobalContext* globalCtx, Player* this) {
    return (this->stateFlags1 & 0x20000080) || (this->csMode != 0) || (globalCtx->sceneLoadFlag == 0x14) ||
           (this->stateFlags1 & 1) || (this->stateFlags3 & 0x80) ||
           ((gSaveContext.unk_13F0 != 0) && (Player_ActionToMagicSpell(this, this->itemActionParam) >= 0));
}

s32 Player_InCsMode(GlobalContext* globalCtx) {
    Player* this = GET_PLAYER(globalCtx);

    return Player_InBlockingCsMode(globalCtx, this) || (this->unk_6AD == 4);
}

s32 func_8008E9C4(Player* this) {
    return (this->stateFlags1 & 0x10);
}

s32 Player_IsChildWithHylianShield(Player* this) {
    return gSaveContext.linkAge != 0 && (this->currentShield == PLAYER_SHIELD_HYLIAN);
}

s32 Player_ActionToModelGroup(Player* this, s32 actionParam) {
    s32 modelGroup = sActionModelGroups[actionParam];

    if ((modelGroup == 2) && Player_IsChildWithHylianShield(this)) {
        return 1;
    } else {
        return modelGroup;
    }
}

void Player_SetModelsForHoldingShield(Player* this) {
    if ((this->stateFlags1 & 0x400000) &&
        ((this->itemActionParam < 0) || (this->itemActionParam == this->heldItemActionParam))) {
        if (!Player_HoldsTwoHandedWeapon(this) && !Player_IsChildWithHylianShield(this)) {
            this->rightHandType = 10;
            this->rightHandDLists = &sPlayerDListGroups[10][(void)0, gSaveContext.linkAge];
            if (this->sheathType == 18) {
                this->sheathType = 16;
            } else if (this->sheathType == 19) {
                this->sheathType = 17;
            }
            this->sheathDLists = &sPlayerDListGroups[this->sheathType][(void)0, gSaveContext.linkAge];
            this->modelAnimType = 2;
            this->itemActionParam = -1;
        }
    }
}

void Player_SetModels(Player* this, s32 modelGroup) {
    this->leftHandType = gPlayerModelTypes[modelGroup][1];
    this->rightHandType = gPlayerModelTypes[modelGroup][2];
    this->sheathType = gPlayerModelTypes[modelGroup][3];

    this->leftHandDLists = &sPlayerDListGroups[gPlayerModelTypes[modelGroup][1]][(void)0, gSaveContext.linkAge];
    this->rightHandDLists = &sPlayerDListGroups[gPlayerModelTypes[modelGroup][2]][(void)0, gSaveContext.linkAge];
    this->sheathDLists = &sPlayerDListGroups[gPlayerModelTypes[modelGroup][3]][(void)0, gSaveContext.linkAge];
    this->waistDLists = &sPlayerDListGroups[gPlayerModelTypes[modelGroup][4]][(void)0, gSaveContext.linkAge];

    Player_SetModelsForHoldingShield(this);
}

void Player_SetModelGroup(Player* this, s32 modelGroup) {
    this->modelGroup = modelGroup;

    if (modelGroup == 1) {
        this->modelAnimType = 0;
    } else {
        this->modelAnimType = gPlayerModelTypes[modelGroup][0];
    }

    if ((this->modelAnimType < 3) && (this->currentShield == PLAYER_SHIELD_NONE)) {
        this->modelAnimType = 0;
    }

    Player_SetModels(this, modelGroup);
}

void func_8008EC70(Player* this) {
    this->itemActionParam = this->heldItemActionParam;
    Player_SetModelGroup(this, Player_ActionToModelGroup(this, this->heldItemActionParam));
    this->unk_6AD = 0;
}

void Player_SetEquipmentData(GlobalContext* globalCtx, Player* this) {
    if (this->csMode != 0x56) {
        this->currentShield = CUR_EQUIP_VALUE(EQUIP_SHIELD);
        this->currentTunic = CUR_EQUIP_VALUE(EQUIP_TUNIC) - 1;
        this->currentBoots = CUR_EQUIP_VALUE(EQUIP_BOOTS) - 1;
        this->currentSwordItem = B_BTN_ITEM;
        Player_SetModelGroup(this, Player_ActionToModelGroup(this, this->heldItemActionParam));
        Player_SetBootData(globalCtx, this);
    }
}

void Player_UpdateBottleHeld(GlobalContext* globalCtx, Player* this, s32 item, s32 actionParam) {
    Inventory_UpdateBottleItem(globalCtx, item, this->heldItemButton);

    if (item != ITEM_BOTTLE) {
        this->heldItemId = item;
        this->heldItemActionParam = actionParam;
    }

    this->itemActionParam = actionParam;
}

void func_8008EDF0(Player* this) {
    this->unk_664 = NULL;
    this->stateFlags2 &= ~0x2000;
}

void func_8008EE08(Player* this) {
    if ((this->actor.bgCheckFlags & 1) || (this->stateFlags1 & 0x8A00000) ||
        (!(this->stateFlags1 & 0xC0000) && ((this->actor.world.pos.y - this->actor.floorHeight) < 100.0f))) {
        this->stateFlags1 &= ~0x400F8000;
    } else if (!(this->stateFlags1 & 0x2C0000)) {
        this->stateFlags1 |= 0x80000;
    }

    func_8008EDF0(this);
}

void func_8008EEAC(GlobalContext* globalCtx, Actor* actor) {
    Player* this = GET_PLAYER(globalCtx);

    func_8008EE08(this);
    this->unk_664 = actor;
    this->unk_684 = actor;
    this->stateFlags1 |= 0x10000;
    Camera_SetParam(Gameplay_GetCamera(globalCtx, 0), 8, actor);
    Camera_ChangeMode(Gameplay_GetCamera(globalCtx, 0), 2);
}

s32 func_8008EF30(GlobalContext* globalCtx) {
    Player* this = GET_PLAYER(globalCtx);

    return (this->stateFlags1 & 0x800000);
}

s32 func_8008EF44(GlobalContext* globalCtx, s32 ammo) {
    globalCtx->shootingGalleryStatus = ammo + 1;
    return 1;
}

s32 Player_IsBurningStickInRange(GlobalContext* globalCtx, Vec3f* pos, f32 xzRange, f32 yRange) {
    Player* this = GET_PLAYER(globalCtx);
    Vec3f diff;
    s32 pad;

    if ((this->heldItemActionParam == PLAYER_AP_STICK) && (this->unk_860 != 0)) {
        Math_Vec3f_Diff(&this->swordInfo[0].tip, pos, &diff);
        return ((SQ(diff.x) + SQ(diff.z)) <= SQ(xzRange)) && (0.0f <= diff.y) && (diff.y <= yRange);
    } else {
        return false;
    }
}

s32 Player_GetStrength(void) {
    s32 strengthUpgrade = CUR_UPG_VALUE(UPG_STRENGTH);

    if (LINK_IS_ADULT) {
        return strengthUpgrade;
    } else if (strengthUpgrade != 0) {
        return PLAYER_STR_BRACELET;
    } else {
        return PLAYER_STR_NONE;
    }
}

u8 Player_GetMask(GlobalContext* globalCtx) {
    Player* this = GET_PLAYER(globalCtx);

    return this->currentMask;
}

Player* Player_UnsetMask(GlobalContext* globalCtx) {
    Player* this = GET_PLAYER(globalCtx);

    this->currentMask = PLAYER_MASK_NONE;

    return this;
}

s32 Player_HasMirrorShieldEquipped(GlobalContext* globalCtx) {
    Player* this = GET_PLAYER(globalCtx);

    return (this->currentShield == PLAYER_SHIELD_MIRROR);
}

s32 Player_HasMirrorShieldSetToDraw(GlobalContext* globalCtx) {
    Player* this = GET_PLAYER(globalCtx);

    return (this->rightHandType == 10) && (this->currentShield == PLAYER_SHIELD_MIRROR);
}

s32 Player_ActionToMagicSpell(Player* this, s32 actionParam) {
    s32 magicSpell = actionParam - PLAYER_AP_MAGIC_SPELL_15;

    if ((magicSpell >= 0) && (magicSpell < 6)) {
        return magicSpell;
    } else {
        return -1;
    }
}

s32 Player_HoldsHookshot(Player* this) {
    return (this->heldItemActionParam == PLAYER_AP_HOOKSHOT) || (this->heldItemActionParam == PLAYER_AP_LONGSHOT);
}

s32 func_8008F128(Player* this) {
    return Player_HoldsHookshot(this) && (this->heldActor == NULL);
}

s32 Player_ActionToSword(s32 actionParam) {
    s32 sword = actionParam - PLAYER_AP_FISHING_POLE;

    if ((sword > 0) && (sword < 6)) {
        return sword;
    } else {
        return 0;
    }
}

s32 Player_GetSwordHeld(Player* this) {
    return Player_ActionToSword(this->heldItemActionParam);
}

s32 Player_HoldsTwoHandedWeapon(Player* this) {
    if ((this->heldItemActionParam >= PLAYER_AP_SWORD_BGS) && (this->heldItemActionParam <= PLAYER_AP_HAMMER)) {
        return 1;
    } else {
        return 0;
    }
}

s32 Player_HoldsBrokenKnife(Player* this) {
    return (this->heldItemActionParam == PLAYER_AP_SWORD_BGS) && (gSaveContext.swordHealth <= 0.0f);
}

s32 Player_ActionToBottle(Player* this, s32 actionParam) {
    s32 bottle = actionParam - PLAYER_AP_BOTTLE;

    if ((bottle >= 0) && (bottle < 13)) {
        return bottle;
    } else {
        return -1;
    }
}

s32 Player_GetBottleHeld(Player* this) {
    return Player_ActionToBottle(this, this->heldItemActionParam);
}

s32 Player_ActionToExplosive(Player* this, s32 actionParam) {
    s32 explosive = actionParam - PLAYER_AP_BOMB;

    if ((explosive >= 0) && (explosive < 2)) {
        return explosive;
    } else {
        return -1;
    }
}

s32 Player_GetExplosiveHeld(Player* this) {
    return Player_ActionToExplosive(this, this->heldItemActionParam);
}

s32 func_8008F2BC(Player* this, s32 actionParam) {
    s32 sword = 0;

    if (actionParam != PLAYER_AP_LAST_USED) {
        sword = actionParam - PLAYER_AP_SWORD_MASTER;
        if ((sword < 0) || (sword >= 3)) {
            goto return_neg;
        }
    }

    return sword;

return_neg:
    return -1;
}

s32 func_8008F2F8(GlobalContext* globalCtx) {
    Player* this = GET_PLAYER(globalCtx);
    TextTriggerEntry* triggerEntry;
    s32 var;

    if (globalCtx->roomCtx.curRoom.unk_02 == 3) { // Room is hot
        var = 0;
    } else if ((this->unk_840 > 80) &&
               ((this->currentBoots == PLAYER_BOOTS_IRON) || (this->unk_840 >= 300))) { // Deep underwater
        var = ((this->currentBoots == PLAYER_BOOTS_IRON) && (this->actor.bgCheckFlags & 1)) ? 1 : 3;
    } else if (this->stateFlags1 & 0x8000000) { // Swimming
        var = 2;
    } else {
        return 0;
    }

    // Trigger general textboxes under certain conditions, like "It's so hot in here!"
    if (!Player_InCsMode(globalCtx)) {
        triggerEntry = &sTextTriggers[var];

        if (0) {}

        if ((triggerEntry->flag != 0) && !(gSaveContext.textTriggerFlags & triggerEntry->flag) &&
            (((var == 0) && (this->currentTunic != PLAYER_TUNIC_GORON && CVar_GetS32("gSuperTunic", 0) == 0)) ||
             (((var == 1) || (var == 3)) && (this->currentBoots == PLAYER_BOOTS_IRON) &&
              (this->currentTunic != PLAYER_TUNIC_ZORA && CVar_GetS32("gSuperTunic", 0) == 0)))) {
            Message_StartTextbox(globalCtx, triggerEntry->textId, NULL);
            gSaveContext.textTriggerFlags |= triggerEntry->flag;
        }
    }

    return var + 1;
}

u8 sEyeMouthIndexes[][2] = {
    { 0, 0 }, { 1, 0 }, { 2, 0 }, { 0, 0 }, { 1, 0 }, { 2, 0 }, { 4, 0 }, { 5, 1 },
    { 7, 2 }, { 0, 2 }, { 3, 0 }, { 4, 0 }, { 2, 2 }, { 1, 1 }, { 0, 2 }, { 0, 0 },
};

/**
 * Link's eye and mouth textures are placed at the exact same place in adult and child Link's respective object files.
 * This allows the array to only contain the symbols for one file and have it apply to both. This is a problem for
 * shiftability, and changes will need to be made in the code to account for this in a modding scenario. The symbols
 * from adult Link's object are used here.
 */

#if defined(MODDING) || defined(_MSC_VER) || defined(__GNUC__)
//TODO: Formatting
void* sEyeTextures[2][8] = {
    { gLinkAdultEyesOpenTex, gLinkAdultEyesHalfTex, gLinkAdultEyesClosedfTex, gLinkAdultEyesRollLeftTex,
      gLinkAdultEyesRollRightTex, gLinkAdultEyesShockTex, gLinkAdultEyesUnk1Tex, gLinkAdultEyesUnk2Tex },
    { gLinkChildEyesOpenTex, gLinkChildEyesHalfTex, gLinkChildEyesClosedfTex, gLinkChildEyesRollLeftTex,
      gLinkChildEyesRollRightTex, gLinkChildEyesShockTex, gLinkChildEyesUnk1Tex, gLinkChildEyesUnk2Tex },
};

#else
void* sEyeTextures[] = {
    gLinkAdultEyesOpenTex,      gLinkAdultEyesHalfTex,  gLinkAdultEyesClosedfTex, gLinkAdultEyesRollLeftTex,
    gLinkAdultEyesRollRightTex, gLinkAdultEyesShockTex, gLinkAdultEyesUnk1Tex,    gLinkAdultEyesUnk2Tex,
};
#endif

#if defined(MODDING) || defined(_MSC_VER) || defined(__GNUC__)
void* sMouthTextures[2][4] = {
    {
        gLinkAdultMouth1Tex,
        gLinkAdultMouth2Tex,
        gLinkAdultMouth3Tex,
        gLinkAdultMouth4Tex,
    },
    {
        gLinkChildMouth1Tex,
        gLinkChildMouth2Tex,
        gLinkChildMouth3Tex,
        gLinkChildMouth4Tex,
    },
};
#else
void* sMouthTextures[] = {
    gLinkAdultMouth1Tex,
    gLinkAdultMouth2Tex,
    gLinkAdultMouth3Tex,
    gLinkAdultMouth4Tex,
};
#endif

Color_RGB8 sTunicColors[] = {
    { 30, 105, 27 },
    { 100, 20, 0 },
    { 0, 60, 100 },
};

Color_RGB8 sGauntletColors[] = {
    { 255, 255, 255 },
    { 254, 207, 15 },
};

Gfx* sBootDListGroups[][2] = {
    { gLinkAdultLeftIronBootDL, gLinkAdultRightIronBootDL },
    { gLinkAdultLeftHoverBootDL, gLinkAdultRightHoverBootDL },
};

void func_8008F470(GlobalContext* globalCtx, void** skeleton, Vec3s* jointTable, s32 dListCount, s32 lod, s32 tunic,
                   s32 boots, s32 face, OverrideLimbDrawOpa overrideLimbDraw, PostLimbDrawOpa postLimbDraw,
                   void* data) {
    Color_RGB8* color;
    s32 eyeIndex = (jointTable[22].x & 0xF) - 1;
    s32 mouthIndex = (jointTable[22].x >> 4) - 1;

    OPEN_DISPS(globalCtx->state.gfxCtx, "../z_player_lib.c", 1721);

    if (eyeIndex < 0) {
        eyeIndex = sEyeMouthIndexes[face][0];
    }

    if (eyeIndex > 7)
        eyeIndex = 7;

#if defined(MODDING) || defined(_MSC_VER) || defined(__GNUC__)
    gSPSegment(POLY_OPA_DISP++, 0x08, SEGMENTED_TO_VIRTUAL(sEyeTextures[gSaveContext.linkAge][eyeIndex]));
#else
    gSPSegment(POLY_OPA_DISP++, 0x08, SEGMENTED_TO_VIRTUAL(sEyeTextures[eyeIndex]));
#endif
    if (mouthIndex < 0) {
        mouthIndex = sEyeMouthIndexes[face][1];
    }

    if (mouthIndex > 3)
        mouthIndex = 3;

#if defined(MODDING) || defined(_MSC_VER) || defined(__GNUC__)
    gSPSegment(POLY_OPA_DISP++, 0x09, SEGMENTED_TO_VIRTUAL(sMouthTextures[gSaveContext.linkAge][mouthIndex]));
#else
    gSPSegment(POLY_OPA_DISP++, 0x09, SEGMENTED_TO_VIRTUAL(sMouthTextures[eyeIndex]));
#endif
    Color_RGB8 sTemp;
    color = &sTemp;
    if (tunic == PLAYER_TUNIC_KOKIRI) {
        color->r = CVar_GetS32("gTunic_Kokiri_Red", sTunicColors[PLAYER_TUNIC_KOKIRI].r);
        color->g = CVar_GetS32("gTunic_Kokiri_Green", sTunicColors[PLAYER_TUNIC_KOKIRI].g);
        color->b = CVar_GetS32("gTunic_Kokiri_Blue", sTunicColors[PLAYER_TUNIC_KOKIRI].b);
    } else if (tunic == PLAYER_TUNIC_GORON) {
        color->r = CVar_GetS32("gTunic_Goron_Red", sTunicColors[PLAYER_TUNIC_GORON].r);
        color->g = CVar_GetS32("gTunic_Goron_Green", sTunicColors[PLAYER_TUNIC_GORON].g);
        color->b = CVar_GetS32("gTunic_Goron_Blue", sTunicColors[PLAYER_TUNIC_GORON].b);
    } else if (tunic == PLAYER_TUNIC_ZORA) {
        color->r = CVar_GetS32("gTunic_Zora_Red", sTunicColors[PLAYER_TUNIC_ZORA].r);
        color->g = CVar_GetS32("gTunic_Zora_Green", sTunicColors[PLAYER_TUNIC_ZORA].g);
        color->b = CVar_GetS32("gTunic_Zora_Blue", sTunicColors[PLAYER_TUNIC_ZORA].b);
    } else {
        color->r = CVar_GetS32("gTunic_Kokiri_Red", sTunicColors[PLAYER_TUNIC_KOKIRI].r);
        color->g = CVar_GetS32("gTunic_Kokiri_Green", sTunicColors[PLAYER_TUNIC_KOKIRI].g);
        color->b = CVar_GetS32("gTunic_Kokiri_Blue", sTunicColors[PLAYER_TUNIC_KOKIRI].b);
    }
    gDPSetEnvColor(POLY_OPA_DISP++, color->r, color->g, color->b, 0);

    sDListsLodOffset = lod * 2;

    SkelAnime_DrawFlexLod(globalCtx, skeleton, jointTable, dListCount, overrideLimbDraw, postLimbDraw, data, lod);

    if ((overrideLimbDraw != func_800902F0) && (overrideLimbDraw != func_80090440) && (gSaveContext.gameMode != 3)) {
        if (LINK_IS_ADULT) {
            s32 strengthUpgrade = CUR_UPG_VALUE(UPG_STRENGTH);

            if (strengthUpgrade >= 2) { // silver or gold gauntlets
                gDPPipeSync(POLY_OPA_DISP++);

                color = &sGauntletColors[strengthUpgrade - 2];
                gDPSetEnvColor(POLY_OPA_DISP++, color->r, color->g, color->b, 0);

                gSPDisplayList(POLY_OPA_DISP++, gLinkAdultLeftGauntletPlate1DL);
                gSPDisplayList(POLY_OPA_DISP++, gLinkAdultRightGauntletPlate1DL);
                gSPDisplayList(POLY_OPA_DISP++,
                               (D_80160014 == 0) ? gLinkAdultLeftGauntletPlate2DL : gLinkAdultLeftGauntletPlate3DL);
                gSPDisplayList(POLY_OPA_DISP++,
                               (D_80160018 == 8) ? gLinkAdultRightGauntletPlate2DL : gLinkAdultRightGauntletPlate3DL);
            }

            if (boots != 0) {
                Gfx** bootDLists = sBootDListGroups[boots - 1];

                gSPDisplayList(POLY_OPA_DISP++, bootDLists[0]);
                gSPDisplayList(POLY_OPA_DISP++, bootDLists[1]);
            }
        } else {
            if (Player_GetStrength() > PLAYER_STR_NONE) {
                gSPDisplayList(POLY_OPA_DISP++, gLinkChildGoronBraceletDL);
            }
        }
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx, "../z_player_lib.c", 1803);
}

Vec3f D_8012602C = { 0.0f, 0.0f, 0.0f };

Vec3f D_80126038[] = {
    { 1304.0f, 0.0f, 0.0f },
    { 695.0f, 0.0f, 0.0f },
};

f32 D_80126050[] = { 1265.0f, 826.0f };
f32 D_80126058[] = { SQ(13.04f), SQ(6.95f) };
f32 D_80126060[] = { 10.019104f, -19.925102f };
f32 D_80126068[] = { 5.0f, 3.0f };

Vec3f D_80126070 = { 0.0f, -300.0f, 0.0f };

void func_8008F87C(GlobalContext* globalCtx, Player* this, SkelAnime* skelAnime, Vec3f* pos, Vec3s* rot,
                   s32 thighLimbIndex, s32 shinLimbIndex, s32 footLimbIndex) {
    Vec3f spA4;
    Vec3f sp98;
    Vec3f footprintPos;
    CollisionPoly* sp88;
    s32 sp84;
    f32 sp80;
    f32 sp7C;
    f32 sp78;
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    s16 temp1;
    s16 temp2;
    s32 temp3;

    if ((this->actor.scale.y >= 0.0f) && !(this->stateFlags1 & 0x80) &&
        (Player_ActionToMagicSpell(this, this->itemActionParam) < 0)) {
        s32 pad;

        sp7C = D_80126058[(void)0, gSaveContext.linkAge];
        sp78 = D_80126060[(void)0, gSaveContext.linkAge];
        sp74 = D_80126068[(void)0, gSaveContext.linkAge] - this->unk_6C4;

        Matrix_Push();
        Matrix_TranslateRotateZYX(pos, rot);
        Matrix_MultVec3f(&D_8012602C, &spA4);
        Matrix_TranslateRotateZYX(&D_80126038[(void)0, gSaveContext.linkAge], &skelAnime->jointTable[shinLimbIndex]);
        Matrix_Translate(D_80126050[(void)0, gSaveContext.linkAge], 0.0f, 0.0f, MTXMODE_APPLY);
        Matrix_MultVec3f(&D_8012602C, &sp98);
        Matrix_MultVec3f(&D_80126070, &footprintPos);
        Matrix_Pop();

        footprintPos.y += 15.0f;

        sp80 = BgCheck_EntityRaycastFloor4(&globalCtx->colCtx, &sp88, &sp84, &this->actor, &footprintPos) + sp74;

        if (sp98.y < sp80) {
            sp70 = sp98.x - spA4.x;
            sp6C = sp98.y - spA4.y;
            sp68 = sp98.z - spA4.z;

            sp64 = sqrtf(SQ(sp70) + SQ(sp6C) + SQ(sp68));
            sp60 = (SQ(sp64) + sp78) / (2.0f * sp64);

            sp58 = sp7C - SQ(sp60);
            sp58 = (sp7C < SQ(sp60)) ? 0.0f : sqrtf(sp58);

            sp54 = Math_FAtan2F(sp58, sp60);

            sp6C = sp80 - spA4.y;

            sp64 = sqrtf(SQ(sp70) + SQ(sp6C) + SQ(sp68));
            sp60 = (SQ(sp64) + sp78) / (2.0f * sp64);
            sp5C = sp64 - sp60;

            sp58 = sp7C - SQ(sp60);
            sp58 = (sp7C < SQ(sp60)) ? 0.0f : sqrtf(sp58);

            sp50 = Math_FAtan2F(sp58, sp60);

            temp1 = (M_PI - (Math_FAtan2F(sp5C, sp58) + ((M_PI / 2) - sp50))) * (0x8000 / M_PI);
            temp1 = temp1 - skelAnime->jointTable[shinLimbIndex].z;

            if ((s16)(ABS(skelAnime->jointTable[shinLimbIndex].x) + ABS(skelAnime->jointTable[shinLimbIndex].y)) < 0) {
                temp1 += 0x8000;
            }

            temp2 = (sp50 - sp54) * (0x8000 / M_PI);
            rot->z -= temp2;

            skelAnime->jointTable[thighLimbIndex].z = skelAnime->jointTable[thighLimbIndex].z - temp2;
            skelAnime->jointTable[shinLimbIndex].z = skelAnime->jointTable[shinLimbIndex].z + temp1;
            skelAnime->jointTable[footLimbIndex].z = skelAnime->jointTable[footLimbIndex].z + temp2 - temp1;

            temp3 = func_80041D4C(&globalCtx->colCtx, sp88, sp84);

            if ((temp3 >= 2) && (temp3 < 4) && !SurfaceType_IsWallDamage(&globalCtx->colCtx, sp88, sp84)) {
                footprintPos.y = sp80;
                EffectSsGFire_Spawn(globalCtx, &footprintPos);
            }
        }
    }
}

s32 func_8008FCC8(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, void* thisx) {
    Player* this = (Player*)thisx;

    if (limbIndex == PLAYER_LIMB_ROOT) {
        D_80160014 = this->leftHandType;
        D_80160018 = this->rightHandType;
        D_80160000 = &this->swordInfo[2].base;

        if (!LINK_IS_ADULT) {
            if (!(this->skelAnime.moveFlags & 4) || (this->skelAnime.moveFlags & 1)) {
                pos->x *= 0.64f;
                pos->z *= 0.64f;
            }

            if (!(this->skelAnime.moveFlags & 4) || (this->skelAnime.moveFlags & 2)) {
                pos->y *= 0.64f;
            }
        }

        pos->y -= this->unk_6C4;

        if (this->unk_6C2 != 0) {
            Matrix_Translate(pos->x, ((Math_CosS(this->unk_6C2) - 1.0f) * 200.0f) + pos->y, pos->z, MTXMODE_APPLY);
            Matrix_RotateX(this->unk_6C2 * (M_PI / 0x8000), MTXMODE_APPLY);
            Matrix_RotateZYX(rot->x, rot->y, rot->z, MTXMODE_APPLY);
            pos->x = pos->y = pos->z = 0.0f;
            rot->x = rot->y = rot->z = 0;
        }
    } else {
        if (*dList != NULL) {
            D_80160000++;
        }

        if (limbIndex == PLAYER_LIMB_HEAD) {
            rot->x += this->unk_6BA;
            rot->y -= this->unk_6B8;
            rot->z += this->unk_6B6;
        } else if (limbIndex == PLAYER_LIMB_UPPER) {
            if (this->unk_6B0 != 0) {
                Matrix_RotateZ(0x44C * (M_PI / 0x8000), MTXMODE_APPLY);
                Matrix_RotateY(this->unk_6B0 * (M_PI / 0x8000), MTXMODE_APPLY);
            }
            if (this->unk_6BE != 0) {
                Matrix_RotateY(this->unk_6BE * (M_PI / 0x8000), MTXMODE_APPLY);
            }
            if (this->unk_6BC != 0) {
                Matrix_RotateX(this->unk_6BC * (M_PI / 0x8000), MTXMODE_APPLY);
            }
            if (this->unk_6C0 != 0) {
                Matrix_RotateZ(this->unk_6C0 * (M_PI / 0x8000), MTXMODE_APPLY);
            }
        } else if (limbIndex == PLAYER_LIMB_L_THIGH) {
            func_8008F87C(globalCtx, this, &this->skelAnime, pos, rot, PLAYER_LIMB_L_THIGH, PLAYER_LIMB_L_SHIN,
                          PLAYER_LIMB_L_FOOT);
        } else if (limbIndex == PLAYER_LIMB_R_THIGH) {
            func_8008F87C(globalCtx, this, &this->skelAnime, pos, rot, PLAYER_LIMB_R_THIGH, PLAYER_LIMB_R_SHIN,
                          PLAYER_LIMB_R_FOOT);
            return false;
        } else {
            return false;
        }
    }

    return false;
}

s32 func_80090014(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, void* thisx) {
    Player* this = (Player*)thisx;

    if (!func_8008FCC8(globalCtx, limbIndex, dList, pos, rot, thisx)) {
        if (limbIndex == PLAYER_LIMB_L_HAND) {
            Gfx** dLists = this->leftHandDLists;

            if ((D_80160014 == 4) && (gSaveContext.swordHealth <= 0.0f)) {
                dLists += 4;
            } else if ((D_80160014 == 6) && (this->stateFlags1 & 0x2000000)) {
                dLists = &D_80125E08[gSaveContext.linkAge];
                D_80160014 = 0;
            } else if ((this->leftHandType == 0) && (this->actor.speedXZ > 2.0f) && !(this->stateFlags1 & 0x8000000)) {
                dLists = &D_80125E18[gSaveContext.linkAge];
                D_80160014 = 1;
            }

            *dList = ResourceMgr_LoadGfxByName(dLists[sDListsLodOffset]);
        } else if (limbIndex == PLAYER_LIMB_R_HAND) {
            Gfx** dLists = this->rightHandDLists;

            if (D_80160018 == 10) {
                dLists += this->currentShield * 4;
            } else if ((this->rightHandType == 8) && (this->actor.speedXZ > 2.0f) && !(this->stateFlags1 & 0x8000000)) {
                dLists = &D_80125E58[gSaveContext.linkAge];
                D_80160018 = 9;
            }

            *dList = ResourceMgr_LoadGfxByName(dLists[sDListsLodOffset]);
        } else if (limbIndex == PLAYER_LIMB_SHEATH) {
            Gfx** dLists = this->sheathDLists;

            if ((this->sheathType == 18) || (this->sheathType == 19)) {
                dLists += this->currentShield * 4;
                if (!LINK_IS_ADULT && (this->currentShield < PLAYER_SHIELD_HYLIAN) &&
                    (gSaveContext.equips.buttonItems[0] != ITEM_SWORD_KOKIRI)) {
                    dLists += 16;
                }
            } else if (!LINK_IS_ADULT && ((this->sheathType == 16) || (this->sheathType == 17)) &&
                       (gSaveContext.equips.buttonItems[0] != ITEM_SWORD_KOKIRI)) {
                dLists = &D_80125D28[16];
            }

            if (dLists[sDListsLodOffset] != NULL) {
                *dList = ResourceMgr_LoadGfxByName(dLists[sDListsLodOffset]);
            } else {
                *dList = NULL;
            }


        } else if (limbIndex == PLAYER_LIMB_WAIST) {
            *dList = ResourceMgr_LoadGfxByName(this->waistDLists[sDListsLodOffset]);
        }
    }

    return false;
}

s32 func_800902F0(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, void* thisx) {
    Player* this = (Player*)thisx;

    if (!func_8008FCC8(globalCtx, limbIndex, dList, pos, rot, thisx)) {
        if (this->unk_6AD != 2) {
            *dList = NULL;
        } else if (limbIndex == PLAYER_LIMB_L_FOREARM) {
            *dList = sArmOutDLs[(void)0, gSaveContext.linkAge];
        } else if (limbIndex == PLAYER_LIMB_L_HAND) {
            *dList = sHandOutDLs[(void)0, gSaveContext.linkAge];
        } else if (limbIndex == PLAYER_LIMB_R_SHOULDER) {
            *dList = sRightShoulderNearDLs[(void)0, gSaveContext.linkAge];
        } else if (limbIndex == PLAYER_LIMB_R_FOREARM) {
            *dList = D_80125F30[(void)0, gSaveContext.linkAge];
        } else if (limbIndex == PLAYER_LIMB_R_HAND) {
            *dList = Player_HoldsHookshot(this) ? gLinkAdultRightHandHoldingHookshotFarDL
                                                : sHoldingFirstPersonWeaponDLs[(void)0, gSaveContext.linkAge];
        } else {
            *dList = NULL;
        }
    }

    return false;
}

s32 func_80090440(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, void* thisx) {
    if (!func_8008FCC8(globalCtx, limbIndex, dList, pos, rot, thisx)) {
        *dList = NULL;
    }

    return false;
}

u8 func_80090480(GlobalContext* globalCtx, ColliderQuad* collider, WeaponInfo* weaponInfo, Vec3f* newTip,
                 Vec3f* newBase) {
    if (weaponInfo->active == 0) {
        if (collider != NULL) {
            Collider_ResetQuadAT(globalCtx, &collider->base);
        }
        Math_Vec3f_Copy(&weaponInfo->tip, newTip);
        Math_Vec3f_Copy(&weaponInfo->base, newBase);
        weaponInfo->active = 1;
        return 1;
    } else if ((weaponInfo->tip.x == newTip->x) && (weaponInfo->tip.y == newTip->y) &&
               (weaponInfo->tip.z == newTip->z) && (weaponInfo->base.x == newBase->x) &&
               (weaponInfo->base.y == newBase->y) && (weaponInfo->base.z == newBase->z)) {
        if (collider != NULL) {
            Collider_ResetQuadAT(globalCtx, &collider->base);
        }
        return 0;
    } else {
        if (collider != NULL) {
            Collider_SetQuadVertices(collider, newBase, newTip, &weaponInfo->base, &weaponInfo->tip);
            CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &collider->base);
        }
        Math_Vec3f_Copy(&weaponInfo->base, newBase);
        Math_Vec3f_Copy(&weaponInfo->tip, newTip);
        weaponInfo->active = 1;
        return 1;
    }
}

void func_80090604(GlobalContext* globalCtx, Player* this, ColliderQuad* collider, Vec3f* quadSrc) {
    static u8 shieldColTypes[PLAYER_SHIELD_MAX] = {
        COLTYPE_METAL,
        COLTYPE_WOOD,
        COLTYPE_METAL,
        COLTYPE_METAL,
    };

    if (this->stateFlags1 & 0x400000) {
        Vec3f quadDest[4];

        this->shieldQuad.base.colType = shieldColTypes[this->currentShield];

        Matrix_MultVec3f(&quadSrc[0], &quadDest[0]);
        Matrix_MultVec3f(&quadSrc[1], &quadDest[1]);
        Matrix_MultVec3f(&quadSrc[2], &quadDest[2]);
        Matrix_MultVec3f(&quadSrc[3], &quadDest[3]);
        Collider_SetQuadVertices(collider, &quadDest[0], &quadDest[1], &quadDest[2], &quadDest[3]);

        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &collider->base);
        CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &collider->base);
    }
}

Vec3f D_80126080 = { 5000.0f, 400.0f, 0.0f };
Vec3f D_8012608C = { 5000.0f, -400.0f, 1000.0f };
Vec3f D_80126098 = { 5000.0f, 1400.0f, -1000.0f };

Vec3f D_801260A4[3] = {
    { 0.0f, 400.0f, 0.0f },
    { 0.0f, 1400.0f, -1000.0f },
    { 0.0f, -400.0f, 1000.0f },
};

void func_800906D4(GlobalContext* globalCtx, Player* this, Vec3f* newTipPos) {
    Vec3f newBasePos[3];

    Matrix_MultVec3f(&D_801260A4[0], &newBasePos[0]);
    Matrix_MultVec3f(&D_801260A4[1], &newBasePos[1]);
    Matrix_MultVec3f(&D_801260A4[2], &newBasePos[2]);

    if (func_80090480(globalCtx, NULL, &this->swordInfo[0], &newTipPos[0], &newBasePos[0]) &&
        !(this->stateFlags1 & 0x400000)) {
        EffectBlure_AddVertex(Effect_GetByIndex(this->swordEffectIndex), &this->swordInfo[0].tip,
                              &this->swordInfo[0].base);
    }

    if ((this->swordState > 0) && ((this->swordAnimation < 0x18) || (this->stateFlags2 & 0x20000))) {
        func_80090480(globalCtx, &this->swordQuads[0], &this->swordInfo[1], &newTipPos[1], &newBasePos[1]);
        func_80090480(globalCtx, &this->swordQuads[1], &this->swordInfo[2], &newTipPos[2], &newBasePos[2]);
    }
}

void Player_DrawGetItemImpl(GlobalContext* globalCtx, Player* this, Vec3f* refPos, s32 drawIdPlusOne) {
    f32 height = (this->exchangeItemId != EXCH_ITEM_NONE) ? 6.0f : 14.0f;

    OPEN_DISPS(globalCtx->state.gfxCtx, "../z_player_lib.c", 2401);

    gSegments[6] = VIRTUAL_TO_PHYSICAL(this->giObjectSegment);

    gSPSegment(POLY_OPA_DISP++, 0x06, this->giObjectSegment);
    gSPSegment(POLY_XLU_DISP++, 0x06, this->giObjectSegment);

    Matrix_Translate(refPos->x + (3.3f * Math_SinS(this->actor.shape.rot.y)), refPos->y + height,
                     refPos->z + ((3.3f + (IREG(90) / 10.0f)) * Math_CosS(this->actor.shape.rot.y)), MTXMODE_NEW);
    Matrix_RotateZYX(0, globalCtx->gameplayFrames * 1000, 0, MTXMODE_APPLY);
    Matrix_Scale(0.2f, 0.2f, 0.2f, MTXMODE_APPLY);

    GetItem_Draw(globalCtx, drawIdPlusOne - 1);

    CLOSE_DISPS(globalCtx->state.gfxCtx, "../z_player_lib.c", 2421);
}

void Player_DrawGetItem(GlobalContext* globalCtx, Player* this) {
    //if (!this->giObjectLoading || !osRecvMesg(&this->giObjectLoadQueue, NULL, OS_MESG_NOBLOCK)) // OTRTODO: Do something about osRecvMesg here...
    {
        this->giObjectLoading = false;
        Player_DrawGetItemImpl(globalCtx, this, &sGetItemRefPos, ABS(this->unk_862));
    }
}

void func_80090A28(Player* this, Vec3f* vecs) {
    D_8012608C.x = D_80126080.x;

    if (this->unk_845 >= 3) {
        this->unk_845 += 1;
        D_8012608C.x *= 1.0f + ((9 - this->unk_845) * 0.1f);
    }

    D_8012608C.x += 1200.0f;
    D_80126098.x = D_8012608C.x;

    Matrix_MultVec3f(&D_80126080, &vecs[0]);
    Matrix_MultVec3f(&D_8012608C, &vecs[1]);
    Matrix_MultVec3f(&D_80126098, &vecs[2]);
}

void Player_DrawHookshotReticle(GlobalContext* globalCtx, Player* this, f32 arg2) {
    static Vec3f D_801260C8 = { -500.0f, -100.0f, 0.0f };
    CollisionPoly* sp9C;
    s32 bgId;
    Vec3f sp8C;
    Vec3f sp80;
    Vec3f sp74;
    Vec3f sp68;
    f32 sp64;
    f32 sp60;

    D_801260C8.z = 0.0f;
    Matrix_MultVec3f(&D_801260C8, &sp8C);
    D_801260C8.z = arg2;
    Matrix_MultVec3f(&D_801260C8, &sp80);

    if (1) {}

    if (BgCheck_AnyLineTest3(&globalCtx->colCtx, &sp8C, &sp80, &sp74, &sp9C, 1, 1, 1, 1, &bgId)) {
        OPEN_DISPS(globalCtx->state.gfxCtx, "../z_player_lib.c", 2572);

        WORLD_OVERLAY_DISP = Gfx_CallSetupDL(WORLD_OVERLAY_DISP, 0x07);

        SkinMatrix_Vec3fMtxFMultXYZW(&globalCtx->viewProjectionMtxF, &sp74, &sp68, &sp64);

        sp60 = (sp64 < 200.0f) ? 0.08f : (sp64 / 200.0f) * 0.08f;

        Matrix_Translate(sp74.x, sp74.y, sp74.z, MTXMODE_NEW);
        Matrix_Scale(sp60, sp60, sp60, MTXMODE_APPLY);

        gSPMatrix(WORLD_OVERLAY_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_player_lib.c", 2587),
                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPSegment(WORLD_OVERLAY_DISP++, 0x06, globalCtx->objectCtx.status[this->actor.objBankIndex].segment);
        gSPDisplayList(WORLD_OVERLAY_DISP++, gLinkAdultHookshotReticleDL);

        CLOSE_DISPS(globalCtx->state.gfxCtx, "../z_player_lib.c", 2592);
    }
}

Vec3f D_801260D4 = { 1100.0f, -700.0f, 0.0f };

f32 sSwordLengths[] = {
    0.0f, 4000.0f, 3000.0f, 5500.0f, 0.0f, 2500.0f,
};

Gfx* sBottleDLists[] = { gLinkAdultBottleDL, gLinkChildBottleDL };

Color_RGB8 sBottleColors[] = {
    { 255, 255, 255 }, { 80, 80, 255 },   { 255, 100, 255 }, { 0, 0, 255 }, { 255, 0, 255 },
    { 255, 0, 255 },   { 200, 200, 100 }, { 255, 0, 0 },     { 0, 0, 255 }, { 0, 255, 0 },
    { 255, 255, 255 }, { 255, 255, 255 }, { 80, 80, 255 },
};

Vec3f D_80126128 = { 398.0f, 1419.0f, 244.0f };

BowStringData sBowStringData[] = {
    { gLinkAdultBowStringDL, { 0.0f, -360.4f, 0.0f } },       // bow
    { gLinkChildSlinghotStringDL, { 606.0f, 236.0f, 0.0f } }, // slingshot
};

Vec3f D_80126154[] = {
    { -4500.0f, -3000.0f, -600.0f },
    { 1500.0f, -3000.0f, -600.0f },
    { -4500.0f, 3000.0f, -600.0f },
    { 1500.0f, 3000.0f, -600.0f },
};

Vec3f D_80126184 = { 100.0f, 1500.0f, 0.0f };
Vec3f D_80126190 = { 100.0f, 1640.0f, 0.0f };

Vec3f D_8012619C[] = {
    { -3000.0f, -3000.0f, -900.0f },
    { 3000.0f, -3000.0f, -900.0f },
    { -3000.0f, 3000.0f, -900.0f },
    { 3000.0f, 3000.0f, -900.0f },
};

Vec3f D_801261CC = { 630.0f, 100.0f, -30.0f };
Vec3s D_801261D8 = { 0, 0, 0x7FFF };

Vec3f D_801261E0[] = {
    { 200.0f, 300.0f, 0.0f },
    { 200.0f, 200.0f, 0.0f },
};

typedef struct SoundCue {
    bool active;
    Vec3f position;
    f32 pitch;
    f32 volume;
    s32 sfxId;
    u32 repeatCount;
    u32 repeatIntervalFrames;
    f32 volumeModulateAmp;
    u32 volumeModulateFreq;

    bool isPlaying;
    u32 startFrame;
    u32 timesPlayed;
} SoundCue;

void SoundCue_Update(SoundCue* this, GlobalContext* globalCtx) {
    if (this->active) {
        if ((!this->isPlaying || (globalCtx->gameplayFrames - this->startFrame) % this->repeatIntervalFrames == 0) &&
            (this->repeatCount == 0 || this->repeatCount < this->timesPlayed)) {
            Audio_PlaySoundGeneral(this->sfxId, &this->position, 4, &this->pitch, &this->volume, &D_801333E8);
            if (!this->isPlaying) {
                this->isPlaying = true;
                this->startFrame = globalCtx->gameplayFrames;
            }
            this->timesPlayed++;
        }

        this->volume =
            MAX(0.0f, this->volume + this->volumeModulateAmp *
                                         Math_SinF((float)(globalCtx->gameplayFrames % this->volumeModulateFreq) /
                                                   this->volumeModulateFreq * 2.0f * M_PI));
    } else if (this->isPlaying) {
        Audio_StopSfxByPos(&this->position);
        this->isPlaying = false;
        this->timesPlayed = 0;
    }
}

static SoundCue sFallCue = 
{
    false,
    { 0.0f, 0.0f, 0.0f },
    2.2f,
    1.0f,
    NA_SE_SY_MESSAGE_WOMAN,
    0,
    1,
    0.0f,
    20,
    false,
    0,
    0
};

static SoundCue sFallWarningCue = 
{
    false,
    { 0.0f, 0.0f, 0.0f },
    0.7f,
    1.0f,
    NA_SE_PL_HOBBERBOOTS_LV,
    0,
    20,
    0.0f,
    20,
    false,
    0,
    0
};

static struct FallCueInfo {
    bool willFall;
    bool willLandSafely;
    bool willLandInWater;
    Vec3f fallPosition;
};

void Player_UpdateFallCueClimbing(Player* this, GlobalContext* globalCtx, struct FallCueInfo* fallInfo) {
    Vec3f vecInput;
    f32 stickRadius = this->unk_A7C;
    s16 stickAngle = this->unk_A80;

    if (this->actor.wallPoly == NULL) {
        return;
    }

    Vec3f wallNormal;
    wallNormal.x = COLPOLY_GET_NORMAL(this->actor.wallPoly->normal.x);
    wallNormal.y = COLPOLY_GET_NORMAL(this->actor.wallPoly->normal.y);
    wallNormal.z = COLPOLY_GET_NORMAL(this->actor.wallPoly->normal.z);

    Vec3f vecA;
    Vec3f vecB;
    CollisionPoly* wallPoly = this->actor.wallPoly;
    s32 bgId = this->actor.wallBgId;

    MtxF rotationMtx;

    Vec3f vecUp;
    vecUp.x = 0.0f;
    vecUp.y = 16.0f;
    vecUp.z = 0.0f;

    s16 currentYaw = this->actor.shape.rot.y;
    Vec3f vecCurrent = this->actor.world.pos;
    Vec3f vecPrev;
    Vec3f vecStep;

    bool isPlayerClimbingLadder = !!(func_80041DB8(&globalCtx->colCtx, this->actor.wallPoly, this->actor.wallBgId) & 2);
    if (isPlayerClimbingLadder) {
        //round to nearest 2-way direction
        stickRadius = stickRadius * ABS(Math_CosS(stickAngle));
        stickAngle = (((u32)stickAngle + (0x4000)) / 0x8000) * 0x8000;
    } else {
        //round to nearest 4-way direction
        stickAngle = (((u32)stickAngle + (0x2000)) / 0x4000) * 0x4000;
    }

    const int numSamples = ceilf(stickRadius / 60.0f * 3.0f);
    for (int i = 0; i < numSamples; i++) {
        vecPrev = vecCurrent;

        SkinMatrix_SetRotateAxis(&rotationMtx, stickAngle, wallNormal.x,
                                 wallNormal.y, wallNormal.z);
        SkinMatrix_Vec3fMtxFMultXYZ(&rotationMtx, &vecUp, &vecStep);
        Math_Vec3f_Sum(&vecCurrent, &vecStep, &vecCurrent);

        f32 yawCos = Math_CosS(currentYaw);
        f32 yawSin = Math_SinS(currentYaw);

        CollisionPoly* polyResult;
        Vec3f vecResult;
        s32 bgIdResult;

        const f32 wallCheckRadius = this->ageProperties->unk_38;
        const f32 wallCheckHeight = 26.0f;
        const f32 ceilingCheckHeight = this->ageProperties->unk_00;
        f32 heightDiff = vecCurrent.y - vecPrev.y;
        if (BgCheck_EntitySphVsWall3(&globalCtx->colCtx, &vecResult, &vecCurrent, &vecPrev, wallCheckRadius,
                                      &polyResult, &bgIdResult, &this->actor, wallCheckHeight)) {
            vecCurrent = vecResult;
        }
        f32 outY;
        if (BgCheck_EntityCheckCeiling(&globalCtx->colCtx, &outY, &vecCurrent, (ceilingCheckHeight + heightDiff) - 10.0f,
                                       &polyResult, &bgIdResult, &this->actor)) {
            vecCurrent.y = (outY + heightDiff) - 10.0f;
        }

        //arbitrary constants from z_player.c:11623
        vecA.x = vecCurrent.x + (-20.0f * yawSin);
        vecA.z = vecCurrent.z + (-20.0f * yawCos);
        vecB.x = vecCurrent.x + (50.0f * yawSin);
        vecB.z = vecCurrent.z + (50.0f * yawCos);
        vecA.y = vecB.y = vecCurrent.y + wallCheckHeight;

        if (BgCheck_EntityLineTest1(&globalCtx->colCtx, &vecA, &vecB, &vecResult, &polyResult, true, false, false, true,
                                    &bgIdResult) &&
            (func_80041DB8(&globalCtx->colCtx, polyResult, bgIdResult) & (8 | 2))) {

            wallPoly = polyResult;
            bgId = bgIdResult;

            wallNormal.x = COLPOLY_GET_NORMAL(wallPoly->normal.x);
            wallNormal.y = COLPOLY_GET_NORMAL(wallPoly->normal.y);
            wallNormal.z = COLPOLY_GET_NORMAL(wallPoly->normal.z);
            currentYaw = Math_Atan2S(-wallNormal.z, -wallNormal.x);

            vecCurrent.x = vecResult.x - (Math_SinS(currentYaw) * this->ageProperties->unk_3C);
            vecCurrent.z = vecResult.z - (Math_CosS(currentYaw) * this->ageProperties->unk_3C);

        } else {
            fallInfo->willFall = true;
            fallInfo->fallPosition = vecCurrent;

            if (stickAngle == 0x0000) {
                f32 wallDistance = Math3D_UDistPlaneToPos(wallNormal.x, wallNormal.y, wallNormal.z,
                                                          wallPoly->dist,
                                                          &vecPrev);
                f32 testDistance = wallDistance + 10.0f;
                Vec3f vecTestPoint;
                vecTestPoint.x = vecCurrent.x - (testDistance * wallNormal.x);
                vecTestPoint.z = vecCurrent.z - (testDistance * wallNormal.z);
                vecTestPoint.y = vecCurrent.y + 50.0f;

                CollisionPoly* floorPoly;
                f32 floorHeight =
                    BgCheck_EntityRaycastFloor1(&globalCtx->colCtx, &floorPoly, &vecTestPoint);
                if (floorHeight > BGCHECK_Y_MIN && floorHeight > vecPrev.y) {
                    fallInfo->willLandSafely = true;
                }
            } else {
                const f32 safeDropDistance = this->ageProperties->unk_0C;
                const f32 raycastPosYMargin = 50.0f;
                vecA = vecCurrent;
                vecA.y += raycastPosYMargin;
                CollisionPoly* floorPoly;
                f32 floorHeight = BgCheck_EntityRaycastFloor5(globalCtx, &globalCtx->colCtx, &floorPoly, &bgId, &this->actor, &vecA);
                if (floorHeight > BGCHECK_Y_MIN && vecCurrent.y - floorHeight <= safeDropDistance) {
                    fallInfo->willLandSafely = true;
                }
            }

            break;
        }
    }

    if (CVar_GetS32("gDebugEnabled", 0)) {
        DebugDisplay_AddObject(vecCurrent.x, vecCurrent.y + 26.0f, vecCurrent.z, 0, currentYaw,
                               0, 1.0f,
                               1.0f, 1.0f,
                               (fallInfo->willFall && !fallInfo->willLandSafely) ? 255 : 0,
                               (!fallInfo->willFall) ? 255 : 0,
                               (fallInfo->willLandSafely) ? 255 : 0, 255, 4,
                               globalCtx->state.gfxCtx);
    }
}

Actor playerProxy;

static void func_808395DC(Actor* this, Vec3f* arg1, Vec3f* arg2, Vec3f* arg3) {
    f32 cos = Math_CosS(this->shape.rot.y);
    f32 sin = Math_SinS(this->shape.rot.y);

    arg3->x = arg1->x + ((arg2->x * cos) + (arg2->z * sin));
    arg3->y = arg1->y + arg2->y;
    arg3->z = arg1->z + ((arg2->z * cos) - (arg2->x * sin));
}

static s32 func_80839768(GlobalContext* globalCtx, Actor* this, Vec3f* arg2, CollisionPoly** arg3, s32* arg4, Vec3f* arg5) {
    Vec3f sp44;
    Vec3f sp38;

    sp44.x = this->world.pos.x;
    sp44.y = this->world.pos.y + arg2->y;
    sp44.z = this->world.pos.z;

    func_808395DC(this, &this->world.pos, arg2, &sp38);

    return BgCheck_EntityLineTest1(&globalCtx->colCtx, &sp44, &sp38, arg5, arg3, true, false, false, true, arg4);
}

void Player_UpdateFallCueNormal(Player* this, GlobalContext* globalCtx, struct FallCueInfo* fallInfo) {
    const int maxSamples = 100;
    const int numWarnAheadFrames = 20;
    const f32 jumpHeightThreshold = 20.0f;
    const f32 jumpLinearVelocityThreshold = 3.0f;
    const f32 safeJumpHeightDiffThreshold = this->ageProperties->unk_14;
    const f32 maxJumpLinearVelocity = this->unk_880; // R_RUN_SPEED_LIMIT / 100.0f;
    const f32 defaultYVelocity = -4.0f;              // z_actor.c:1535

    bool isPlayerWearingHoverBoots = (this->currentBoots == PLAYER_BOOTS_HOVER);
    s32 hoverBootsTimer = (isPlayerWearingHoverBoots) ? this->hoverBootsTimer : 0;

    fallInfo->willFall = !(this->actor.bgCheckFlags & 1); //player is already falling
    bool willGrabLedge = false; //mainly for debug

    f32 fallStartHeight = (fallInfo->willFall) ? this->fallStartHeight : BGCHECK_Y_MIN;

    // z_player.c:4589
    f32 jumpYVelocity;
    if (this->linearVelocity > (IREG(66) / 100.0f)) {
        jumpYVelocity = IREG(67) / 100.0f;
    } else {
        jumpYVelocity = (IREG(68) / 100.0f) + ((IREG(69) * this->linearVelocity) / 1000.0f);
    }

    Vec3f vecStep;
    f32 linearVelocity;
    playerProxy.velocity.y = defaultYVelocity;

    if (this->linearVelocity > 0.0f || fallInfo->willFall) {
        linearVelocity = MIN(this->linearVelocity, maxJumpLinearVelocity);
    } else {
        linearVelocity = jumpLinearVelocityThreshold;
    }

    playerProxy = this->actor;
    playerProxy.speedXZ = linearVelocity;

    for (int i = 0; i < maxSamples; i++) {
        if (CVar_GetS32("gDebugEnabled", 0) && i % 4 == 0) {
            DebugDisplay_AddObject(playerProxy.world.pos.x, playerProxy.world.pos.y + 26.0f, playerProxy.world.pos.z,
                               0x4000, 0, 0, 1.0f, 1.0f, 1.0f, (fallInfo->willFall && !fallInfo->willLandSafely) ? 255 : 0,
                               (!fallInfo->willFall || willGrabLedge) ? 255 : 0, (fallInfo->willLandSafely) ? 255 : 0, 255,
                               4,
                               globalCtx->state.gfxCtx);
        }
        

        playerProxy.prevPos = playerProxy.world.pos;

        func_8002D868(&playerProxy); // update velocity

        if ((this->windSpeed != 0.0f) && !Player_InCsMode(globalCtx) &&
            !(this->stateFlags1 & (PLAYER_STATE1_13 | PLAYER_STATE1_14 | PLAYER_STATE1_21))) { // &&
            //(func_80845668 != this->func_674) && (func_808507F4 != this->func_674)) {
            playerProxy.velocity.x += this->windSpeed * Math_SinS(this->windDirection);
            playerProxy.velocity.z += this->windSpeed * Math_CosS(this->windDirection);
        }

        func_8002D7EC(&playerProxy); // update position

        const f32 wallCheckRadius = this->ageProperties->unk_38;
        const f32 wallCheckHeight = 26.0f;
        const f32 ceilingCheckHeight = this->ageProperties->unk_00;
        Actor_UpdateBgCheckInfo(globalCtx, &playerProxy, wallCheckHeight, wallCheckRadius, ceilingCheckHeight, 0x7F);

        bool isProxyOnFloor = playerProxy.bgCheckFlags & 1;
        bool isProxySwimming = playerProxy.yDistToWater > this->ageProperties->unk_2C;

        if (!isProxyOnFloor || isProxySwimming) {
            if (fallInfo->willFall == false) {
                fallInfo->fallPosition = playerProxy.world.pos;
                fallInfo->willFall = true;

                fallStartHeight = playerProxy.world.pos.y;

                bool willJump = !isPlayerWearingHoverBoots && (playerProxy.speedXZ > jumpLinearVelocityThreshold) &&
                                (playerProxy.world.pos.y - playerProxy.floorHeight >= jumpHeightThreshold);
                if (willJump) {
                    playerProxy.velocity.y = jumpYVelocity;
                }

                if (isPlayerWearingHoverBoots && playerProxy.yDistToWater >= 0.0f) { //z_player.c:9758
                    hoverBootsTimer = 20; //19 (+1 for the decrement below)
                    playerProxy.world.pos.y = playerProxy.prevPos.y;
                }
            }

            if (isPlayerWearingHoverBoots && hoverBootsTimer != 0) {
                --hoverBootsTimer;
                playerProxy.velocity.y = 1.0f;
            } else if (isProxySwimming) {
                fallInfo->willLandInWater = true;
                break;
            }

            // WIP: ledge grab detection mostly just copied from z_player.c:9894
            if (playerProxy.bgCheckFlags & 8) {
                CollisionPoly* spA0;
                s32 sp9C;
                s16 sp9A;
                s32 pad;
                s32 spC7;
                f32 spB0;
                f32 spAC;

                Vec3f D_80854798;
                s32 D_808535F0;
                s32 D_80853608;
                s32 D_8085360C;
                Vec3f D_80858AA8;

                D_80854798.y = 0.0f;
                D_80854798.y = 18.0f;
                D_80854798.z = this->ageProperties->unk_38 + 10.0f;

                sp9A = playerProxy.shape.rot.y - (s16)(playerProxy.wallYaw + 0x8000);

                D_808535F0 = func_80041DB8(&globalCtx->colCtx, playerProxy.wallPoly, playerProxy.wallBgId);

                D_80853608 = ABS(sp9A);

                sp9A = /* this->currentYaw */ playerProxy.shape.rot.y - (s16)(playerProxy.wallYaw + 0x8000);

                D_8085360C = ABS(sp9A);

                spB0 = D_8085360C * 0.00008f;
                if (!(playerProxy.bgCheckFlags & 1) || spB0 >= 1.0f) {
                    // this->unk_880 = R_RUN_SPEED_LIMIT / 100.0f;
                } else {
                    spAC = (R_RUN_SPEED_LIMIT / 100.0f * spB0);
                    // this->unk_880 = spAC;
                    if (spAC < 0.1f) {
                        // this->unk_880 = 0.1f;
                    }
                }

                if (/* (this->actor.bgCheckFlags & 0x200) && */ (D_80853608 < 0x3000) && hoverBootsTimer == 0) {
                    CollisionPoly* wallPoly = playerProxy.wallPoly;

                    if ((ABS(wallPoly->normal.y) < 600) || (CVar_GetS32("gClimbEverything", 0) != 0)) {
                        f32 sp8C = COLPOLY_GET_NORMAL(wallPoly->normal.x);
                        f32 sp88 = COLPOLY_GET_NORMAL(wallPoly->normal.y);
                        f32 sp84 = COLPOLY_GET_NORMAL(wallPoly->normal.z);
                        f32 wallHeight;
                        f32 wallDistance;
                        CollisionPoly* sp7C;
                        CollisionPoly* sp78;
                        s32 sp74;
                        Vec3f sp68;
                        f32 sp64;
                        f32 sp60;
                        s32 temp3;

                        wallDistance = Math3D_UDistPlaneToPos(sp8C, sp88, sp84, wallPoly->dist, &playerProxy.world.pos);

                        spB0 = wallDistance + 10.0f;
                        sp68.x = playerProxy.world.pos.x - (spB0 * sp8C);
                        sp68.z = playerProxy.world.pos.z - (spB0 * sp84);
                        sp68.y = playerProxy.world.pos.y + this->ageProperties->unk_0C;

                        sp64 = BgCheck_EntityRaycastFloor1(&globalCtx->colCtx, &sp7C, &sp68);
                        wallHeight = sp64 - playerProxy.world.pos.y;
                        wallHeight = wallHeight;

                        if ((wallHeight < 18.0f) ||
                            BgCheck_EntityCheckCeiling(&globalCtx->colCtx, &sp60, &playerProxy.world.pos,
                                                       (sp64 - playerProxy.world.pos.y) + 20.0f, &sp78, &sp74,
                                                       &playerProxy)) {
                            wallHeight = 399.96002f;
                        } else {
                            D_80854798.y = (sp64 + 5.0f) - playerProxy.world.pos.y;

                            if (func_80839768(globalCtx, this, &D_80854798, &sp78, &sp74, &D_80858AA8) &&
                                (temp3 = playerProxy.wallYaw - Math_Atan2S(sp78->normal.z, sp78->normal.x),
                                 ABS(temp3) < 0x4000) &&
                                !func_80041E18(&globalCtx->colCtx, sp78, sp74)) {
                                wallHeight = 399.96002f;
                            } else if (func_80041DE4(&globalCtx->colCtx, wallPoly, playerProxy.wallBgId) == 0) {
                                sp68.y = sp64;
                                playerProxy.world.pos = sp68;
                                willGrabLedge = true;
                            }
                        }
                    }
                }
            }

            continue;
        }

        playerProxy.velocity.y = defaultYVelocity;

        if (fallInfo->willFall) {
            f32 landingSpotHeightDifference = playerProxy.world.pos.y - fallStartHeight;
            DynaPolyActor* floorActor = DynaPoly_GetActor(&globalCtx->colCtx, playerProxy.floorBgId);
            bool isSafeSpot = false;
            if (floorActor != NULL) {
                switch (floorActor->actor.id) {
                    case ACTOR_BG_YDAN_SP: // deku tree web
                        isSafeSpot = (landingSpotHeightDifference < -750.0f);
                        break;
                    case ACTOR_BG_YDAN_HASI: // deku tree platforms
                        isSafeSpot = (floorActor->actor.params != 1);
                    case ACTOR_BG_HIDAN_FSLIFT:
                    case ACTOR_OBJ_LIFT:
                        isSafeSpot = true;
                        break;
                    default:
                        break;
                }
            }

            if (landingSpotHeightDifference > -safeJumpHeightDiffThreshold || isSafeSpot) {
                fallInfo->willLandSafely = true;
            }
            break;
        } else if (i >= numWarnAheadFrames) {
            break;
        }
    }

    if (CVar_GetS32("gDebugEnabled", 0)) {
        DebugDisplay_AddObject(playerProxy.world.pos.x, playerProxy.world.pos.y + 26.0f, playerProxy.world.pos.z,
                               0x4000, 0, 0, 1.0f, 1.0f, 1.0f, (fallInfo->willFall && !fallInfo->willLandSafely) ? 255 : 0,
                               (!fallInfo->willFall || willGrabLedge) ? 255 : 0, (fallInfo->willLandSafely) ? 255 : 0, 255,
                               4,
                               globalCtx->state.gfxCtx);
    }
}

void Player_UpdateFallCue(Player* this, GlobalContext* globalCtx) {
    bool isPlayerOnFloor = this->actor.bgCheckFlags & 1;
    bool isPlayerAiming = !!func_8002DD78(this);
    bool isPlayerPushingBlock = this->stateFlags2 & PLAYER_STATE2_0;
    bool isPlayerClimbing = this->stateFlags1 & PLAYER_STATE1_21;
    bool isPlayerHanging = this->stateFlags1 & (PLAYER_STATE1_13 | PLAYER_STATE1_14);
    bool isPlayerRidingHorse = this->stateFlags1 & (PLAYER_STATE1_23);
    bool isPlayerSwimming = this->stateFlags1 & PLAYER_STATE1_27;

    struct FallCueInfo fallInfo = { 0 };

    if (isPlayerClimbing) {
        Player_UpdateFallCueClimbing(this, globalCtx, &fallInfo);
    } else if (!isPlayerAiming && !isPlayerRidingHorse && !isPlayerHanging &&
        !isPlayerSwimming) {
        Player_UpdateFallCueNormal(this, globalCtx, &fallInfo);
    }

    sFallCue.active = false;
    sFallWarningCue.active = false;

    if (fallInfo.willFall && (isPlayerOnFloor || isPlayerClimbing)) {
        if (fallInfo.willLandSafely) {
            sFallCue.sfxId = NA_SE_SY_MESSAGE_WOMAN;
        } else {
            if (fallInfo.willLandInWater) {
                sFallCue.sfxId = NA_SE_PL_JUMP_WATER2;
            } else {
                sFallCue.sfxId = NA_SE_IT_ARROW_STICK_HRAD;
            }
        }

        SkinMatrix_Vec3fMtxFMultXYZ(&globalCtx->viewProjectionMtxF, &fallInfo.fallPosition, &sFallWarningCue.position);
        Math_Vec3f_Diff(&sFallWarningCue.position, &this->actor.projectedPos, &sFallWarningCue.position);

        if (this->linearVelocity > 0.1f || isPlayerClimbing) {
            sFallCue.active = true;
        } else {
            /*sFallWarningCue.volume =
                LERP(0.1f, 1.0f, Math_Vec3f_DistXZ(&this->actor.world.pos, &sFallWarningCue.position) / 30.0f);*/
            sFallWarningCue.active = true;
        }
    }

    SoundCue_Update(&sFallCue, globalCtx);
    SoundCue_Update(&sFallWarningCue, globalCtx);
}

static struct WallCueHit {
    f32 distance;
    Vec3f vecHitPos;
    s32 bgId;
    CollisionPoly* colPoly;
};
static struct WallCueHit sWallCueHits[2];
static SoundCue sWallCues[2] = 
{
    { //walls
        false,
        { 0.0f, 0.0f, 0.0f },
        1.0f,
        1.0f,
        NA_SE_OC_OCARINA,
        0,
        20,
        0.1f,
        20,
        false,
        0,
        0
    },
    { //climbable walls
        false,
        { 0.0f, 0.0f, 0.0f },
        1.0f,
        1.0f,
        NA_SE_IT_SHIELD_CHARGE_LV1,
        0,
        40,
        0.0f,
        1,
        false,
        0,
        0
    }
};

void Player_UpdateWallCue(Player* this, GlobalContext* globalCtx) {
    Vec3f vecA;
    Vec3f vecB;
    Vec3f vecResult;
    CollisionPoly* outPoly;
    f32 dist = FLT_MAX;
    s32 bgId;

    bool isPlayerOnFloor = this->actor.bgCheckFlags & 1;
    bool isPlayerAiming = !!func_8002DD78(this);
    bool isPlayerPushingBlock = CHECK_FLAG_ALL(this->stateFlags2, PLAYER_STATE2_0 | PLAYER_STATE2_6 | PLAYER_STATE2_8);
    bool isPlayerClimbing = this->stateFlags1 & PLAYER_STATE1_21;
    bool isPlayerHanging = this->stateFlags1 & (PLAYER_STATE1_13 | PLAYER_STATE1_14);
    bool isPlayerRidingHorse = this->stateFlags1 & (PLAYER_STATE1_23);
    bool isPlayerInCrawlspace = this->stateFlags2 & PLAYER_STATE2_18;
    s16 prevYaw = this->actor.world.rot.y;

    const f32 climbRadarRange = 100.0f;
    const f32 normalRadarRange = 200.0f;
    const f32 horseRadarRange = 600.0f;
    f32 radarRange = normalRadarRange;

    const f32 wallCheckHeight = 26.0f; //z_player.c:9798

    struct WallCueHit* closestWall = &sWallCueHits[0];
    struct WallCueHit* closestClimbableWall = &sWallCueHits[1];

    if (!isPlayerHanging && !isPlayerPushingBlock && !isPlayerAiming && !isPlayerInCrawlspace) {
        if (isPlayerClimbing && this->actor.wallPoly != NULL) {
            const int radarSamples = 8;
            radarRange = climbRadarRange;

            MtxF rotationMtx;

            Vec3f vecUp;
            vecUp.x = 0.0f;
            vecUp.y = 1.0f;
            vecUp.z = 0.0f;

            Vec3f wallNormal;
            wallNormal.x = COLPOLY_GET_NORMAL(this->actor.wallPoly->normal.x);
            wallNormal.y = COLPOLY_GET_NORMAL(this->actor.wallPoly->normal.y);
            wallNormal.z = COLPOLY_GET_NORMAL(this->actor.wallPoly->normal.z);

            f32 minDist = FLT_MAX;
            Vec3f vecClosest;

            vecA = this->actor.world.pos;
            vecA.y += wallCheckHeight;

            closestWall->distance = FLT_MAX;
            closestClimbableWall->distance = FLT_MAX;

            s16 angle = 0;
            for (int i = 0; i < radarSamples; i++) {
                SkinMatrix_SetRotateAxis(&rotationMtx, angle, wallNormal.x,
                                         wallNormal.y, wallNormal.z);
                SkinMatrix_Vec3fMtxFMultXYZ(&rotationMtx, &vecUp, &vecB);
                Math_Vec3f_Scale(&vecB, radarRange);
                Math_Vec3f_Sum(&vecA, &vecB, &vecB);

                if (BgCheck_AnyLineTest3(&globalCtx->colCtx, &vecA, &vecB, &vecResult, &outPoly, false, true, true,
                                         1, &bgId)) {
                    dist = Math_Vec3f_DistXYZ(&vecA, &vecResult);
                    if (dist < closestWall->distance) {
                        closestWall->distance = dist;
                        closestWall->vecHitPos = vecResult;
                        closestWall->colPoly = outPoly;
                        closestWall->bgId = bgId;
                    }
                }

                angle += SHT_MAX / radarSamples * 2;
            }

            // if (closestWall->distance < radarRange) {
            //     Math_Vec3f_Diff(&closestWall->vecHitPos, &vecA, &vecB);
            //     f32 intoWall = Math3D_Vec3fMagnitude(&vecB);

            //     sWallCuePitch = LERP(0.1f, 0.5f, 0.5f); //(intoWall + 60.0f) / 120.0f);
            //     sWallCueVolume = LERP(0.1f, 1.2f, SQ((radarRange - minDist) / radarRange));

            //     SkinMatrix_Vec3fMtxFMultXYZ(&globalCtx->viewProjectionMtxF, &vecA, &vecB);
            //     SkinMatrix_Vec3fMtxFMultXYZ(&globalCtx->viewProjectionMtxF, &vecClosest, &vecA);
            //     Math_Vec3f_Diff(&vecA, &vecB, &sWallCuePosition);
            //     dist = minDist;
            // }
        } else {
            const int radarSamples = 16;
            const s32 numOffsetSubdivisions = 4;
            f32 sampleOffset = (float)(globalCtx->gameplayFrames % numOffsetSubdivisions) / numOffsetSubdivisions;
            radarRange = (isPlayerRidingHorse) ? horseRadarRange : normalRadarRange;

            vecA = this->actor.world.pos;
            vecA.y += wallCheckHeight;

            if (globalCtx->gameplayFrames % numOffsetSubdivisions == 0) {
                //only reset the hit after accumulating all of the offset angles
                closestWall->distance = FLT_MAX;
                closestClimbableWall->distance = FLT_MAX;
            }

            for (int i = 0; i < radarSamples; i++) {
                f32 angle = 2.0f * M_PI * ((float)i + sampleOffset) / radarSamples;
                vecB.x = Math_CosF(angle);
                vecB.y = 0.0f;
                vecB.z = Math_SinF(angle);
                Math_Vec3f_Scale(&vecB, radarRange);
                Math_Vec3f_Sum(&vecA, &vecB, &vecB);

                if (BgCheck_AnyLineTest3(&globalCtx->colCtx, &vecA, &vecB, &vecResult, &outPoly, true, false, false, 1,
                                         &bgId)) {
                    dist = Math_Vec3f_DistXZ(&vecA, &vecResult);

                    if (dist < closestWall->distance) {
                        closestWall->distance = dist;
                        closestWall->vecHitPos = vecResult;
                        closestWall->colPoly = outPoly;
                        closestWall->bgId = bgId;
                    }

                    if (dist < closestClimbableWall->distance) {
                        if (func_80041DB8(&globalCtx->colCtx, outPoly, bgId) & (8 | 2)) {
                            closestClimbableWall->distance = dist;
                            closestClimbableWall->vecHitPos = vecResult;
                            closestClimbableWall->colPoly = outPoly;
                            closestClimbableWall->bgId = bgId;
                        } else if (LINK_IS_ADULT && (func_80041DB8(&globalCtx->colCtx, outPoly, bgId) & 0x30)) {
                            //crawlspace possibly
                            closestClimbableWall->distance = dist;
                            closestClimbableWall->vecHitPos = vecResult;
                            closestClimbableWall->colPoly = outPoly;
                            closestClimbableWall->bgId = bgId;
                        } else {
                            Vec3f wallNormal;
                            wallNormal.x = COLPOLY_GET_NORMAL(outPoly->normal.x);
                            wallNormal.y = COLPOLY_GET_NORMAL(outPoly->normal.y);
                            wallNormal.z = COLPOLY_GET_NORMAL(outPoly->normal.z);
                            f32 wallDistance = Math3D_UDistPlaneToPos(wallNormal.x, wallNormal.y, wallNormal.z,
                                                                      outPoly->dist,
                                                                      &this->actor.world.pos);
                            f32 testDistance = wallDistance + 10.0f;
                            Vec3f vecTestPoint;
                            vecTestPoint.x = this->actor.world.pos.x - (testDistance * wallNormal.x);
                            vecTestPoint.z = this->actor.world.pos.z - (testDistance * wallNormal.z);
                            vecTestPoint.y = this->actor.world.pos.y + this->ageProperties->unk_0C;

                            CollisionPoly* floorPoly;
                            f32 floorHeight =
                                BgCheck_EntityRaycastFloor1(&globalCtx->colCtx, &floorPoly, &vecTestPoint);
                            f32 wallHeight = floorHeight - this->actor.world.pos.y;
                            if (wallHeight > 18.0f) { // z_player.c:9962
                                if ((func_80041DE4(&globalCtx->colCtx, outPoly, bgId) == 0) &&
                                    this->ageProperties->unk_1C <= wallHeight) {
                                    if (ABS(floorPoly->normal.y) > 28000) {
                                        closestClimbableWall->distance = dist;
                                        closestClimbableWall->vecHitPos = vecResult;
                                        closestClimbableWall->colPoly = outPoly;
                                        closestClimbableWall->bgId = bgId;
                                    }
                                }
                            }
                        }
                    }
                }
            }

            // if (closestWall.distance < radarRange) {
            //     Vec3f vecTestDir;
            //     if (false) {
            //         f32 stickRadius = this->unk_A7C;
            //         s16 stickAngle = this->unk_A80;
            //         Camera* currentCamera = GET_ACTIVE_CAM(globalCtx);
            //         stickAngle = this->currentYaw; // stickAngle + currentCamera->camDir.y;
            //         vecTestDir.x = Math_SinS(stickAngle);
            //         vecTestDir.y = 0.0f;
            //         vecTestDir.z = Math_CosS(stickAngle);
            //         Math_Vec3f_Scale(&vecTestDir, -stickRadius);
            //     } else {
            //         if (isPlayerRidingHorse && this->rideActor != NULL) {
            //             vecTestDir = this->rideActor->velocity;
            //         } else {
            //             vecTestDir = this->actor.velocity;
            //         }
            //         vecTestDir.y = 0.0f;
            //         Math_Vec3f_Scale(&vecTestDir, -1.0);
            //     }

            //     // Vec3f wallNormal;
            //     // wallNormal.x = COLPOLY_GET_NORMAL(closestWall.colPoly->normal.x);
            //     // wallNormal.y = COLPOLY_GET_NORMAL(closestWall.colPoly->normal.y);
            //     // wallNormal.z = COLPOLY_GET_NORMAL(closestWall.colPoly->normal.z);

            //     // // Math_Vec3f_Scale(&intendedMove, 20.0f);

            //     // f32 intoWall = DOTXYZ(wallNormal, vecTestDir) / 60.0f;
            //     // sWallCuePitch = LERP(0.05f, 0.8f, (intoWall + 1.0f) / 2.0f);
            //     // sWallCueVolume = LERP(0.1f, 0.6f, SQ((radarRange - closestWall.distance) / radarRange));
            // }
        }
    }

    for (int i = 0; i < 2; i++) {
        struct WallCueHit* hit = &sWallCueHits[i];
        SoundCue* cue = &sWallCues[i];

        if (hit->distance < radarRange) {
            cue->pitch = LERP(0.1f, 0.5f, 0.5f); //(intoWall + 60.0f) / 120.0f);
            cue->volume = LERP(0.1f, 0.5f, SQ((radarRange - hit->distance) / radarRange));

            SkinMatrix_Vec3fMtxFMultXYZ(&globalCtx->viewProjectionMtxF, &hit->vecHitPos, &cue->position);
            cue->active = true;
        } else {
            cue->active = false;
        }

        SoundCue_Update(cue, globalCtx);
    }
}

void Player_UpdateSpatialCues(Player* this, GlobalContext* globalCtx) {
    if (Player_InBlockingCsMode(globalCtx, this)) {
        return;
    }

    Player_UpdateFallCue(this, globalCtx);
    Player_UpdateWallCue(this, globalCtx);
}

#define AIMCUE_COLLIDER_COUNT 5
static ColliderQuad sAimCueCollider[AIMCUE_COLLIDER_COUNT];
static s32 sAimSurfaceHookshotable;
static s32 sAimLastHookshotableState;

static SoundCue sTargetCues[3] =
{
    { //ranged aiming
        false,
        { 0.0f, 0.0f, 0.0f },
        1.0f,
        1.0f,
        NA_SE_EN_BIMOS_LAZER,
        0,
        20,
        0.0f,
        1,
        false,
        0,
        0
    },
    { //position searching
        false,
        { 0.0f, 0.0f, 0.0f },
        1.0f,
        1.0f,
        NA_SE_PL_SPIRAL_HEAL_BEAM,
        0,
        20,
        0.0f,
        1,
        false,
        0,
        0
    },
    { //entrances
        false,
        { 0.0f, 0.0f, 0.0f },
        1.0f,
        1.0f,
        NA_SE_EV_GOTO_HEAVEN,
        0,
        80,
        0.0f,
        1,
        false,
        0,
        0
    }
};

static ColliderQuadInit sSensingColliderInit = {
    {
        COLTYPE_NONE,
        AT_ON | AT_TYPE_PLAYER,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_2 | OC2_TYPE_1,
        COLSHAPE_QUAD,
    },
    {
        ELEMTYPE_SENSING,
        { 0xFFFFFFFF, 0x02, 0x00 },
        { 0xFFFFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_NEAREST | TOUCH_SFX_NONE,
        BUMP_NONE,
        OCELEM_NONE,
    },
    { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } },
};

void Player_InitAimCueCollision(Player* this, GlobalContext* globalCtx) {
    for (int i = 0; i < AIMCUE_COLLIDER_COUNT; i++) {
        Collider_InitQuad(globalCtx, &sAimCueCollider[i]);
        Collider_SetQuad(globalCtx, &sAimCueCollider[i], NULL, &sSensingColliderInit);
    }
}

Actor* Player_UpdateStickTargetCue(Player* this, GlobalContext* globalCtx) {
    bool isStickBurning = (this->unk_860 != 0);
    Vec3f vecStickTipPos = this->swordInfo[0].tip;

    Actor* closestActor = NULL;
    const f32 maxDist = 1500.0f;
    f32 closestActorXYZDistSq = SQ(maxDist);

    ActorContext* actorCtx = &globalCtx->actorCtx;
    ActorListEntry* actorListEntry;
    actorListEntry = &actorCtx->actorLists[0];
    Actor* actor;

    for (int i = 0; i < ARRAY_COUNT(actorCtx->actorLists); i++, actorListEntry++) {
        actor = actorListEntry->head;

        while (actor != NULL) {
            if (actor->xyzDistToPlayerSq < closestActorXYZDistSq &&
                ABS(actor->yDistToPlayer) < 20.0f) {
                if (actor->id == ACTOR_OBJ_SYOKUDAI) {
                    ObjSyokudai* torchActor = (ObjSyokudai*)actor;
                    if ((isStickBurning && torchActor->litTimer == 0) ||
                        (!isStickBurning && torchActor->litTimer != 0)) {
                        closestActor = actor;
                        closestActorXYZDistSq = actor->xyzDistToPlayerSq;
                    }
                } else if (actor->id == ACTOR_BG_YDAN_SP && isStickBurning) {
                    closestActor = actor;
                    closestActorXYZDistSq = actor->xyzDistToPlayerSq;
                }
            }

            actor = actor->next;
        }
    }

    
    if (closestActor != NULL) {
        SoundCue* soundCue = &sTargetCues[1];
        f32 closestActorDist = Math_Vec3f_DistXYZ(&closestActor->world.pos, &vecStickTipPos);
        //soundCue->volume = LERP(0.1f, 1.5f, SQ(1.0f - closestActorDist / maxDist));
        soundCue->pitch = 0.8;
        Math_Vec3f_Copy(&soundCue->position, &closestActor->projectedPos);
        soundCue->active = true;
    }

    return closestActor;
}

Actor* Player_UpdateEntranceTargetCue(Player* this, GlobalContext* globalCtx) {
    Actor* closestActor = NULL;
    const f32 maxDist = 250.0f;
    f32 closestActorXYZDistSq = SQ(maxDist);

    ActorContext* actorCtx = &globalCtx->actorCtx;
    ActorListEntry* actorListEntry;
    actorListEntry = &actorCtx->actorLists[0];
    Actor* actor;

    for (int i = 0; i < ARRAY_COUNT(actorCtx->actorLists); i++, actorListEntry++) {
        actor = actorListEntry->head;

        while (actor != NULL) {
            if (actor->id != ACTOR_PLAYER &&
                ((actor->category == ACTORCAT_DOOR && actor->id != ACTOR_EN_HOLL) ||
                 actor->id == ACTOR_SCENE_EXIT) &&
                actor->xyzDistToPlayerSq < closestActorXYZDistSq) {

                closestActor = actor;
                closestActorXYZDistSq = actor->xyzDistToPlayerSq;
            }

            actor = actor->next;
        }
    }

    if (closestActor != NULL) {
        SoundCue* soundCue = &sTargetCues[2];
        f32 closestActorDist = sqrtf(closestActorXYZDistSq);
        soundCue->volume = LERP(0.3f, 1.2f, SQ(1.0f - closestActorDist / maxDist));
        if (closestActorDist < 30.0f) {
            soundCue->pitch = 1.2;
        } else {
            soundCue->pitch = 0.5;
        }
        Math_Vec3f_Copy(&soundCue->position, &closestActor->projectedPos);
        soundCue->active = true;
    }

    return closestActor;
}

Actor* Player_UpdateSwimTargetCue(Player* this, GlobalContext* globalCtx) {
    Actor* closestActor = NULL;
    const f32 maxDist = 500.0f;
    f32 closestActorXZDist = maxDist;

    ActorContext* actorCtx = &globalCtx->actorCtx;
    ActorListEntry* actorListEntry;
    actorListEntry = &actorCtx->actorLists[0];
    Actor* actor;

    for (int i = 0; i < ARRAY_COUNT(actorCtx->actorLists); i++, actorListEntry++) {
        actor = actorListEntry->head;

        while (actor != NULL) {
            if (actor->id != ACTOR_PLAYER &&
                actor->category != ACTORCAT_NPC &&
                actor->world.pos.y < this->actor.world.pos.y &&
                actor->xzDistToPlayer < closestActorXZDist) {

                closestActor = actor;
                closestActorXZDist = actor->xzDistToPlayer;
            }

            actor = actor->next;
        }
    }

    if (closestActor != NULL) {
        SoundCue* soundCue = &sTargetCues[1];
        soundCue->volume = LERP(0.1f, 1.5f, SQ(1.0f - closestActorXZDist / maxDist));
        u16 soundEffect;
        if (closestActorXZDist < 28.0f) {
            soundCue->pitch = 1.2;
        } else {
            soundCue->pitch = 0.8;
        }
        Math_Vec3f_Copy(&soundCue->position, &closestActor->projectedPos);
        soundCue->active = true;
    }

    return closestActor;
}

Actor* Player_UpdateAimTargetCue(Player* this, GlobalContext* globalCtx) {
    Actor* hitActor = NULL;
    SoundCue* soundCue = &sTargetCues[0];

    for (int i = 0; i < AIMCUE_COLLIDER_COUNT; i++) {
        if (sAimCueCollider[i].base.atFlags & AT_HIT) {
            sAimCueCollider[i].base.atFlags &= ~AC_HIT;

            if (hitActor == NULL && sAimCueCollider[i].base.at != NULL) {
                hitActor = sAimCueCollider[i].base.at;
            } else {
                continue;
            }

            if (i != 0 && (globalCtx->gameplayFrames % 1) != 0) {
                continue;
            }

            if (i == 0) { //target centered
                soundCue->pitch = 1.3;
            } else {
                soundCue->pitch = 0.8;
            }

            Math_Vec3f_Copy(&soundCue->position, &hitActor->projectedPos);

            if (hitActor->category == ACTORCAT_ENEMY || hitActor->category == ACTORCAT_BOSS) {
                soundCue->active = true;
            } else if (hitActor->category == ACTORCAT_SWITCH) {
                soundCue->active = true;
            } else if (hitActor->category == ACTORCAT_NPC) {
                soundCue->active = true;
            } else if (hitActor->category == ACTORCAT_PROP &&
                           (hitActor->id == ACTOR_EN_DNT_NOMAL && hitActor->params == 0) ||
                       hitActor->id == ACTOR_EN_G_SWITCH ||
                       hitActor->id == ACTOR_OBJ_SYOKUDAI ||
                       hitActor->id == ACTOR_BG_YDAN_MARUTA) {
                // lost woods slingshot target, shooting gallery rupees
                soundCue->active = true;
            }
        }
    }

    if (sAimSurfaceHookshotable != sAimLastHookshotableState) {
        if (sAimSurfaceHookshotable) {
            Audio_PlaySoundGeneral(NA_SE_SY_LOCK_ON_HUMAN, &D_801333D4, 4, &D_801333E0, &D_801333E0, &D_801333E8);
        } else {
            Audio_PlaySoundGeneral(NA_SE_SY_LOCK_OFF, &D_801333D4, 4, &D_801333E0, &D_801333E0, &D_801333E8);
        }
        sAimLastHookshotableState = sAimSurfaceHookshotable;
    }

    return hitActor;
}

void Player_UpdateTargetCues(Player* this, GlobalContext* globalCtx) {
    Actor* hitActor = NULL;

    for (int i = 0; i < 3; i++) {
        sTargetCues[i].active = false;
    }

    if (Player_InBlockingCsMode(globalCtx, this)) {
        return;
    }

    Player_UpdateEntranceTargetCue(this, globalCtx);

    bool isPlayerSwimming = this->stateFlags1 & PLAYER_STATE1_27;
    bool isPlayerOnFloor = this->actor.bgCheckFlags & 1;
    bool isPlayerInFirstPersonMode = this->stateFlags1 & PLAYER_STATE1_20;

    bool isPlayerHoldingStick = (this->heldItemActionParam == PLAYER_AP_STICK);
    bool isPlayerHoldingBurningStick = isPlayerHoldingStick && (this->unk_860 != 0);

    bool isPlayerAiming = !!func_8002DD78(this);

    if (isPlayerSwimming && !isPlayerOnFloor && !isPlayerInFirstPersonMode) {
        Player_UpdateSwimTargetCue(this, globalCtx);
    } else if (isPlayerOnFloor && isPlayerHoldingStick) {
        Player_UpdateStickTargetCue(this, globalCtx);
    } else if (isPlayerAiming) {
        Player_UpdateAimTargetCue(this, globalCtx);
    }

    for (int i = 0; i < 3; i++) {
        SoundCue_Update(&sTargetCues[i], globalCtx);
    }
}

void Player_ComputeHandAimCue(Player* this, GlobalContext* globalCtx, s32 limbIndex) {
    if (this->heldItemId == 0) {
        return;
    }

    bool isHoldingHookshotType = Player_HoldsHookshot(this);

    if (!isHoldingHookshotType && limbIndex != PLAYER_LIMB_L_HAND ||
        isHoldingHookshotType && limbIndex != PLAYER_LIMB_R_HAND) {
        return;
    }

    sAimSurfaceHookshotable = 0;
    
    bool isAimingCharged = (this->stateFlags1 & 0x200) && (this->unk_834 <= 10) && (this->unk_860 >= 0);
    bool isPlayerAiming = !!func_8002DD78(this);
    if (!isPlayerAiming || !(isAimingCharged || isHoldingHookshotType)) {
        return;
    }

    CollisionPoly* polyResult;
    s32 bgId;

    Matrix_Push();

    f32 distance;
    Vec3f vecCenter;
    Vec3f vecCenterFar;
    Vec3f vecA;
    Vec3f vecB;
    Vec3f vecC;
    Vec3f vecD;
    Vec3f vecResult;
    Vec3f vecZero = { 0.0f, 0.0f, 0.0f };
    Vec3f vecLeft = { 0.0f, 50.0f, 0.0f };
    Vec3f vecRight = { 0.0f, -50.0f, 0.0f };

    if (isHoldingHookshotType) {
        if (this->heldItemActionParam == PLAYER_AP_HOOKSHOT) {
            distance = 38600.0f;
        } else {
            distance = 77600.0f;
        }
        Matrix_Translate(0.0f, 150.0f, -100.0f, MTXMODE_APPLY);
    } else {
        distance = 200000.0f;
        Matrix_Translate(-550.0f, -50.0f, -100.0f, MTXMODE_APPLY);
    }

    Matrix_MultVec3f(&vecZero, &vecCenter);
    vecZero.z = distance;
    Matrix_MultVec3f(&vecZero, &vecCenterFar);

    if (BgCheck_AnyLineTest3(&globalCtx->colCtx, &vecCenter, &vecCenterFar, &vecResult, &polyResult, 1, 1, 1, 1,
                             &bgId)) {
        sAimSurfaceHookshotable =
            isHoldingHookshotType && SurfaceType_IsHookshotSurface(&globalCtx->colCtx, polyResult, bgId);
        distance *= Math_Vec3f_DistXYZ(&vecCenter, &vecResult) / Math_Vec3f_DistXYZ(&vecCenter, &vecCenterFar);
    }

    if (!isAimingCharged) {
        Matrix_Pop();
        return;
    }

    Matrix_MultVec3f(&vecLeft, &vecA);
    Matrix_MultVec3f(&vecRight, &vecB);

    vecLeft.z = distance;
    vecRight.z = distance;

    Matrix_MultVec3f(&vecLeft, &vecC);
    Matrix_MultVec3f(&vecRight, &vecD);

    Collider_SetQuadVertices(&sAimCueCollider[0], &vecA, &vecB, &vecC, &vecD);
    CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &sAimCueCollider[0].base);

    Matrix_Scale(500.0f, 500.0f, 1.0f, MTXMODE_APPLY);

    f32 rotateOffset = (globalCtx->gameplayFrames % 4) * M_PI / 16;
    Matrix_RotateZ(rotateOffset, MTXMODE_APPLY);

    for (int i = 1; i < AIMCUE_COLLIDER_COUNT; i++) {
        if (i > 1) {
            Matrix_RotateZ(M_PI / 4, MTXMODE_APPLY);
        }

        vecLeft.z = 0;
        vecLeft.y = 0.5;
        vecRight.z = 0;
        vecRight.y = -0.5;

        Matrix_MultVec3f(&vecLeft, &vecA);
        Matrix_MultVec3f(&vecRight, &vecB);

        vecLeft.z = distance * 1.2;
        vecLeft.y = sqrtf(distance) * 0.2f;
        vecRight.z = distance * 1.2;
        vecRight.y = sqrtf(distance) * -0.2f;

        Matrix_MultVec3f(&vecLeft, &vecC);
        Matrix_MultVec3f(&vecRight, &vecD);

        Collider_SetQuadVertices(&sAimCueCollider[i], &vecA, &vecB, &vecC, &vecD);
        CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &sAimCueCollider[i].base);
    }

    Matrix_Pop();
}

union VisibleItem {
    Actor* actor;
    u32 polyFlags;
};
static union VisibleItem sTopVisibleItems[10];
static union VisibleItem sPrevFocusedVisibleItem;
static s32 sFocusedVisibleItemIdx;
static bool sFocusedItemBeaconActive;

extern Actor* gActorIdTable[ACTOR_NUMBER_MAX];
extern int fbSceneInfo;
static u8* sceneInfoFramebuffer = NULL;
static s32 sceneInfoFbWidth;
static s32 sceneInfoFbHeight;
static bool sFirstPersonStart;
static bool sSceneInfoContinuous;

//TODO: temp, replace with SoundCue
static f32 sBeaconFreq;

static SoundCue sBeaconCue = 
{
    false,
    { 0.0f, 0.0f, 0.0f },
    1.0f,
    1.0f,
    NA_SE_EV_SHIP_BELL,
    0,
    20,
    0.0f,
    20,
    false,
    0,
    0
};

void Player_UpdateVisionCue(Player* this, GlobalContext* globalCtx, Input* input) {
    bool isPlayerInFirstPersonMode = this->stateFlags1 & PLAYER_STATE1_20;

    if (isPlayerInFirstPersonMode && !sFirstPersonStart) {
        sFirstPersonStart = true;
        sSceneInfoContinuous = true;
    } else if (!isPlayerInFirstPersonMode && sFirstPersonStart) {
        sFirstPersonStart = false;
        sSceneInfoContinuous = false;
    }

    bool needsUpdate = false;

    if (CHECK_BTN_ALL(input->press.button, BTN_DUP)) {
        sSceneInfoContinuous = false;
        sPrevFocusedVisibleItem.actor = NULL;
        needsUpdate = true;
    }
    if (CHECK_BTN_ALL(input->press.button, BTN_DDOWN)) {
        sSceneInfoContinuous = false;
        if (!sFocusedItemBeaconActive && sPrevFocusedVisibleItem.actor != NULL) {
            sFocusedItemBeaconActive = true;
        } else {
            sFocusedItemBeaconActive = false;
        }
    }
    if (CHECK_BTN_ALL(input->press.button, BTN_DLEFT)) {
        sSceneInfoContinuous = false;
        if (sFocusedVisibleItemIdx == 0) {
            //Audio_PlaySoundGeneral(NA_SE_IT_SWORD_IMPACT, &D_801333D4, 4, &D_801333E0, &D_801333E0, &D_801333E8);
        } else {
            Audio_PlaySoundGeneral(NA_SE_SY_CURSOR, &D_801333D4, 4, &D_801333E0, &D_801333E0, &D_801333E8);
            sFocusedVisibleItemIdx--;
        }
    }
    if (CHECK_BTN_ALL(input->press.button, BTN_DRIGHT)) {
        sSceneInfoContinuous = false;
        if (sFocusedVisibleItemIdx == ARRAY_COUNT(sTopVisibleItems) - 1 ||
            sTopVisibleItems[sFocusedVisibleItemIdx + 1].actor == NULL) {
            //Audio_PlaySoundGeneral(NA_SE_IT_SWORD_IMPACT, &D_801333D4, 4, &D_801333E0, &D_801333E0, &D_801333E8);
        }
        else {
            Audio_PlaySoundGeneral(NA_SE_SY_CURSOR, &D_801333D4, 4, &D_801333E0, &D_801333E0, &D_801333E8);
            sFocusedVisibleItemIdx++;
        }
    }

    needsUpdate = needsUpdate || (sSceneInfoContinuous && (globalCtx->state.frames % 10 == 0));

    if (needsUpdate) {
        sFocusedVisibleItemIdx = 0;
        memset(&sTopVisibleItems, 0, sizeof(sTopVisibleItems));

        if (sceneInfoFbWidth != OTRGetFramebufferWidth(fbSceneInfo) ||
            sceneInfoFbHeight != OTRGetFramebufferHeight(fbSceneInfo)) {
            if (sceneInfoFramebuffer != NULL) {
                free(sceneInfoFramebuffer);
            }

            sceneInfoFbWidth = OTRGetFramebufferWidth(fbSceneInfo);
            sceneInfoFbHeight = OTRGetFramebufferHeight(fbSceneInfo);
            sceneInfoFramebuffer = malloc(sceneInfoFbWidth * sceneInfoFbHeight * 4);
        }
        OTRReadFramebufferPixels(fbSceneInfo, 0, 0, sceneInfoFbWidth, sceneInfoFbHeight, 0,
                                    sceneInfoFramebuffer);

        struct VisibleId {
            u32 id;
            u32 pixelCount;
        };
        struct VisibleId topIds[256] = {0};

        u32 width = sceneInfoFbWidth;
        u32 height = sceneInfoFbHeight;
        u32 x;
        u32 y;
        u32 offset;
        u32 id;

        u32 widthMargin = (sSceneInfoContinuous) ? width / 4 : 0;
        u32 heightMargin = (sSceneInfoContinuous) ? height / 4 : 0;
        for (x = widthMargin; x < width - widthMargin; x++) {
            for (y = heightMargin; y < height - heightMargin; y++) {
                offset = (x + y * width) * 4;
                id = (sceneInfoFramebuffer[offset + 0] << 16) |
                     (sceneInfoFramebuffer[offset + 1] << 8) |
                     sceneInfoFramebuffer[offset + 2];

                if (id == 0)
                    continue;

                s32 itemIndex = 0;
                u32 currItemCount = 0;
                while (itemIndex < 256) {
                    if (topIds[itemIndex].id == id) {
                        topIds[itemIndex].pixelCount++;
                        currItemCount = topIds[itemIndex].pixelCount;
                        break;
                    } else if (topIds[itemIndex].id == 0) {
                        topIds[itemIndex].id = id;
                        topIds[itemIndex].pixelCount = 1;
                        currItemCount = topIds[itemIndex].pixelCount;
                        break;
                    }
                    ++itemIndex;
                }
                while (--itemIndex >= 0) {
                    if (topIds[itemIndex].pixelCount > currItemCount) {
                        break;
                    }
                    //swap
                    struct VisibleId tmp = topIds[itemIndex];
                    topIds[itemIndex] = topIds[itemIndex + 1];
                    topIds[itemIndex + 1] = tmp;
                }
            }
        }

        s32 topItemIndex = 0;
        
        for (int i = 0; i < ARRAY_COUNT(topIds); i++) {
            if (topIds[i].id == 0)
                break;

            u32 itemType = topIds[i].id & 0xFF0000;
            if (itemType == 0x500000) {
                Actor* actor = gActorIdTable[(topIds[i].id & 0xFF) - 1];
                if (actor->id == ACTOR_PLAYER || actor->id == ACTOR_EN_ELF)
                    continue;
                sTopVisibleItems[topItemIndex].actor = actor;
                // topItems[topItemIndex].polyFlags = 0;
            } else if (itemType == 0xA00000) {
                // topItems[topItemIndex].actor = NULL;
                sTopVisibleItems[topItemIndex].polyFlags = topIds[i].id & 0xFF;
            }

            if (++topItemIndex == ARRAY_COUNT(sTopVisibleItems)) {
                break;
            }
        }
    }

    union VisibleItem focusedVisibleItem = sTopVisibleItems[sFocusedVisibleItemIdx];

    sBeaconCue.active = false;
    if (sFocusedItemBeaconActive && ((focusedVisibleItem.polyFlags & 0xFFFFFF00) != 0)) {
        sBeaconCue.active = true;
        sBeaconCue.pitch = LERP(0.08f, 0.2f, 1.0f - MAX(0.1f, MIN(1.0f, focusedVisibleItem.actor->xyzDistToPlayerSq / SQ(500.0f))));
        Math_Vec3f_Diff(&focusedVisibleItem.actor->projectedPos, &this->actor.projectedPos, &sBeaconCue.position);
    }
    SoundCue_Update(&sBeaconCue, globalCtx);

    if (focusedVisibleItem.actor != NULL &&
        focusedVisibleItem.actor != sPrevFocusedVisibleItem.actor) {

        u8 announceStr[256];
        s32 announceStrLength = 0;
        announceStr[0] = '\0';
        u8 arg[48];
        arg[0] = '\0';

        u32 textId;
        if ((focusedVisibleItem.polyFlags & 0xFFFFFF00) == 0) {
            textId = 0x900 + focusedVisibleItem.polyFlags;
        } else {
            if (focusedVisibleItem.actor->id == ACTOR_SCENE_EXIT) {
                u16 exitId = focusedVisibleItem.actor->params;
                u16 sceneId = gEntranceTable[globalCtx->setupExitList[exitId - 1]].scene;
                size_t result = sprintf(arg, "%s", OTRGetAccessibilityText(0x0300 + sceneId));
                ASSERT(result < sizeof(arg), "Text arg buffer exceeded", __FILE__, __LINE__);

                textId = 0x1000 + focusedVisibleItem.actor->id;
            } else {
                textId = (focusedVisibleItem.actor->params << 16) | (0x1000 + focusedVisibleItem.actor->id);
            }
        }
        char* accessibilityText = OTRGetAccessibilityText(textId, arg);
        if (accessibilityText != NULL) {
            size_t result = sprintf(announceStr + announceStrLength, "%s", accessibilityText);
            ASSERT(result < sizeof(announceStr) - announceStrLength, "Text str buffer exceeded", __FILE__, __LINE__);
            announceStrLength += result;
        }

        OTRTextToSpeechCallback(announceStr);

        sPrevFocusedVisibleItem.actor = focusedVisibleItem.actor;
    }
}

void func_80090D20(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, void* thisx) {
    Player* this = (Player*)thisx;

    if (*dList != NULL) {
        Matrix_MultVec3f(&D_8012602C, D_80160000);
    }

    if (limbIndex == PLAYER_LIMB_L_HAND) {
        MtxF sp14C;
        Actor* hookedActor;

        Math_Vec3f_Copy(&this->leftHandPos, D_80160000);

        if (this->itemActionParam == PLAYER_AP_STICK) {
            Vec3f sp124[3];

            OPEN_DISPS(globalCtx->state.gfxCtx, "../z_player_lib.c", 2633);

            if (this->actor.scale.y >= 0.0f) {
                D_80126080.x = this->unk_85C * 5000.0f;
                func_80090A28(this, sp124);
                if (this->swordState != 0) {
                    func_800906D4(globalCtx, this, sp124);
                } else {
                    Math_Vec3f_Copy(&this->swordInfo[0].tip, &sp124[0]);
                }
            }

            Matrix_Translate(-428.26f, 267.2f, -33.82f, MTXMODE_APPLY);
            Matrix_RotateZYX(-0x8000, 0, 0x4000, MTXMODE_APPLY);
            Matrix_Scale(1.0f, this->unk_85C, 1.0f, MTXMODE_APPLY);

            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_player_lib.c", 2653),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_OPA_DISP++, gLinkChildLinkDekuStickDL);

            CLOSE_DISPS(globalCtx->state.gfxCtx, "../z_player_lib.c", 2656);
        } else if ((this->actor.scale.y >= 0.0f) && (this->swordState != 0)) {
            Vec3f spE4[3];

            if (Player_HoldsBrokenKnife(this)) {
                D_80126080.x = 1500.0f;
            } else {
                D_80126080.x = sSwordLengths[Player_GetSwordHeld(this)];
            }

            func_80090A28(this, spE4);
            func_800906D4(globalCtx, this, spE4);
        } else if ((*dList != NULL) && (this->leftHandType == 7)) {
            Color_RGB8* bottleColor = &sBottleColors[Player_ActionToBottle(this, this->itemActionParam)];

            OPEN_DISPS(globalCtx->state.gfxCtx, "../z_player_lib.c", 2710);

            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_player_lib.c", 2712),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gDPSetEnvColor(POLY_XLU_DISP++, bottleColor->r, bottleColor->g, bottleColor->b, 0);
            gSPDisplayList(POLY_XLU_DISP++, sBottleDLists[((void)0, gSaveContext.linkAge)]);

            CLOSE_DISPS(globalCtx->state.gfxCtx, "../z_player_lib.c", 2717);
        }

        if (this->actor.scale.y >= 0.0f) {
            if (!Player_HoldsHookshot(this) && ((hookedActor = this->heldActor) != NULL)) {
                if (this->stateFlags1 & 0x200) {
                    Matrix_MultVec3f(&D_80126128, &hookedActor->world.pos);
                    Matrix_RotateZYX(0x69E8, -0x5708, 0x458E, MTXMODE_APPLY);
                    Matrix_Get(&sp14C);
                    Matrix_MtxFToYXZRotS(&sp14C, &hookedActor->world.rot, 0);
                    hookedActor->shape.rot = hookedActor->world.rot;
                } else if (this->stateFlags1 & 0x800) {
                    Vec3s spB8;

                    Matrix_Get(&sp14C);
                    Matrix_MtxFToYXZRotS(&sp14C, &spB8, 0);

                    if (hookedActor->flags & ACTOR_FLAG_17) {
                        hookedActor->world.rot.x = hookedActor->shape.rot.x = spB8.x - this->unk_3BC.x;
                    } else {
                        hookedActor->world.rot.y = hookedActor->shape.rot.y = this->actor.shape.rot.y + this->unk_3BC.y;
                    }
                }
            } else {
                Matrix_Get(&this->mf_9E0);
                Matrix_MtxFToYXZRotS(&this->mf_9E0, &this->unk_3BC, 0);
            }
        }
    } else if (limbIndex == PLAYER_LIMB_R_HAND) {
        Actor* heldActor = this->heldActor;

        if (this->rightHandType == 0xFF) {
            Matrix_Get(&this->shieldMf);
        } else if ((this->rightHandType == 11) || (this->rightHandType == 12)) {
            BowStringData* stringData = &sBowStringData[gSaveContext.linkAge];

            OPEN_DISPS(globalCtx->state.gfxCtx, "../z_player_lib.c", 2783);

            Matrix_Push();
            Matrix_Translate(stringData->pos.x, stringData->pos.y, stringData->pos.z, MTXMODE_APPLY);

            if ((this->stateFlags1 & 0x200) && (this->unk_860 >= 0) && (this->unk_834 <= 10)) {
                Vec3f sp90;
                f32 distXYZ;

                Matrix_MultVec3f(&D_8012602C, &sp90);
                distXYZ = Math_Vec3f_DistXYZ(D_80160000, &sp90);

                this->unk_858 = distXYZ - 3.0f;
                if (distXYZ < 3.0f) {
                    this->unk_858 = 0.0f;
                } else {
                    this->unk_858 *= 1.6f;
                    if (this->unk_858 > 1.0f) {
                        this->unk_858 = 1.0f;
                    }
                }

                this->unk_85C = -0.5f;
            }

            Matrix_Scale(1.0f, this->unk_858, 1.0f, MTXMODE_APPLY);

            if (!LINK_IS_ADULT) {
                Matrix_RotateZ(this->unk_858 * -0.2f, MTXMODE_APPLY);
            }

            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_player_lib.c", 2804),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, stringData->dList);

            Matrix_Pop();

            CLOSE_DISPS(globalCtx->state.gfxCtx, "../z_player_lib.c", 2809);
        } else if ((this->actor.scale.y >= 0.0f) && (this->rightHandType == 10)) {
            Matrix_Get(&this->shieldMf);
            func_80090604(globalCtx, this, &this->shieldQuad, D_80126154);
        }

        if (this->actor.scale.y >= 0.0f) {
            if ((this->heldItemActionParam == PLAYER_AP_HOOKSHOT) ||
                (this->heldItemActionParam == PLAYER_AP_LONGSHOT)) {
                Matrix_MultVec3f(&D_80126184, &this->unk_3C8);

                if (heldActor != NULL) {
                    MtxF sp44;
                    s32 pad;

                    Matrix_MultVec3f(&D_80126190, &heldActor->world.pos);
                    Matrix_RotateZYX(0, -0x4000, -0x4000, MTXMODE_APPLY);
                    Matrix_Get(&sp44);
                    Matrix_MtxFToYXZRotS(&sp44, &heldActor->world.rot, 0);
                    heldActor->shape.rot = heldActor->world.rot;

                    if (func_8002DD78(this) != 0) {
                        Matrix_Push();
                        Matrix_Translate(500.0f, 300.0f, 0.0f, MTXMODE_APPLY);
                        Player_DrawHookshotReticle(
                            globalCtx, this, (this->heldItemActionParam == PLAYER_AP_HOOKSHOT) ? 38600.0f : 77600.0f);
                        Matrix_Pop();
                    }
                }
            }

            if ((this->unk_862 != 0) || ((func_8002DD6C(this) == 0) && (heldActor != NULL))) {
                if (!(this->stateFlags1 & 0x400) && (this->unk_862 != 0) && (this->exchangeItemId != EXCH_ITEM_NONE)) {
                    Math_Vec3f_Copy(&sGetItemRefPos, &this->leftHandPos);
                } else {
                    sGetItemRefPos.x = (this->bodyPartsPos[15].x + this->leftHandPos.x) * 0.5f;
                    sGetItemRefPos.y = (this->bodyPartsPos[15].y + this->leftHandPos.y) * 0.5f;
                    sGetItemRefPos.z = (this->bodyPartsPos[15].z + this->leftHandPos.z) * 0.5f;
                }

                if (this->unk_862 == 0) {
                    Math_Vec3f_Copy(&heldActor->world.pos, &sGetItemRefPos);
                }
            }
        }
    } else if (this->actor.scale.y >= 0.0f) {
        if (limbIndex == PLAYER_LIMB_SHEATH) {
            if ((this->rightHandType != 10) && (this->rightHandType != 0xFF)) {
                if (Player_IsChildWithHylianShield(this)) {
                    func_80090604(globalCtx, this, &this->shieldQuad, D_8012619C);
                }

                Matrix_TranslateRotateZYX(&D_801261CC, &D_801261D8);
                Matrix_Get(&this->shieldMf);
            }
        } else if (limbIndex == PLAYER_LIMB_HEAD) {
            Matrix_MultVec3f(&D_801260D4, &this->actor.focus.pos);
        } else {
            Vec3f* vec = &D_801261E0[((void)0, gSaveContext.linkAge)];

            Actor_SetFeetPos(&this->actor, limbIndex, PLAYER_LIMB_L_FOOT, vec, PLAYER_LIMB_R_FOOT, vec);
        }
    }

    if (CVar_GetS32("gBlind_AimAudioCues", 0)) {
        Player_ComputeHandAimCue(this, globalCtx, limbIndex);
    }
}

u32 func_80091738(GlobalContext* globalCtx, u8* segment, SkelAnime* skelAnime) {
    s16 linkObjectId = gLinkObjectIds[(void)0, gSaveContext.linkAge];
    size_t size;
    void* ptr;

    size = gObjectTable[OBJECT_GAMEPLAY_KEEP].vromEnd - gObjectTable[OBJECT_GAMEPLAY_KEEP].vromStart;
    ptr = segment + 0x3800;
    DmaMgr_SendRequest1(ptr, gObjectTable[OBJECT_GAMEPLAY_KEEP].vromStart, size, "../z_player_lib.c", 2982);

    size = gObjectTable[linkObjectId].vromEnd - gObjectTable[linkObjectId].vromStart;
    ptr = segment + 0x8800;
    DmaMgr_SendRequest1(ptr, gObjectTable[linkObjectId].vromStart, size, "../z_player_lib.c", 2988);

    ptr = (void*)ALIGN16((intptr_t)ptr + size);

    gSegments[4] = VIRTUAL_TO_PHYSICAL(segment + 0x3800);
    gSegments[6] = VIRTUAL_TO_PHYSICAL(segment + 0x8800);

    SkelAnime_InitLink(globalCtx, skelAnime, gPlayerSkelHeaders[(void)0, gSaveContext.linkAge], &gPlayerAnim_003238, 9,
                       ptr, ptr, PLAYER_LIMB_MAX);

    return size + 0x8800 + 0x90;
}

u8 D_801261F8[] = { 2, 2, 5 };

s32 func_80091880(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, void* arg) {
    u8* ptr = arg;
    u8 modelGroup = D_801261F8[ptr[0] > 0 ? ptr[0] - 1 : 0];
    s32 type;
    s32 dListOffset = 0;
    Gfx** dLists;

    if ((modelGroup == 2) && !LINK_IS_ADULT && (ptr[1] == 2)) {
        modelGroup = 1;
    }

    if (limbIndex == PLAYER_LIMB_L_HAND) {
        type = gPlayerModelTypes[modelGroup][1];
        D_80160014 = type;

        if (ptr[0] == 0)
            type = 0;

        if ((type == 4) && (gSaveContext.swordHealth <= 0.0f)) {
            dListOffset = 4;
        }
    } else if (limbIndex == PLAYER_LIMB_R_HAND) {
        type = gPlayerModelTypes[modelGroup][2];
        D_80160018 = type;
        if (type == 10) {
            dListOffset = ptr[1] * sizeof(uintptr_t);
        }
    } else if (limbIndex == PLAYER_LIMB_SHEATH) {
        type = gPlayerModelTypes[modelGroup][3];
        if ((type == 18) || (type == 19)) {
            dListOffset = ptr[1] * sizeof(uintptr_t);
        } else if (type == 16 && CVar_GetS32("gPauseLiveLink", 0)) {
            //if (ptr[0] == 1)
                //dListOffset = 4;
        }
    } else if (limbIndex == PLAYER_LIMB_WAIST) {
        type = gPlayerModelTypes[modelGroup][4];
    } else {
        return 0;
    }

    dLists = &sPlayerDListGroups[type][(void)0, gSaveContext.linkAge];
    *dList = dLists[dListOffset];

    return 0;
}

#include <overlays/actors/ovl_Demo_Effect/z_demo_effect.h>

void Pause_DrawTriforceSpot(GlobalContext* globalCtx, s32 showLightColumn) {
    static DemoEffect triforce;
    static s16 rotation = 0;

    triforce.triforceSpot.crystalLightOpacity = 244;
    triforce.triforceSpot.triforceSpotOpacity = 249;
    triforce.triforceSpot.lightColumnOpacity = showLightColumn ? 244 : 0;
    triforce.triforceSpot.rotation = rotation;

    DemoEffect_DrawTriforceSpot(&triforce, globalCtx);

    rotation += 0x03E8;
}

void func_80091A24(GlobalContext* globalCtx, void* seg04, void* seg06, SkelAnime* skelAnime, Vec3f* pos, Vec3s* rot,
                   f32 scale, s32 sword, s32 tunic, s32 shield, s32 boots, s32 width, s32 height, Vec3f* eye, Vec3f* at,
                   f32 fovy, void* img1, void* img2) {
    static Vp viewport = { 128, 224, 511, 0, 128, 224, 511, 0 };
    static Lights1 lights1 = gdSPDefLights1(80, 80, 80, 255, 255, 255, 84, 84, 172);
    static Vec3f lightDir = { 89.8f, 0.0f, 89.8f };
    u8 sp12C[2];
    Gfx* opaRef;
    Gfx* xluRef;
    Gfx* kalRef;
    u16 perspNorm;
    Mtx* perspMtx = Graph_Alloc(globalCtx->state.gfxCtx, sizeof(Mtx));
    Mtx* lookAtMtx = Graph_Alloc(globalCtx->state.gfxCtx, sizeof(Mtx));

    OPEN_DISPS(globalCtx->state.gfxCtx, "../z_player_lib.c", 3129);

    gSPSegment(POLY_OPA_DISP++, 0x00, NULL);

    gDPPipeSync(POLY_OPA_DISP++);

    gSPLoadGeometryMode(POLY_OPA_DISP++, 0);
    gSPTexture(POLY_OPA_DISP++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF);
    gDPSetCombineMode(POLY_OPA_DISP++, G_CC_SHADE, G_CC_SHADE);
    gDPSetOtherMode(POLY_OPA_DISP++,
                    G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                        G_TD_CLAMP | G_TP_PERSP | G_CYC_FILL | G_PM_NPRIMITIVE,
                    G_AC_NONE | G_ZS_PIXEL | G_RM_NOOP | G_RM_NOOP2);
    gSPLoadGeometryMode(POLY_OPA_DISP++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH);
    gDPSetScissor(POLY_OPA_DISP++, G_SC_NON_INTERLACE, 0, 0, width, height);
    gSPClipRatio(POLY_OPA_DISP++, FRUSTRATIO_1);

    viewport.vp.vscale[0] = viewport.vp.vtrans[0] = width * 2;
    viewport.vp.vscale[1] = viewport.vp.vtrans[1] = height * 2;
    gSPViewport(POLY_OPA_DISP++, &viewport);
    
    guPerspective(perspMtx, &perspNorm, fovy, (f32)width / (f32)height, 10.0f, 4000.0f, 1.0f);

    gSPPerspNormalize(POLY_OPA_DISP++, perspNorm);
    gSPMatrix(POLY_OPA_DISP++, perspMtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);

    guLookAt(lookAtMtx, eye->x, eye->y, eye->z, at->x, at->y, at->z, 0.0f, 1.0f, 0.0f);

    gSPMatrix(POLY_OPA_DISP++, lookAtMtx, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);

    sp12C[0] = sword;
    sp12C[1] = shield;

    Matrix_SetTranslateRotateYXZ(pos->x - ((CVar_GetS32("gPauseLiveLink", 0) && LINK_AGE_IN_YEARS == YEARS_ADULT) ? 25 : 0),
                                 pos->y - (CVar_GetS32("gPauseTriforce", 0) ? 16 : 0), pos->z, rot);
    Matrix_Scale(scale, scale, scale, MTXMODE_APPLY);

    gSPSegment(POLY_OPA_DISP++, 0x04, seg04);
    gSPSegment(POLY_OPA_DISP++, 0x06, seg06);

    gSPSetLights1(POLY_OPA_DISP++, lights1);

    func_80093C80(globalCtx);

    POLY_OPA_DISP = Gfx_SetFog2(POLY_OPA_DISP++, 0, 0, 0, 0, 997, 1000);

    func_8002EABC(pos, &globalCtx->view.eye, &lightDir, globalCtx->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x0C, gCullBackDList);

    func_8008F470(globalCtx, skelAnime->skeleton, skelAnime->jointTable, skelAnime->dListCount, 0, tunic, boots, 0,
                  func_80091880, NULL, &sp12C);

     if (CVar_GetS32("gPauseTriforce", 0)) {

        Matrix_SetTranslateRotateYXZ(pos->x - (LINK_AGE_IN_YEARS == YEARS_ADULT ? 25 : 0),
                                      pos->y + 280 + (LINK_AGE_IN_YEARS == YEARS_ADULT ? 48 : 0), pos->z, rot);
        Matrix_Scale(scale * 1, scale * 1, scale * 1, MTXMODE_APPLY);

        Gfx* ohNo = POLY_XLU_DISP;
        POLY_XLU_DISP = POLY_OPA_DISP;

        Pause_DrawTriforceSpot(globalCtx, 1);

        POLY_OPA_DISP = POLY_XLU_DISP;
        POLY_XLU_DISP = ohNo;
    }

    POLY_OPA_DISP = Gameplay_SetFog(globalCtx, POLY_OPA_DISP++);

    CLOSE_DISPS(globalCtx->state.gfxCtx, "../z_player_lib.c", 3288);
}

void func_8009214C(GlobalContext* globalCtx, u8* segment, SkelAnime* skelAnime, Vec3f* pos, Vec3s* rot, f32 scale,
                   s32 sword, s32 tunic, s32 shield, s32 boots) {
    Vec3f eye = { 0.0f, 0.0f, -400.0f };
    Vec3f at = { 0.0f, 0.0f, 0.0f };
    Vec3s* destTable;
    Vec3s* srcTable;
    s32 i;

    gSegments[4] = VIRTUAL_TO_PHYSICAL(segment + 0x3800);
    gSegments[6] = VIRTUAL_TO_PHYSICAL(segment + 0x8800);

    if (CVar_GetS32("gPauseLiveLink", 0) || CVar_GetS32("gPauseTriforce", 0)) {
        uintptr_t anim = gPlayerAnim_003238; // idle

        if (CUR_EQUIP_VALUE(EQUIP_SWORD) >= 3)
            anim = gPlayerAnim_002BE0; // Two Handed Anim
        else if (CUR_EQUIP_VALUE(EQUIP_SHIELD) == 0)
            anim = gPlayerAnim_003240;
        else if (CUR_EQUIP_VALUE(EQUIP_SHIELD) == 2 && LINK_AGE_IN_YEARS == YEARS_CHILD)
            anim = gPlayerAnim_003240;

        //anim = gPlayerAnim_003428; // Use for biggoron sword?

        if (CVar_GetS32("gPauseTriforce", 0)) {
            anim = gPlayerAnim_002D00;
            sword = 0;
            shield = 0;
        }

        if (skelAnime->animation != anim) {
            LinkAnimation_Change(globalCtx, skelAnime, anim, 1.0f, 0.0f, Animation_GetLastFrame(anim), ANIMMODE_LOOP,
                                 -6.0f);
        }

        LinkAnimation_Update(globalCtx, skelAnime);

        if (!LINK_IS_ADULT) {
            // Link is placed too far up by default when animating
            at.y += 60;
        }
    } else {

        if (!LINK_IS_ADULT) {
            if (shield == PLAYER_SHIELD_DEKU) {
                srcTable = D_040020D0;
            } else {
                srcTable = D_04002040;
            }
        } else {
            if (sword == 3) {
                srcTable = D_04002160;
            } else if (shield != PLAYER_SHIELD_NONE) {
                srcTable = D_04002280;
            } else {
                srcTable = D_040021F0;
            }
        }

        srcTable = ResourceMgr_LoadArrayByNameAsVec3s(srcTable);
        destTable = skelAnime->jointTable;
        for (i = 0; i < skelAnime->limbCount; i++) {
            *destTable++ = *srcTable++;
        }
    }


    func_80091A24(globalCtx, segment + 0x3800, segment + 0x8800, skelAnime, pos, rot, scale, sword, tunic, shield,
                  boots, 64, 112, &eye, &at, 60.0f, globalCtx->state.gfxCtx->curFrameBuffer,
                  globalCtx->state.gfxCtx->curFrameBuffer + 0x1C00);
}
