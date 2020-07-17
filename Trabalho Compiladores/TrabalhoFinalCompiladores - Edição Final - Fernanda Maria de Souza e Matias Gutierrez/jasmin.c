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

#include "jasmin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

Lista tabelaSimbolos, listaInstrucoes, listaFuncoes; // Conforme baseado na ideia de outros autores, estudamos e criamos três listas: uma para armazenamento de símbolos, outra para instruções e outra para funções.
int contPos = 0, contLabel = 0, contFuncao = 0; // auxiliares para definição de posições e variáveis para a linguagem Jasmin.

// Função responsável por inicializar as listas conforme explicado anteriormente.
void inicializa() {
    inicializa_lista(&tabelaSimbolos, sizeof(struct Simbolo));
    inicializa_lista(&listaInstrucoes, sizeof(struct Instrucao));
    inicializa_lista(&listaFuncoes, sizeof(struct Funcao));
}

// Função responsável por inserir na tabela de símbolos e verificar caso algum ID já esteja presente, retornando um erro caso já conste na tabela evitando sobreposição de dados e futuros erros.
void TabelaDeSimbolos(Lista *l, int tipo) {
    char info[10];
    while(!listaVazia(l)) {
        removeDoInicio(l, info);
        struct Simbolo s;
        strcpy(s.id, info);
        s.tipo = tipo;
        if (elementoExiste(&tabelaSimbolos, &s, compara_simbolos)) {
            printf("ID ja existe na tabela de simbolos: %s\n", info);
            exit(-1);
        }
        s.pos = contPos++;
        insereNoFim(&tabelaSimbolos, &s);
    }
}

// Lista auxiliar para guarda IDs para posterior comparações.
void IDinicialization(Lista *l) {
    inicializa_lista(l, sizeof(char) * 10);
}

// Lista auxiliar para guardar os parâmetros para posterior comparações.
void ParametrosLista(Lista *l) {
    inicializa_lista(l, sizeof(struct Parametro));
}

// Caso algum ID seja identificado o mesmo é inserido na lista de ids.
void ID(Lista *l, char id[10]) {
    insereNoFim(l, id);
}

// Função auxiliar responsável por comparar símbolos. É utilizada para identificar em outra função casos de existência.
int compara_simbolos(void *a, void *b) {
    struct Simbolo *s1 = (struct Simbolo*) a;
    struct Simbolo *s2 = (struct Simbolo*) b;
    return strcmp(s1->id, s2->id);
}

// Função que armazena e estrutura a lista de parâmetros e a Struct Função.
void Funcao(Lista *lParam, int tipoRetorno, char id[10]) {
    struct Funcao f;
    strcpy(f.id, id); // Passagem de parâmetros.
    f.tipoRetorno = tipoRetorno; // Passagem de parâmetros.
    f.pos = contFuncao; // Passagem de parâmetros.
    inicializa_lista(&(f.listaParametros), sizeof(struct Parametro));
    while(!listaVazia(lParam)) {
        struct Parametro p;
        removeDoFim(lParam, &p);
        insereNoInicio(&(f.listaParametros), &p); //  É feita a passagem de dados dos parâmetros para a Struct função.
    }
    insereNoFim(&listaFuncoes, &f);
    contFuncao++;
}

// Funcao que insere na tabela de símbolos e na lista de parâmetros.
void Parametro(Lista *l, int tipo, char id[10]) {
    struct Parametro p;
    p.tipo = tipo; // Passagem de parâmetros.
    strcpy(p.id, id); // Passagem de parâmetros.
    insereNoFim(l, &p); // Inserção na lista de parâmetros.
    struct Simbolo s;
    strcpy(s.id, id); // Passagem de parâmetros.
    s.tipo = tipo; // Passagem de parâmetros.
    s.pos = contPos; // Passagem de parâmetros.
    insereNoFim(&tabelaSimbolos, &s); // Inserção na tabela de Símbolos.
    contPos++;
}

// Função que apenas insere na lista de parâmetros caso a tabela de símbolos já contenha o símbolo.
void Parametro2(Lista *l, int tipo) {
    struct Parametro p;
    p.tipo = tipo; // Passagem de parâmetros.
    insereNoFim(l, &p);
}

// Contador de função para delimitar o escopo do programa.
// Chamado na função gerarInstrucoes para marcar o fim das funções.
void contfunc() {
    Instrucao(0, DELIMITADORFUNC, 0, "");
}

