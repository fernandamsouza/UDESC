#include "gerar_arquivo.h"

typedef struct oi {
	unsigned long chave1;
	float chave2;
}Dado;

int ler_arquivo_binario(char *nome_arquivo) {
	FILE *arquivo = fopen(nome_arquivo, "rb");
	if (!arquivo) {
		printf("Erro ao abrir o arquivo!");
		return 1;
	}
	Dado aux;
	while (fread(&aux, sizeof(Dado), 1, arquivo) == 1) {
		printf("%lu %f\n", aux.chave1, aux.chave2);
	}
	fclose(arquivo);

	return 0;
}

int main(int argc, char *argv[])
{
	ler_arquivo_binario(argv[1]);
	return 0;
}
