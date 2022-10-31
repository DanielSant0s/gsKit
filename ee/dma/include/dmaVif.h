//  ____     ___ |    / _____ _____
// |  __    |    |___/    |     |
// |___| ___|    |    \ __|__   |     gsKit Open Source Project.
// ----------------------------------------------------------------------
// Copyright 2004 - Chris "Neovanglist" Gilbert <Neovanglist@LainOS.org>
// Copyright 2022 - Daniel Santos <danielsantos346@gmail.com>
// Licenced under Academic Free License version 2.0
// Review gsKit README & LICENSE files for further details.
//
// dmaVif.h - Header for dmaVif.c
//

#ifndef __DMAVIF_H__
#define __DMAVIF_H__

#include "dmaKit.h"

#define UNPACK_S_32 0x00
#define UNPACK_S_16 0x01
#define UNPACK_S_8 0x02
#define UNPACK_V2_32 0x04
#define UNPACK_V2_16 0x05
#define UNPACK_V2_8 0x06
#define UNPACK_V3_32 0x08
#define UNPACK_V3_16 0x09
#define UNPACK_V3_8 0x0A
#define UNPACK_V4_32 0x0C
#define UNPACK_V4_16 0x0D
#define UNPACK_V4_8 0x0E
#define UNPACK_V4_5 0x0F

#define VIF_NOP 0
#define VIF_STCYCL 1
#define VIF_OFFSET 2
#define VIF_BASE 3
#define VIF_ITOP 4
#define VIF_STMOD 5
#define VIF_MSKPATH3 6
#define VIF_MARK 7
#define VIF_FLUSHE 16
#define VIF_FLUSH 17
#define VIF_FLUSHA 19
#define VIF_MSCAL 20
#define VIF_MSCNT 23
#define VIF_MSCALF 21
#define VIF_STMASK 32
#define VIF_STROW 48
#define VIF_STCOL 49
#define VIF_MPG 74
#define VIF_DIRECT 80
#define VIF_DIRECTHL 81

#define VIF_CODE(_immediate, _num, _cmd, _irq) ((u32)(_immediate) | ((u32)(_num) << 16) | ((u32)(_cmd) << 24) | ((u32)(_irq) << 31))

#ifdef __cplusplus
extern "C" {
#endif

void dmaKit_upload_microprogram(u32* start, u32* end, u8 vu);
u64* dmaKit_append_unpack_data(u64 *p_data, u32 vu_addr, void *data, u32 size, u8 d_buffered);
u64* dmaKit_append_start_microprogram(u64* p_data, u32 vu_addr);

#ifdef __cplusplus
}
#endif

#endif /* __DMAVIF_H__ */