// Comando instrução que recebe todas as labels, instuções, parâmetros e strings e insere no fim da Lista de Instruções para posterior checagem e escrita no arquivo .jout
void Instrucao(int label, int inst, int p1, char str[100]) {
    struct Instrucao i;
    i.label = label; // Passagem de parâmetros.
    i.inst = inst; // Passagem de parâmetros.
    i.p1 = p1; // Passagem de parâmetros.
    if (str[0] != '\0') { // Passagem de parâmetros - Se string for válida.
        strcpy(i.literal, str); // Passagem de parâmetros.
    }
    insereNoFim(&listaInstrucoes, &i); // Inserção no fim da Lista de Instruções.
}

// Função que gera a o comando de atribuição istore ou astore.
void CMD_atribuicao(char var[10], int tipo1, int tipo2) {
    if (tipo1 == tipo2) { // Caso os dois tipos sejam iguais como na linguagem C.
        if (tipo1 == _INT) // Se for inteiro, usamos istore.
            Instrucao(0, ISTORE, buscaPos(var), ""); // Importante buscar a posição da variável, caso contrário sempre começará do 0.
        else // Se for outra coisa, usamos astore.
            Instrucao(0, ASTORE, buscaPos(var), ""); // Importante buscar a posição da variável, caso contrário sempre começará do 0.
    }
}

// Instrução para comparação que de acordo com o operador comparativo gera uma instrução para ser interpretada pela função gerarInstrucoes.
void CMD_comparacao(int pam) {
    switch(pam) {
    case 1: // >
    Instrucao(0, IF_ICMPGT, 0, ""); break;
    case 2: // <
    Instrucao(0, IF_ICMPLT, 0, ""); break;
    case 3: // >=
    Instrucao(0, IF_ICMPGE, 0, ""); break;
    case 4: // <=
    Instrucao(0, IF_ICMPLE, 0, ""); break;
    case 5: // ==
    Instrucao(0, IF_ICMPEQ, 0, ""); break;
    case 6: // !=
    Instrucao(0, IF_ICMPNE, 0, ""); break;
    default: // Diferente dos outros operadores:
      printf ("Comparacao nao existente!\n");
      exit(-1);
  }
}

// Função para enviar o GOTO para a função gerarInstrucoes
void CMD_GOTO() {
    Instrucao(0, GOTO, 0, "");
}

// Instrução para operações aritméticas que de acordo com o operador aritmético gera uma instrução para ser interpretada pela função gerarInstrucoes
void CMD_operacao(int param) {
    switch(param) {
        case 1: // (+)
            Instrucao(0, IADD, 0, ""); break;
        case 2: // (-)
            Instrucao(0, ISUB, 0, ""); break;
        case 3: // (/)
            Instrucao(0, IDIV, 0, ""); break;
        case 4: // (*)
            Instrucao(0, IMUL, 0, ""); break;
        default: // Diferente dos outros operadores:
            printf ("Instrucao desconhecida!\n");
            exit(-1);
    }
}

// Instrução para leitura na linguagem Jasmin. Todas podem ser chamadas independente de tipos ou requisitos. Conforme o professor pediu para mapear o máximo possível, tentamos seguir o conselho.
void CMD_read(int pos) {
    Instrucao(0, NEWSCANNER, 0, "");
    Instrucao(0, DUP, 0, "");
    Instrucao(0, GETINPUTSTREAM, 0, "");
    Instrucao(0, INVOKEINPUTSTR, 0, "");
    Instrucao(0, NEXTINT, 0, "");
    Instrucao(0, ISTORE, pos, ""); // istore necessita da posição.
}

// Instrução para chamada de função: passados o id presente na Struct Funcao de acordo com a posição printamos o INVOKESTATIC.
void CMD_chamadafunc(char id[10]) {
    struct Funcao f;
    strcpy(f.id, id);
    Instrucao(0, INVOKESTATIC, f.pos, f.id);
}

// Instrução para retornos. De acordo com o tipo podem ser chamados IRETURN, ARETURN ou RETURN.
void CMD_retorno(int tipo) {
    if (tipo == _INT) // Caso o tipo do retorno seja inteiro.
        Instrucao(0, IRETURN, 0, "");
    else if (tipo == _STRING) // Caso o tipo do retorno seja uma string.
        Instrucao(0, ARETURN, 0, "");
    else // Caso o tipo do retorno seja qualquer outro.
        Instrucao(0, RETURN, 0, "");
}

// Instrução para printa inteiros (ldc).
void CMD_inteiro(int num) {
    Instrucao(0, LDC, num, "");
}

