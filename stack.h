#pragma once

#include <stdbool.h>

typedef struct StackElement {
    char value;
    struct StackElement *next;
} StackElement;

typedef struct {
    StackElement *top;
} Stack;

bool push(Stack *stack, char value);

char pop(Stack *stack);

bool isEmpty(const Stack *stack);

void clear(Stack *stack);
