#include <stdlib.h>

#include "dstring.h"
#include "hanoimonk.h"

struct HanoiMonk_
{
    DString *name;
};

HanoiMonk *HanoiMonkNew(char *name)
{
    HanoiMonk *monk = malloc(sizeof(*monk));
    monk->name      = DStringNew();

    DStringSet(monk->name, name);

    return monk;
}

void HanoiMonkDelete(HanoiMonk *monk)
{
    DStringDestroy(monk->name);

    free(monk);
}

void HanoiMonkCpy(HanoiMonk *dest, HanoiMonk *src)
{
    char *str = malloc(DStringSize(src->name));
    DStringCopy(str, src->name);
    DStringSet(dest->name, str);
}

size_t HanoiMonkNameSz(HanoiMonk *monk)
{
    return DStringSize(monk->name);
}

void HanoiMonkNameCpy(HanoiMonk *monk, char *dest)
{
    DStringCopy(dest, monk->name);
}