// Instrução para printar strings (ldcstring).
void CMD_ldc(char str[100]) {
    Instrucao(0, LDCSTRING, 0, str);
}

// Contador de posições auxiliar para localização de iloads e istore não só no programa como em funções.
void contadorpos() {
    contPos++;
}

// Função responsável por atualizar a lista de funções de acordo com o número de funções presentes no código.
void att() {
    struct Funcao f;
    leNaPosicao(&listaFuncoes, &f, contFuncao-1);
    modificaNaPosicao(&listaFuncoes, &f, contFuncao-1);
    contPos = 0;
}

// Instrução para criação de um novo Label de acordo com a quantidade já somada, evitando sobreposição.
int CMD_novolabel() {
    contLabel++;
    Instrucao(contLabel, NEWLABEL, 0, "");
    return contLabel;
}

// Função para de acordo com o tipo do id retornar a instrução iload (inteiro) ou aload (string) para a função gerarInstrucoes.
void CMD_iload_aload(char id[10]) {
    int pos = buscaPos(id);
    if( buscaTipo(id) == _INT) // buscaTipo é uma função auxiliar criada também para determinar o erro de variáveis não declaradas.
    Instrucao(0, ILOAD, pos, "");
    if( buscaTipo(id) == _STRING)
    Instrucao(0, ALOAD, pos, "");
}

// Função para gerar o comando invokestatic de acordo com o Tipo: inteiro ou String.
void CMD_invokestatic(int TIPO) {
      if (TIPO == _INT)
    Instrucao(0, INVOKEPRINT_INT, 0, "");
else if (TIPO == _STRING)
    Instrucao(0, INVOKEPRINT_STR, 0, "");
}

// Função auxiliar para buscar o tipo de símbolos comparados com a tabela de símbolo.
int buscaTipo(char id[10]) {
    struct Simbolo s;
    strcpy(s.id, id); // Passagem de parâmetros.
    if (buscaElemento(&tabelaSimbolos, &s, compara_simbolos) == ERRO) { // Realizando uma condição de erro para comparar a tabela de símbolos com a Struct Símbolos, vendo se algum elemento não foi passado, ou seja, não foi declarado.
        printf("Variavel nao declarada: %s!\n", id);
        exit(-1);
    }
    return s.tipo; // retorna o tipo do símbolo.
}

// Função para printar instrução getprint.
void CMD_getprint() {
    Instrucao(0, GETPRINT, 0, "");
}

// Função auxiliar para buscar a posição de um símbolo (id) na tabela de símbolos. Pode ocorrer de não acharmos o símbolo na tabela, resultando em uma variável não declarada.
int buscaPos(char id[10]) {
    struct Simbolo s;
    strcpy(s.id, id); // Passagem de parâmetros.
    if (buscaElemento(&tabelaSimbolos, &s, compara_simbolos) == ERRO) {
        printf("Variavel nao declarada: %s!\n", id);
        exit(-1);
    }
    return s.pos;
}

