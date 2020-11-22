// github.com/luizffgv

#include <stdlib.h>
#include <string.h>

#include "dstring.h"

struct DString_
{
    char *txt;
};

DString *DStringNew(void)
{
    return calloc(1, sizeof(struct DString_));
}

void DStringDestroy(DString *string)
{
    free(string);
}

void DStringSet(DString *str, const char *src)
{
    free(str->txt);
    str->txt = malloc(strlen(src) + 1);
    strcpy(str->txt, src);
}

void DStringCopy(char *dest, DString *str)
{
    strcpy(dest, str->txt);
}

size_t DStringLen(DString *str)
{
    return strlen(str->txt);
}

size_t DStringSize(DString *str)
{
    return strlen(str->txt) + 1;
}

int DStringComp(DString *str_1, const char *str_2)
{
    return strcmp(str_1->txt, str_2);
}
