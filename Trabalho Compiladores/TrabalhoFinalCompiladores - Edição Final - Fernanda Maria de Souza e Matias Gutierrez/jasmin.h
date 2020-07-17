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

// Definição de instruções como tipos inteiros para facilitar a manipulação.
#define ILOAD           5
#define ISTORE          6
#define GETPRINT        7
#define INVOKEPRINT_INT 8
#define INVOKEPRINT_STR 9
#define IF_ICMPGT       10
#define GOTO            11
#define NEWLABEL        12
#define LDC             13
#define DUP             14
#define NEWSCANNER      15
#define GETINPUTSTREAM  16
#define INVOKEINPUTSTR  17
#define NEXTINT         18
#define LDCSTRING       19
#define ASTORE          20
#define ALOAD           21
#define NEXTLINE        22
#define DELIMITADORFUNC 23
#define INVOKESTATIC    24
#define IRETURN         25
#define ARETURN         26
#define RETURN          27
#define IINC            28
#define CMP_GTHAN       29
#define IDIV            30
#define IMUL            31
#define IADD            32
#define ISUB            33
#define IF_ICMPEQ       34
#define IF_ICMPNE       35
#define IF_ICMPLT       36
#define IF_ICMPLE       37
#define IF_ICMPGE       38

// Definição de tipos auxiliares valendo valores inteiros para facilitar a manipulação.
#define _INT     1
#define _STRING  2
#define _VOID    3
#define _FLOAT   4

// Definição das struct auxiliares.
struct Atributo {
    int  tipo, label;
    char      id[10], literal[100];
    int       num;
    Lista     listaIDs, listaParametros;
};

struct Simbolo {
    char        id[10];
    int    tipo, pos;
};

struct Instrucao {
    int label;
    int inst, p1;
    char literal[100];
};

struct Parametro {
    char id[10];
    int tipo, pos;
};

struct Funcao {
    char id[10];
    int tipoRetorno, pos;
    Lista listaParametros;
};

// Funções de inicialização.
void inicializa();
void TabelaDeSimbolos(Lista *l, int tipo);
void Parametro(Lista *l, int tipo, char id[10]);
void Parametro2(Lista *l, int tipo);
void ID(Lista *l, char id[10]);
void ParametrosLista(Lista *l);
void Instrucao (int label, int inst, int p1,char str[100]);

//Funções auxiliares.
int compara_simbolos(void *a, void *b);
int buscaTipo(char id[10]);
int buscaPos(char id[10]);
void att();
void contadorpos();
void contfunc();
void IDinicialization(Lista *l);

//Funcões de atribuição geradoras para converter à linguagem Jasmin.
void CMD_operacao(int param);
void gerarInstrucoes();
void CMD_atribuicao(char var[10], int tipo1, int tipo2);
void CMD_comparacao(int pam);
void CMD_GOTO();
void CMD_read(int pos);
void CMD_getprint();
void CMD_chamadafunc(char id[10]);
void CMD_retorno(int tipo);
void CMD_inteiro(int num);
void CMD_ldc(char str[100]);
void CMD_iload_aload(char id[10]);
void CMD_invokestatic(int TIPO);
int CMD_novolabel();
