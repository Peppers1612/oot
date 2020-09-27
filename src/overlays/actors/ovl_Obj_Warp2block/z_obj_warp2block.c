/*
 * File: z_obj_warp2block.c
 * Overlay: ovl_Obj_Warp2Block
 * Description: Time Block - Warp 2
 *
 * These blocks are placed in pairs and playing the song of time will make
 * one block disappear and the other appear, giving the impression that the
 * block is warping between positions.
 */

#include "z_obj_warp2block.h"

#define FLAGS 0x0A000011

#define THIS ((ObjWarp2block*)thisx)

void ObjWarp2block_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjWarp2block_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjWarp2block_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjWarp2block_Draw(Actor* thisx, GlobalContext* globalCtx);

// func_80BA1DF0
// func_80BA1EEC
void func_80BA2048(ObjWarp2block* this, GlobalContext* globalCtx);
void func_80BA2218(ObjWarp2block* this, GlobalContext* globalCtx);
void func_80BA228C(ObjWarp2block* this, GlobalContext* globalCtx);
void func_80BA2304(ObjWarp2block* this, GlobalContext* globalCtx);
void func_80BA24C8(ObjWarp2block* this);
void func_80BA24DC(ObjWarp2block* this, GlobalContext* globalCtx);
void func_80BA24E8(ObjWarp2block* this);
void func_80BA24F8(ObjWarp2block* this, GlobalContext* globalCtx);
// func_80BA2600
void func_80BA2610(ObjWarp2block* this, GlobalContext* globalCtx);

extern s32 D_06000B30;

const ActorInit Obj_Warp2block_InitVars = {
    ACTOR_OBJ_WARP2BLOCK,
    ACTORTYPE_ITEMACTION,
    FLAGS,
    OBJECT_TIMEBLOCK,
    sizeof(ObjWarp2block),
    (ActorFunc)ObjWarp2block_Init,
    (ActorFunc)ObjWarp2block_Destroy,
    (ActorFunc)ObjWarp2block_Update,
    (ActorFunc)ObjWarp2block_Draw,
};

typedef struct ObjWarp2block_SizeOptions {
    /* 0x00 */ f32 scale;
    /* 0x04 */ f32 height;
    /* 0x08 */ s16 demoEffectParams;
} ObjWarp2block_SizeOptions;

ObjWarp2block_SizeOptions D_80BA2840[] = {
    { 1.0, 60.0, 0x0018 },
    { 0.6, 40.0, 0x0019 },
};

s32 D_80BA2858[] = { 0x42700000, 0x42C80000, 0x430C0000, 0x43340000, 0x435C0000, 0x43820000, 0x43960000, 0x43960000 };

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 1800, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 300, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 1500, ICHAIN_STOP),
};

s32 D_80BA2884[] = { 0x64788C50, 0x8CC86496, 0xC864C8F0, 0x506E8C46, 0xA0E15064, 0x82646EBE, 0x00000000 };

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Obj_Warp2block/func_80BA1DF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Obj_Warp2block/func_80BA1ECC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Obj_Warp2block/func_80BA2048.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Obj_Warp2block/func_80BA2218.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Obj_Warp2block/func_80BA228C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Obj_Warp2block/func_80BA2304.s")

void ObjWarp2block_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjWarp2block* this = THIS;
    s32 pad;
    UNK_PTR colHeader = NULL;

    this->dyna.actor.shape.rot.z = 0;
    this->dyna.actor.posRot.rot.z = this->dyna.actor.shape.rot.z;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    Actor_SetScale(&this->dyna.actor, D_80BA2840[(this->dyna.actor.params >> 8) & 1].scale);

    this->actionFunc_168 = &func_80BA2218;

    Actor_SetHeight(&this->dyna.actor, D_80BA2840[(this->dyna.actor.params >> 8) & 1].height);

    if ((this->dyna.actor.params >> 15) & 1) {
        func_80BA24E8(this);
        if (Flags_GetSwitch(globalCtx, this->dyna.actor.params & 0x3F)) {
            this->dyna.actor.draw = NULL;
        }
        DynaPolyInfo_SetActorMove(&this->dyna, 0);
        DynaPolyInfo_Alloc(&D_06000B30, &colHeader);
        this->dyna.dynaPolyId =
            DynaPolyInfo_RegisterActor(globalCtx, &globalCtx->colCtx.dyna, &this->dyna.actor, colHeader);
    } else {
        func_80BA24C8(this);
    }
    // Time Block (Warp 2) (...)
    osSyncPrintf("時のブロック(ワープ２) (<arg> %04xH <type> color:%d range:%d)\n", (u16)this->dyna.actor.params,
                 this->dyna.actor.initPosRot.rot.z & 7, (this->dyna.actor.params >> 11) & 7);
}

void ObjWarp2block_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ObjWarp2block* this = THIS;
    if ((this->dyna.actor.params >> 15) & 1) {
        DynaPolyInfo_Free(globalCtx, &globalCtx->colCtx.dyna, this->dyna.dynaPolyId);
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Obj_Warp2block/func_80BA24C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Obj_Warp2block/func_80BA24DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Obj_Warp2block/func_80BA24E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Obj_Warp2block/func_80BA24F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Obj_Warp2block/func_80BA2600.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Obj_Warp2block/func_80BA2610.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Obj_Warp2block/ObjWarp2block_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Obj_Warp2block/ObjWarp2block_Draw.s")
