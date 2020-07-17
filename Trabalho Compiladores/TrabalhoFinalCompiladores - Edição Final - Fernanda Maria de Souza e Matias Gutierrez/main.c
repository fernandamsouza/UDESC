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

#include <stdio.h>

extern FILE *yyin;

extern void inicializa();

// Main apenas para abrir o arquivo e ler o mesmo.
int main(int argc, char **argv) {
    inicializa();
    FILE *arquivo = fopen("exemplo.j", "r");
    if (arquivo == NULL) {
        printf("Problema na abertura do arquivo\n");
        return -1;
    }
    yyin = arquivo;
    yyparse();
    fclose(arquivo);
    return 0;
}
