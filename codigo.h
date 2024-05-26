#ifndef _CODIGO_H_
#define _CODIGO_H_

#include "huffmanTree.h"

typedef unsigned int* CodigoList; //Representa la lista de 256 caracteres

void calcularCodigos(Arbol* arbol, unsigned int codigoParcial,CodigoList lista);
//CodigoList calcularCodigos(Arbol* arbol);

#endif
