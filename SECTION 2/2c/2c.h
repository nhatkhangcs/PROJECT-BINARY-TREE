#include <iostream>
#include <stack>
#include <cstring>
#include <cmath>
#include <algorithm>

class Stack
{
    public:
    int top;
    unsigned capacity;
    double* array;
};
 
// Stack Operations
Stack* createStack( unsigned capacity )
{
    Stack* stack = new Stack();
 
    if (!stack) return NULL;
 
    stack->top = -1;
    stack->capacity = capacity;
    stack->array = new double[(stack->capacity * sizeof(double))];
 
    if (!stack->array) return NULL;
 
    return stack;
}
 
double isEmpty(Stack* stack)
{
    return stack->top == -1 ;
}
 
double peek(Stack* stack)
{
    return stack->array[stack->top];
}
 
double pop(Stack* stack)
{
    if (!isEmpty(stack))
        return stack->array[stack->top--];
    return '$';
}
 
void push(Stack* stack,double op)
{
    stack->array[++stack->top] = op;
}