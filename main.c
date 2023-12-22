#include "double_circular_linked_list.h"
#include "queue.h"

int main() {
    puts("-=-=- Bienvenido al examen final de Algoritmos y Estructuras de Datos -=-=-");
    FILE *inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        puts("Error: No se pudo abrir el archivo input.txt");
        return 1;
    }
    DoubleCircularLinkedList list = createDoubleCircularLinkedList();
    char *fileContent = NULL;
    int fileContentLength = 0;
    char c;
    DoubleCircularLinkedListData data;
    TreeNode *treeNode;
    TreeNodeData treeNodeData;
    while ((c = fgetc(inputFile)) != EOF) {
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
        fileContent[fileContentLength++] = c;
        fileContent[fileContentLength] = '\0';
        data = findDataDoubleCircularLinkedList(list, c);
        if (data.treeNode == NULL) {
            treeNodeData.c = c;
            treeNodeData.frequency = 1;
            treeNode = createTreeNode(treeNodeData);
            data.treeNode = treeNode;
            insertAtEndDoubleCircularLinkedList(&list, data);
        } else {
            data.treeNode->data.frequency++;
        }
    }

    puts("-=-=- Texto leído -=-=-");
    printf("%s\n", fileContent);

    puts("-=-=- Lista de frecuencias sin ordenar -=-=-");
    printDoubleCircularLinkedList(list);
    sortBySelectionDoubleCircularLinkedList(&list);
    puts("-=-=- Lista de frecuencias ordenada -=-=-");
    printDoubleCircularLinkedList(list);

    puts("-=-=- Creando arbol de Huffman... -=-=-");
    TreeNode *huffmanTree = createHuffmanTree(&list);
    printHuffmanTree(huffmanTree);
    puts("-=-=- Arbol de Huffman creado -=-=-");

    puts("-=-= Codificando texto... -=-=-");
    encodeToFilePath(fileContent, "output.txt", huffmanTree);
    puts("-=-= Texto codificado -=-=-");

    puts("-=-=- Decodificando texto... -=-=-");
    char *decodedText = decodeFromFilePath("output.txt", huffmanTree);
    printf("%s\n", decodedText);
    puts("-=-=- Texto decodificado -=-=-");

    fclose(inputFile);
    free(fileContent);
    destroyDoubleCircularLinkedList(&list);
    destroyHuffmanTree(huffmanTree);
    return 0;
}
