/**
 * Nombres: González Garcés Rodrigo y Miranda San Martin Angel
 * Grupo: 2BV2
 * Carrera: Ingeniería en Inteligencia Artificial
 * Última fecha de modificación: 22/12/2023 - 14:00
 */
#include "huffman.h"

void printTreeNodeData(TreeNodeData data) {
    if (data.c == '\0') { // NULL
        printf("NULL: %d\n", data.frequency);
    } else if (data.c == '\n') { // \n salto de línea
        printf("\\n: %d\n", data.frequency);
    } else { // Otro carácter
        printf("%c: %d\n", data.c, data.frequency);
    }
}

TreeNode *createTreeNode(TreeNodeData data) {
    TreeNode *node = (TreeNode *) malloc(sizeof(TreeNode));
    if (node == NULL) {
        puts("Error: No hay memoria suficiente para continuar.");
        exit(1);
    }
    // Inicializar nodo
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void destroyHuffmanTree(TreeNode *node) {
    if (node == NULL) {
        return;
    }
    // Destruir nodo y sus hijos recursivamente en postorden
    destroyHuffmanTree(node->left);
    destroyHuffmanTree(node->right);
    free(node);
}

TreeNode *createHuffmanTree(DoubleCircularLinkedList *list) {
    while (calculateLengthDoubleCircularLinkedList(*list) > 1) { // Mientras la lista tenga más de un elemento
        DoubleCircularLinkedListData data1 = deleteAtStartDoubleCircularLinkedList(list);
        DoubleCircularLinkedListData data2 = deleteAtStartDoubleCircularLinkedList(list);
        int data1Frequency = data1.treeNode->data.frequency;
        int data2Frequency = data2.treeNode->data.frequency;
        TreeNode *node = createTreeNode((TreeNodeData) {.c = '\0', .frequency = data1Frequency + data2Frequency}); // Crear nodo con frecuencia igual a la suma de las frecuencias de los nodos extraídos
        node->left = data1.treeNode; // Asignar nodo extraído 1 como hijo izquierdo
        node->right = data2.treeNode; // Asignar nodo extraído 2 como hijo derecho
        insertAtEndDoubleCircularLinkedList(list, (DoubleCircularLinkedListData) {.treeNode = node}); // Insertar nodo en la lista
        sortBySelectionDoubleCircularLinkedList(list);
    }
    return (*list)->next->data.treeNode; // Devolver el único nodo que queda en la lista, que es la raíz del árbol
}

char *encodeChar(TreeNode *node, char c) {
    if (node == NULL) { // Hemos llegado a una hoja y no se ha encontrado el carácter
        return NULL;
    }
    if (node->left == NULL && node->right == NULL) { // Hemos llegado a una hoja y se ha encontrado un carácter
        if (node->data.c == c) { // El carácter de la hoja es el carácter buscado
            char *huffmanCode = (char *) malloc(sizeof(char) * 2);
            if (huffmanCode == NULL) {
                puts("Error: No hay memoria suficiente para continuar.");
                exit(1);
            }
            huffmanCode[0] = '\0'; // Inicializar cadena vacía
            return huffmanCode;
        } else { // El carácter de la hoja no es el carácter buscado, por lo que no se ha encontrado el carácter
            return NULL;
        }
    }
    char *huffmanCode = encodeChar(node->left, c); // Buscar carácter por la izquierda
    if (huffmanCode != NULL) { // Se ha encontrado el carácter
        char *newHuffmanCode = (char *) malloc(sizeof(char) * (strlen(huffmanCode) + 2));
        if (newHuffmanCode == NULL) {
            puts("Error: No hay memoria suficiente para continuar.");
            exit(1);
        }
        // Concatenar '0' y el código de Huffman del carácter
        strcpy(newHuffmanCode, "0");
        strcat(newHuffmanCode, huffmanCode);
        free(huffmanCode);
        return newHuffmanCode;
    }
    huffmanCode = encodeChar(node->right, c); // Buscar carácter por la derecha
    if (huffmanCode != NULL) { // Se ha encontrado el carácter
        char *newHuffmanCode = (char *) malloc(sizeof(char) * (strlen(huffmanCode) + 2));
        if (newHuffmanCode == NULL) {
            puts("Error: No hay memoria suficiente para continuar.");
            exit(1);
        }
        // Concatenar '1' y el código de Huffman del carácter
        strcpy(newHuffmanCode, "1");
        strcat(newHuffmanCode, huffmanCode);
        free(huffmanCode);
        return newHuffmanCode;
    }
    return NULL;
}

char decodeChar(TreeNode *node, Queue *queue) {
    if (node == NULL) { // Hemos llegado a una hoja y no se ha encontrado el carácter
        return '\0';
    }
    if (node->left == NULL && node->right == NULL) { // Hemos llegado a una hoja y se ha encontrado un carácter
        return node->data.c;
    }
    if (*queue != NULL && (*queue)->data.c == '0') { // El carácter es '0' y se debe buscar por la izquierda
        dequeue(queue);
        return decodeChar(node->left, queue);
    }
    if (*queue != NULL && (*queue)->data.c == '1') { // El carácter es '1' y se debe buscar por la derecha
        dequeue(queue);
        return decodeChar(node->right, queue);
    }
    return '\0'; // No se ha encontrado el carácter
}

char *encode(char *text, TreeNode *huffmanTree) {
    int textLength = strlen(text);
    char *encodedText = NULL;
    int encodedTextLength = 0;
    char *huffmanCode = NULL; // Almacena el código de Huffman de cada carácter temporalmente
    for (int i = 0; i < textLength; i++) { // Recorrer el texto
        huffmanCode = encodeChar(huffmanTree, text[i]); // Codificar el carácter
        if (huffmanCode == NULL) { // El carácter no está contemplado en el Árbol de Huffman
            puts("Error: El texto contiene carácteres que no están contemplados en el Árbol de Huffman..");
            return NULL;
        }
        encodedTextLength += strlen(huffmanCode); // Calcular la longitud del texto codificado
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
        strcat(encodedText, huffmanCode); // Concatenar el código de Huffman del carácter al texto codificado
        free(huffmanCode); // Liberar los recursos del código de Huffman del carácter
    }
    if (encodedText != NULL) { // El texto no está vacío
        encodedText[encodedTextLength] = '\0'; // Agregar el carácter nulo al final del texto codificado
    }
    return encodedText;
}

void encodeToFilePath(char *text, char *filePath, TreeNode *huffmanTree) {
    FILE *file = fopen(filePath, "w");
    if (file == NULL) {
        printf("Error: No se pudo abrir el archivo %s.", filePath);
        return;
    }
    char *encodedText = encode(text, huffmanTree); // Codificar el texto
    fputs(encodedText, file); // Escribir el texto codificado en el archivo
    fclose(file);
    printf("%s\n", encodedText);
    free(encodedText);
}

char *decode(Queue queue, TreeNode *huffmanTree) {
    int queueLength = calculateLengthQueue(queue); // Calcular la longitud de la cola
    char *decodedText = (char *) malloc(sizeof(char) * (queueLength + 1)); // Reservar memoria para el texto decodificado
    if (decodedText == NULL) {
        puts("Error: No hay memoria suficiente para continuar.");
        exit(1);
    }
    for (int i = 0; i < queueLength; i++) { // Recorrer la cola
        decodedText[i] = decodeChar(huffmanTree, &queue); // Decodificar el carácter y agregarlo al texto decodificado
    }
    decodedText[queueLength] = '\0'; // Agregar el carácter nulo al final del texto decodificado
    return decodedText;
}

char *decodeFromFilePath(char *filePath, TreeNode *huffmanTree) {
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        printf("Error: No se pudo abrir el archivo %s.", filePath);
        return NULL;
    }
    Queue queue = createQueue(); // Crear cola
    char c;
    while ((c = fgetc(file)) != EOF) { // Leer el archivo carácter por carácter
        enqueue(&queue, (QueueData) {.c = c}); // Agregar el carácter a la cola
    }
    fclose(file);
    return decode(queue, huffmanTree); // Decodificar la cola
}

void printHuffmanTree(TreeNode *node) {
    if (node == NULL) {
        return;
    }
    // Imprimir nodo y sus hijos recursivamente en inorden
    printHuffmanTree(node->left);
    printTreeNodeData(node->data);
    printHuffmanTree(node->right);
}