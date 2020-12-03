#include "z_bg_hidan_fwbig.h"

#define FLAGS 0x00000010

#define THIS ((BgHidanFwbig*)thisx)

typedef enum {
    /* 0 */ FWBIG_MOVE,
    /* 1 */ FWBIG_RESET,
    /* 2 */ FWBIG_KILL
} HidanFwbigMoveState;

void BgHidanFwbig_Init(Actor* thisx, GlobalContext* globalCtx);
void BgHidanFwbig_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgHidanFwbig_Update(Actor* thisx, GlobalContext* globalCtx);
void BgHidanFwbig_Draw(Actor* thisx, GlobalContext* globalCtx);

void BgHidanFwbig_UpdatePosition(BgHidanFwbig* this);

void BgHidanFwbig_WaitForSwitch(BgHidanFwbig* this, GlobalContext* globalCtx);
void BgHidanFwbig_WaitForCs(BgHidanFwbig* this, GlobalContext* globalCtx);
void BgHidanFwbig_Lower(BgHidanFwbig* this, GlobalContext* globalCtx);
void BgHidanFwbig_WaitForTimer(BgHidanFwbig* this, GlobalContext* globalCtx);
void BgHidanFwbig_WaitForPlayer(BgHidanFwbig* this, GlobalContext* globalCtx);
void BgHidanFwbig_Move(BgHidanFwbig* this, GlobalContext* globalCtx);

extern Gfx D_0600DB20[];
extern Gfx D_040173D0[];
extern Gfx D_04017BD0[];

const ActorInit Bg_Hidan_Fwbig_InitVars = {
    ACTOR_BG_HIDAN_FWBIG,
    ACTORTYPE_PROP,
    FLAGS,
    OBJECT_HIDAN_OBJECTS,
    sizeof(BgHidanFwbig),
    (ActorFunc)BgHidanFwbig_Init,
    (ActorFunc)BgHidanFwbig_Destroy,
    (ActorFunc)BgHidanFwbig_Update,
    (ActorFunc)BgHidanFwbig_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    { COLTYPE_UNK10, 0x11, 0x00, 0x09, 0x20, COLSHAPE_CYLINDER },
    { 0x00, { 0x20000000, 0x01, 0x04 }, { 0xFFCFFFFF, 0x00, 0x00 }, 0x19, 0x00, 0x01 },
    { 30, 130, 0, { 0, 0, 0 } },
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneScale, 1000, ICHAIN_STOP),
};

void BgHidanFwbig_Init(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    BgHidanFwbig* this = THIS;
    Player* player = PLAYER;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    this->actor.colChkInfo.mass = 0xFF;
    this->direction = (u16)(thisx->params >> 8);
    thisx->params &= 0xFF;
    if (this->direction != 0) {
        this->actor.initPosRot.pos.x = 1560.0f;
        this->actor.initPosRot.pos.z = 0.0f;
        if (player->actor.posRot.pos.z > 300.0f) {
            this->direction = -1;
            this->actor.initPosRot.rot.y = this->actor.shape.rot.y = -0x4E38;
        } else if (player->actor.posRot.pos.z < -300.0f) {
            this->direction = 1;
            this->actor.initPosRot.rot.y = this->actor.shape.rot.y = -0x31C8;
        } else {
            Actor_Kill(&this->actor);
            return;
        }
        BgHidanFwbig_UpdatePosition(this);
        Actor_SetScale(&this->actor, 0.15f);
        this->collider.dim.height = 230;
        this->actor.flags |= 0x10;
        this->moveState = FWBIG_MOVE;
        this->actionFunc = BgHidanFwbig_WaitForPlayer;
        this->actor.posRot.pos.y = this->actor.initPosRot.pos.y - (2400.0f * this->actor.scale.y);
    } else {
        Actor_SetScale(&this->actor, 0.1f);
        this->actionFunc = BgHidanFwbig_WaitForSwitch;
    }
}

void BgHidanFwbig_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    BgHidanFwbig* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void BgHidanFwbig_UpdatePosition(BgHidanFwbig* this) {
    s16 startAngle = this->actor.shape.rot.y + this->direction * -0x4000;

    this->actor.posRot.pos.x = (Math_Sins(startAngle) * 885.4f) + this->actor.initPosRot.pos.x;
    this->actor.posRot.pos.z = (Math_Coss(startAngle) * 885.4f) + this->actor.initPosRot.pos.z;
}

void BgHidanFwbig_WaitForSwitch(BgHidanFwbig* this, GlobalContext* globalCtx) {
    if (Flags_GetSwitch(globalCtx, this->actor.params)) {
        this->actionFunc = BgHidanFwbig_WaitForCs;
        func_800800F8(globalCtx, 0xD0C, -0x63, &this->actor, 0);
        this->timer = 35;
    }
}

void BgHidanFwbig_WaitForCs(BgHidanFwbig* this, GlobalContext* globalCtx) {
    if (this->timer-- == 0) {
        this->actionFunc = BgHidanFwbig_Lower;
    }
}

void BgHidanFwbig_Rise(BgHidanFwbig* this, GlobalContext* globalCtx) {
    if (Math_ApproxF(&this->actor.posRot.pos.y, this->actor.initPosRot.pos.y, 10.0f)) {
        if (this->direction == 0) {
            Flags_UnsetSwitch(globalCtx, this->actor.params);
            this->actionFunc = BgHidanFwbig_WaitForSwitch;
        } else {
            this->actionFunc = BgHidanFwbig_Move;
        }
    }
}

