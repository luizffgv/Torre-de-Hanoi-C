/*    github.com/luizffgv    */

#include <stdlib.h>

#include "queue.h"

typedef struct Node_
{
    void *data;
    struct Node_ *next;
} Node_;

struct Queue_
{
    Node_ *front;
    Node_ *back;
};

Queue *QueueNew(void)
{
    return calloc(1, sizeof(Queue));
}

bool QueueIsEmpty(const Queue *q)
{
    return !q->front;
}

void QueueEnqueue(Queue *q, void *data)
{
    Node_ *node = malloc(sizeof(*node));
    node->data  = data;
    node->next  = NULL;

    if (QueueIsEmpty(q))
        q->front = node;
    else
        q->back->next = node;
    q->back = node;
}

void *QueueDequeue(Queue *q)
{
    if (QueueIsEmpty(q))
        return NULL;

    Node_ *front = q->front;
    void *data   = q->front->data;
    q->front     = q->front->next;

    free(front);

    return data;
}

void *QueuePeek(Queue *q)
{
    if (QueueIsEmpty(q))
        return NULL;

    return q->front->data;
}

void QueueEmpty(Queue *q, void destructor(void *))
{
    while (!QueueIsEmpty(q))
        if (destructor)
            destructor(QueueDequeue(q));
        else
            free(QueueDequeue(q));
}

void QueueDelete(Queue *q, void destructor(void *))
{
    QueueEmpty(q, destructor);
    free(q);
}
