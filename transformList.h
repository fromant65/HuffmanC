#ifndef _TRANSFORM_LIST_H_
#define _TRANSFORM_LIST_H_

#include <stdlib.h>
#include "readInput.h"

typedef enum{
    PAR,
    ARBOL
}TYPES;

typedef struct
{
    size_t weight;
    TYPES type;
    void* data;
}recursiveListElement;

typedef struct recursiveListElementList{
    recursiveListElement* data;
    struct recursiveListElementList* next;
    struct recursiveListElementList* prev;
}recursiveListElementList;

typedef struct{
    recursiveListElementList* first;
    recursiveListElementList* last;
}ListStruct;

ListStruct transformListForRecursion(charWeightList list);

#endif