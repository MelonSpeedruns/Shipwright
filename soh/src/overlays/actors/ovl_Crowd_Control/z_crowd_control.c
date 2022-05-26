#include "vt.h"
#include "z_crowd_control.h"
#include <objects/gameplay_keep/gameplay_keep.h>

void CrowdControl_Init(Actor* thisx, GlobalContext* globalCtx);
void CrowdControl_Destroy(Actor* thisx, GlobalContext* globalCtx);
void CrowdControl_Update(Actor* thisx, GlobalContext* globalCtx);
void CrowdControl_Draw(Actor* thisx, GlobalContext* globalCtx);

const ActorInit Obj_CrowdControl_InitVars = {
    ACTOR_CROWD_CONTROL,
    ACTORCAT_PLAYER,
    0,
    OBJECT_LINK_BOY,
    sizeof(CrowdControl),
    (ActorFunc)CrowdControl_Init,
    (ActorFunc)CrowdControl_Destroy,
    (ActorFunc)CrowdControl_Update,
    (ActorFunc)CrowdControl_Draw,
    NULL,
};

void SpawnCuccoWave() {
    gGlobalCrowdControlPacket.effectType = 2;
}

void CrowdControl_Init(Actor* thisx, GlobalContext* globalCtx) {
    CrowdControl* this = (CrowdControl*)thisx;

    gGlobalCrowdControlPacket.effectType = 1;
}

void CrowdControl_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void CrowdControl_Update(Actor* thisx, GlobalContext* globalCtx) {
    if (gGlobalCrowdControlPacket.effectType == 1) {
        SpawnCuccoWave();
    }

    gGlobalCrowdControlPacket.effectType = 0;
    gGlobalCrowdControlPacket.effectData = 0;
}

void CrowdControl_Draw(Actor* thisx, GlobalContext* globalCtx) {
}