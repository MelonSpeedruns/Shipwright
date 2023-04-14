/*
 * File: z_obj_ganon_romance.c
 * Overlay: ovl_Obj_Ganon_Romance
 * Description: Ganon Romance Actor
 */

#include "z_obj_ganon_romance.h"
#include <objects/object_gndd/object_gndd.h>

#define FLAGS (ACTOR_FLAG_0)

void ObjGanonRomance_Init(Actor* thisx, PlayState* play);
void ObjGanonRomance_Destroy(Actor* thisx, PlayState* play);
void ObjGanonRomance_Update(Actor* thisx, PlayState* play);
void ObjGanonRomance_Draw(Actor* thisx, PlayState* play);

const ActorInit Obj_Ganon_Romance_InitVars = {
    ACTOR_OBJ_GANON_ROMANCE,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_GANON,
    sizeof(ObjGanonRomance),
    (ActorFunc)ObjGanonRomance_Init,
    (ActorFunc)ObjGanonRomance_Destroy,
    (ActorFunc)ObjGanonRomance_Update,
    (ActorFunc)ObjGanonRomance_Draw,
    NULL,
};

void ObjGanonRomance_Init(Actor* thisx, PlayState* play) {
    ObjGanonRomance* this = (ObjGanonRomance*)thisx;

    Actor_SetObjectDependency(play, &this->actor);

    SkelAnime_InitFlex(play, &this->skelAnime, &gYoungGanondorfSkel, NULL, this->jointTable, this->morphTable, 24);

    f32 frames = Animation_GetLastFrame(&gYoungGanondorfArmsCrossedAnim);
    Animation_Change(&this->skelAnime, &gYoungGanondorfArmsCrossedAnim, 1.0f, 0.0f, (s16)frames, ANIMMODE_LOOP, 0.0f);
}

void ObjGanonRomance_Destroy(Actor* thisx, PlayState* play) {
    ObjGanonRomance* this = (ObjGanonRomance*)thisx;
    SkelAnime_Free(&this->skelAnime, play);
}

void ObjGanonRomance_Update(Actor* thisx, PlayState* play) {
    ObjGanonRomance* this = (ObjGanonRomance*)thisx;
    SkelAnime_Update(&this->skelAnime);
}

void ObjGanonRomance_Draw(Actor* thisx, PlayState* play) {
    ObjGanonRomance* this = (ObjGanonRomance*)thisx;

    s16 frames = 0;

    OPEN_DISPS(play->state.gfxCtx);

    if (gSaveContext.sceneSetupIndex != 4) {
        frames = 149;
    }

    if (frames + 1127 >= play->csCtx.frames) {
        gSPSegment(POLY_OPA_DISP++, 0x08, SEGMENTED_TO_VIRTUAL(&gYoungGanondorfEyeOpenTex));
        gSPSegment(POLY_OPA_DISP++, 0x09, SEGMENTED_TO_VIRTUAL(&gYoungGanondorfEyeOpenTex));

    } else if (frames + 1128 >= play->csCtx.frames) {
        gSPSegment(POLY_OPA_DISP++, 0x08, SEGMENTED_TO_VIRTUAL(&gYoungGanondorfEyeHalfTex));
        gSPSegment(POLY_OPA_DISP++, 0x09, SEGMENTED_TO_VIRTUAL(&gYoungGanondorfEyeHalfTex));

    } else if (frames + 1129 >= play->csCtx.frames) {
        gSPSegment(POLY_OPA_DISP++, 0x08, SEGMENTED_TO_VIRTUAL(&gYoungGanondorfEyeClosedTex));
        gSPSegment(POLY_OPA_DISP++, 0x09, SEGMENTED_TO_VIRTUAL(&gYoungGanondorfEyeClosedTex));

    } else {
        gSPSegment(POLY_OPA_DISP++, 0x08, SEGMENTED_TO_VIRTUAL(&gYoungGanondorfEyeLookingDownTex));
        gSPSegment(POLY_OPA_DISP++, 0x09, SEGMENTED_TO_VIRTUAL(&gYoungGanondorfEyeLookingDownTex));
    }

    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable,
                          this->skelAnime.dListCount, NULL, 0, this);

    CLOSE_DISPS(play->state.gfxCtx);
}