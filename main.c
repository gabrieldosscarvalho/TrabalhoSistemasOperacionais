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
 * Carregar BD
 */
struct Produto *carregarBd()
{
	FILE *_arqBd = fopen("db", "r");

	if(_arqBd == NULL)
	{
		printf("\n::: Erro abrindo arquivo de destino!");
		exit(EXIT_FAILURE);
	}
	
	int _quantidade_itens = 0;
	
	struct Produto _p;
	while(!feof(_arqBd)) {
		fread (&_p, sizeof(struct Produto), 1, _arqBd);

        _quantidade_itens++;
    }
    
    rewind(_arqBd);
    
    struct Produto *_bd = malloc( _quantidade_itens * sizeof(struct Produto) );
    
    _quantidade_itens = 0;
    
    // Carregar os produtos no vetor
    while(!feof(_arqBd)) {
		fread (&_bd[_quantidade_itens], sizeof(struct Produto), 1, _arqBd);
		
		printf("\nCodigo: %4d\n", _bd[_quantidade_itens].Codigo);

		printf("Nome: %s \n", _bd[_quantidade_itens].Nome);

		printf("Valor: %lf \n", _bd[_quantidade_itens].Valor);

		printf("Data Cadastro: %.8s\n", _bd[_quantidade_itens].DataCadastro);

		printf("Ativo: %s %d\n", (_bd[_quantidade_itens].Ativo ? "SIM": "NAO"), _bd[_quantidade_itens].Ativo);
		
		_quantidade_itens++;
    }
	
	printf("\nquantidade: %d", _quantidade_itens);

	fclose(_arqBd);
	
	return _bd;
}

/**
 * --- COMEÇO ---
 */
int main(int argc, char *argv[]) 
{
	setlocale(LC_ALL,"portuguese");
	
	struct Produto *bd = carregarBd();
	
//	if( bd[10] == NULL ) {
//		printf("\nNAO TEM");
//	} else {
//		printf("\nTEM");
//	}
	
	printf("\nproduto: %d", bd[9].Codigo);


	printf("\n");
	return 0;
}