void BgHidanFwbig_Lower(BgHidanFwbig* this, GlobalContext* globalCtx) {
    if (Math_ApproxF(&this->actor.posRot.pos.y, this->actor.initPosRot.pos.y - (2400.0f * this->actor.scale.y),
                     10.0f)) {
        if (this->direction == 0) {
            this->actionFunc = BgHidanFwbig_WaitForTimer;
            this->timer = 150;
        } else if (this->moveState == FWBIG_KILL) {
            Actor_Kill(&this->actor);
        } else {
            if (this->moveState == FWBIG_MOVE) {
                this->actor.shape.rot.y -= (this->direction * 0x1800);
            } else {
                this->moveState = FWBIG_MOVE;
                this->actor.shape.rot.y = this->actor.initPosRot.rot.y;
            }
            BgHidanFwbig_UpdatePosition(this);
            this->actionFunc = BgHidanFwbig_Rise;
        }
    }
}

void BgHidanFwbig_WaitForTimer(BgHidanFwbig* this, GlobalContext* globalCtx) {
    if (this->timer != 0) {
        this->timer--;
    }
    if (this->timer == 0) {
        this->actionFunc = BgHidanFwbig_Rise;
    }
    func_8002F994(&this->actor, this->timer);
}

void BgHidanFwbig_WaitForPlayer(BgHidanFwbig* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    if (player->actor.posRot.pos.x < 1150.0f) {
        this->actionFunc = BgHidanFwbig_Rise;
        func_800800F8(globalCtx, 0xCDA, -0x63, &this->actor, 0);
    }
}

void BgHidanFwbig_Move(BgHidanFwbig* this, GlobalContext* globalCtx) {
    if (!Player_InCsMode(globalCtx)) {
        if (Math_ApproxUpdateScaledS(&this->actor.shape.rot.y,
                                     this->actor.initPosRot.rot.y + (this->direction * 0x6390), 0x20)) {
            this->moveState = FWBIG_RESET;
            this->actionFunc = BgHidanFwbig_Lower;
        } else {
            BgHidanFwbig_UpdatePosition(this);
        }
    }
}

void BgHidanFwbig_MoveCollider(BgHidanFwbig* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    Vec3f projPos;
    f32 cs;
    f32 sn;

    func_8002DBD0(&this->actor, &projPos, &player->actor.posRot.pos);
    projPos.z = ((projPos.z >= 0.0f) ? 1.0f : -1.0f) * 25.0f * -1.0f;
    if (this->direction == 0) {
        projPos.x = CLAMP(projPos.x, -360.0f, 360.0f);
    } else {
        projPos.x = CLAMP(projPos.x, -500.0f, 500.0f);
    }

    sn = Math_Sins(this->actor.shape.rot.y);
    cs = Math_Coss(this->actor.shape.rot.y);
    this->collider.dim.pos.x = this->actor.posRot.pos.x + (projPos.x * cs) + (projPos.z * sn);
    this->collider.dim.pos.z = this->actor.posRot.pos.z - (projPos.x * sn) + (projPos.z * cs);
    this->collider.dim.pos.y = this->actor.posRot.pos.y;

    this->actor.posRot.rot.y = (projPos.z < 0.0f) ? this->actor.shape.rot.y : this->actor.shape.rot.y + 0x8000;
}

void BgHidanFwbig_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    BgHidanFwbig* this = THIS;

    if (this->collider.base.atFlags & 2) {
        this->collider.base.atFlags &= ~2;
        func_8002F71C(globalCtx, &this->actor, 5.0f, this->actor.posRot.rot.y, 1.0f);
        if (this->direction != 0) {
            this->actionFunc = BgHidanFwbig_Lower;
        }
    }
    if ((this->direction != 0) && (globalCtx->roomCtx.prevRoom.num == this->actor.room)) {
        this->moveState = FWBIG_KILL;
        this->actionFunc = BgHidanFwbig_Lower;
    }

    this->actionFunc(this, globalCtx);

    if ((this->actor.initPosRot.pos.y - 200.0f) < this->actor.posRot.pos.y) {
        if (gSaveContext.sceneSetupIndex < 4) {
            func_8002F974(&this->actor, NA_SE_EV_BURNING - SFX_FLAG);
        } else if ((s16)this->actor.posRot.pos.x == -513) {
            func_8002F974(&this->actor, NA_SE_EV_FLAME_OF_FIRE - SFX_FLAG);
        }
        BgHidanFwbig_MoveCollider(this, globalCtx);
        CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }
}

void BgHidanFwbig_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    f32 height;

    OPEN_DISPS(globalCtx->state.gfxCtx, "../z_bg_hidan_fwbig.c", 630);
    func_80093D84(globalCtx->state.gfxCtx);

    gSPSegment(POLY_XLU_DISP++, 0x09, SEGMENTED_TO_VIRTUAL(D_040173D0));

    gSPSegment(POLY_XLU_DISP++, 0x0A, SEGMENTED_TO_VIRTUAL(D_04017BD0));

    height = thisx->scale.y * 2400.0f;
    gDPSetPrimColor(POLY_XLU_DISP++, 0x80, 0x80, 255, 220, 0,
                    ((height - (thisx->initPosRot.pos.y - thisx->posRot.pos.y)) * 255.0f) / height);

    gDPSetEnvColor(POLY_XLU_DISP++, 255, 0, 0, 0);

    gSPSegment(POLY_XLU_DISP++, 0x08,
               Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, globalCtx->gameplayFrames % 0x80, 0, 0x20, 0x40, 1, 0,
                                (u8)(globalCtx->gameplayFrames * -15), 0x20, 0x40));

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_bg_hidan_fwbig.c", 660),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gSPDisplayList(POLY_XLU_DISP++, D_0600DB20);

    CLOSE_DISPS(globalCtx->state.gfxCtx, "../z_bg_hidan_fwbig.c", 664);
}
