#include "gerar_arquivo.h"

int main() {
		printf("\nCriando o arquivo:\n");
		clock_t inicio, fim;
		inicio = clock();
		FILE *arquivo = fopen("entrada.bin", "rb");
		escrever_arquivo("entrada.bin", 475 * MB);
		fim = clock();
		double tempo_gasto = (double) (fim- inicio) / CLOCKS_PER_SEC;
		printf("\nTEMPO GASTO: %lf\n", tempo_gasto * 1000);
	return 0;
}
