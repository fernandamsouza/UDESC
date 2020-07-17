#include "ordenar_arquivo.h"

void insert (pilha_no a_node, pilha_no *heap, int size) {
	int idx;
	pilha_no tmp;
	idx = size + 1;
	heap[idx] = a_node;
	while (heap[idx].value < heap[idx/2].value && idx > 1) {
		tmp = heap[idx];
		heap[idx] = heap[idx/2];
		heap[idx/2] = tmp;
		idx /= 2;
	}
}

void shift_down (pilha_no *heap, int size, int idx) {
	int cidx;
	pilha_no tmp;
	for (;;) {
		cidx = idx*2;
		if (cidx > size) {
			break;
		}
		if (cidx < size) {
			if (heap[cidx].value > heap[cidx+1].value) {
				++cidx;
			}
		}
		if (heap[cidx].value < heap[idx].value) {
			tmp = heap[cidx];
			heap[cidx] = heap[idx];
			heap[idx] = tmp;
			idx = cidx;
		}
		else {
			break;
		}
	}
}

pilha_no remove_min (pilha_no *heap, int size) {
	pilha_no rv = heap[1];
	heap[1] = heap[size];
	--size;
	shift_down(heap, size, 1);
	return rv;
}

void enqueue (pilha_no node, Priore *q) {
	insert(node, q->heap, q->size);
	++q->size;
}

pilha_no dequeue (Priore *q) {
	pilha_no rv = remove_min(q->heap, q->size);
	--q->size;
	return rv;
}

void init_queue (Priore *q, int n) {
	q->size = 0;
	q->heap = (pilha_no*) malloc(sizeof(pilha_no) * (n+1));
}

/* Essa função compara dois números para verificar qual o maior */
unsigned long compare_function (const void * a, const void * b) {
	return (*(unsigned long*)a - *(unsigned long*)b);
}

/* Gera as fitas iniciais */
Fita* generate_Fitas (const int K) {
	Fita *files = malloc ((2 * K) * sizeof(Fita));
	int i;
	for (i = 0; i < (2 * K); i++) {
		char *tmp_char = malloc (sizeof(int));
		sprintf(tmp_char, "%d", i);
		char *file_name = malloc(strlen("Fita_") + strlen(tmp_char) + strlen(".bin") + 1);
		strcpy(file_name, "Fita_");
		strcat(file_name, tmp_char);
		strcat(file_name, ".bin");
		files[i].id = i;
		files[i].name = file_name;
		files[i].file = fopen(file_name, "w+b");
		files[i].actual_size = 0;
		files[i].actual_run.size = 0;
	}
	return files;
}


unsigned long get_file_length (FILE* file) {
	unsigned long fileLength;
	fseek(file, 0, SEEK_END);
	fileLength = ftell(file);
	fseek(file, 0, SEEK_SET);
	return fileLength;
}

int get_number_of_runs (unsigned long file_length, const int mem) {
	int number_of_runs = ceil((float) file_length / mem);
	return number_of_runs;
}

/* Gera as execuções iniciais */
Fita* generate_runs (FILE *file, const int mem, const int K) {
	Fita* files = generate_Fitas(K);
	unsigned long * buffer = NULL;
	int number_of_total_runs = get_number_of_runs(get_file_length(file), mem);
	int x;
	for (x = 0; x < number_of_total_runs; x++) {
		buffer = (unsigned long *) malloc(mem);
		size_t bytes_read = fread(buffer, 1, mem, file);
		qsort(buffer, bytes_read / ITEM_SIZE, sizeof(unsigned long), compare_function);
		int actual_position = x % K;
		files[actual_position].actual_size = files[actual_position].actual_size + bytes_read;
		Run run;
		run.size = bytes_read;
		if (files[actual_position].actual_run.size == 0) {
			files[actual_position].actual_run = run;
		}
		fwrite(buffer, bytes_read, 1, files[actual_position].file);
	}
	for (x = 0; x < K + 1; x++) {
		fseek(files[x].file, SEEK_SET, 0);
	}
    free(buffer);
	return files;
}

