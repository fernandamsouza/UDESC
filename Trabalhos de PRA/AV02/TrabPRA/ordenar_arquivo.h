#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define ITEM_SIZE 8
#define TRUE 1
#define FALSE 0

#define GB 1000 * 1000 * 1000
#define MB 1000 * 1000


typedef struct pilha_no {
    unsigned long value;
    float value2;
    int Fita_index;
} pilha_no;

typedef struct Priore {
    pilha_no *heap;
    int size;
} Priore;

typedef struct Run {
    size_t size;
} Run;

typedef struct Fita {
    int id;
    char *name;
    FILE *file;
    Run actual_run;
    unsigned long actual_size;
} Fita;


void init_queue(Priore *q, int n);
void enqueue(pilha_no node, Priore *q);
pilha_no dequeue(Priore *q);
void insert (pilha_no a_node, pilha_no *heap, int size);
void shift_down (pilha_no *heap, int size, int idx);
pilha_no remove_min (pilha_no *heap, int size);
void enqueue (pilha_no node, Priore *q);
pilha_no dequeue (Priore *q);
void init_queue (Priore *q, int n);
unsigned long compare_function (const void * a, const void * b);
Fita* generate_Fitas (const int K);
unsigned long get_file_length (FILE* file);
int get_number_of_runs (unsigned long file_length, const int mem);
Fita* generate_runs (FILE *file, const int mem, const int K);
int int_log (double base, double x);
int interpolate(Fita *files, unsigned long input_file_length, const unsigned long mem, const int K);
