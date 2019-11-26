#ifndef INDICE_H
#define INDICE_H

/**
 * Estrutura de um indice
 */
typedef struct Indice
{
	void *conteudo;

	struct Indice *prox;
} Indice;

/**
 * Gerar um novo Indice
 */
struct Indice *indiceGerar();

/**
 *Listar os indices
 */
typedef void (*IndiceListarCallback)( void *conteudo, int vazio );
void indiceListar ( struct Indice *root, IndiceListarCallback callback );

/**
 *Listar de maneira gerenciada os indices
 */
typedef int (*IndiceListarGerenciadoCallback)( void *conteudo, void *aux_parametro );
int indiceListarGerenciado ( struct Indice *root, IndiceListarGerenciadoCallback callback, void *aux_parametro );


#endif /* INDICE_H */
