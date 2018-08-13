#include "old3ds.h"

void old3ds::init()
{
    //TODO
    boot9 = (u8*)calloc(0x10000, 1);
    datatcm = (u8*)calloc(0x4000, 1);
    axi_wram = (u8*)calloc(0x80000, 1);
    arm9_wram = (u8*)calloc(0x100000, 1);

    reg_access_log = fopen("reglog.txt","w+");
}

void old3ds::exit()
{
    free(boot9);
    free(datatcm);
    free(axi_wram);
    free(arm9_wram);
    if(reg_access_log) fclose(reg_access_log);
}

u32 old3ds_cpu9_rw(void* dev, u32 addr)
{
    old3ds* device = (old3ds*) dev;
    addr &= 0xfffffffc;

    if(addr >= 0x08000000 && addr < 0x08100000)
    {
        return *(u32*)(device->arm9_wram + (addr & 0xfffff));
    }
    else if(addr >= 0x10000000 && addr < 0x18000000)
    {
        fprintf(device->reg_access_log, "Unknown I/O read address %08x pc %08x\n", addr, device->cpu9->r[15]);
    }
    else if(addr >= 0x1ff80000 && addr < 0x20000000)
    {
        return *(u32*)(device->axi_wram + (addr & 0x7ffff));
    }
    else if(addr >= 0xfff00000 && addr < 0xfff04000)
    {
        return *(u32*)(device->datatcm + (addr & 0x3fff));
    }
    else if(addr >= 0xffff0000)
    {
        return *(u32*)(device->boot9 + (addr & 0xffff));
    }
    else printf("Unknown read address %08x!\n", addr);
    return 0;
}

void old3ds_cpu9_ww(void* dev, u32 addr, u32 data)
{
    old3ds* device = (old3ds*) dev;
    addr &= 0xfffffffc;
    if(addr >= 0x08000000 && addr < 0x08100000)
    {
        *(u32*)(device->arm9_wram + (addr & 0xfffff)) = data;
    }
    else if(addr >= 0x10000000 && addr < 0x18000000)
    {
        fprintf(device->reg_access_log, "Unknown I/O write address %08x data %08x pc %08x\n", addr, data, device->cpu9->r[15]);
    }
    else if(addr >= 0x1ff80000 && addr < 0x20000000)
    {
        *(u32*)(device->axi_wram + (addr & 0x7ffff)) = data;
    }
    else if(addr >= 0xfff00000 && addr < 0xfff04000)
    {
        *(u32*)(device->datatcm + (addr & 0x3fff)) = data;
    }
    else printf("Unknown write address %08x data %08x!\n", addr, data);
}