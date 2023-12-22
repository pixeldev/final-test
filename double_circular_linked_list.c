/**
 * Nombres: González Garcés Rodrigo y Miranda San Martin Angel
 * Grupo: 2BV2
 * Carrera: Ingeniería en Inteligencia Artificial
 * Última fecha de modificación: 22/12/2023 - 14:00
 */
#include "double_circular_linked_list.h"

int calculateLengthDoubleCircularLinkedList(DoubleCircularLinkedList list) {
    int length = 0;
    // Se recorre la lista desde el siguiente del nodo centinela hasta el nodo centinela.
    DoubleCircularLinkedList temp = list->next;
    while (temp != list) {
        length++;
        temp = temp->next; // Se pasa al siguiente nodo.
    }
    return length;
}

DoubleCircularLinkedList createDoubleCircularLinkedList() {
    DoubleCircularLinkedList list = (DoubleCircularLinkedList) malloc(sizeof(DoubleCircularLinkedNode));
    if (list == NULL) {
        puts("Error: No hay memoria suficiente para continuar.");
        exit(1);
    }
    // Se inicializa el nodo centinela de forma que apunte a si mismo en ambos sentidos.
    list->next = list;
    list->prev = list;
    return list;
}

DoubleCircularLinkedListData findDataDoubleCircularLinkedList(DoubleCircularLinkedList list, char c) {
    DoubleCircularLinkedList temp = list->next;
    while (temp != list) { // Mientras no se llegue al nodo centinela.
        if (temp->data.treeNode->data.c == c) { // Si el caracter del nodo actual es igual al caracter buscado.
            return temp->data;
        }
        temp = temp->next; // Se pasa al siguiente nodo.
    }
    DoubleCircularLinkedListData data;
    data.treeNode = NULL; // Se retorna un nodo nulo si no se encuentra el caracter.
    return data;
}

void insertAtEndDoubleCircularLinkedList(DoubleCircularLinkedList *list, DoubleCircularLinkedListData data) {
    DoubleCircularLinkedList newNode = (DoubleCircularLinkedList) malloc(sizeof(DoubleCircularLinkedNode));
    if (newNode == NULL) {
        puts("Error: No hay memoria suficiente para continuar.");
        exit(1);
    }
    // Conexion del nuevo nodo con el nodo centinela.
    newNode->data = data; // Se asigna el dato al nuevo nodo.
    newNode->next = *list; // El siguiente del nuevo nodo apunta al nodo centinela.
    newNode->prev = (*list)->prev; // El anterior del nuevo nodo apunta al anterior del nodo centinela.
    (*list)->prev->next = newNode; // El siguiente del anterior del nodo centinela apunta al nuevo nodo.
    (*list)->prev = newNode; // El anterior del nodo centinela apunta al nuevo nodo.
}

DoubleCircularLinkedListData deleteAtStartDoubleCircularLinkedList(DoubleCircularLinkedList *list) {
    DoubleCircularLinkedList temp = (*list)->next; // Se guarda el nodo a eliminar.
    DoubleCircularLinkedListData data = temp->data; // Se guarda el dato del nodo a eliminar.
    (*list)->next = temp->next; // El siguiente del nodo centinela apunta al siguiente del nodo a eliminar.
    temp->next->prev = *list; // El anterior del siguiente del nodo a eliminar apunta al nodo centinela.
    free(temp);
    return data;
}

void sortBySelectionDoubleCircularLinkedList(DoubleCircularLinkedList *list) {
    DoubleCircularLinkedList temp = (*list)->next; // Se guarda el siguiente del nodo centinela.
    while (temp->next != *list) { // Mientras no se llegue al nodo centinela.
        DoubleCircularLinkedList min = temp; // Se guarda el nodo actual como el nodo con el menor valor.
        DoubleCircularLinkedList temp2 = temp->next; // Se guarda el siguiente del nodo actual.
        while (temp2 != *list) { // Mientras no se llegue al nodo centinela.
            if (temp2->data.treeNode->data.frequency < min->data.treeNode->data.frequency) { // Si el valor del nodo actual es menor al valor del nodo con el menor valor.
                min = temp2; // Se guarda el nodo actual como el nodo con el menor valor.
            }
            temp2 = temp2->next; // Se pasa al siguiente nodo.
        }
        DoubleCircularLinkedListData data = temp->data; // Se guarda el dato del nodo actual.
        temp->data = min->data; // Se asigna el dato del nodo con el menor valor al nodo actual.
        min->data = data; // Se asigna el dato del nodo actual al nodo con el menor valor.
        temp = temp->next; // Se pasa al siguiente nodo.
    }
}

void printDoubleCircularLinkedList(DoubleCircularLinkedList list) {
    DoubleCircularLinkedList temp = list->next;
    while (temp != list) { // Mientras no se llegue al nodo centinela.
        printTreeNodeData(temp->data.treeNode->data);
        temp = temp->next; // Se pasa al siguiente nodo.
    }
}

void destroyDoubleCircularLinkedList(DoubleCircularLinkedList *list) {
    DoubleCircularLinkedList temp = (*list)->next;
    while (temp != *list) { // Mientras no se llegue al nodo centinela.
        DoubleCircularLinkedList temp2 = temp; // Se guarda el nodo actual.
        temp = temp->next; // Se pasa al siguiente nodo.
        free(temp2); // Se libera la memoria del nodo actual.
    }
    free(*list); // Se libera la memoria del nodo centinela.
}