int int_log (double base, double x) {
	return ceil((double) (log(x) / log(base)));
}

/* Intercala os valores e retorna o arquivo final. */
int interpolate(Fita *files, unsigned long input_file_length, const unsigned long mem, const int K)
{
	Priore priority_queue;
	int num_of_interpolation_steps = int_log(K, input_file_length / mem);
	int count_num_of_interpolations;
	int count_num_of_combination_per_interpolation;
	int actual_output_position = -1;
	for (count_num_of_interpolations = 0; count_num_of_interpolations < num_of_interpolation_steps; count_num_of_interpolations++)
	{
		int num_of_combinations_per_interpolation = num_of_interpolation_steps - count_num_of_interpolations;
		int start, end;
		if (count_num_of_interpolations % 2 == 0)
		{
			start = 0;
			end = K;
			actual_output_position = K;
		}
		else
		{
			start = K;
			end = 2 * K;
			actual_output_position = 0;
		}
		for (count_num_of_combination_per_interpolation = 0; count_num_of_combination_per_interpolation < num_of_combinations_per_interpolation; count_num_of_combination_per_interpolation++)
		{
			int count;
			size_t total_bytes_written = 0;
			init_queue(&priority_queue, K);
			/* Enche a pilha com os primeiros valores de cada execução*/
			for (count = start; count < end; count++)
			{
				if (files[count].actual_size == 0)
				{
					continue;
				}
				/* pula apenas na primeira vez */
				if (count_num_of_combination_per_interpolation == 0 && count_num_of_interpolations > 0)
				{
					fseek(files[count].file, SEEK_SET, 0);
				}
				/* Cria a execução inicial para cada fita que vai ser intercalada */
				if (files[count].actual_size != 0 && files[count].actual_run.size == 0)
				{
					Run run;
					if(files[count].actual_size <= mem)
					{
						run.size = files[count].actual_size;
					}
					else
					{
						run.size = (count_num_of_interpolations + 1) * mem;
					}
					files[count].actual_run = run;
				}
				pilha_no tmp_pilha_no;
				tmp_pilha_no.Fita_index = count;
				fread(&tmp_pilha_no.value, 1, ITEM_SIZE, files[count].file);
				total_bytes_written += files[count].actual_run.size;
				files[count].actual_run.size -= sizeof(int);
				files[count].actual_size -= sizeof(int);
				enqueue(tmp_pilha_no, &priority_queue);
			}
			total_bytes_written = 0;
			/* Se o arquivo final tem combinações e estamos na primeira interação, é limpado. */
			if (count_num_of_combination_per_interpolation == 0 && count_num_of_interpolations > 0)
			{
				ftruncate(fileno(files[actual_output_position].file), 0);
				fseek(files[actual_output_position].file, SEEK_SET, 0);
			}
			while (priority_queue.size > 0)
			{
				pilha_no pilha_no = dequeue(&priority_queue);
				fwrite(&pilha_no, sizeof(unsigned long), 1, files[actual_output_position].file);
				files[actual_output_position].actual_size += sizeof(int);
				total_bytes_written += sizeof(int);
				if (files[pilha_no.Fita_index].actual_run.size == 0)
				{
					continue;
				}
				fread(&pilha_no.value, 1, ITEM_SIZE, files[pilha_no.Fita_index].file);
				files[pilha_no.Fita_index].actual_run.size -= sizeof(int);
				files[pilha_no.Fita_index].actual_size = files[pilha_no.Fita_index].actual_size - sizeof(int);
				enqueue(pilha_no, &priority_queue);
			}
			/*Gera a execução para o output file.*/
			Run run;
			run.size = total_bytes_written;
			if (files[actual_output_position].actual_run.size == 0)
			{
				files[actual_output_position].actual_run = run;
			}
			actual_output_position++;
		}
	}
	return (actual_output_position - 1);
}
