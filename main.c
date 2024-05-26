#include <stdlib.h>
#include <stdio.h>
#include "readInput.h"
#include "transformList.h"
#include "huffmanTree.h"
#include "codigo.h"
#include "comprimir.h"

int main(int argc, char* argv[]){
    if(argc!=2){
        printf("El input recibido es incorrecto.");
        return argc;
    }
    charWeightList cwlist = readInput(argv[1]);
    sortWeights(&cwlist);
    for(int i=0;i<cwlist.size && cwlist.list[i].weight>0;i++){
        printf("%c %d  ", cwlist.list[i].character, cwlist.list[i].weight);
    }
    printf("%c %d\n",cwlist.list[0].character, cwlist.list[0].weight);
    ListStruct lsList = transformListForRecursion(cwlist);
    Arbol* arbol = crearArbol(&lsList);
    //printArbol(arbol);
    CodigoList lista = calloc(256,sizeof(unsigned int));
    printf("break 24");
    char* serializado = serializar(arbol);
    printf("break26");
    printf("%s\n", serializado);
    //Arbol* deserializado = deserializar(&serializado);
    //printf("%s\n", serializar(deserializado));
    
    calcularCodigos(arbol,1,lista);
    /*for(int i=1;i<256;i++){
        if(lista[i]>0){
            printf("%c %d\n", i, lista[i]);
        }
    }*/
    printf("break37");
    write_binary_file(lista, argv[1], "output.txt", serializado);
    return 0;
}