#include <stdlib.h>
#include "teste.h"

struct Teste soma (struct Teste a, struct Teste b){
    struct Teste *t = (struct Teste*) malloc(sizeof(struct Teste));

    t->x = a.x + b.x;
    t->y = a.y + b.y;

    return *t;
}
