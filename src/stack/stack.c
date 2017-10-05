#include <stdlib.h>
#include "stack.h"

/* list_init */
void stack_init(Stack *stack, void(*destroy)(void *data)) {
    /* Initialize the list */
    stack->size = 0;
    stack->destroy = destroy;
    stack->head = NULL;
    stack->tail = NULL;
    return;
}

/* stack_destroy */
void stack_destroy(Stack *stack){
    void *data;
    /* Remove each element. */
    while(stack_pop(stack, (void**)&data) == 0 && stack->destroy != NULL) {
        /* Call a user-defined function to free dynamically allocated data. */
        stack->destroy(data);
    }
    /* No operations are allowed now, but clean the structure as a precaution.*/
    memset(stack, 0, sizeof(Stack));
    return;
}

int stack_push(Stack *stack, const void *data){
    StackElmt *new_element;

    /* Allocate storage for the element. */
    if( (new_element = (StackElmt*)malloc(sizeof(StackElmt))) == NULL || stack == NULL )
       return -1;

    /* Insert the element into the list. */
    new_element->data = (void*)data;

    if(stack_size(stack) == 0)
        stack->tail = new_element;
    new_element->next = stack->head;
    stack->head = new_element;


    /* Adjust the size of the list to account for the inserted element. */
    stack->size++;
    return 0;
}

int stack_pop(Stack *stack, void **data) {
    /* Pop the data off the stack */
    StackElmt *old_element;

    /* Do not allow removal from an empty list. */
    if(stack_size(stack) == 0)
        return -1;

    *data = stack->head->data;
    old_element = stack->head;
    stack->head = stack->head->next;

    if(stack_size(stack) == 1)
        stack->tail = NULL;


    /* Free the storage allocated by the abstract datatype. */
    free(old_element);

    /* Adjust the size of the list to account for the removed element. */
    stack->size--;
    return 0;
}


/* test */
void print_stack(Stack *stack) {

    if(stack == NULL)
        return;

    for(StackElmt *item = stack->head; item != NULL; item=item->next){
        printf("%2d\n", *((int *)(item->data)) );
    }
    printf("--print done --\n");
}


int main_stack() {

    Stack *stack;
    if( ( stack = malloc(sizeof(Stack)) ) == NULL )
        return;

    stack_init(stack, NULL);


    int a = 10;
    int b = 100;
    int c = 1000;
    int *d;
    stack_push(stack, &a);
    stack_push(stack, &b);

    print_stack(stack);

    stack_pop(stack, (void *)&d);

    print_stack(stack);

    stack_push(stack,&c);

    print_stack(stack);

    stack_destroy(stack);

    return 0;
}
