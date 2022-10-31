//  ____     ___ |    / _____ _____
// |  __    |    |___/    |     |
// |___| ___|    |    \ __|__   |     gsKit Open Source Project.
// ----------------------------------------------------------------------
// Copyright 2004 - Chris "Neovanglist" Gilbert <Neovanglist@LainOS.org>
// Copyright 2022 - Daniel Santos <danielsantos346@gmail.com>
// Licenced under Academic Free License version 2.0
// Review gsKit README & LICENSE files for further details.
//
// dmaVif.c - Interface to VIF.
//

#include "dmaVif.h"
#include <kernel.h>
#include <malloc.h>

#ifdef F_dmaKit_append_unpack_data
u64* dmaKit_append_unpack_data(u64 *p_data, u32 vu_addr, void *data, u32 size, u8 d_buffered)
{
    *p_data++ = DMA_TAG(size, 0, DMA_REF, 0, data, 0);
	*p_data++ = (VIF_CODE(0x0101 | (0 << 8), 0, VIF_STCYCL, 0) | (u64)
	VIF_CODE(vu_addr | ((u32)1 << 14) | ((u32)d_buffered << 15), ((size == 256) ? 0 : size), UNPACK_V4_32 | ((u32)0 << 4) | 0x60, 0) << 32 );

	return p_data;
}
#endif

#ifdef F_dmakit_append_start_microprogram
u64* dmaKit_append_start_microprogram(u64* p_data, u32 vu_addr)
{
    *p_data++ = DMA_TAG(0, 0, DMA_CNT, 0, 0, 0);
	*p_data++ = ((VIF_CODE(0, 0, VIF_FLUSH, 0) | (u64)VIF_CODE(0, 0, VIF_MSCAL, 0) << 32));

	*p_data++ = DMA_TAG(0, 0, DMA_END, 0, 0 , 0);
	*p_data++ = (VIF_CODE(0, 0, VIF_NOP, 0) | (u64)VIF_CODE(0, 0, VIF_NOP, 0) << 32);

    return p_data;
}
#endif

u32 dmaKit_get_microprogram_size(u32 *start, u32 *end)
{
    // Count instructions
    u32 count = (end - start) / 2;
    if (count & 1)
        count++;
    return count;
}

#ifdef F_dmaKit_upload_microprogram
void dmaKit_upload_microprogram(u32* start, u32* end, u8 vu)
{
    u32 channel = (vu == 1? DMA_CHANNEL_VIF1 : DMA_CHANNEL_VIF0);
    u32 size = dmaKit_get_microprogram_size(start, end);
	u32 packet_size = (size >> 8) + 1;
    u32 dest = 0;
	u64* p_store;
	u64* p_data;
    
    p_data = p_store = memalign(128, 16*packet_size);

    u32 *l_start = start;

    while (size > 0)
    {
        // We can only send 256 instructions in each MPGtag
        u16 curr_count = size > 256 ? 256 : size;

		*p_data++ = DMA_TAG(curr_count / 2, 0, DMA_REF, 0, (const u128 *)l_start, 0);

		*p_data++ = (VIF_CODE(0, 0, VIF_NOP, 0) | (u64)VIF_CODE(dest, curr_count & 0xFF, VIF_MPG, 0) << 32);

        l_start += curr_count * 2;
        size -= curr_count;
        dest += curr_count;
    }

	*p_data++ = DMA_TAG(0, 0, DMA_END, 0, 0 , 0);
	*p_data++ = (VIF_CODE(0, 0, VIF_NOP, 0) | (u64)VIF_CODE(0, 0, VIF_NOP, 0) << 32);

	FlushCache(0);
	dmaKit_send_chain(channel, (void *)((u32)p_store & 0x0FFFFFFF), 0);
	dmaKit_wait(channel, 0);
	free(p_store);
}
#endif
