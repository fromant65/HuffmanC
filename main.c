#include <stdlib.h>
#include <stdio.h>
#include "readInput.h"
#include "transformList.h"
#include "huffmanTree.h"
#include "codigo.h"
#include "comprimir.h"
#include "descomprimir.h"
int main(int argc, char* argv[]){
    if(argc!=3){
        printf("El input recibido es incorrecto.");
        return argc;
    }
    if(argv[2][0]=='c'){
        charWeightList cwlist = readInput(argv[1]);
        sortWeights(&cwlist);
        printf("Lista de caracteres:\n");
        for(int i=0;i<cwlist.size && cwlist.list[i].weight>0;i++){
            printf("%c %d  ", cwlist.list[i].character, cwlist.list[i].weight);
        }
        ListStruct lsList = transformListForRecursion(cwlist);
        //
        printf("\nLista para recursion\n");
        recursiveListElementList* temp = lsList.first;
        for(;temp!=NULL;temp=temp->next){
            printf("%c %d ", *(char*)(temp->data->data),temp->data->weight);
        }
        printf("\n");
        //
        Arbol* arbol = crearArbol(&lsList);
        printArbol(arbol);
        CodigoList lista = calloc(256,sizeof(unsigned int));
        char* serializado = serializar(arbol);
        printf("%s\n", serializado);
        calcularCodigos(arbol,1,lista);
        destruirArbol(arbol);
        write_binary_file(lista, argv[1], "output.txt", serializado);
    }else{
        descomprimir(argv[1], "descomprimido.txt");
    }
    return 0;
}