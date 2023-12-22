#include "queue.h"

Queue createQueue() {
    return NULL;
}

int calculateLengthQueue(Queue queue) {
    int length = 0;
    Queue temp = queue;
    while (temp != NULL) {
        length++;
        temp = temp->next;
    }
    return length;
}

void enqueue(Queue *queue, QueueData data) {
    Queue newNode = (Queue) malloc(sizeof(QueueNode));
    if (newNode == NULL) {
        puts("Error: No hay memoria suficiente para continuar.");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    if (*queue == NULL) {
        *queue = newNode;
    } else {
        Queue temp = *queue;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

QueueData dequeue(Queue *queue) {
    if (*queue == NULL) {
        QueueData data;
        data.c = '\0';
        return data;
    }
    Queue temp = *queue;
    QueueData data = temp->data;
    *queue = (*queue)->next;
    free(temp);
    return data;
}

void printQueue(Queue queue) {
    if (queue == NULL) {
        puts("La cola esta vacia");
        return;
    }
    Queue temp = queue;
    while (temp != NULL) {
        printf("%c ", temp->data.c);
        temp = temp->next;
    }
    puts("");
}

void destroyQueue(Queue *queue) {
    if (*queue == NULL) {
        return;
    }
    Queue temp = *queue;
    while (temp != NULL) {
        *queue = (*queue)->next;
        free(temp);
        temp = *queue;
    }
}