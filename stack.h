// Generic stack
/*    github.com/luizffgv    */

#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stddef.h>

typedef struct Stack_ Stack;

// Returns a newly created stack
Stack *StackNew(void);
// Returns true if the stack is empty
bool StackIsEmpty(const Stack *s);
// Pushes an element onto the stack
void StackPush(Stack *s, void *data);
// Peeks the top of the stack
void *StackPeek(const Stack *s);
// Pops an element from the stack
void *StackPop(Stack *s);
// Returns the number of elements in the stack
size_t StackSize(Stack *s);
// Empties the stack
void StackEmpty(Stack *s, void destructor(void *));
// Deletes the stack and its elements
void StackDelete(Stack *s, void destructor(void *));

#endif  // #ifndef STACK_H
