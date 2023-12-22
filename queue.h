#ifndef FINAL_TEST_QUEUE_H
#define FINAL_TEST_QUEUE_H

#include "definitions.h"

/**
 * Método que crea una cola vacía, es decir, una cola que apunta a NULL.
 * @return El apuntador NULL.
 */
Queue createQueue();

/**
 * Método que calcula la longitud de una cola.
 * @param queue La cola de la cual se quiere calcular la longitud.
 * @return La longitud de la cola.
 */
int calculateLengthQueue(Queue queue);

/**
 * Método que agrega un elemento al final de la cola.
 * @param queue La cola a la cual se le quiere agregar un elemento.
 * @param data El elemento que se quiere agregar a la cola.
 */
void enqueue(Queue *queue, QueueData data);

/**
 * Método que elimina el primer elemento de la cola.
 * @param queue La cola de la cual se quiere eliminar el primer elemento.
 * @return El elemento que se eliminó de la cola.
 */
QueueData dequeue(Queue *queue);

/**
 * Método que imprime los elementos de la cola.
 * @param queue La cola que se quiere imprimir.
 */
void printQueue(Queue queue);

/**
 * Método que libera la memoria de la cola.
 * @param queue La cola que se quiere liberar.
 */
void destroyQueue(Queue *queue);

#endif
