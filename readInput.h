#ifndef _READ_INPUT_H_
#define _READ_INPUT_H_

#include <stdlib.h>
#include <stdio.h>

typedef struct{
    char character;
    size_t weight;
}charWeight;

typedef struct{
    charWeight* list;
    size_t size;
}charWeightList;

charWeightList readInput(char* name);
int compararCW(const void* a,const void* b);
void sortWeights(charWeightList *cwlist);

#endif