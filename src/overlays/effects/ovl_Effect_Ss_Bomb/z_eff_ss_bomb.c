/*
 * File: z_eff_ss_bomb.c
 * Overlay: ovl_Effect_Ss_Bomb
 * Description: Bomb Blast. Unused in the orignal game.
 */

#include "z_eff_ss_bomb.h"

#define rScale regs[0]
#define rTexIdx regs[1]

u32 EffectSsBomb_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx);
void EffectSsBomb_Draw(GlobalContext* globalCtx, u32 index, EffectSs* this);
void EffectSsBomb_Update(GlobalContext* globalCtx, u32 index, EffectSs* this);

EffectSsInit Effect_Ss_Bomb_InitVars = {
    EFFECT_SS_BOMB,
    EffectSsBomb_Init,
};

extern Gfx D_0400BF80[];

u32 EffectSsBomb_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx) {
    EffectSsBombInitParams* initParams = (EffectSsBombInitParams*)initParamsx;

    Math_Vec3f_Copy(&this->pos, &initParams->pos);
    Math_Vec3f_Copy(&this->velocity, &initParams->velocity);
    Math_Vec3f_Copy(&this->accel, &initParams->accel);
    this->gfx = SEGMENTED_TO_VIRTUAL(D_0400BF80);
    this->life = 20;
    this->draw = EffectSsBomb_Draw;
    this->update = EffectSsBomb_Update;
    this->rScale = 100;
    this->rTexIdx = 0;

    return 1;
}

static void* sTextures[] = {
    0x04007F80,
    0x04008780,
    0x04008F80,
    0x04009780,
};

void EffectSsBomb_Draw(GlobalContext* globalCtx, u32 index, EffectSs* this) {
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    MtxF mfTrans;
    MtxF mfScale;
    MtxF mfResult;
    MtxF mfTrans11DA0;
    Mtx* mtx;
    s32 pad;
    f32 scale;
    s16 color;

    if (1) {}

    OPEN_DISPS(gfxCtx, "../z_eff_ss_bomb.c", 168);

    scale = this->rScale / 100.0f;

    SkinMatrix_SetTranslate(&mfTrans, this->pos.x, this->pos.y, this->pos.z);
    SkinMatrix_SetScale(&mfScale, scale, scale, 1.0f);
    SkinMatrix_MtxFMtxFMult(&mfTrans, &globalCtx->mf_11DA0, &mfTrans11DA0);
    SkinMatrix_MtxFMtxFMult(&mfTrans11DA0, &mfScale, &mfResult);

    gSPMatrix(oGfxCtx->polyXlu.p++, &gMtxClear, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    mtx = SkinMatrix_MtxFToNewMtx(gfxCtx, &mfResult);

    if (mtx != NULL) {
        gSPMatrix(oGfxCtx->polyXlu.p++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPSegment(oGfxCtx->polyXlu.p++, 0x08, SEGMENTED_TO_VIRTUAL(sTextures[this->rTexIdx]));
        gDPPipeSync(oGfxCtx->polyXlu.p++);
        func_80094C50(gfxCtx);
        color = this->life * 12.75f;
        gDPSetPrimColor(oGfxCtx->polyXlu.p++, 0, 0, color, color, color, color);
        gDPPipeSync(oGfxCtx->polyXlu.p++);
        gSPDisplayList(oGfxCtx->polyXlu.p++, this->gfx);
        gDPPipeSync(oGfxCtx->polyXlu.p++);
    }

    CLOSE_DISPS(gfxCtx, "../z_eff_ss_bomb.c", 214);
}

void EffectSsBomb_Update(GlobalContext* globalCtx, u32 index, EffectSs* this) {
    if ((this->life < 21) && (this->life > 16)) {
        this->rTexIdx = (20 - this->life);
    } else {
        this->rScale += 0;
        this->rTexIdx = 3;
    }

    this->accel.x = ((Math_Rand_ZeroOne() * 0.4f) - 0.2f);
    this->accel.z = ((Math_Rand_ZeroOne() * 0.4f) - 0.2f);
}
