#ifndef NODO_H
#define NODO_H

/**
 * Estrutura de um indice
 */
typedef struct Nodo
{
	void *conteudo;

	struct Nodo *prox;
} Nodo;

/**
 * Gerar um novo Nodo
 */
struct Nodo *nodoGerar();

/**
 *Listar os nodos
 */
typedef void (*NodoListarCallback)( void *conteudo, int vazio );
void nodoListar ( struct Nodo *root, NodoListarCallback callback );

/**
 *Listar de maneira gerenciada os nodos
 */
typedef int (*NodoListarGerenciadoCallback)( void *conteudo, void *aux_parametro );
int nodoListarGerenciado ( struct Nodo *root, NodoListarGerenciadoCallback callback, void *aux_parametro );


#endif /* NODO_H */
