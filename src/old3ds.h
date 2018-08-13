#pragma once

#include "common.h"
#include "arm.h"

struct old3ds
{
    u8* boot9; //[0x10000]
    u8* datatcm; //[0x4000]
    u8* axi_wram; //[0x80000]
    u8* arm9_wram; //[0x100000]

    arm_cpu* cpu9;

    FILE* reg_access_log;

    void init();
    void exit();
};

u32 old3ds_cpu9_rw(void* dev, u32 addr);
void old3ds_cpu9_ww(void* dev, u32 addr, u32 data);