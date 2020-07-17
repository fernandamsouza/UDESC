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

%{
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
extern char * yytext;
extern int yylex();
extern int numLinha; // chamada externa do número de Linhas contido no Flex.
extern int numCol; // chamada externa do número de Colunas contido no Flex.
extern FILE* yyin;
extern int erroOrigem;
void yyerror( char const *s);
#include "jasmin.h" // chamada da struct atributo e headers de função para tradução.
#define YYSTYPE struct Atributo // definição de uma struct atributo definindo que o valor semântico das expressões será armazenado lá.
%}

/* Declaração dos tokens */
%token T_FLOAT T_INT T_STRING // Tipos numéricos.
%token T_VOID T_RETURN T_IF T_ELSE T_WHILE T_READ T_PRINT // Funções.
%token T_MAIS T_MENOS T_VEZES T_IGUAL T_DIVIDIR // Operadores aritméticos.
%token T_ABREPARENTESES T_FECHAPARENTESES T_ABRECHAVES T_FECHACHAVES T_PONTOEVIRGULA T_VIRGULA // Operadores separadores.
%token T_MENOR T_MAIOR T_MENORIGUAL T_MAIORIGUAL T_IGUAL_IGUAL T_DIFERENTE // Operadores comparativos.
%token T_E T_OU T_NEGACAO // Operadores gerais.
%token T_NUM T_ID T_LITERAL // Classes léxicas.

%start Start // definição do ponto de partida para execução da gramática.

%%

Start: Programa { gerarInstrucoes(); } // Início do programa e atribuição para função gerarInstrucoes, a qual irá escrever todas as instruções e sintaxe Jasmin.
;                                     // Todas as demais funções relativas a instruções do Jasmin serão encaminhadas para a mesma escrever.


Programa: ListaFuncoes CONTADOR BlocoPrincipal
| CONTADOR BlocoPrincipal
;

CONTADOR: { contadorpos();}; // Contador para localização de iloads e istore não só no programa como em funções.

ExpressaoLogica: ExpressaoLogica T_OU ExpressaoLogica2 // Mapeamento não terminado.
| ExpressaoLogica T_E ExpressaoLogica2 // Mapeamento não terminado.
| ExpressaoLogica2 // Mapeamento não terminado.
;

AUX2
      : { $$.label = CMD_novolabel(); } // Auxiliar para estabelecimento de novos labels.
      ;

ExpressaoLogica2: T_NEGACAO ExpressaoLogica2 // Mapeamento não terminado.
| T_ABREPARENTESES ExpressaoLogica T_FECHAPARENTESES
| ExpressaoComparacoes
| ExpressaoAritmetica
;

ExpressaoAritmetica: ExpressaoAritmetica T_MAIS Termo { CMD_operacao(1); } // Leva para a função CMD_operacao que de acordo com o parametro passa o sinal chamado(+).
| ExpressaoAritmetica T_MENOS Termo { CMD_operacao(2); } // Leva para a função CMD_operacao que de acordo com o parametro passa o sinal chamado(-).
| Termo
;

ExpressaoComparacoes
      : ExpressaoAritmetica T_MAIOR ExpressaoAritmetica {CMD_comparacao(1); CMD_GOTO(); } //Expressão de comparação que passa o sinal mapeado (>).
      | ExpressaoAritmetica T_MENOR ExpressaoAritmetica {CMD_comparacao(2); CMD_GOTO(); } //Expressão de comparação que passa o sinal mapeado (<).
      | ExpressaoAritmetica T_MAIORIGUAL ExpressaoAritmetica {CMD_comparacao(3); CMD_GOTO(); } //Expressão de comparação que passa o sinal mapeado (>=).
      | ExpressaoAritmetica T_MENORIGUAL ExpressaoAritmetica {CMD_comparacao(4); CMD_GOTO(); } //Expressão de comparação que passa o sinal mapeado (<=).
      | ExpressaoAritmetica T_IGUAL_IGUAL ExpressaoAritmetica {CMD_comparacao(5); CMD_GOTO(); } //Expressão de comparação que passa o sinal mapeado (==).
      | ExpressaoAritmetica T_DIFERENTE ExpressaoAritmetica {CMD_comparacao(6); CMD_GOTO(); } //Expressão de comparação que passa o sinal mapeado (!=).
      ;

Termo: Termo T_VEZES Fator {CMD_operacao(3);}
| Termo T_DIVIDIR Fator{CMD_operacao(3);}
| Fator
;

Fator:
T_NUM { CMD_inteiro($1.num); $$.tipo = _INT; } // Instrução LDC
| T_ABREPARENTESES ExpressaoAritmetica T_FECHAPARENTESES
| ChamadaFuncao { $$.tipo = $1.tipo; }
| T_ID    {CMD_iload_aload($1.id);} // Instrução jasmin para carregar um id ou string. Determinação do comando diretamente na função.
;

ListaFuncoes: ListaFuncoes Funcao { contfunc();} // Delimitador de cada função, controlando seu funcionamento
| Funcao  {contfunc();}
;

Funcao: TipoRetorno T_ID T_ABREPARENTESES DeclParametros T_FECHAPARENTESES BlocoPrincipal { Funcao(&($4.listaParametros), $1.tipo, $2.id); att();} // É passado uma lista de parâmetros para manipulação e estruturação da Struct Função; A função att lê e modifica na posição de acordo com as funções mapeadas.
| TipoRetorno T_ID T_ABREPARENTESES T_FECHAPARENTESES BlocoPrincipal
;

