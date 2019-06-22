#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int lin , col;
	int **m;
}matriz;

int inteiro(char num[10]){
    int conv, i;   
    conv=atoi(num);
	return conv;
	
	}

matriz* aloca(int lin, int col){
	int i, j;
	matriz *M = malloc(sizeof(matriz));
	if (M == NULL){
		printf ("Erro na alocacao");
		exit (1);
	}
	M->m = malloc(sizeof(int*) * lin);
	for(i = 0; i < lin; i++){
		M->m[i] = malloc(sizeof(int) * col);
	}
	M->lin = lin;
	M->col = col;
	return M;
	for (i=0;i<lin;i++) {
		free(M->m[i]);
	}
	free(M->m);
}



matriz* leitura(char nameof[20]){
	FILE *arq;
	arq = fopen(nameof,"r");
	
	matriz *M = malloc(sizeof(matriz));
	
	fscanf(arq, "%d %d", &M->lin, &M->col);
	M->m = malloc(sizeof(int*) * M->lin);
	
	int i, j;
	for(i = 0; i < M->lin; i++){
		M->m[i] = malloc(sizeof(int) * M->col);
	}

	for(i = 0; i < M->lin; i++){
		for(j = 0; j < M->col; j++){
			fscanf(arq, "%d", &M->m[i][j]);
		}
	}	
	return M;
	for (i=0;i<M->lin;i++) {
		free(M->m[i]);
	}
	free(M->m);
	fclose(arq);
}


void escreve(char nameof[20] ,matriz *R){
	int i, j;
	FILE *W = fopen(nameof,"w");
	int l = R->lin;
	int c = R->col;
	
	fprintf(W,"%d %d\n",l,c);
	
	for(i=0;i<l;i++){
			for(j=0;j<c;j++){
				fprintf(W,"%d ", R->m[i][j]);
			}
			fprintf (W,"\n");
		}
	
}


matriz* transposta(matriz* M){
	int i, j, l, c;
	l = M->lin;
	c = M->col;
	matriz *R;
	
	if (l==c){
	R = aloca(l,c);
	for(i=0;i<l;i++){
			for(j=0;j<c;j++){
				R->m[i][j]=M->m[j][i];
			}
		}
			printf ("Operacao bem sucedida");
	}else{
		R = aloca(c,l);
		for(i=0;i<c;i++){
			for(j=0;j<l;j++){
				R->m[i][j]=M->m[j][i];
			}
		}
		printf ("Operacao bem sucedida");
	}
	return R;
}

matriz* soma(matriz* M1,matriz* M2){
	if (M1->lin == M2->lin && M1->col == M2->col){
	int i, j;
		
	matriz *R = aloca(M1->lin,M1->col);
		
	for(i=0;i<M1->lin;i++){
		for(j=0;j<M1->col;j++){
			R->m[i][j] = M1->m[i][j]+M2->m[i][j];
		}
	}
		
	printf("Resultado obtido.");
	return R;
	
	}else{
		printf("Matrizes sao incompativeis.");
	}
}

matriz* subtracao(matriz* M1,matriz* M2){
	if (M1->lin == M2->lin && M1->col == M2->col){
	int i, j;
		
	matriz *R = aloca(M1->lin,M2->col);
		
	for(i=0;i<M1->lin;i++){
		for(j=0;j<M1->col;j++){
			R->m[i][j] = M1->m[i][j]-M2->m[i][j];
		}
	}
		
	printf("Resultado obtido.");
	return R;
	
	}else{
		printf("Matrizes sao incompativeis.");
	}
}

matriz* multiplicacao (matriz* M1, matriz* M2){
	int soma;
	if ((M1->lin<1 || M1->col<1) || M2->lin<1 || M2->col<1){
		printf("Colunas ou Linhas não podem ter valores menores que 1.\n");
		exit(1); 
	}
	else if (M1->col!=M2->lin){
		printf("Numero de colunas da Matriz 1 diferente ao numero de linhas da Matriz 2.\nImpossível realizar multiplicação.\n");
		exit(1);
	}else {
		int i,j,k,n,m,p,soma; 
		matriz *R = aloca(M1->lin,M2->col);
		m=M1->lin;
		p=M2->lin;
		n=M2->col;
		
		for (i = 0; i < m; i = i + 1) {
			for (j = 0; j < p; j = j + 1) {
				soma = 0;
				for (k = 0; k < m; k = k + 1) {
					soma = soma + M1->m[i][k] * M2->m[k][j];
					R->m[i][j] = soma;
				}
			}
		}
		printf ("Resultado obtido!");
		return R;
	}
}

matriz* multiplicacao_escalar(matriz* M, int f){
	int i, j;
	for(i=0;i<M->lin;i++){
		for(j=0;j<M->col;j++){
			M->m[i][j]=f*(M->m[i][j]);
			}
		}
		printf ("Resultado obtido");
	return M;
	for (i=0;i<M->lin;i++) {
		free(M->m[i]);
	}
	free(M->m);
	}


void iguais(matriz* M1,matriz* M2){
	int i, j, tru=1;
	
	if (M1->lin == M2->lin && M1->col == M2->col){
		for(i=0;i<M1->lin;i++){
			for(j=0;j<M1->col;j++){
				if(M1->m[i][j]!=M2->m[i][j]){
					tru=-1;
				}
			}
		}
		
	}else{
		tru = -1;
	}
	if(tru == -1){
		printf("As matrizes comparadas nao sao iguais");
	}else{
		printf("As matrizes comparadas sao iguais");
	}
}	

void simetrica(matriz* M){
	int i, j, tru=1;
	
	for(i=0;i<M->lin;i++){
		for(j=0;j<M->col;j++){
			if(M->m[i][j]!=M->m[j][i]){
				tru=-1;
			}
		}
	}
	if(tru == -1){
		printf("Nao eh simetrica");
	}else{
		printf("Eh simetrica");
	}
}

int help() {
		printf ("Parametros insuficientes");
		return -1;
}

