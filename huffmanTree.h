#ifndef _HUFFMAN_TREE_H_
#define _HUFFMAN_TREE_H_

#include <stdlib.h>
#include "transformList.h"

typedef struct arbol{
    struct arbol* izq;
    struct arbol* der;
    char* dato;
}Arbol;

Arbol* crearArbol(ListStruct* list);
void insertArbolSegunPeso(ListStruct* list, Arbol* arbol, size_t peso); 
Arbol* crearArbolSegunDatos(Arbol* izq, Arbol* der, void* dato);
void printArbol(Arbol* arbol);
char* serializar(Arbol* arbol);
Arbol* deserializar(char** buffer);
#endif