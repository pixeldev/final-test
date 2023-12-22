#ifndef FINAL_TEST_DOUBLE_CIRCULAR_LINKED_LIST_H
#define FINAL_TEST_DOUBLE_CIRCULAR_LINKED_LIST_H

#include "definitions.h"
#include "huffman.h"

/**
 * Metodo que calcula el tamaño de una lista doblemente enlazada circular.
 * @param list Lista doblemente enlazada circular.
 * @return Tamaño de la lista.
 */
int calculateLengthDoubleCircularLinkedList(DoubleCircularLinkedList list);

/**
 * Metodo que crea una lista doblemente enlazada circular. En caso de que no haya memoria suficiente para crear la lista
 * se termina la ejecucion del programa.
 * @return Lista doblemente enlazada circular.
 */
DoubleCircularLinkedList createDoubleCircularLinkedList();

/**
 * Metodo que busca un dato de forma lineal en una lista doblemente enlazada circular.
 * @param list Lista doblemente enlazada circular.
 * @param c Caracter a buscar.
 * @return Dato encontrado.
 */
DoubleCircularLinkedListData findDataDoubleCircularLinkedList(DoubleCircularLinkedList list, char c);

/**
 * Metodo que inserta un dato al final de una lista doblemente enlazada circular.
 * @param list Lista doblemente enlazada circular.
 * @param data Dato a insertar.
 */
void insertAtEndDoubleCircularLinkedList(DoubleCircularLinkedList *list, DoubleCircularLinkedListData data);

/**
 * Metodo que elimina un dato al inicio de una lista doblemente enlazada circular.
 * @param list Lista doblemente enlazada circular.
 * @return Dato eliminado.
 */
DoubleCircularLinkedListData deleteAtStartDoubleCircularLinkedList(DoubleCircularLinkedList *list);

/**
 * Metodo que ordena una lista doblemente enlazada circular utilizando el algoritmo de ordenamiento por seleccion.
 * @param list Lista doblemente enlazada circular.
 */
void sortBySelectionDoubleCircularLinkedList(DoubleCircularLinkedList *list);

/**
 * Metodo que imprime una lista doblemente enlazada circular.
 * @param list Lista doblemente enlazada circular.
 */
void printDoubleCircularLinkedList(DoubleCircularLinkedList list);

/**
 * Metodo que libera la memoria utilizada por una lista doblemente enlazada circular. Al finalizar la ejecucion de este
 * el puntero a la lista apuntara a NULL.
 * @param list Lista doblemente enlazada circular.
 */
void destroyDoubleCircularLinkedList(DoubleCircularLinkedList *list);

#endif