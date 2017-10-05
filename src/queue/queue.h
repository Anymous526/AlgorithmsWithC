#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>

typedef struct QueueElmt_ {
    void*               data;
    struct QueueElmt_   *next;
}QueueElmt;

typedef struct Queue_{
    int size;
    int (*match)(const void *key1, const void *key2);
    void (*destroy)(void *data);
    QueueElmt *head;
    QueueElmt *tail;
}Queue;

/* public interface */
void queue_init(Queue *queue, void(*destroy)(void *data) );
void queue_destroy(Queue *queue);

int queue_enqueue(Queue *queue, const void *data);
int queue_dequeue(Queue *queue, void **data);

#define queue_peek(queue)   ( (queue)->head == NULL ? NULL: (queue)->head->data )
#define queue_size(queue)   ((queue)->size)

#endif // QUEUE_H
