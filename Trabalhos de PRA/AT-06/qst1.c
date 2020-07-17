#include <stdio.h>
#include <stdlib.h>
#define M 5 //14,7

struct dados{
  int chave;
  int value;
};

struct dados *array;
int size = 0;

int hashcode(int chave)
{
return (chave % M);
}


void CalcColisoes(int j){
  int cont=0;
  for(int i = 0; i < 100 ; i++){
      if(array[j].chave==array[i].chave)
        cont++;
  }
  printf("Numero de colisoes = %d\n",cont);

}

void init_array()
{
int i;
    int a = 7;
array = (struct dados*) malloc(100 * sizeof(struct dados));
for (i = 0; i < 100; i++){
array[i].chave = hashcode(a);
array[i].value = a;
        a = a+7;
}
    for (i=0;i<M;i++) {
                printf("%d %d\n",array[i].chave, array[i].value);
                CalcColisoes(i);
    }
}

int main(){
  init_array();
  return 0;
}
