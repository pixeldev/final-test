#include "double_circular_linked_list.h"

int calculateLengthDoubleCircularLinkedList(DoubleCircularLinkedList list) {
    int length = 0;
    DoubleCircularLinkedList temp = list->next;
    while (temp != list) {
        length++;
        temp = temp->next;
    }
    return length;
}

DoubleCircularLinkedList createDoubleCircularLinkedList() {
    DoubleCircularLinkedList list = (DoubleCircularLinkedList) malloc(sizeof(DoubleCircularLinkedNode));
    if (list == NULL) {
        puts("Error: No hay memoria suficiente para continuar.");
        exit(1);
    }
    list->next = list;
    list->prev = list;
    return list;
}

DoubleCircularLinkedListData findDataDoubleCircularLinkedList(DoubleCircularLinkedList list, char c) {
    DoubleCircularLinkedList temp = list->next;
    while (temp != list) {
        if (temp->data.treeNode->data.c == c) {
            return temp->data;
        }
        temp = temp->next;
    }
    DoubleCircularLinkedListData data;
    data.treeNode = NULL;
    return data;
}

void insertAtEndDoubleCircularLinkedList(DoubleCircularLinkedList *list, DoubleCircularLinkedListData data) {
    DoubleCircularLinkedList newNode = (DoubleCircularLinkedList) malloc(sizeof(DoubleCircularLinkedNode));
    if (newNode == NULL) {
        puts("Error: No hay memoria suficiente para continuar.");
        exit(1);
    }
    newNode->data = data;
    newNode->next = *list;
    newNode->prev = (*list)->prev;
    (*list)->prev->next = newNode;
    (*list)->prev = newNode;
}

DoubleCircularLinkedListData deleteAtStartDoubleCircularLinkedList(DoubleCircularLinkedList *list) {
    DoubleCircularLinkedList temp = (*list)->next;
    DoubleCircularLinkedListData data = temp->data;
    (*list)->next = temp->next;
    temp->next->prev = *list;
    free(temp);
    return data;
}

void sortBySelectionDoubleCircularLinkedList(DoubleCircularLinkedList *list) {
    DoubleCircularLinkedList temp = (*list)->next;
    while (temp->next != *list) {
        DoubleCircularLinkedList min = temp;
        DoubleCircularLinkedList temp2 = temp->next;
        while (temp2 != *list) {
            if (temp2->data.treeNode->data.frequency < min->data.treeNode->data.frequency) {
                min = temp2;
            }
            temp2 = temp2->next;
        }
        DoubleCircularLinkedListData data = temp->data;
        temp->data = min->data;
        min->data = data;
        temp = temp->next;
    }
}

void printDoubleCircularLinkedList(DoubleCircularLinkedList list) {
    DoubleCircularLinkedList temp = list->next;
    while (temp != list) {
        printTreeNodeData(temp->data.treeNode->data);
        temp = temp->next;
    }
}

void destroyDoubleCircularLinkedList(DoubleCircularLinkedList *list) {
    DoubleCircularLinkedList temp = (*list)->next;
    while (temp != *list) {
        DoubleCircularLinkedList temp2 = temp;
        temp = temp->next;
        free(temp2);
    }
    free(*list);
}