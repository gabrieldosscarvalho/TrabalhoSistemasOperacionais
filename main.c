#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "teste/teste.h"
#include "indice/indice.h"

struct Produto
{
	int Codigo;
	char DataCadastro[8]; // AAAAMMDD
	bool Ativo;
	char Nome[50];
	double Valor;
};

/**
 * Gerar um novo produto na memória
 */
struct Produto *gerarProduto()
{
	struct Produto *_p = (struct Produto*) malloc( sizeof (struct Produto) );
	struct tm *_aux_data_cadastro;
  
  	_p->Codigo = (int)time(NULL); // Timestamp

	_aux_data_cadastro = localtime(&_p->Codigo);

	sprintf(_p->DataCadastro, "%.4d%.2d%.2d",
		_aux_data_cadastro->tm_year+1900,
		_aux_data_cadastro->tm_mon+1,
		_aux_data_cadastro->tm_mday
	);

	_p->Ativo = false;

	strcpy(_p->Nome, "");

	_p->Valor = 0.0;

	return _p;
}

/**
 * Listar os dados de um Produto
 */
void listarProduto( void *conteudo, int listaVazia )
{
	if( listaVazia == 1 ) {
		printf("\n--- Lista esta vazia ---");
		return;
	}

	struct Produto *_p = (struct Produto*) conteudo;
	
	printf("\n--Produto");
	printf("\nCódigo:.............:\t %d",	_p->Codigo);
	printf("\nData de cadastro:...:\t %.8s",	_p->DataCadastro);
	printf("\nNome:...............:\t %s",	_p->Nome);
	printf("\nValor:..............:\t %.2f",	_p->Valor);
	printf("\nAtivo:..............:\t %s",	_p->Ativo? "[*]": "[]");
	printf("\n");
}

/**
 * Persistir cada produto no arquivo
 */
int persistirIndice( void *conteudo, void *arquivo )
{
	FILE *_a = (FILE *) arquivo;
	printf("\n Arquivo: %p", arquivo);
	
	fwrite((struct Produto*) conteudo, sizeof(struct Produto), 1, _a);
	return 0;
}

/**
 * Persistir os produtos no arquivo
 */
void persistir( struct Indice *root )
{
	FILE *arqDestino = fopen("indice_teste", "wb");

	if(arqDestino == NULL)
	{
		printf("\n::: Erro abrindo arquivo de destino!");
		exit(EXIT_FAILURE);
	}

	indiceListarGerenciado(root, persistirIndice, arqDestino);

	fclose(arqDestino);
}

/**
 * --- COMEÇO ---
 */
int main(int argc, char *argv[]) 
{
	setlocale(LC_ALL,"portuguese");

	// Lista
	struct Indice *root = indiceGerar();
	
	// Item 1
	struct Indice *item1 = indiceGerar();	
	struct Produto *p = gerarProduto();	
	strcpy(p->Nome, "Caneta 1");	
	item1->conteudo = p;
	root->prox = item1;
	
	// Item 2
	struct Indice *item2 = indiceGerar();	
	struct Produto *p2 = gerarProduto();
	strcpy(p2->Nome, "Lapís");
	p2->Ativo = true;
	item2->conteudo = p2;	
	item1->prox = item2;
	
	indiceListar(root, listarProduto);
	
	// TEMPORARIO
	persistir( root );


	printf("\n");
	return 0;
}
