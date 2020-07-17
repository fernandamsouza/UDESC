
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int binaria(int* v, int e, int size);

int main() {
    int n = 500000;
    int vet[n],i,posicao,busca;
    for (i=0;i<=n;i++) {
        vet[i] = i;
    }
    for (i=0;i<=n;i++){
        printf("%d\n",vet[i]);
    }
    printf("\n Digite qual valor voce deseja procurar:");
    scanf("%d",&busca);
    clock_t Ticks[2];
    Ticks[0] = clock();
    posicao = binaria(vet, busca , n);
    Ticks[1] = clock();
    double Tempo = (double)((Ticks[1] - Ticks[0]) ) * 1000000.0/ CLOCKS_PER_SEC;
    printf("Tempo gasto: %g us.", Tempo);
    if (posicao!=-1) {
        printf("\nValor encontrado na %d posicao!\n",posicao);
    }
    else {
        printf("\nValor nao encontrado!\n");
    }
    return 0;
}


int binaria(int* v, int e, int size) {
 int inicio = 0, fim = size;
 int meio;
 while(inicio <= fim){
    meio = (inicio+fim)/2;
   if(v[meio] == e) {
    return meio;
    }
   if(v[meio] < e) {
    inicio = meio+1;
    }
   else {
    fim = meio-1;
    }
}
return -1;
}
