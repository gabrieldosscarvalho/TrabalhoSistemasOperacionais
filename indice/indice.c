#include <stdlib.h>
#include <stdio.h>
#include "indice.h"

struct Indice *indiceGerar()
{
	struct Indice *_temp = (struct Indice*) malloc( sizeof (struct Indice) );
	_temp->prox = NULL;

	return _temp;
}

void indiceListar( struct Indice *root, IndiceListarCallback callback )
{
	struct Indice *_prox = root->prox;
	
	if( _prox == NULL ) {
		callback(NULL, 1);

		return;
	}
	
	do{
		callback(_prox->conteudo, 0);
		
		_prox = _prox->prox;
	} while( _prox != NULL );
}

int indiceListarGerenciado( struct Indice *root, IndiceListarGerenciadoCallback callback, void *aux_parametro )
{
	struct Indice *_prox = root->prox;
	int _sair = 0;
	
	do{
		_sair = callback(_prox->conteudo, aux_parametro);
		
		_prox = _prox->prox;
	} while( _sair == 0 && _prox != NULL );
}
