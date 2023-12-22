/**
 * Nombres: González Garcés Rodrigo y Miranda San Martin Angel
 * Grupo: 2BV2
 * Carrera: Ingeniería en Inteligencia Artificial
 * Última fecha de modificación: 22/12/2023 - 14:00
 */
#include "queue.h"

Queue createQueue() {
    return NULL; // Simplemente se retorna NULL, ya que NULL es el apuntador a una cola vacía.
}

int calculateLengthQueue(Queue queue) {
    int length = 0;
    Queue temp = queue; // Se crea un apuntador temporal para no perder la referencia de la cola.
    while (temp != NULL) { // Mientras el apuntador temporal no sea NULL, se aumenta la longitud y se avanza el apuntador.
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
    // Se asignan los valores al nuevo nodo.
    newNode->data = data;
    newNode->next = NULL;
    if (*queue == NULL) { // Si la cola está vacía, se asigna el nuevo nodo como la cola.
        *queue = newNode;
    } else { // Si la cola no está vacía, se recorre la cola hasta llegar al último nodo y se asigna el nuevo nodo como el siguiente del último nodo.
        Queue temp = *queue;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

QueueData dequeue(Queue *queue) {
    if (*queue == NULL) { // Si la cola está vacía, se retorna un elemento nulo.
        QueueData data;
        data.c = '\0';
        return data;
    }
    Queue temp = *queue; // Se crea un apuntador temporal para no perder la referencia de la cola.
    QueueData data = temp->data; // Se guarda el dato del primer nodo.
    *queue = (*queue)->next; // Se avanza la cola.
    free(temp); // Se libera la memoria del primer nodo.
    return data;
}

void printQueue(Queue queue) {
    if (queue == NULL) { // Si la cola está vacía, se imprime un mensaje.
        puts("La cola esta vacia");
        return;
    }
    Queue temp = queue; // Se crea un apuntador temporal para no perder la referencia de la cola.
    while (temp != NULL) { // Mientras el apuntador temporal no sea NULL, se imprime el dato del nodo y se avanza el apuntador.
        printf("%c ", temp->data.c);
        temp = temp->next;
    }
    puts("");
}

void destroyQueue(Queue *queue) {
    if (*queue == NULL) { // Si la cola está vacía, no se hace nada.
        return;
    }
    Queue temp = *queue; // Se crea un apuntador temporal para no perder la referencia de la cola.
    while (temp != NULL) { // Mientras el apuntador temporal no sea NULL, se libera la memoria del nodo y se avanza el apuntador.
        *queue = (*queue)->next;
        free(temp);
        temp = *queue;
    }
}