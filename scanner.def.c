#include "scanner.def.h"
#include <stdlib.h>

void initYYSTYPEList(YYSTYPEList *l, size_t initialSize) {
    l->values = (YYSTYPE *)malloc(initialSize * sizeof(YYSTYPE));
    l->used = 0;
    l->size = initialSize;
}

void insertYYSTYPE(YYSTYPEList *l, YYSTYPE element) {
    if (l->used == l->size) {
        if (l->size == 0) {
            l->size = 1;
        } else {
            l->size *= 2;
        }
        l->values = (YYSTYPE *)realloc(l->values, l->size * sizeof(YYSTYPE));
    }
    l->values[l->used] = element;
    l->used += 1;
}

void freeYYSTYPElist(YYSTYPEList *l) {
    /*for (int i = 0; i < l->used; ++i) {*/
        /*free(l->values[i]);*/
    /*}*/
    free(l->values);
    //l->values = NULL;
}