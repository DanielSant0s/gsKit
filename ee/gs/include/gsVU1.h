//  ____     ___ |    / _____ _____
// |  __    |    |___/    |     |
// |___| ___|    |    \ __|__   |     gsKit Open Source Project.
// ----------------------------------------------------------------------
// Copyright 2004 - Chris "Neovanglist" Gilbert <Neovanglist@LainOS.org>
// Licenced under Academic Free License version 2.0
// Review gsKit README & LICENSE files for further details.
//
// gsVU1.h - Header for gsVU1.c
//

#ifndef __GSVU1_H__
#define __GSVU1_H__

#include "gsKit.h"

#define VU_GS_PRIM(PRIM, IIP, TME, FGE, ABE, AA1, FST, CTXT, FIX) (u128)(((FIX << 10) | (CTXT << 9) | (FST << 8) | (AA1 << 7) | (ABE << 6) | (FGE << 5) | (TME << 4) | (IIP << 3) | (PRIM)))
#define VU_GS_GIFTAG(NLOOP, EOP, PRE, PRIM, FLG, NREG) (((u64)(NREG) << 60) | ((u64)(FLG) << 58) | ((u64)(PRIM) << 47) | ((u64)(PRE) << 46) | (EOP << 15) | (NLOOP << 0))

#define GIF_SET_TAG(NLOOP, EOP, PRE, PRIM, FLG, NREG)                    \
    (u64)((NLOOP)&0x00007FFF) << 0 | (u64)((EOP)&0x00000001) << 15 |     \
        (u64)((PRE)&0x00000001) << 46 | (u64)((PRIM)&0x000007FF) << 47 | \
        (u64)((FLG)&0x00000003) << 58 | (u64)((NREG)&0x0000000F) << 60

void gsKit_init_vu1(GSGLOBAL* gsGlobal);

#endif /* __GSVU1_H__ */
