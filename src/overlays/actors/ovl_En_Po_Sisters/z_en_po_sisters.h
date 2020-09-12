#ifndef _Z_EN_PO_SISTERS_H_
#define _Z_EN_PO_SISTERS_H_

#include <ultra64.h>
#include <global.h>

struct EnPoSisters;

typedef struct EnPoSisters {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ SkelAnime unk_14C;
    /* 0x0190 */ s32 unk_190;
    /* 0x0194 */ u8 color;
    /* 0x0195 */ u8 unk_195;
    /* 0x0196 */ u8 unk_196;
    /* 0x0197 */ u8 unk_197;
    /* 0x0198 */ u8 unk_198;
    /* 0x0199 */ u8 unk_199;
    /* 0x019A */ char unk_19A[4];
    /* 0x019E */ Vec3s limbDrawTable[12];
    /* 0x01E6 */ Vec3s limbTransitionDrawTable[12];
    /* 0x022E */ u8 unk_22E;
    /* 0x022F */ u8 unk_22F;
    /* 0x0230 */ u8 unk_230;
    /* 0x0231 */ u8 unk_231;
    /* 0x0230 */ char unk_232[0x62];
    /* 0x0294 */ f32 unk_294;
    /* 0x0298 */ LightNode* lightNode;
    /* 0x029C */ LightInfo lightInfo;
    /* 0x02AA */ char unk_2AA[0x2];
    /* 0x02AC */ ColliderCylinder collider;
    /* 0x02F8 */ char unk_2F8[0x40];
} EnPoSisters; // size = 0x0338

extern const ActorInit En_Po_Sisters_InitVars;

#endif
