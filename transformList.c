#include "transformList.h"
#include <stdio.h>

ListStruct transformListForRecursion(charWeightList cwlist){
    ListStruct finalList = {NULL, NULL};
    for(int i=0; i<cwlist.size && cwlist.list[i].weight>0;i++){
        char caracter = cwlist.list[i].character;
        int weight = cwlist.list[i].weight;
        recursiveListElement* data = newParRLE(caracter, PAR, weight);
        pushRLE(&finalList, data);
    }
    free(cwlist.list);
    return finalList;
}

recursiveListElement* newParRLE(char caracter, TYPES type, size_t weight){
    recursiveListElement *data=malloc(sizeof(recursiveListElement));
    char* charCopy = malloc(sizeof(char));
    *charCopy = caracter;
    data->data = charCopy;
    data->type = type;
    data->weight= weight;
    return data;
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