#include "readInput.h"

charWeightList readInput(char* name){
    FILE* input = fopen(name, "r");
    charWeightList cwlist = {calloc(256,sizeof(charWeight)),256};
    char c;
    while((c = getc(input))!=EOF){
        if(cwlist.list[(int)c].weight==0){
            cwlist.list[(int)c].character=c;
            cwlist.list[(int)c].weight=1;
        }else{
            cwlist.list[(int)c].weight++;
        }
    }
    return cwlist;
}

int compararCW(const void* a,const void* b){
    return ((charWeight*)b)->weight - ((charWeight*)a)->weight;
}

void sortWeights(charWeightList *cwlist){
    qsort(cwlist->list,cwlist->size, sizeof(charWeight), compararCW);
}
