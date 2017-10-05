#include <stdlib.h>
#include "queue.h"

void queue_init(Queue *queue, void(*destroy)(void *data)){
    queue->size = 0;
    queue->head = NULL;
    queue->tail = NULL;
    queue->destroy = destroy;
    return;
}

void queue_destroy(Queue *queue) {
    void *data;

    while( queue_dequeue(queue, (void**)&data) == 0 && queue->destroy != NULL)
        queue->destroy(data);

    return;
}

int queue_enqueue(Queue *queue, const void *data){
    QueueElmt *new_element;

    if( ((new_element = malloc(sizeof(Queue)) ) == NULL) || queue == NULL)
        return -1;

    new_element->data = data;
    new_element->next = NULL;

    if(queue_size(queue) == 0 ){
        queue->head = new_element;
        queue->tail = new_element;
    }

    queue->tail->next = new_element;
    queue->tail = new_element;


    queue->size++;
    return 0;

}
int queue_dequeue(Queue *queue, void **data){

    QueueElmt *old_element;

    if(queue == NULL || queue_size(queue) == 0)
        return NULL;

    *data = queue->head->data;
    old_element = queue->head;
    queue->head = queue->head->next;

    if(queue_size(queue) == 1)
        queue->tail = NULL;

    free(old_element);
    return 0;
}

/* test */
void print_queue(Queue *queue) {
    if (queue == NULL)
        return;
    for(QueueElmt *item = queue->head; item != NULL; item=item->next) {

        printf("%3d\n", *((int*)item->data));
    }

    printf("--print done---\n");
}
int main(){
    Queue *queue =  malloc(sizeof(Queue));
    queue_init(queue, NULL);

    int a =10;
    int b = 100;
    int c = 1000;
    int *d;

    queue_enqueue(queue, &a);
    queue_enqueue(queue, &b);

    print_queue(queue);

    queue_dequeue(queue,&d);

    print_queue(queue);

    queue_enqueue(queue, &c);
    print_queue(queue);



    queue_destroy(queue);

    return 0;
}
