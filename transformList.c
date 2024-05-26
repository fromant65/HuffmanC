#include "transformList.h"
#include <stdio.h>

ListStruct transformListForRecursion(charWeightList list){
    ListStruct finalList = {NULL, NULL};
    for(int i=0; i<list.size && list.list[i].weight>0;i++){
        recursiveListElement *data=malloc(sizeof(recursiveListElement));
        char* caracter = malloc(sizeof(char));
        *caracter = list.list[i].character;
        data->data = caracter;
        data->type = PAR;
        data->weight= list.list[i].weight;
        
        recursiveListElementList* newNode = malloc(sizeof(recursiveListElementList));
        newNode->data=data;
        newNode->next=NULL;
        newNode->prev=finalList.last;
        if(!finalList.first) finalList.first=newNode;
        if(finalList.last) finalList.last->next=newNode;
        finalList.last=newNode;
    }
    free(list.list);
    return finalList;
}
