//  ____     ___ |    / _____ _____
// |  __    |    |___/    |     |
// |___| ___|    |    \ __|__   |     gsKit Open Source Project.
// ----------------------------------------------------------------------
// Copyright 2004 - Chris "Neovanglist" Gilbert <Neovanglist@LainOS.org>
// Copyright 2022 - Daniel Santos <danielsantos346@gmail.com>
// Licenced under Academic Free License version 2.0
// Review gsKit README & LICENSE files for further details.
//
// gsVU1.c - VU1 Related Routines
//
//

#include "gsKit.h"
#include <kernel.h>
#include <malloc.h>

void gsKit_vu1_set_double_buffer(u32 base, u32 offset)
{
	u64* p_data;
	u64* p_store;
	p_data = p_store = memalign(128, 4*sizeof(u64));

	*p_data++ = DMA_TAG(0, 0, DMA_CNT, 0, 0 , 0);
	*p_data++ = (VIF_CODE(base, 0, VIF_BASE, 0) | (u64)VIF_CODE(offset, 0, VIF_OFFSET, 0) << 32);

	*p_data++ = DMA_TAG(0, 0, DMA_END, 0, 0 , 0);
	*p_data++ = (VIF_CODE(0, 0, VIF_NOP, 0) | (u64)VIF_CODE(0, 0, VIF_NOP, 0) << 32);

	FlushCache(0);
	dmaKit_send_chain(DMA_CHANNEL_VIF1, (void *)((u32)p_store & 0x0FFFFFFF), 0);
	dmaKit_wait(DMA_CHANNEL_VIF1, 0);
	free(p_store);
}

#ifdef F_gsKit_init_vu1
void gsKit_init_vu1(GSGLOBAL* gsGlobal){
    if(gsGlobal->DoubleBuffering == GS_SETTING_ON){
        gsKit_vu1_set_double_buffer(8, 496);
    }
}
#endif
