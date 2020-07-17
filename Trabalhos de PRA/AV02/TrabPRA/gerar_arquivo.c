#include "gerar_arquivo.h"

typedef struct oi {
	unsigned long chave1;
	float chave2;
}Dado;

// tamanho total é 475mb, passado por função e caracterizado como tamanho_total.
int escrever_arquivo(char *nome_arquivo, long tamanho_total) {
	FILE *arquivo = fopen(nome_arquivo, "wb");
	long tamanho_arquivo = 0;
	if (!arquivo) {
		printf("Erro ao abrir arquivo!");
		return 1;
	}
			Dado aux;
	while (tamanho_arquivo < tamanho_total) {
		aux.chave1 =  (unsigned long)(((unsigned long)rand())*rand());
		aux.chave2 = (float)((rand()*rand())/(rand()+0.0));
		fwrite(&aux, sizeof(Dado), 1, arquivo);
		tamanho_arquivo = tamanho_arquivo + sizeof(Dado);
	}
	fclose(arquivo);
	return 0;
}
