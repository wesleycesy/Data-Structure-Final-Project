#include <stdio.h>
#include <stdlib.h>

#define T 5		//DEFINIÇÃO DE ORDEM DA ÁRVORE B

typedef struct ArvB
{
        int n;						//QUANTIDADE DE ELEMENTOS NO VETOR
        int Tamanho;				//TAMANHO DA ÁRVORE DE FILHOS(ACHO)
        int chaves[T-1];			//CRIAÇÃO DO VETOR DE CHAVES (4 POSIÇÕES)
        struct ArvB *filhos[T];		//CRIAÇÃO DO VETOR DE POSSÍVEIS FILHOS (5 POSIÇÕES)
}ArvB;		//NOME DA STRUCT

ArvB * CriarArv()		//FUNÇÃO PARA CRIAÇÃO DE ÁRVORE
{
	int i;
	ArvB *R = (ArvB*) malloc (sizeof(ArvB));	//ALOCAÇÃO
	R->n = 0;									//QUANTIDADE DE ELEMENTOS NO VETOR
	for (i=0; i < T; i++)						//ANULADOR DOS FILHOD
	{
	   R->filhos[i] = NULL;						//CADA FILHO ANULADO
	}
	return R;									//RETORNA A ALOCAÇÃO
}

int Ordena(ArvB ** No, int LimiteDeInsercao)		//FUNÇÃO DE ORDENAÇÃO NA INSERÇÃO
{
	int i;
	for(i = T-2; i > LimiteDeInsercao; i--)			//DO FINAL AO INÍCIO
	{
		(*No)->chaves[i] = (*No)->chaves[i-1];		//ATUAL RECEBE O ANTERIOR ATÉ O LIMITE
	}
	
	return i;			//RETORNA A POSIÇÃO QUE SERÁ INSERIDO NOVO ELEMENTO
}

/*void Split(ArvB *N, ArvB *A)	//FUNÇÃO DA QUEBRA(ALTERAR)
{
     
}*/

void InserirNaoCheio(ArvB *N2, int k)
{
	if(N2->n == 0)					//CASO VETOR DE CHAVES SEM ELEMENTOS
	{
		N2->chaves[0] = k;			//PRIMEIRO ELEMENTO RECEBE A CHAVE NOVA
		N2->n = N2->n+1;			//MAIS UM ELEMENTO NO VETOR
	}else{
		int i;
		for(i = 0; i <= T-2; i++)
		{
			if(i == N2->n)			//ULTIMO CASO DA ÁRVORE (QUANDO O ITEM É O MAIOR DAQUELE VETOR)
			{
				N2->chaves[i] = k;
			}else{
				if(k < N2->chaves[i])		//CHAVE MENOR QUE ALGUM ELEMENTO
				{
					int j;
					j = Ordena(&N2, i);			//ORDENA PARA ACHAR O LUGAR DE INSERÇÃO DO NOVO NÍ
					N2->chaves[j] = k;			//INSERE NA POSIÇÃO RETORNADA PELA FUNÇÃO DE ORDENAÇÃO
					N2->n = N2->n+1;			//MAIS UM ELEMENTO NO VETOR
					break;
				}
			}
		}
	}
}

void Inserir(ArvB **R, int k)		//FUNÇÃO DE INSERÇÃO DE NÓ NA ÁRVORE
{
	ArvB *A = *R;

	if (A->n == T-1)				//CASO VETOR DE CHAVES ESTEJA CHEIO (T-1 = 4)
	{
		ArvB *N = CriarArv();		//CRIAÇÃO DE UMA ÁRVORE AUXILIAR
		
		*R = N;						//ELA VIRA A NOVA RAIZ POR TER TIDO UM ESTOURO NA ANTERIOR

		//SplitFilhos(N, 1, A);		//ANTIGAMENTE TINHA ESTA SPLIT AQUI!!!!

		InserirNaoCheio(N, k);		//INSERINDO NO NOVO VETOR

		*R = A;						//RECUPERANDO O PONTEIRO PRINCIPAL
	}else{
		InserirNaoCheio(A, k);		//PREENCHE O VETOR
	}
}

void Imprimir(ArvB *R)		//IMPRESSÃO DA ÁRVORE
{
	if(R == NULL)	//CASO NULO
		return;
	
	int i;
	for(i = 0; i < T-1; i++)		//POR ENQUANTO SÓ IMPRIME A RAIZ
		printf("Tamanho = %d, n = %d, Chave = %d, Filhos %p\n\n", R->Tamanho, R->n, R->chaves[i], R->filhos[i]);
}

void main()
{
	ArvB *R = CriarArv();	//CRIAÇÃO DA ÁRVORE


	/*TESTE - SEQUÊNCIA DE INSERÇÕES QUE DEPOIS SERÃO DADAS PELO ARQUIVO*/
	Inserir(&R, 12);
	Inserir(&R, 8);
	Inserir(&R, 3);
	Inserir(&R, 1);
	//Inserir(&R, 0);	//NOVO CASO
	Imprimir(R);		//IMPRESSÃO DA ÁRVORE
}
