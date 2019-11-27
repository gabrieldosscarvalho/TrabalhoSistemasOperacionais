#include <stdlib.h>
#include <stdio.h>
#include "nodo.h"

/**
 * Gerar um novo Nodo
 */
struct Nodo *nodoGerar()
{
	struct Nodo *_temp = (struct Nodo*) malloc( sizeof (struct Nodo) );
	_temp->prox = NULL;

	return _temp;
}

/**
 *Listar os nodos
 */
void nodoListar ( struct Nodo *root, NodoListarCallback callback )
{
	struct Nodo *_prox = root->prox;
	
	if( _prox == NULL ) {
		callback(NULL, 1);

		return;
	}
	
	do{
		callback(_prox->conteudo, 0);
		
		_prox = _prox->prox;
	} while( _prox != NULL );
}

/**
 *Listar de maneira gerenciada os nodos
 */
int nodoListarGerenciado ( struct Nodo *root, NodoListarGerenciadoCallback callback, void *aux_parametro )
{
	struct Nodo *_prox = root->prox;
	int _sair = 0;
	
	do{
		_sair = callback(_prox->conteudo, aux_parametro);
		
		_prox = _prox->prox;
	} while( _sair == 0 && _prox != NULL );
}
