/**
 * Nombres: González Garcés Rodrigo y Miranda San Martin Angel
 * Grupo: 2BV2
 * Carrera: Ingeniería en Inteligencia Artificial
 * Última fecha de modificación: 22/12/2023 - 14:00
 */
#include "double_circular_linked_list.h"
#include "queue.h"

int main() {
    puts("-=-=- Bienvenido al examen final de Algoritmos y Estructuras de Datos -=-=-");
    FILE *inputFile = fopen("input.txt", "r"); // Se abre el archivo input.txt en modo lectura.
    if (inputFile == NULL) {
        puts("Error: No se pudo abrir el archivo input.txt");
        return 1;
    }
    DoubleCircularLinkedList frequenciesList = createDoubleCircularLinkedList(); // Se crea la lista doblemente enlazada circular.
    char *fileContent = NULL;
    int fileContentLength = 0;
    char c;
    DoubleCircularLinkedListData listData;
    TreeNode *characterTreeNode;
    TreeNodeData treeNodeData;
    while ((c = fgetc(inputFile)) != EOF) { // Se lee el archivo caracter por caracter.
        if (fileContent == NULL) {
            fileContent = (char *) malloc(sizeof(char) * 2);
            if (fileContent == NULL) {
                puts("Error: No hay memoria suficiente para continuar.");
                exit(1);
            }
        } else {
            fileContent = (char *) realloc(fileContent, sizeof(char) * (fileContentLength + 2));
            if (fileContent == NULL) {
                puts("Error: No hay memoria suficiente para continuar.");
                exit(1);
            }
        }
        fileContent[fileContentLength++] = c; // Se agrega el caracter al contenido del archivo.
        fileContent[fileContentLength] = '\0'; // Se agrega el caracter nulo al final del contenido del archivo.
        listData = findDataDoubleCircularLinkedList(frequenciesList, c); // Se busca el caracter en la lista de frecuencias.
        if (listData.treeNode == NULL) { // Si no se encuentra el caracter en la lista de frecuencias.
            treeNodeData.c = c; // Se crea un nuevo nodo con el caracter.
            treeNodeData.frequency = 1; // Se inicializa la frecuencia del caracter en 1.
            characterTreeNode = createTreeNode(treeNodeData); // Se crea el nodo de árbol.
            listData.treeNode = characterTreeNode; // Se asigna el nodo de árbol al dato de la lista.
            insertAtEndDoubleCircularLinkedList(&frequenciesList, listData); // Se agrega el dato a la lista de frecuencias.
        } else { // Si se encuentra el caracter en la lista de frecuencias.
            listData.treeNode->data.frequency++; // Se incrementa la frecuencia del caracter.
        }
    }

    puts("-=-=- Texto leído -=-=-");
    printf("%s\n", fileContent); // Se imprime el contenido del archivo.

    puts("-=-=- Lista de frecuencias sin ordenar -=-=-");
    printDoubleCircularLinkedList(frequenciesList); // Se imprime la lista de frecuencias sin ordenar.
    sortBySelectionDoubleCircularLinkedList(&frequenciesList); // Se ordena la lista de frecuencias.
    puts("-=-=- Lista de frecuencias ordenada -=-=-");
    printDoubleCircularLinkedList(frequenciesList);

    puts("-=-=- Creando arbol de Huffman... -=-=-");
    TreeNode *huffmanTree = createHuffmanTree(&frequenciesList); // Se crea el árbol de Huffman.
    printHuffmanTree(huffmanTree); // Se imprime el árbol de Huffman.
    puts("-=-=- Arbol de Huffman creado -=-=-");

    puts("-=-= Codificando texto... -=-=-");
    encodeToFilePath(fileContent, "output.txt", huffmanTree); // Se codifica el contenido del archivo.
    puts("-=-= Texto codificado -=-=-");

    puts("-=-=- Decodificando texto... -=-=-");
    char *decodedText = decodeFromFilePath("output.txt", huffmanTree); // Se decodifica el contenido del archivo.
    printf("%s\n", decodedText); // Se imprime el contenido del archivo decodificado.
    puts("-=-=- Texto decodificado -=-=-");

    fclose(inputFile); // Se cierra el archivo input.txt.
    free(fileContent); // Se libera la memoria del contenido del archivo.
    destroyDoubleCircularLinkedList(&frequenciesList); // Se destruye la lista de frecuencias.
    destroyHuffmanTree(huffmanTree); // Se destruye el árbol de Huffman.
    return 0;
}
