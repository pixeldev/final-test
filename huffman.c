#include "huffman.h"

void printTreeNodeData(TreeNodeData data) {
    if (data.c == '\0') {
        printf("NULL: %d\n", data.frequency);
    } else if (data.c == '\n') {
        printf("\\n: %d\n", data.frequency);
    } else {
        printf("%c: %d\n", data.c, data.frequency);
    }
}

TreeNode *createTreeNode(TreeNodeData data) {
    TreeNode *node = (TreeNode *) malloc(sizeof(TreeNode));
    if (node == NULL) {
        puts("Error: No hay memoria suficiente para continuar.");
        exit(1);
    }
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void destroyHuffmanTree(TreeNode *node) {
    if (node == NULL) {
        return;
    }
    destroyHuffmanTree(node->left);
    destroyHuffmanTree(node->right);
    free(node);
}

TreeNode *createHuffmanTree(DoubleCircularLinkedList *list) {
    while (calculateLengthDoubleCircularLinkedList(*list) > 1) {
        DoubleCircularLinkedListData data1 = deleteAtStartDoubleCircularLinkedList(list);
        DoubleCircularLinkedListData data2 = deleteAtStartDoubleCircularLinkedList(list);
        int data1Frequency = data1.treeNode->data.frequency;
        int data2Frequency = data2.treeNode->data.frequency;
        TreeNode *node = createTreeNode((TreeNodeData) {.c = '\0', .frequency = data1Frequency + data2Frequency});
        node->left = data1.treeNode;
        node->right = data2.treeNode;
        insertAtEndDoubleCircularLinkedList(list, (DoubleCircularLinkedListData) {.treeNode = node});
        sortBySelectionDoubleCircularLinkedList(list);
    }
    return (*list)->next->data.treeNode;
}

char *encodeChar(TreeNode *node, char c) {
    if (node == NULL) {
        return NULL;
    }
    if (node->left == NULL && node->right == NULL) {
        if (node->data.c == c) {
            char *huffmanCode = (char *) malloc(sizeof(char) * 2);
            if (huffmanCode == NULL) {
                puts("Error: No hay memoria suficiente para continuar.");
                exit(1);
            }
            huffmanCode[0] = '\0';
            return huffmanCode;
        } else {
            return NULL;
        }
    }
    char *huffmanCode = encodeChar(node->left, c);
    if (huffmanCode != NULL) {
        char *newHuffmanCode = (char *) malloc(sizeof(char) * (strlen(huffmanCode) + 2));
        if (newHuffmanCode == NULL) {
            puts("Error: No hay memoria suficiente para continuar.");
            exit(1);
        }
        strcpy(newHuffmanCode, "0");
        strcat(newHuffmanCode, huffmanCode);
        free(huffmanCode);
        return newHuffmanCode;
    }
    huffmanCode = encodeChar(node->right, c);
    if (huffmanCode != NULL) {
        char *newHuffmanCode = (char *) malloc(sizeof(char) * (strlen(huffmanCode) + 2));
        if (newHuffmanCode == NULL) {
            puts("Error: No hay memoria suficiente para continuar.");
            exit(1);
        }
        strcpy(newHuffmanCode, "1");
        strcat(newHuffmanCode, huffmanCode);
        free(huffmanCode);
        return newHuffmanCode;
    }
    return NULL;
}

char decodeChar(TreeNode *node, Queue *queue) {
    if (node == NULL) {
        return '\0';
    }
    if (node->left == NULL && node->right == NULL) {
        return node->data.c;
    }
    if (*queue != NULL && (*queue)->data.c == '0') {
        dequeue(queue);
        return decodeChar(node->left, queue);
    }
    if (*queue != NULL && (*queue)->data.c == '1') {
        dequeue(queue);
        return decodeChar(node->right, queue);
    }
    return '\0';
}

char *encode(char *text, TreeNode *huffmanTree) {
    int textLength = strlen(text);
    char *encodedText = NULL;
    int encodedTextLength = 0;
    char *huffmanCode = NULL;
    for (int i = 0; i < textLength; i++) {
        huffmanCode = encodeChar(huffmanTree, text[i]);
        if (huffmanCode == NULL) {
            puts("Error: Invalid text.");
            return NULL;
        }
        encodedTextLength += strlen(huffmanCode);
        if (encodedText == NULL) {
            encodedText = (char *) malloc(sizeof(char) * (encodedTextLength + 1));
            if (encodedText == NULL) {
                puts("Error: No hay memoria suficiente para continuar.");
                exit(1);
            }
        } else {
            encodedText = (char *) realloc(encodedText, sizeof(char) * (encodedTextLength + 1));
            if (encodedText == NULL) {
                puts("Error: No hay memoria suficiente para continuar.");
                exit(1);
            }
        }
        strcat(encodedText, huffmanCode);
        free(huffmanCode);
    }
    if (encodedText != NULL) {
        encodedText[encodedTextLength] = '\0';
    }
    return encodedText;
}

void encodeToFilePath(char *text, char *filePath, TreeNode *huffmanTree) {
    FILE *file = fopen(filePath, "w");
    if (file == NULL) {
        printf("Error: No se pudo abrir el archivo %s.", filePath);
        return;
    }
    char *encodedText = encode(text, huffmanTree);
    fputs(encodedText, file);
    fclose(file);
    printf("%s\n", encodedText);
    free(encodedText);
}

char *decode(Queue queue, TreeNode *huffmanTree) {
    int queueLength = calculateLengthQueue(queue);
    char *decodedText = (char *) malloc(sizeof(char) * (queueLength + 1));
    if (decodedText == NULL) {
        puts("Error: No hay memoria suficiente para continuar.");
        exit(1);
    }
    for (int i = 0; i < queueLength; i++) {
        decodedText[i] = decodeChar(huffmanTree, &queue);
    }
    decodedText[queueLength] = '\0';
    return decodedText;
}

char *decodeFromFilePath(char *filePath, TreeNode *huffmanTree) {
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        printf("Error: No se pudo abrir el archivo %s.", filePath);
        return NULL;
    }
    Queue queue = createQueue();
    char c;
    while ((c = fgetc(file)) != EOF) {
        enqueue(&queue, (QueueData) {.c = c});
    }
    fclose(file);
    return decode(queue, huffmanTree);
}

void printHuffmanTree(TreeNode *node) {
    if (node == NULL) {
        return;
    }
    printHuffmanTree(node->left);
    printTreeNodeData(node->data);
    printHuffmanTree(node->right);
}