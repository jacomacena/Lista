#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

struct no{
	int num;
	struct no *ant, *prox;
	int tamanho;
};

//------------------------------------------------------------------------------
void menu();
void add_inicio(struct no **lista, int valor);
void add_fim(struct no **lista, int valor);
void imprimir_ant(struct no *lista);
void imprimir_prox(struct no *lista);
void remover_inicio(struct no *lista, int tamanho);
void remover_fim(struct no *lista, int tamanho);
void remover(struct no **lista, int valor);
struct no *buscar(struct no *lista, int valor);

int j;
//------------------------------------------------------------------------------
/* ------- Menu de opções ------- */
void menu(){
     system("color 17");
     
     printf("%65s","--------------------- MENU ---------------------\n");
	 printf("\n                - 1: Inserir no inicio                         -");
	 printf("\n                - 2: Inserir no fim                            -");
	 printf("\n                - 3: Imprimir da esquerda para direita         -");
	 printf("\n                - 4: Imprimir da direita para esquerda         -");
	 printf("\n                - 5: Buscar um elemento e exibir ponteiro      -");
	 printf("\n                - 6: Remover elemento desejado                 -");
	 printf("\n                - 0: Sair                                      -\n");
	 printf("%65s","------------------------------------------------\n");
	 printf("\n->");
}

int main (int argc, char *argv){
	struct no *lista, *p;
	int op, valor;

	lista = NULL;

	do{
		system("cls");
		menu();
		scanf("%d",&op);

		switch(op){
			case 0:
				 break;
			case 1:
				add_inicio(&lista, valor);
				break;
			case 2:
				add_fim(&lista, valor);
				break;
			case 3:
				imprimir_ant(lista);
				break;
			case 4:
				imprimir_prox(lista);
				break;
			case 5:
				printf("\nBuscar Elemento: ");
				scanf("%d",&valor);
				printf("\nPonteiro: %p",buscar(lista,valor));
				break;
			case 6:
				remover(&lista, valor);
				break;
			default:
				printf("\nOpcao Invalida!\n");
				break;
		}
		getch();
	}while(op!=0);

	while(lista!=NULL){
		p = lista;
		lista = lista->prox;
		free(p);
	}
}
//------------------------------------------------------------------------------
// Adicionar numero no inicio
void add_inicio(struct no **lista, int valor){
	struct no *aux;

	printf("\nValor do Elemento: ");
	scanf("%d",&valor);

    if((aux = malloc(sizeof(struct no))) == NULL){
		printf("\nMemoria Insuficiente");
	}
	else{
		aux->num = valor;
		aux->ant = NULL;
		aux->prox = *lista;

		if(*lista != NULL){
			(*lista)->ant = aux;
		}
		*lista = aux;
	}
}
//------------------------------------------------------------------------------
// Adicionar numero no final
void add_fim(struct no **lista, int valor){
	struct no *pNow, *pNavegar;

	printf("\nValor do Elemento: ");
	scanf("%d",&valor);

	pNavegar = *lista;

	if((pNow = malloc(sizeof(struct no))) == NULL){
		printf("\nMemory Failure\n");
	}
	else{
		pNow->num = valor;
		pNow->prox = NULL;
		pNow->ant = NULL;
		if(*lista == NULL){
			*lista = pNow;
		}
		else{
			while(pNavegar->prox != NULL){
				pNavegar = pNavegar->prox;
			}
			pNavegar->prox = pNow;
			pNow->ant = pNavegar;
		}
	}
}
//------------------------------------------------------------------------------
// Exibi a lista 
void imprimir_ant(struct no *lista){
	struct no *p;
	p = lista;
	if(p == NULL){
		printf("\nLista Vazia");
	}
	else{
         printf("\n--------------------------------------------------------------------------------\n");
         printf("\nElementos: ");
	   	 while(p!=NULL){
			printf("%d",p->num);
			if(p->prox!=NULL)printf(", ");
			if(p->prox==NULL)printf(".");
			p = p->prox;
		}
		printf("\n--------------------------------------------------------------------------------\n");
	}
}
//------------------------------------------------------------------------------

void imprimir_prox(struct no *lista){
	struct no *p;
	p=lista;
	if(lista == NULL){
		printf("\nLista Vazia\n");
	}
	else{
		while(p->prox != NULL){
			p = p->prox;
		}
		
		printf("\n--------------------------------------------------------------------------------\n");
		printf("\nElementos: ");
		while(p != NULL){
			printf("%d",p->num);
			if(p->ant!=NULL)printf(", ");
			if(p->ant==NULL)printf(".");
			p = p->ant;
		}
		printf("\n--------------------------------------------------------------------------------\n");
	}
}
//-----------------------------------------------------------------------------------------
struct no *buscar(struct no *lista, int valor){
	struct no *retorno;

	int encontrou = 0;
	retorno = NULL;
	while(lista != NULL){
		if((lista->num) == valor){
			retorno = lista;
			encontrou = 1;
			break;
		}
		lista = lista->prox;
	}
	if(encontrou == 1){
		printf("\nElemento Encontrado com Sucesso!\n");
	}
	else{
		printf("\nElemento digitado invalido!\n");
	}
	return retorno;
}

//------------------------------------------------------------------------------------------
void remover(struct no **lista, int valor){
	struct no *p,*aux;
	int encontrou = 0;
	p = *lista;

	printf("\nValor a Ser Removido: ");
	scanf("%d",&valor);

	aux = buscar(*lista, valor);

	if(*lista == NULL){
		printf("\nLista Vazia\n");
	}
	else{
		if(aux != NULL){
			if(aux->prox != NULL){
				aux->prox->ant = aux->ant;

            }
			if(aux->ant != NULL){
				aux->ant->prox = aux->prox;
			}
			else{
				*lista = aux->prox;
			}
			free(aux);
			encontrou = 1;
		}

		if(encontrou == 1){
			printf("\nElemento removido com Sucesso!\n");
		}
		else{
			printf("\nElemento nao Encontrado\n");
		}
	}
}
