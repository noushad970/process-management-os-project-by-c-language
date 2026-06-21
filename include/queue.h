#ifndef QUEUE_H
#define QUEUE_H

#include "process.h"

typedef struct {
    int pid[MAX_PROCESSES];
    int front;
    int rear;
} Queue;

Queue* createQueue();
void enqueue(Queue *q, int pid);
int dequeue(Queue *q);
int isQueueEmpty(Queue *q);
void freeQueue(Queue *q);

#endif