// Função geral que está diretamente relacionada com a função Instrução. Todos as instruções geradas com base nas outras funções são chamadas por meio de #defines contidos no arquivo jasmin.h
// para escrever no arquivo ,jout final, contendo a linguagem Jasmin.
void gerarInstrucoes() {
    struct Instrucao i;
    FILE *fp = fopen("comp.jout", "w"); // arquivo de saída com a tradução para o Jasmin.
    int j = 0, sair = 0, cont = 0;
    fprintf(fp, ".class public %s\n"          // Cabeçalho Jasmin.
                ".super java/lang/Object\n\n" // Cabeçalho Jasmin.
                ".method public <init>()V\n" // Cabeçalho Jasmin.
                "\taload_0\n\n"              // Cabeçalho Jasmin.
                "\tinvokenonvirtual java/lang/Object/<init>()V\n" // Cabeçalho Jasmin.
                "\treturn\n" // Cabeçalho Jasmin.
                ".end method\n\n", "comp"); // Cabeçalho Jasmin.
    while(!j) {
        struct Funcao f;
        if (cont == contFuncao) {
            fprintf(fp, ".method public static main([Ljava/lang/String;)V\n");
            j = 1;
        }
        else {
            leNaPosicao(&listaFuncoes, &f, cont);
            cont++;
            fprintf(fp, ".method public static %s(II)I\n", f.id);
            struct Parametro p;
        }
        if (j) {
            fprintf(fp, "\t.limit stack 3\n"); // Não conseguimos implementar isso :/
            fprintf(fp, "\t.limit locals 4\n"); // Não conseguimos implementar isso :/
        }
        else {
            fprintf(fp, "\t.limit stack 2\n");   // Não conseguimos implementar isso :/
            fprintf(fp, "\t.limit locals 2\n");  // Não conseguimos implementar isso :/
        }
        while (!listaVazia(&listaInstrucoes)) { // Como tudo foi armazenado em uma lista, agora tudo é removido do início da lista e printando no arquivo .jout até a lista estar vazia.
            removeDoInicio(&listaInstrucoes, &i); // removendo do início.
            switch(i.inst) { // de acordo com a instrução retornada pelas outras funções é determinado o case.
              case IDIV:
                fprintf(fp, "\tidiv\n"); break;
              case IMUL:
                fprintf(fp, "\timul\n"); break;
              case IADD:
                fprintf(fp, "\tiadd\n"); break;
              case ISUB:
                fprintf(fp, "\tisub\n"); break;
                case ILOAD:
                    fprintf(fp, "\tiload %d\n", i.p1); break;
                case ISTORE:
                    fprintf(fp, "\tistore %d\n", i.p1); break;
                case GETPRINT:
                    fprintf(fp, "\tgetstatic java/lang/System/out Ljava/io/PrintStream;\n"); break;
                case INVOKEPRINT_INT:
                    fprintf(fp, "\tinvokevirtual java/io/PrintStream/println(I)V\n"); break;
                case INVOKEPRINT_STR:
                    fprintf(fp, "\tinvokevirtual java/io/PrintStream/println(Ljava/lang/String;)V\n"); break;
                case IF_ICMPGT:
                    fprintf(fp, "\tif_icmpgt l%u\n", i.label); break;
                case IF_ICMPEQ:
                    fprintf(fp, "\tif_icmpeq l%u\n", i.label); break;
                case IF_ICMPNE:
                    fprintf(fp, "\tif_icmpne l%u\n", i.label); break;
                case IF_ICMPLT:
                    fprintf(fp, "\tif_icmplt l%u\n", i.label); break;
                case IF_ICMPLE:
                    fprintf(fp, "\tif_icmple l%u\n", i.label); break;
                case IF_ICMPGE:
                    fprintf(fp, "\tif_icmpge l%u\n", i.label); break;
                case GOTO:
                    fprintf(fp, "\tgoto l%u\n", i.label); break;
                case NEWLABEL:
                    fprintf(fp, "l%u:\n", i.label); break;
                case LDC:
                    fprintf(fp, "\tldc %d\n", i.p1); break;
                case DUP:
                    fprintf(fp, "\tdup\n"); break;
                case NEWSCANNER:
                    fprintf(fp, "\tnew java/util/Scanner\n"); break;
                case GETINPUTSTREAM:
                    fprintf(fp, "\tgetstatic java/lang/System/in Ljava/io/InputStream;\n"); break;
                case INVOKEINPUTSTR:
                    fprintf(fp, "\tinvokespecial java/util/Scanner/<init>(Ljava/io/InputStream;)V\n"); break;
                case NEXTINT:
                    fprintf(fp, "\tinvokevirtual java/util/Scanner/nextInt()I\n"); break;
                case LDCSTRING:
                    fprintf(fp, "\tldc %s\n", i.literal); break;
                case ASTORE:
                    fprintf(fp, "\tastore %d\n", i.p1); break;
                case ALOAD:
                    fprintf(fp, "\taload %d\n", i.p1); break;
                case NEXTLINE:
                    fprintf(fp, "\tinvokevirtual java/util/Scanner/nextLine()Ljava/lang/String;\n"); break;
                case DELIMITADORFUNC:
                    sair = 1; break; // Caso tenha acabado as funções.
                case INVOKESTATIC:
                    fprintf(fp, "\tinvokestatic %s/%s(II)I\n", "comp", i.literal); break;
                case IRETURN:
                    fprintf(fp, "\tireturn\n"); break;
                case ARETURN:
                    fprintf(fp, "\tareturn\n"); break;
                case RETURN:
                    fprintf(fp, "\treturn\n"); break;
                default:
                    printf("Erro na instrução %d!\n", i.inst); break;
            }
            if (sair) {
                sair = 0;
                break;
            }
        }
        fprintf(fp, "\treturn\n");
        fprintf(fp, ".end method\n\n"); // Fim
    }
    fclose(fp);
}
