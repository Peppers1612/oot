glabel func_800F50EC
/* B6C28C 800F50EC 3C028013 */  lui   $v0, %hi(D_8013064C) # $v0, 0x8013
/* B6C290 800F50F0 2442064C */  addiu $v0, %lo(D_8013064C) # addiu $v0, $v0, 0x64c
/* B6C294 800F50F4 8C4E0000 */  lw    $t6, ($v0)
/* B6C298 800F50F8 148E0002 */  bne   $a0, $t6, .L800F5104
/* B6C29C 800F50FC 00000000 */   nop   
/* B6C2A0 800F5100 AC400000 */  sw    $zero, ($v0)
.L800F5104:
/* B6C2A4 800F5104 03E00008 */  jr    $ra
/* B6C2A8 800F5108 00000000 */   nop   

