/*    github.com/luizffgv    */

#include <stdlib.h>

#include "stack.h"

typedef struct Node_
{
    void *data;
    struct Node_ *next;
} Node_;

struct Stack_
{
    Node_ *top;
    size_t size;
};

Stack *StackNew(void)
{
    return calloc(1, sizeof(Stack));
}

bool StackIsEmpty(const Stack *s)
{
    return !s->top;
}

void StackPush(Stack *s, void *data)
{
    Node_ *node = malloc(sizeof(*node));

    node->data = data;
    node->next = s->top;
    s->top     = node;

    ++s->size;
}

void *StackPeek(const Stack *s)
{
    if (StackIsEmpty(s))
        return NULL;

    return s->top->data;
}

void *StackPop(Stack *s)
{
    if (StackIsEmpty(s))
        return NULL;

    void *data = s->top->data;

    Node_ *top_old = s->top;
    s->top         = s->top->next;
    free(top_old);

    --s->size;

    return data;
}

size_t StackSize(Stack *s)
{
    return s->size;
}

void StackEmpty(Stack *s, void destructor(void *))
{
    while (!StackIsEmpty(s))
        if (destructor)
            destructor(StackPop(s));
        else
            free(StackPop(s));
}

void StackDelete(Stack *s, void destructor(void *))
{
    StackEmpty(s, destructor);
    free(s);
}
