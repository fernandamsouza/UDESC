#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define M 11 // 9

typedef struct{
    int codigo;
    int cod2;
}TItem;

typedef struct{
    TItem item;
    struct TCelula *prox;
}TCelula;

typedef struct{
    TCelula *primeiro;
    TCelula *ultimo;
}TLista;

void inicializa(TLista *lista)
{
    lista->primeiro = (TCelula*)malloc(sizeof(TCelula));
    lista->primeiro->prox = NULL;
    lista->ultimo = lista->primeiro;
}

TCelula* alocaCelula()
{
    return (TCelula*)malloc(sizeof(TCelula));
}

void inserir(TLista *lista,TItem *item)
{
    TCelula *novaCelula;

    novaCelula = alocaCelula();
    novaCelula->item = *item;
    novaCelula->prox = NULL;

    lista->ultimo->prox  = novaCelula;
    lista->ultimo = novaCelula;
}

void imprimir(TLista *lista)
{
    TCelula *celulaAux;
    celulaAux = lista->primeiro->prox;

    while (celulaAux != NULL)
    {
        printf("valor: %d\n",celulaAux->item.codigo);
        celulaAux = celulaAux->prox;
    }
}

int calculaH(TItem item) {
    return (item.codigo % M);
}

int main () {
    FILE *arq;
    int codigo,i;
    int h;
    TLista lista[M];
    TItem x;
    for(i=0;i<M;i++) {
        inicializa(&lista[i]);
    }
    arq = fopen("numeros.txt","r");
   if(arq){
       while(fscanf(arq,"%d\n",&codigo)!= EOF){
           x.codigo = codigo;
           h = calculaH(x);
           inserir(&lista[h],&x);
        }
      for(i=0;i<M;i++) {
         imprimir(&lista[i]);
     }
 } else {
       printf("Erro ! Arquivo nao encontrado\n");
   }
}
