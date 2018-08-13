#include "old3ds.h"

void old3ds::init()
{
    //TODO
    boot9 = (u8*)calloc(1, 0x10000);
    datatcm = (u8*)calloc(1, 0x4000);

    reg_access_log = fopen("reglog.txt","w+");
}

void old3ds::exit()
{
    free(boot9);
    if(reg_access_log) fclose(reg_access_log);
}

u32 old3ds_cpu9_rw(void* dev, u32 addr)
{
    old3ds* device = (old3ds*) dev;
    addr &= 0xfffffffc;

    if(addr >= 0x10000000 && addr < 0x18000000)
    {
        fprintf(device->reg_access_log, "Unknown I/O read address %08x pc %08x\n", addr, device->cpu9->r[15]);
        return 0;
    }
    else if(addr >= 0xfff00000 && addr < 0xfff04000)
    {
        return *(u32*)(device->datatcm + (addr & 0x3fff));
    }
    else if(addr >= 0xffff0000)
    {
        return *(u32*)(device->boot9 + (addr & 0xffff));
    }
    else printf("Unknown address %08x!\n", addr);
    return 0;
}

void old3ds_cpu9_ww(void* dev, u32 addr, u32 data)
{
    old3ds* device = (old3ds*) dev;
    addr &= 0xfffffffc;
    if(addr >= 0x10000000 && addr < 0x18000000)
    {
        fprintf(device->reg_access_log, "Unknown I/O write address %08x data %08x pc %08x\n", addr, data, device->cpu9->r[15]);
    }
    else if(addr >= 0xfff00000 && addr < 0xfff04000)
    {
        *(u32*)(device->datatcm + (addr & 0x3fff)) = data;
    }
}