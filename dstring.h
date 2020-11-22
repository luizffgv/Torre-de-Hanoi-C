// Dynamic strings module interface
/*    github.com/luizffgv    */

#ifndef DSTRING_H
#define DSTRING_H

#include <stddef.h>

typedef struct DString_ DString;

DString *DStringNew(void);
void DStringDestroy(DString *string);
void DStringSet(DString *str, const char *src);
void DStringCopy(char *dest, DString *str);
size_t DStringLen(DString *str);
size_t DStringSize(DString *str);
int DStringComp(DString *str_1, const char *str_2);

#endif  // #ifndef DSTRING_H
