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
    free(l->values);
}

int compare(const void* a, const void* b) {
     YYSTYPE yya = * ( (YYSTYPE*) a );
     YYSTYPE yyb = * ( (YYSTYPE*) b );

     if ( yya.spos == yyb.spos ) return 0;
     else if ( yya.spos < yyb.spos ) return -1;
     else return 1;
}

void sortYYSTYPElist(YYSTYPEList *l) {
    qsort(l->values, l->used, sizeof(YYSTYPE), compare);
}
