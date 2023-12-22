#ifndef FINAL_TEST_DEFINITIONS_H
#define FINAL_TEST_DEFINITIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Representa la información que va a contener un nodo de un árbol binario.
 * En este caso, la información es el caracter correspondiente con su frecuencia de aparición.
 */
typedef struct {
    char c;
    int frequency;
} TreeNodeData;

/**
 * Representa un nodo de un árbol binario que contiene su información y sus hijos.
 */
struct TreeNode {
    TreeNodeData data;
    struct TreeNode *left;
    struct TreeNode *right;
};

/**
 * Definición de nuestro tipo de dato TreeNode para evitar escribir struct TreeNode cada vez que lo necesitemos.
 */
typedef struct TreeNode TreeNode;

/**
 * Representa la información que va a contener un nodo de una lista enlazada doble circular.
 * En este caso, la información es un puntero a un nodo de un árbol binario.
 */
typedef struct {
    TreeNode *treeNode;
} DoubleCircularLinkedListData;

/**
 * Representa un nodo de una lista enlazada doble circular que contiene su información y sus nodos adyacentes.
 */
struct DoubleCircularLinkedNode {
    DoubleCircularLinkedListData data;
    struct DoubleCircularLinkedNode *next;
    struct DoubleCircularLinkedNode *prev;
};

/**
 * Definición de nuestro tipo de dato DoubleCircularLinkedNode para evitar escribir struct DoubleCircularLinkedNode
 * cada vez que lo necesitemos.
 */
typedef struct DoubleCircularLinkedNode DoubleCircularLinkedNode;

/**
 * Definición de nuestro tipo de dato DoubleCircularLinkedList para evitar escribir DoubleCircularLinkedNode *
 * cada vez que lo necesitemos.
 */
typedef DoubleCircularLinkedNode *DoubleCircularLinkedList;

/**
 * Representa la información que va a contener un nodo de una cola.
 * En este caso, la información es un caracter ya que está principalmente diseñada para el algoritmo de Huffman
 * en la parte de decodificación de carácteres.
 */
typedef struct {
    char c;
} QueueData;

/**
 * Representa un nodo de una cola que contiene su información y su nodo adyacente.
 */
struct QueueNode {
    QueueData data;
    struct QueueNode *next;
};

/**
 * Definición de nuestro tipo de dato QueueNode para evitar escribir struct QueueNode cada vez que lo necesitemos.
 */
typedef struct QueueNode QueueNode;

/**
 * Definición de nuestro tipo de dato Queue para evitar escribir QueueNode * cada vez que lo necesitemos.
 */
typedef QueueNode *Queue;

#endif
