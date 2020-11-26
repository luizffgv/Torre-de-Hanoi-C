/**
 * @file hanoimonk.c
 * @author Luiz Fernando F. G. Valle (github.com/luizffgv)
 * @brief Implementation of the module hanoimonk
 * @version 1.0
 * @date 2020-11-26
 *
 * @copyright Copyright (c) 2020.
 *            Licensed under the GPL-3.0 License.
 *            See LICENSE in the project root for license information
 *
 */

#include <stdlib.h>

#include "dstring.h"
#include "hanoimonk.h"

/**
 * @brief Internal representation of HanoiMonk
 * 
 */
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
