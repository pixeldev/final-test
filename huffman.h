#ifndef FINAL_TEST_HUFFMAN_H
#define FINAL_TEST_HUFFMAN_H

#include "definitions.h"
#include "double_circular_linked_list.h"
#include "queue.h"

/**
 * Método que imprime la información de un nodo de un árbol. En caso de que el caracter sea un salto de línea se imprime
 * \\n, en caso de que el caracter sea '\0' se imprime 'NULL', en caso contrario se imprime el caracter.
 * @param data Información del nodo.
 */
void printTreeNodeData(TreeNodeData data);

/**
 * Método que crea un nodo de un árbol donde sus hijos apuntarán a NULL. En caso de que no haya memoria suficiente para
 * crear el nodo se termina la ejecución del programa.
 * @param data Información del nodo.
 * @return Nodo creado.
 */
TreeNode *createTreeNode(TreeNodeData data);

/**
 * Método que destruye un árbol binario de forma recursiva, liberando la memoria utilizada por cada nodo.
 * @param node Nodo del árbol.
 */
void destroyHuffmanTree(TreeNode *node);

/**
 * Método que crea un árbol de Huffman a partir de una lista doblemente enlazada circular que debe contener las
 * frecuencias de aparición de los carácteres correctamente ordenada. En caso de que no haya memoria suficiente para
 * crear el árbol se termina la ejecución del programa.
 * Se sigue el siguiente algoritmo:
 * 1. Mientras la lista tenga más de un elemento:
 * 1.1. Se crea eliminan y se guardan temporalmente los dos primeros elementos de la lista.
 * 1.2. Se crea un nuevo nodo de árbol binario con la suma de las frecuencias de los dos elementos eliminados y con un
 *      caracter '\0'.
 * 1.3. Se asigna el primer elemento eliminado como hijo izquierdo del nuevo nodo.
 * 1.4. Se asigna el segundo elemento eliminado como hijo derecho del nuevo nodo.
 * 1.5. Se inserta el nuevo nodo en la lista.
 * 1.6. Se ordena la lista.
 * 1.7. Se repite el proceso.
 * 2. Se retorna el primer elemento de la lista.
 * @param list Lista doblemente enlazada circular que contiene las frecuencias correctamente ordenadas.
 * @return Árbol de Huffman.
 */
TreeNode *createHuffmanTree(DoubleCircularLinkedList *list);

/**
 * Método que obtiene el código de Huffman de un carácter a partir de un árbol de Huffman.
 * Se sigue el siguiente algoritmo:
 * 1. Si el nodo es nulo se retorna NULL.
 * 2. Si el nodo es una hoja:
 * 2.1. Si el caracter del nodo es igual al caracter buscado se retorna una cadena de caracteres con el caracter '\0'.
 * 2.2. En caso contrario se retorna NULL ya que el caracter no se encuentra en el árbol.
 * 3. Se busca recursivamente en el hijo izquierdo del nodo.
 * 4. Si el resultado de la búsqueda es diferente de NULL se retorna una cadena de caracteres con el caracter '0'
 *    concatenado con el resultado de la búsqueda.
 * 5. Se busca recursivamente en el hijo derecho del nodo.
 * 6. Si el resultado de la búsqueda es diferente de NULL se retorna una cadena de caracteres con el caracter '1'
 *    concatenado con el resultado de la búsqueda.
 * 7. Si se llega a este punto, se retorna NULL ya que el caracter no se encuentra en el árbol.
 * @param node Árbol de Huffman.
 * @param c Carácter que se quiere codificar.
 * @return Código de Huffman del carácter en forma de cadena de caracteres. En caso de que el carácter no se encuentre en
 * el árbol se retorna NULL.
 */
char *encodeChar(TreeNode *node, char c);

