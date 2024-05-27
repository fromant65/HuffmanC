#include "comprimir.h"
#include "huffmanTree.h"
#include <stdio.h>
#include <stdlib.h>

int getCharCount(FILE* comprimido){
    char char_count[17];
    int char_count_index=0;
    char c;
    while((c=fgetc(comprimido))!='\n'){
        char_count[char_count_index++]=c;
    } 
    char_count[char_count_index]='\0';
    return atoi(char_count);
}

void descomprimir(char* nombreArchivo, char* nombreSalida){
    FILE *comprimido = fopen(nombreArchivo, "r");
    if(!comprimido){
        perror("No se pudo abrir el archivo comprimido.\n");
        return;
    }
    FILE *descomprimido = fopen(nombreSalida, "w");
    if(!descomprimido){
        perror("No se pudo abrir el archivo de salida.\n");
        fclose(comprimido);
        return;
    }
    int i=0, size=2048;
    char* buffer = malloc(sizeof(char)*size);
    char c, prev;
    while(!((c=fgetc(comprimido))=='T'&&prev=='E')){
        prev=c;
        if(i>=size){
            size*=2;
            buffer = realloc(buffer, size);
        }
        buffer[i++]=c;
    }
    buffer[i-1]='\0';
    //printf("%s\n\n", buffer);
    Arbol* arbol = deserializar(&buffer);
    free(buffer);
    Arbol* currentNode = arbol;
    int char_count = getCharCount(comprimido);
    printf("CARACTERES %d\n", char_count);
    for(int i=0; i<char_count; i++){
        c=fgetc(comprimido);

        for (int bit = 7; bit >= 0; bit--) {
            int currentBit = (c >> bit) & 1;
            
            if (currentBit == 0) {
                currentNode = currentNode->izq;
            } else {
                currentNode = currentNode->der;
            }
            
            // Si encontramos una hoja
            if (currentNode->izq == NULL && currentNode->der == NULL) {
                printf("%c%d ", *(char*)(currentNode->dato), i);
                putc(*(char*)(currentNode->dato),descomprimido);
                currentNode = arbol; // Reiniciar a la raíz para el próximo carácter
            }
        }
    }
    fclose(comprimido);
    fclose(descomprimido);
}

