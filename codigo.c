#include "codigo.h"
#include <stdlib.h>

void calcularCodigos(Arbol* arbol, unsigned int codigoParcial, CodigoList lista){
    if(arbol==NULL) return;
    if(arbol->dato==NULL){
        calcularCodigos(arbol->izq, codigoParcial<<1, lista);
        calcularCodigos(arbol->der, (codigoParcial<<1)|1, lista);
        return;
    }
    char caracter =*(char*)(arbol->dato);
    lista[(int)caracter]=codigoParcial;
}
