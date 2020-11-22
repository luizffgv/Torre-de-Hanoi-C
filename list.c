#include "list.h"
#include <stdbool.h>
#include <stdlib.h>

typedef struct Node_
{
    void *data;
    struct Node_ *next;
} Node_;

List *ListNew(void)
{
    return NULL;
}

void ListDestroy(List **list, void destructor(void *))
{
    Node_ *node_cur = *list;
    Node_ *node_next;

    while (node_cur)
    {
        node_next = node_cur->next;
        if (destructor)
            destructor(node_cur->data);
        free(node_cur);
        node_cur = node_next;
    }

    *list = NULL;
}

size_t ListSize(List *list)
{
    size_t sz = 0;

    ListIterator *it = ListBegin(list);
    while (!ListIteratorEndReached(it))
    {
        ++sz;
        ListIteratorAdvance(&it);
    }

    return sz;
}

void ListCopy(List **dest, List *src)
{
    while (!ListSize(*dest)) ListRemove(dest, 0, NULL);

    Node_ **src_cur  = &src;
    Node_ **dest_cur = dest;

    while (*src_cur)
    {
        *dest_cur         = malloc(sizeof(**dest_cur));
        (*dest_cur)->data = (*src_cur)->data;
        src_cur           = &(*src_cur)->next;
        (*dest_cur)->next = *src_cur;
        dest_cur          = &(*dest_cur)->next;
    }

    *dest_cur = NULL;
}

int ListInsert(List *list, int pos, void *data)
{
    Node_ **node_ptr = &list;

    while (pos--)
    {
        if (!node_ptr)
            return 1;  // List too small
        node_ptr = &(*node_ptr)->next;
    }

    Node_ *node_aux   = *node_ptr;
    *node_ptr         = malloc(sizeof(**node_ptr));
    (*node_ptr)->next = node_aux;
    (*node_ptr)->data = data;

    return 0;
}

void ListPrepend(List **list, void *data)
{
    Node_ *node_new;
    node_new       = malloc(sizeof(*node_new));
    node_new->data = data;
    node_new->next = *list;
    *list          = node_new;
}

void ListAppend(List **list, void *data)
{
    Node_ **last = list;
    while (*last != NULL) last = &(*last)->next;

    *last           = malloc(sizeof(**last));
    Node_ *new_node = *last;
    new_node->next  = NULL;
    new_node->data  = data;
}

int ListRemove(List **list, int index, void destructor(void *))
{
    Node_ **node_ptr = list;

    while (index--)
    {
        if (!node_ptr)
            return 1;
        node_ptr = &(*node_ptr)->next;
    }

    Node_ *node_tmp = *node_ptr;
    *node_ptr       = (*node_ptr)->next;
    if (destructor)
        destructor(node_tmp->data);
    free(node_tmp);

    return 0;
}

void *ListGet(List *list, int index)
{
    Node_ *node_ptr = list;

    if (!node_ptr)
        return NULL;

    while (index--)
    {
        node_ptr = node_ptr->next;
        if (!node_ptr)
            return NULL;
    }

    return node_ptr->data;
}

void ListReverse(List *list)
{
    Node_ *node_prev = NULL;
    Node_ *node_cur  = list;
    Node_ *node_next = NULL;

    while (node_cur != NULL)
    {
        node_next      = node_cur->next;
        node_cur->next = node_prev;
        node_prev      = node_cur;
        node_cur       = node_next;
    }

    list = node_prev;
}

bool ListIteratorEndReached(ListIterator *iterator)
{
    return iterator == NULL;
}

ListIterator *ListBegin(List *list)
{
    return list;
}

void ListIteratorAdvance(ListIterator **iterator)
{
    if (*iterator)
        *iterator = (*iterator)->next;
}

void *ListIteratorData(ListIterator *iterator)
{
    return iterator->data;
}
