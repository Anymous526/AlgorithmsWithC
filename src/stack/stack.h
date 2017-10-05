#ifndef STACK_H
#define STACK_H

/* Define a structure for linked list elements. */
typedef struct StackElmt_ {
    void *data;
    struct StackElmt_ *next;
}StackElmt;

/* Define a structure for linked lists. */
typedef struct Stack_ {
    int size;
    int (*match)(const void *key1, const void *key2);
    void (*destroy)(void *data);
    StackElmt *head;
    StackElmt *tail;
}Stack;

/* Public Interface */
void stack_init(Stack *stack, void(*destroy)(void *data));
void stack_destroy(Stack *stack);

int stack_push(Stack *stack,const void *data);
int stack_pop(Stack *stack,  void **data);
#define stack_peek(stack)  ((stack)->head == NULL ? NULL : (stack)->head->data)
#define stack_size(stack)  ((stack)->size)

#endif // STACK_H
