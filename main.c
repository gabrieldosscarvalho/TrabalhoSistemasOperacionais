#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>
#include "teste/teste.h"

int main(int argc, char *argv[]) 
{
	setlocale(LC_ALL,"portuguese");

	struct Teste *a = (struct Teste*) malloc(sizeof(struct Teste));
	struct Teste *b = (struct Teste*) malloc(sizeof(struct Teste));

	a->x = 1;
	a->y = 1;
	b->x = 1;
	b->y = 1;

	struct Teste tSoma = soma(*a, *b);

	printf("--Teste\n");
	printf("X == %f\n", tSoma.x);
	printf("Y == %f\n", tSoma.y);


	printf("\n");
	return 0;
}
