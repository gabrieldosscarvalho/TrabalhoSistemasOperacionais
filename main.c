#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "nodo/nodo.h"

/**
 * Estrutura Produto
 */
struct Produto
{
	int Codigo;
	char DataCadastro[8]; // AAAAMMDD
	bool Ativo;
	char Nome[50];
	double Valor;
};

/**
 * Abre um arquivo
 */
FILE *abrirArquivo( char *nomeArquivo, char *modo )
{
	FILE *_arq = fopen(nomeArquivo, modo);

	if(_arq == NULL)
	{
		printf("\n::: Erro abrindo arquivo de destino!");
		exit(EXIT_FAILURE);
	}
	
	return _arq;
}

/**
 * Carregar BD
 */
struct Produto *carregarBd()
{
	FILE *_arqBd = abrirArquivo("db", "r");
	
	int _quantidade_itens = 0;
	
	// Contar a quantidade de itens no arquivo
	struct Produto _p;
	while(!feof(_arqBd)) {
		fread (&_p, sizeof(struct Produto), 1, _arqBd);

        _quantidade_itens++;
    }
    
    rewind(_arqBd);
    
    struct Produto *_bd = malloc( (_quantidade_itens + 1) * sizeof(struct Produto) );
    
    int _index = 0;
    
    // Carregar os produtos no vetor
    while(!feof(_arqBd)) {
		fread (&_bd[_index], sizeof(struct Produto), 1, _arqBd);
		
		_index++;
    }
    
    if( _index == 0 ) {
    	_bd[0] = (struct Produto) _bd[0];
    	_bd[0].Codigo = -1; // hack para parar as futuras listagem
	}
    _bd[_index].Codigo = -1; // hack para parar as futuras listagem

	fclose(_arqBd);
	
	return _bd;
}

/**
 * Montar o indice
 */
void montarIndice( struct Nodo *indice, struct Produto *bd )
{
	struct Nodo *_item = indice;

	int _index = 0;

	while( bd[_index].Codigo != -1 ) {
		_item->prox = nodoGerar();
		_item = _item->prox;

		_item->conteudo = _index;
		
		_index++;
	}
}

/**
 * Persistir cada item do indice
 */
int persistirIndiceItem( void *conteudo, void *arquivo )
{
	FILE *_a = (FILE *) arquivo;
	
	int _index = (int) conteudo;
	
	fwrite(&_index, sizeof(int), 1, _a);
	
	printf("\n IDEX -- %d", _index);
	return 0;
}

/**
 * Persistir indice
 */
void persistirIndice( struct Nodo *indice )
{
	FILE *_arqIndice = abrirArquivo("indice", "wb");

	nodoListarGerenciado( indice, persistirIndiceItem, _arqIndice );

	fclose(_arqIndice);
}

/**
 * Carregar o indice para a memória
 */
void carregarIndice( struct Nodo *indice )
{
	FILE *_arqIndice = abrirArquivo("indice", "r");

	struct Nodo *_item = indice;

	int _index;

	while( fread(&_index, sizeof(int), 1, _arqIndice) ) {
		_item->prox = nodoGerar();
		_item = _item->prox;

		_item->conteudo = _index;
		
		printf("\n IDEX -- %d", _item->conteudo);
    }

	fclose(_arqIndice);
}

/**
 * Listar todos os produtos
 */
int listarProdutos(void *conteudo, void *bd )
{	
	int _index = (int) conteudo;
	struct Produto *_bd = (struct Produto *) bd;
	
	printf("\n--Indice: %d", _index);

	exibirProduto( _bd[_index] );

	return 0;
}

/**
 * Exibir dados do produto
 */
void exibirProduto( struct Produto *p )
{
	printf("\n--Produto");
	printf("\nCódigo:.............:\t %d",		p->Codigo);
	printf("\nData de cadastro:...:\t %.8s",	p->DataCadastro);
	printf("\nNome:...............:\t %s",		p->Nome);
	printf("\nValor:..............:\t %.2f",	p->Valor);
	printf("\nAtivo:..............:\t %s",		p->Ativo? "[*]": "[]");
	printf("\n");
}

/**
 * --- COMEÇO ---
 */
int main(int argc, char *argv[]) 
{
	setlocale(LC_ALL,"portuguese");
	
	struct Produto *bd = carregarBd();
	struct Nodo *indice = nodoGerar();
	
	carregarIndice(indice);
	//montarIndice( indice, bd );
	//persistirIndice(indice);

	nodoListarGerenciado(indice, listarProdutos, bd);

	printf("\n");
	return 0;
}
