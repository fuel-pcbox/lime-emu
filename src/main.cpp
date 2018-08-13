#include "common.h"
#include "arm.h"
#include "old3ds.h"

int main(int ac, char** av)
{
    if(ac < 2)
    {
        printf("usage: %s <path_to_arm9_bootrom>\n", av[0]);
        return 1;
    }

    old3ds dev;
    arm_cpu cpu9;

    cpu9.type = arm_type::arm9;

    cpu9.init();

    dev.cpu9 = &cpu9;

    dev.init();

    cpu9.device = &dev;

    cpu9.rw_real = old3ds_cpu9_rw;
    cpu9.ww_real = old3ds_cpu9_ww;
    
    FILE* fp = fopen(av[1],"rb");
    if(!fp)
    {
        printf("unable to open %s, are you sure it exists?\n", av[2]);
        return 5;
    }
    if(fread(dev.boot9, 1, 0x10000, fp) != 0x10000)
    {
        fclose(fp);
        return 6;
    }
    fclose(fp);

    for(int i = 0; i < 10000; i++)
    {
        cpu9.run(1);
    }

    dev.exit();

    return 0;
}
