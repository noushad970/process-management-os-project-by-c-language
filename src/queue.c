#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

Queue* createQueue() {
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

void enqueue(Queue *q, int pid) {
    if (q->rear >= MAX_PROCESSES - 1) {
        printf("Queue is full!\n");
        return;
    }

    if (q->front == -1)
        q->front = 0;

    q->rear++;
    q->pid[q->rear] = pid;
}

int dequeue(Queue *q) {
    if (q->front == -1 || q->front > q->rear) {
        printf("Queue is empty!\n");
        return -1;
    }

    return q->pid[q->front++];
}

int isQueueEmpty(Queue *q) {
    return (q->front == -1 || q->front > q->rear);
}

void freeQueue(Queue *q) {
    free(q);
}
