glabel func_80A911F0
/* 004D0 80A911F0 27BDFFD8 */  addiu   $sp, $sp, 0xFFD8           ## $sp = FFFFFFD8
/* 004D4 80A911F4 AFA40028 */  sw      $a0, 0x0028($sp)
/* 004D8 80A911F8 AFBF0024 */  sw      $ra, 0x0024($sp)
/* 004DC 80A911FC 3C040600 */  lui     $a0, 0x0600                ## $a0 = 06000000
/* 004E0 80A91200 AFA5002C */  sw      $a1, 0x002C($sp)
/* 004E4 80A91204 0C028800 */  jal     SkelAnime_GetFrameCount

/* 004E8 80A91208 24840214 */  addiu   $a0, $a0, 0x0214           ## $a0 = 06000214
/* 004EC 80A9120C 44822000 */  mtc1    $v0, $f4                   ## $f4 = 0.00
/* 004F0 80A91210 3C01C120 */  lui     $at, 0xC120                ## $at = C1200000
/* 004F4 80A91214 44819000 */  mtc1    $at, $f18                  ## $f18 = -10.00
/* 004F8 80A91218 468021A0 */  cvt.s.w $f6, $f4
/* 004FC 80A9121C 8FA40028 */  lw      $a0, 0x0028($sp)
/* 00500 80A91220 3C050600 */  lui     $a1, 0x0600                ## $a1 = 06000000
/* 00504 80A91224 24A50214 */  addiu   $a1, $a1, 0x0214           ## $a1 = 06000214
/* 00508 80A91228 3C063F80 */  lui     $a2, 0x3F80                ## $a2 = 3F800000
/* 0050C 80A9122C 24070000 */  addiu   $a3, $zero, 0x0000         ## $a3 = 00000000
/* 00510 80A91230 4600320D */  trunc.w.s $f8, $f6
/* 00514 80A91234 AFA00014 */  sw      $zero, 0x0014($sp)
/* 00518 80A91238 E7B20018 */  swc1    $f18, 0x0018($sp)
/* 0051C 80A9123C 24840150 */  addiu   $a0, $a0, 0x0150           ## $a0 = 00000150
/* 00520 80A91240 440F4000 */  mfc1    $t7, $f8
/* 00524 80A91244 00000000 */  nop
/* 00528 80A91248 000FC400 */  sll     $t8, $t7, 16
/* 0052C 80A9124C 0018CC03 */  sra     $t9, $t8, 16
/* 00530 80A91250 44995000 */  mtc1    $t9, $f10                  ## $f10 = 0.00
/* 00534 80A91254 00000000 */  nop
/* 00538 80A91258 46805420 */  cvt.s.w $f16, $f10
/* 0053C 80A9125C 0C029468 */  jal     SkelAnime_ChangeAnim

/* 00540 80A91260 E7B00010 */  swc1    $f16, 0x0010($sp)
/* 00544 80A91264 8FA90028 */  lw      $t1, 0x0028($sp)
/* 00548 80A91268 3C0880A9 */  lui     $t0, %hi(func_80A91284)    ## $t0 = 80A90000
/* 0054C 80A9126C 25081284 */  addiu   $t0, $t0, %lo(func_80A91284) ## $t0 = 80A91284
/* 00550 80A91270 AD28014C */  sw      $t0, 0x014C($t1)           ## 0000014C
/* 00554 80A91274 8FBF0024 */  lw      $ra, 0x0024($sp)
/* 00558 80A91278 27BD0028 */  addiu   $sp, $sp, 0x0028           ## $sp = 00000000
/* 0055C 80A9127C 03E00008 */  jr      $ra
/* 00560 80A91280 00000000 */  nop
