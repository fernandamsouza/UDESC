#include "ordenar_arquivo.h"

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("\nModelo padrão: %s <arquivo_saida> ", argv[0]);
		return 1;
	}
	else {
		int M = 5;
		int memoria = 100 * MB;
		FILE *file = fopen("entrada.bin", "rb");
		clock_t inicio, fim;
		inicio = clock();
		Fita *files = generate_runs(file, memoria, M);
		unsigned long input_file_length = get_file_length(file);
		int output_file_index = interpolate(files, input_file_length, memoria, M);
		fim = clock();
		double tempo_gasto = (double) (fim - inicio) / CLOCKS_PER_SEC;
		int i;
		for (i = 0; i < 2 * M; i++) {
			fclose(files[i].file);
			if (i == output_file_index)
			{
				continue;
			}
		}
		rename(files[output_file_index].name, argv[1]);
		printf("\nTEMPO GASTO: %lf\n", tempo_gasto * 1000);
		printf("\nARQUIVO SAIDA: %s\n", argv[1]);
		fclose(file);
	}
	return 0;
}
