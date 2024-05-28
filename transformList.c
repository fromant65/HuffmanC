#include "transformList.h"
#include <stdio.h>

ListStruct transformListForRecursion(charWeightList cwlist){
    ListStruct finalList = {NULL, NULL};
    for(int i=0; i<cwlist.size && cwlist.list[i].weight>0;i++){
        char caracter = cwlist.list[i].character;
        int weight = cwlist.list[i].weight;
        recursiveListElement* data = newParRLE(caracter, weight);
        pushRLE(&finalList, data);
    }
    free(cwlist.list);
    return finalList;
}

recursiveListElement* newParRLE(char caracter, size_t weight){
    recursiveListElement *data=malloc(sizeof(recursiveListElement));
    char* charCopy = malloc(sizeof(char));
    *charCopy = caracter;
    data->data = charCopy;
    data->type = PAR;
    data->weight= weight;
    return data;
}

recursiveListElement* newArbolRLE(void* arbol, size_t weight){
    recursiveListElement* newElem = malloc(sizeof(recursiveListElement));
    newElem->data=arbol;
    newElem->type=ARBOL;
    newElem->weight=weight;
    return newElem;
}

void pushRLE(ListStruct *list, recursiveListElement *data){
    recursiveListElementList* newNode = malloc(sizeof(recursiveListElementList));
    newNode->data=data;
    newNode->next = NULL;
    newNode->prev=list->last;
    if(!list->first) list->first=newNode;
    if(list->last) list->last->next = newNode;
    list->last=newNode;
}

void popRLE(ListStruct *list){
    if(list->last==NULL) return;
    recursiveListElementList* last = list->last;
    list->last=last->prev; 
    if(list->last==NULL) { //En este caso me queda una lista vacía
        list->first=NULL;
        return;
    } else list->last->next=NULL;
    free(last);
}

void insertByWeight(recursiveListElement* elem, ListStruct* list){
    recursiveListElementList* newNode = malloc(sizeof(recursiveListElementList));
    newNode->data=elem;

    if(list->first ==NULL){
        list->first = newNode;
        list->last = newNode;
        return;
    }
    
    recursiveListElementList* temp=list->first;
    for(; temp->data->weight > newNode->data->weight;temp=temp->next);
    recursiveListElementList* ant = temp->prev;
    
    if(ant==NULL){
        list->first=newNode;
    }else{
        ant->next=newNode;
    }
    newNode->prev=ant;
    newNode->next=temp;
    temp->prev=newNode;
}