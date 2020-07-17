//TRABALHO FEITO POR:
//MATIAS GUTIERREZ E FERNANDA MARIA DE SOUZA

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//TAMANO EM BYTES DA STRUCT 44
typedef struct {
  char delet;
  char nome[10];
  char marca[10];
  char ean13[13];
  int rrn;
  float valor;
} dados;

typedef struct pilhas{
  dados eliminados;
  struct pilhas *prox;
} pilha;

pilha* inicializar(pilha *pi){
  return NULL;
}

void listar(FILE *arq);

dados excluir (pilha *p, FILE *arq) {
  int rrn;
  dados dadoss2;
  printf ("Digite o nro de rrn do produto a ser excluido e incluído na pilha de descarte: \n");
  scanf ("%d", &rrn);
  fseek(arq, sizeof(dados)*rrn,0); // 44*rrn
  fread(&dadoss2,sizeof(dados),1,arq);
  if (dadoss2.rrn == rrn) {
  printf("--------------------------ALERTA--------------------------\n");
  printf("----------------ESTE PRODUTO SERA REMOVIDO----------------\n");
  printf("NOME: %s\n",dadoss2.nome);
  printf("MARCA: %s\n",dadoss2.marca);
  printf("CODIGO: %s\n",dadoss2.ean13);
  printf("VALOR: %.2f\n",dadoss2.valor);
  printf("RRN: %i\n",dadoss2.rrn);
  dadoss2.delet = '*';
  fwrite (&dadoss2, sizeof(dados),1, arq);
  p->eliminados = dadoss2;
    return dadoss2;
  }
  else {
    printf ("RRN nao encontrado");
    exit(1);
  }
}

void organizar(dados dadoss,int qdeprodutos, FILE *arq) {
  int j=qdeprodutos;
  dados dadoss2[j-1],aux[j-1];
  printf("\nOrganizando os dados...\n");
  for(int i = 0; i <= j-1; i++){
    if(dadoss2[i].delet==dadoss.delet){
      for(int p = 0; p < j-i; p++){
        aux[p] = dadoss2[p+1];
      }
      break;
    }
    aux[i] = dadoss2[i+1];
  }
  for(int i = 0; i < j-1; i++)
    fwrite (&dadoss, sizeof(dados),1, arq);
}

int main () {
  pilha *pi = (pilha *)malloc(sizeof(pilha));
  int i,m=0;
  FILE *arq;
  bool si = true, sis = true;
  if (!pi) {
    printf ("Sem memória disponível");
    return 0;
  }
  arq = fopen ("binario.dat", "wb");
  if (arq == NULL) {
    printf ("Problema no arquivo");
    return 0;
  }
  dados dadoso;
  int aux = -1, qdeprodutos = 0;

  while (si) {
    printf ("\n-Digite 1 para agregar um produto.\n \n-Digite 0 para terminar de agregar.\n");
  scanf ("%d", &m);
  switch (m) {
    case 1:
      printf("\nDigite o nome:\n");
      scanf ("%s", dadoso.nome);
      printf("Digite a marca:\n");
      scanf ("%s", dadoso.marca);
      printf("Digite o codigo de 13 digitos:\n");
      scanf ("%s", dadoso.ean13);
      printf("Digite o valor do produto:\n");
      scanf ("%f", &dadoso.valor);
      aux++;
      dadoso.rrn = aux;
      qdeprodutos++;
      fwrite (&dadoso, sizeof(dados),1, arq);
      break;
    case 0:
      si = false;
      break;
    }
  }
  fclose(arq);

  arq = fopen ("binario.dat", "rb");
  if (arq == NULL) {
    printf ("Problema no arquivo");
    return 0;
  }
  dados dadoss[qdeprodutos],dadoss2;
  int l,u;

  while (sis) {
    printf("\n-Quer recuperar um produto em especifico? Digite 1; \n-Para mostrar a lista inteira de produtos. Digite 2;\n-Para excluir um produto da lista. Digite 3;\n-Para sair do programa. Digite 0;\n");
    scanf ("%d",&l);
    switch (l) {

      case 1:
        printf("\nDigite o numero do produto que você quer: (RRN)\n");
        scanf("%d",&u);
        //USANDO A FORMULA ENSINADA DENTRO DO FSEEK PARA IDENTIFICAR A POSICAO DO PRODUTO DENTRO DO ARQUIVO
        //NUMERO DE BYTES * RRN;
        fseek(arq, 44*u,0);
        fread(&dadoss2,sizeof(dados),1,arq);
        printf("NOME: %s\n",dadoss2.nome);
        printf("MARCA: %s\n",dadoss2.marca);
        printf("CODIGO: %s\n",dadoss2.ean13);
        printf("VALOR: %.2f\n",dadoss2.valor);
        printf("RRN: %i\n",dadoss2.rrn);
        break;

      case 2:
      listar(arq);
        break;
      case 3:
        printf("\n");
        organizar(excluir(pi,arq),qdeprodutos, arq);
        break;
      case 0:
        sis = false;
        break;
      }
  }
  fclose(arq);
  return 0;
}

void listar(FILE *arq) {
  fseek(arq,0,0);
  int j;
  dados dadoss;
  while (fread(&dadoss, sizeof(dadoss), 1, arq) == 1){
    printf("\n");
    printf("NOME: %s\n",dadoss.nome);
    printf("MARCA: %s\n",dadoss.marca);
    printf("CODIGO: %s\n",dadoss.ean13);
    printf("VALOR: %.2f\n",dadoss.valor);
    printf("RRN: %i\n",dadoss.rrn);
  }
}