/**
 * Método que obtiene el carácter de Huffman a partir de un árbol de Huffman y una cola de caracteres que contiene
 * el código de Huffman del carácter de forma binaria y en orden.
 * Se sigue el siguiente algoritmo:
 * 1. Si el nodo es nulo se retorna el caracter '\0'.
 * 2. Si el nodo es una hoja se retorna el caracter del nodo.
 * 3. Se elimina y se guarda temporalmente el primer elemento de la cola.
 * 4. Si el primer elemento de la cola no es NULL:
 * 4.1. Si el primer elemento de la cola es igual a '0' se busca recursivamente en el hijo izquierdo del nodo.
 * 4.2. Si el primer elemento de la cola es igual a '1' se busca recursivamente en el hijo derecho del nodo.
 * 5. Se retorna el resultado de la búsqueda.
 * @param node Árbol de Huffman.
 * @param queue Cola de caracteres que contiene el código de Huffman del carácter de forma binaria y en orden.
 * @return Carácter decodificado.
 */
char decodeChar(TreeNode *node, Queue *queue);

/**
 * Método que codifica un texto a partir de un árbol de Huffman.
 * Se sigue el siguiente algoritmo:
 * 1. Se crea una cadena de caracteres vacía.
 * 2. Se recorre el texto caracter por caracter:
 * 2.1. Se obtiene el código de Huffman del caracter.
 * 2.2. Se concatena el código de Huffman del caracter a la cadena de caracteres.
 * 3. Se retorna la cadena de caracteres.
 * @param text Texto a codificar.
 * @param huffmanTree Árbol de Huffman.
 * @return Texto codificado.
 */
char *encode(char *text, TreeNode *huffmanTree);

/**
 * Método que codifica un texto a partir de un árbol de Huffman y lo guarda en un archivo.
 * Se sigue el siguiente algoritmo:
 * 1. Se codifica el texto usando el método encode.
 * 2. Se abre el archivo en modo escritura.
 * 3. Se escribe el texto codificado en el archivo.
 * 4. Se cierra el archivo.
 * @param text
 * @param filePath
 * @param huffmanTree
 */
void encodeToFilePath(char *text, char *filePath, TreeNode *huffmanTree);

/**
 * Método que decodifica un texto a partir de un árbol de Huffman y una cola de caracteres que contiene el código de
 * Huffman del texto de forma binaria y en orden.
 * Se sigue el siguiente algoritmo:
 * 1. Se crea una cadena de caracteres vacía.
 * 2. Se repite mientras la cola no esté vacía:
 * 2.1. Se decodifica el caracter de Huffman.
 * 2.2. Se concatena el caracter decodificado a la cadena de caracteres.
 * 3. Se retorna la cadena de caracteres.
 * @param queue Cola de caracteres que contiene el código de Huffman del texto de forma binaria y en orden.
 * @param huffmanTree Árbol de Huffman.
 * @return Texto decodificado.
 */
char *decode(Queue queue, TreeNode *huffmanTree);

/**
 * Método que decodifica un texto a partir de un árbol de Huffman y una cola de caracteres que contiene el código de
 * Huffman del texto de forma binaria y en orden.
 * Se sigue el siguiente algoritmo:
 * 1. Se abre el archivo en modo lectura.
 * 2. Se crea una cola de caracteres vacía.
 * 3. Se lee el archivo caracter por caracter:
 * 3.1. Se encola el caracter leído.
 * 4. Se cierra el archivo.
 * 5. Se decodifica el texto usando el método decode.
 * @param filePath Ruta del archivo.
 * @param huffmanTree Árbol de Huffman.
 * @return Texto decodificado.
 */
char *decodeFromFilePath(char *filePath, TreeNode *huffmanTree);

/**
 * Método que imprime un árbol de Huffman de forma recursiva en inorden. Se imprime el caracter del nodo y su frecuencia
 * de aparición utilizando el método printTreeNodeData.
 * @param node Nodo del árbol.
 */
void printHuffmanTree(TreeNode *node);

#endif
