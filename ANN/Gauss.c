#include <stdio.h>
#include <stdlib.h>

int main(){

  double termo;
  double m;
  int qnt,i,j,k;

  printf("\nInforme a quantidade de variáveis \n");
  scanf("%d",&qnt);

  double coeficientes[qnt][qnt+1]; // Matriz dos coeficientes
  double x[qnt]; // Vetor das soluções

  printf("\nDigite a matriz extendida \n");

  for(i=0;i<qnt;i++){
    for(j=0;j<qnt+1;j++){
      scanf("%lf",&coeficientes[i][j]);
    }

  }

  printf("\nMatriz antes do escalonamento:\n");

  for(i=0;i<qnt;i++){

    for(j=0;j<qnt+1;j++){
      printf("%lf",coeficientes[i][j]);

      if(j==qnt) printf("\n");
      else printf("\t");

    }



  }

  // FAZ O ESCALONAMENTO DA MATRIZ

  for(i=0;i<qnt-1;i++){

    for(j=i+1;j<qnt;j++){

      m = -1*(coeficientes[j][i] / coeficientes[i][i]);

      for(k=0; k < qnt+1 ; k++){

        coeficientes[j][k] = (coeficientes[i][k] * m) + coeficientes[j][k];

      }

    }

    printf("\nMatriz atualizada:\n");

      for(j=0; j<qnt; j++){

        for(k=0; k<qnt+1; k++){

          printf("%.8lf", coeficientes[j][k]);

          if(k == qnt) printf("\n");
          else printf(" ");

        }
      }
    }

  // FIM DO METODO DE GAUSS

  // RESOLVENDO O SISTEMA

  int aux;
  int cont=0;

  for(i=0;i<qnt;i++){

    termo = 0;
    aux = qnt-i;

    for(j=aux; j<qnt; j++){

      termo += (x[j]*coeficientes[qnt-i-1][j]);

    }

    x[qnt-i-1]=(coeficientes[qnt-1-i][qnt]-termo)/coeficientes[qnt-i-1][qnt-i-1];


  }

  // FIM DA RESOLUÇÃO

  printf("\nVetor solução: \n");

  for(i=0;i<qnt;i++){
    printf("x[%d] = %lf \n",i, x[i]);
  }


}
