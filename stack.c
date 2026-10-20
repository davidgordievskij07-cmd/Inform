#include "stack.h"

#include <stdlib.h>

bool push(Stack *stack, char value)
{
    StackElement *element = malloc(sizeof(StackElement));
    if (element == NULL) {
        return false;
    }
    element->value = value;
    element->next = stack->top;
    stack->top = element;
    return true;
}

char pop(Stack *stack)
{
    StackElement *oldTop = stack->top;
    char value = oldTop->value;
    stack->top = oldTop->next;
    free(oldTop);
    return value;
}

bool isEmpty(const Stack *stack)
{
    return stack->top == NULL;
}

void clear(Stack *stack)
{
    while (!isEmpty(stack)) {
        pop(stack);
    }
}
