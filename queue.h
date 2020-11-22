// Generic queue using linked list */
/*    github.com/luizffgv    */

#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stddef.h>

typedef struct Queue_ Queue;

// Returns a newly created queue
Queue *QueueNew(void);
// Returns true if the queue is empty
bool QueueIsEmpty(const Queue *q);
// Pushes an element into the queue
void QueueEnqueue(Queue *q, void *data);
// Pops an element from the queue
void *QueueDequeue(Queue *q);
// Peeks an element from the queue
void *QueuePeek(Queue *q);
// Empties the queue
void QueueEmpty(Queue *q, void destructor(void *));
// Deletes the queue and its elements
void QueueDelete(Queue *q, void destructor(void *));

#endif  // #ifndef QUEUE_H
