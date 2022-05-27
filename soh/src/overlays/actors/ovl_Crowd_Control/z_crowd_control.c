#include "vt.h"
#include "z_crowd_control.h"
#include <objects/gameplay_keep/gameplay_keep.h>
#include <overlays/actors/ovl_En_Niw/z_en_niw.h>

#define FLAGS (ACTOR_FLAG_4 | ACTOR_FLAG_5)



void CrowdControl_Init(Actor* thisx, GlobalContext* globalCtx);
void CrowdControl_Destroy(Actor* thisx, GlobalContext* globalCtx);
void CrowdControl_Update(Actor* thisx, GlobalContext* globalCtx);
void CrowdControl_Draw(Actor* thisx, GlobalContext* globalCtx);

const ActorInit Obj_CrowdControl_InitVars = {
    ACTOR_CROWD_CONTROL,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_LINK_BOY,
    sizeof(CrowdControl),
    (ActorFunc)CrowdControl_Init,
    (ActorFunc)CrowdControl_Destroy,
    (ActorFunc)CrowdControl_Update,
    (ActorFunc)CrowdControl_Draw,
    NULL,
};

void CrowdControl_Init(Actor* thisx, GlobalContext* globalCtx) {
    CrowdControl* this = (CrowdControl*)thisx;
    this->actor.room = -1;
}

void CrowdControl_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void CrowdControl_Update(Actor* thisx, GlobalContext* globalCtx) {
    //ExecuteCommand(thisx, 0, 0);
}

void CrowdControl_Draw(Actor* thisx, GlobalContext* globalCtx) {
}