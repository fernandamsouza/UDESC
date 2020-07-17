// Código feito por Fernanda Maria de Souza e Matias Giuliano Gutierrez Benitez em C.
// Para entendimento das etapas e norteamente do processo, o código foi baseado principalmente nos projetos feitos por:
// - https://github.com/marcioaleson/Compilador-Java-Simplificado
// - https://github.com/sethrylan/csc512
// - https://github.com/alepmaros/Arxs_Compiler
// - https://github.com/paulomenezes/compilador
// - https://github.com/romaad/compilersPhase3
// A ideia de manipulação de Listas e Structs foi baseada no projeto do Github enviado pelo professor.
// Observação: Código incompleto desenvolvido para a gramática, porém reconhece grande parte do exemplo enviado pelo professor.
// Ainda não gera executável para o Jasmin pois temos erros nas comparações e em labels. Tentamos fazer passo por passo conforme conversado com o professor, mas esse foi nosso limite. Obrigada pela disponibilidade de entregar sexta, conseguimos desenvolver muito mais do que tinhamos quarta.

#include <stdlib.h>

#define ERRO -1

typedef struct elemento {
    void *info;
    struct elemento *proximo;
} Elemento;

typedef struct {
    size_t tamInfo;
    Elemento *cabeca;
} Lista;

void inicializa_lista(Lista *l, size_t t);
void mostra_lista(Lista l, void (*mostra_info)(void *));
int insereNoInicio(Lista *l, void *info);
int insereNoFim(Lista *l, void *info);
int buscaElemento(Lista *l, void *info, int (*compara_info)(void *, void *));
int removeDoInicio(Lista *l, void *info);
int removeNaPosicao(Lista *l, void *info, int pos);
int removeDoFim(Lista *l, void *info);
int modificaNaPosicao(Lista *l, void *info, int pos);
int leNaPosicao(Lista *l, void *info, int pos);
int listaVazia(Lista *l);
int elementoExiste(Lista *l, void *info, int (*compara_info)(void *, void *));
Elemento *aloca_elemento(size_t t, void *info);
