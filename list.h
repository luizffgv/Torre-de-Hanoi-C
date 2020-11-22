// Generic linked list module
/*    github.com/luizffgv    */

#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include <stddef.h>

typedef struct Node_ List;
typedef struct Node_ ListIterator;

List *ListNew(void);
void ListDestroy(List **list, void destructor(void *));
size_t ListSize(List *list);
void ListCopy(List **dest, List *src);
int ListInsert(List *list, int pos, void *data);
void ListPrepend(List **list, void *data);
void ListAppend(List **list, void *data);
int ListRemove(List **list, int index, void destructor(void *));
void *ListGet(List *list, int index);
void ListReverse(List *list);
bool ListIteratorEndReached(ListIterator *iterator);
ListIterator *ListBegin(List *list);
void ListIteratorAdvance(ListIterator **iterator);
void *ListIteratorData(ListIterator *iterator);

#endif  // #ifndef LIST_H
