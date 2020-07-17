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

#include "eda.h"
#include <stdlib.h>
#include <string.h>

void inicializa_lista(Lista *l, size_t t)
{
    l->tamInfo = t;
    l->cabeca = NULL;
}

int listaVazia(Lista *l)
{
    if (l->cabeca == NULL)
        return 1;
    else
        return 0;
}

int insereNoInicio(Lista *l, void *info)
{
    Elemento *p = aloca_elemento(l->tamInfo, info);
    p->proximo = l->cabeca;
    l->cabeca = p;
    return 1;
}

int removeDoInicio(Lista *l, void *info)
{
    if (l->cabeca == NULL)
    {
        return ERRO;
    }
    Elemento *p = l->cabeca;
    l->cabeca = p->proximo;
    memcpy(info, p->info, l->tamInfo);
    free(p->info);
    free(p);
    return 1;
}

int insereNoFim(Lista *l, void *info)
{
    if(l->cabeca == NULL)
    {
        return insereNoInicio(l, info);
    }

    Elemento *aux = l->cabeca;
    while(aux->proximo != NULL)
    {
        aux = aux->proximo;
    }

    Elemento *p = aloca_elemento(l->tamInfo, info);
    p->proximo = NULL;
    aux->proximo = p;
    return 1;
}

int removeDoFim(Lista *l, void *info)
{
    if (l->cabeca == NULL)
        return ERRO;

    if(l->cabeca->proximo == NULL)
        return removeDoInicio(l, info);

    Elemento *aux = l->cabeca;
    while(aux->proximo->proximo != NULL)
    {
        aux = aux->proximo;
    }
    memcpy(info, aux->proximo->info, l->tamInfo);
    free(aux->proximo->info);
    free(aux->proximo);
    aux->proximo = NULL;
    return 1;
}

int removeNaPosicao(Lista *l, void *info, int pos)
{
    if(pos < 0)
        return ERRO;
    if(pos == 0)
        return removeDoInicio(l, info);

    Elemento *aux = l->cabeca;
    int cont = 0;
    while(cont < pos-1 && aux->proximo != NULL)
    {
        aux = aux->proximo;
        cont++;
    }
    if (cont != pos-1 || aux->proximo == NULL)
        return ERRO;

    memcpy(info, aux->proximo->info, l->tamInfo);

    Elemento *aux2 = aux->proximo;
    aux->proximo = aux->proximo->proximo;

    free(aux2->info);
    free(aux2);
    return 1;
}

int modificaNaPosicao(Lista *l, void *info, int pos)
{
    if(pos < 0)
        return ERRO;

    Elemento *aux = l->cabeca;
    int cont = 0;
    while(cont != pos && aux->proximo != NULL)
    {
        aux = aux->proximo;
        cont++;
    }
    if(cont != pos)
        return ERRO;
    memcpy(aux->info, info, l->tamInfo);
    return 1;
}

int leNaPosicao(Lista *l, void *info, int pos)
{
    if(pos < 0)
        return ERRO;

    Elemento *aux = l->cabeca;
    int cont = 0;
    while(cont != pos && aux->proximo != NULL)
    {
        aux = aux->proximo;
        cont++;
    }
    if(cont != pos)
        return ERRO;

    memcpy(info, aux->info, l->tamInfo);
    return 1;
}

Elemento *aloca_elemento(size_t t, void *info)
{
    Elemento *p;
    p = (Elemento*) malloc(sizeof(Elemento));

    if(p == NULL)
        return NULL;

    p->info = malloc(t);
    if (p->info == NULL)
    {
        free(p);
        return NULL;
    }
    memcpy(p->info, info, t);
    return p;
}

int limpa_lista(Lista *l)
{
    Elemento *aux = l->cabeca;
    // Lista vazia
    if (aux == NULL)
        return 1;

    while (aux != NULL)
    {
        if (aux->proximo == NULL)
        {
            l->cabeca = NULL;
            free(aux->info);
            free(aux);
            return 1;
        }

        while (aux->proximo->proximo != NULL)
        {
            aux = aux->proximo;
        }

        free(aux->proximo->info);
        free(aux->proximo);
        aux->proximo = NULL;
        aux = l->cabeca;
    }

    return 1;
}

int elementoExiste(Lista *l, void *info, int (*compara_info)(void *, void *))
{
    Elemento *aux = l->cabeca;
    if (aux == NULL)
        return 0;

    while(aux != NULL)
    {
        if (compara_info(aux->info, info) == 0)
        {
            return 1;
        }
        aux = aux->proximo;
    }

    return 0;

}

void mostra_lista(Lista l, void (*mostra_info)(void *))
{
    Elemento *aux = l.cabeca;
    if (aux == NULL)
        return;

    int cont = 0;
    while(aux != NULL)
    {
        mostra_info(aux->info);
        aux = aux->proximo;
    }
}

int buscaElemento(Lista *l, void *info, int (*compara_info)(void *, void *))
{
    Elemento *aux = l->cabeca;
    if (aux == NULL)
        return ERRO;

    while (aux != NULL)
    {
        if (compara_info(info, aux->info) == 0)
        {
            memcpy(info, aux->info, l->tamInfo);
            return 1;
        }
        aux = aux->proximo;
    }

    return ERRO;
}
