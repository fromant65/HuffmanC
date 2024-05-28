#include "huffmanTree.h"
#include <string.h>
#include <stdio.h>

Arbol* crearArbol(ListStruct* list){
    if(list->first==NULL) return NULL;
    //Si el tamaño de la lista es 1, tenemos el arbol final, lo retornamos
    if(list->first->next==NULL) return list->first->data->data;
    //Si no, tomamos los ultimos dos elementos de la lista
    recursiveListElement* elem1 = list->last->data;
    recursiveListElement* elem2 = list->last->prev->data;
    //Elimino los ultimos dos elementos de la lista
    popRLE(list);
    popRLE(list);
    printf("%c ", list->first==NULL?'!':list->last->data->type==PAR?*(char*)(list->last->data->data):'-');
    //Creamos 3 nodos, un nodo intermedio y dos para los ultimos dos elementos de la lista
    Arbol* nodoIzq;
    if(elem1->type==PAR){
        nodoIzq = crearArbolSegunDatos(NULL, NULL,elem1->data);
    }else{
        nodoIzq = (Arbol*)(elem1->data);
    }
    Arbol* nodoDer;
    if(elem2->type==PAR){
        nodoDer = crearArbolSegunDatos(NULL, NULL,elem2->data);
    }else{
        nodoDer = (Arbol*)(elem2->data);
    }
    Arbol* newNodo = crearArbolSegunDatos(nodoIzq, nodoDer, NULL);
    //Calculamos el peso del nuevo nodo y lo insertamos en la lista
    int newNodoWeight = elem1->weight + elem2->weight;
    insertArbolSegunPeso(list, newNodo, newNodoWeight);
    return crearArbol(list);
}

void insertArbolSegunPeso(ListStruct* list, Arbol* arbol, size_t peso){
    recursiveListElementList* newElem = malloc(sizeof(recursiveListElementList));
    newElem->data=malloc(sizeof(recursiveListElement));
    newElem->data->data=arbol;
    newElem->data->type=ARBOL;
    newElem->data->weight=peso;

    if(list->first ==NULL){
        list->first = newElem;
        list->last = newElem;
        return;
    }

    recursiveListElementList* temp=list->first;
    for(; temp->data->weight > peso;temp=temp->next);
    recursiveListElementList* ant = temp->prev;
    
    if(ant==NULL){
        list->first=newElem;
    }else{
        ant->next=newElem;
    }
    newElem->prev=ant;
    newElem->next=temp;
    temp->prev=newElem;
}

Arbol* crearArbolSegunDatos(Arbol* izq, Arbol* der, void* dato){
    Arbol* nodo = malloc(sizeof(Arbol));
    nodo->dato=dato;
    nodo->der=der;
    nodo->izq=izq;
    return nodo;
}

void printArbol(Arbol* arbol){
    if(arbol==NULL) {printf("-- "); return;}
    printf("%c ", arbol->dato==NULL?'-':*(char*)arbol->dato);
    printArbol(arbol->izq);
    printArbol(arbol->der);
}

char* serializar(Arbol* arbol){
    char* buffer;
    if(arbol==NULL){
        buffer = malloc(sizeof(char)*5);
        strcpy(buffer, "--");
    } else {
        char* buffizq = serializar(arbol->izq);
        char* buffder = serializar(arbol->der);
        char dato[4];
        if(arbol->dato==NULL){
            strcpy(dato, "INT");
        }else{
            sprintf(dato, "%c", *(arbol->dato));
        }
        buffer = malloc(strlen(dato) + strlen(buffizq) + strlen(buffder) + 3);
        sprintf(buffer, "%s\n%s\n%s", dato, buffizq, buffder);
        free(buffizq);
        free(buffder);
    }
    return buffer;
}

Arbol* deserializar(char** buffer){
    if(buffer == NULL) return NULL;
    if (strncmp(*buffer, "--", 2) == 0) {
        *buffer += (*buffer)[2]=='\0'?2:3; 
        return NULL;
    }
    Arbol* arbol = malloc(sizeof(Arbol));
    if (strncmp(*buffer, "INT", 3) == 0) {
        arbol->dato = NULL;
        *buffer += 4;
    } else {
        arbol->dato = malloc(sizeof(char)*2);
        sprintf(arbol->dato, "%c", **buffer);
        *buffer +=2;
    }
    arbol->izq = deserializar(buffer);
    arbol->der = deserializar(buffer);
    return arbol;
}

void destruirArbol(Arbol* arbol){
    if(arbol==NULL) return;
    if(arbol->dato!=NULL) free(arbol->dato);
    destruirArbol(arbol->izq);
    destruirArbol(arbol->der);
    free(arbol);
}