TipoRetorno: Tipo { $$.tipo = $1.tipo;}
| T_VOID { $$.tipo = _VOID;}
;

DeclParametros: DeclParametros T_VIRGULA Tipo T_ID  {Parametro(&($$.listaParametros), $3.tipo, $4.id);} // Função Parametro passa a lista de parâmetros para a Tabela de Símbolos e para a Função Símbolos.
| Tipo T_ID { ParametrosLista(&($$.listaParametros)); Parametro(&($$.listaParametros), $1.tipo, $2.id);} // Função que inicializa a lista de parâmetros e realiza a mesma coisa que a linha de cima.
;

BlocoPrincipal: T_ABRECHAVES Declaracoes ListaCmd T_FECHACHAVES
| T_ABRECHAVES ListaCmd T_FECHACHAVES
;

Declaracoes: Declaracoes Declaracao
| Declaracao
;

Declaracao: Tipo ListaId T_PONTOEVIRGULA {TabelaDeSimbolos( (&$2.listaIDs), $1.tipo );} // Inserção da lista de IDs na Tabela de Símbolos.
;

Tipo: T_INT {$$.tipo = _INT;}
| T_STRING {$$.tipo = _STRING; }
| T_FLOAT {$$.tipo = _FLOAT; }
;

ListaId: ListaId T_VIRGULA T_ID {ID(&($$.listaIDs), $3.id);} // Inserção dos IDs na Lista de IDS.
| T_ID { IDinicialization(&($$.listaIDs)); ID( &($$.listaIDs), $1.id); } // Inicialização da lista de IDS e inserção
;

Bloco: T_ABRECHAVES ListaCmd T_FECHACHAVES
;

ListaCmd: ListaCmd Comando
| Comando
;

Comando: CmdSe
| CmdEnquanto
| CmdAtrib
| CmdEscrita
| CmdLeitura
| ChamadaProc
| Retorno
;

Retorno: T_RETURN ExpressaoAritmetica T_PONTOEVIRGULA { CMD_retorno($2.tipo); } // Passagem do tipo da expressão aritmética para a função informar o retorno certo.
;

CmdSe: T_IF T_ABREPARENTESES ExpressaoLogica T_FECHAPARENTESES Bloco {CMD_novolabel(); CMD_novolabel();} // Criação de novos labels para o comando se.
| T_IF T_ABREPARENTESES ExpressaoLogica T_FECHAPARENTESES Bloco T_ELSE Bloco // Não mapeado, aqui nos perdemos legal.
;


CmdEnquanto: T_WHILE AUX2 T_ABREPARENTESES ExpressaoLogica T_FECHAPARENTESES Bloco // Não mapeado pois demoramos demais em outras coisas :/
;

CmdAtrib: T_ID T_IGUAL ExpressaoAritmetica T_PONTOEVIRGULA { CMD_atribuicao( $1.id, buscaTipo($1.id), $3.tipo); } // Função para gerar a atribuição de acordo com o tipo comparado em ambos os lados.
| T_ID T_IGUAL T_LITERAL T_PONTOEVIRGULA
;

CmdEscrita: T_PRINT T_ABREPARENTESES AUX ExpressaoAritmetica T_FECHAPARENTESES T_PONTOEVIRGULA { CMD_invokestatic(_INT); } // Função chamando a instrução invokestatic para o tipo inteiro.
| T_PRINT T_ABREPARENTESES AUX T_LITERAL T_FECHAPARENTESES T_PONTOEVIRGULA { CMD_ldc($4.literal); CMD_invokestatic(_STRING); } // ldc para printar um inteiro.
;

CmdLeitura: T_READ T_ABREPARENTESES T_ID T_FECHAPARENTESES T_PONTOEVIRGULA  {CMD_read(buscaPos($3.id));} // Função para leitura de determinado id.
;

ChamadaProc: T_ID T_ABREPARENTESES ListaParametros T_FECHAPARENTESES T_PONTOEVIRGULA { CMD_chamadafunc($1.id); } // Função para chamada de função.
      | T_ID T_ABREPARENTESES T_FECHAPARENTESES T_PONTOEVIRGULA { CMD_chamadafunc($1.id); } // Função para chamada de função.
      ;

AUX
      : { CMD_getprint(); }
      ;

ChamadaFuncao: T_ID T_ABREPARENTESES ListaParametros T_FECHAPARENTESES { $$.tipo = _INT; CMD_chamadafunc($1.id); } // De acordo com o tipo inteiro é realizado a chamada da função para determinada posição e id.
| T_ID T_ABREPARENTESES T_FECHAPARENTESES
;

ListaParametros: ListaParametros T_VIRGULA ExpressaoAritmetica { Parametro2(&$$.listaParametros, $3.tipo); } // Função para inserção na lista de parâmetros sem incluir na tabela de símbolos.
| ListaParametros T_VIRGULA T_STRING
| ExpressaoAritmetica { ParametrosLista(&$$.listaParametros); Parametro2(&$$.listaParametros, $1.tipo);  } // Função para inserção na lista de parâmetros sem incluir na tabela de símbolos.
;

%%
#include "lex.yy.c"

void yyerror( char const *s) {
    if (erroOrigem == 0) /*Erro lexico*/ {
        printf("%s na linha %d coluna %d - token: %s\n", s, numLinha, numCol-1, yytext);
    } else {
  printf("Erro sintatico proximo a %s ", yytext);
	printf(" - linha: %d coluna: %d\n", numLinha, numCol-1);
	erroOrigem=1;
    }

    exit(1);
}
