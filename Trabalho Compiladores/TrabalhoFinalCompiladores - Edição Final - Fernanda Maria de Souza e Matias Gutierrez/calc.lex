%option noyywrap

%{
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

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "calc.tab.h"

int erroOrigem = 1, numLinha = 1, numCol = 1;
%}

digito  [0-9]
letra [A-Za-z]
num {digito}+
id ({letra}|\_)+({letra}|{digito}|\_)*
literal \"(\\.|[^"])*\"
%%
[ \t]	;// ignore todos os espaços em branco
[\n]  numCol = 0,numLinha++;
"float"										{printf ("float: %s\n", yytext);numCol++;return T_FLOAT;}
"int"											{printf ("int: %s\n", yytext);numCol++;return T_INT;}
"String"									{numCol++;return T_STRING;}
"void"										{printf ("void: %s\n", yytext);numCol++;return T_VOID;}
"return"									{printf ("return: %s\n", yytext);numCol++;return T_RETURN;}
"if"											{printf ("if: %s\n", yytext);numCol++;return T_IF;}
"else"										{printf ("else: %s\n", yytext);numCol++;return T_ELSE;}
"while"										{printf ("while: %s\n", yytext);numCol++;return T_WHILE;}
"read"										{printf ("read: %s\n", yytext);numCol++;return T_READ;}
"print"									{printf ("print: %s\n", yytext);numCol++;return T_PRINT;}
"+"											{printf ("+: %s\n", yytext);numCol++;return T_MAIS;}
"-"											{printf ("-: %s\n", yytext);numCol++;return T_MENOS;}
"*"											{printf ("*: %s\n", yytext);numCol++;return T_VEZES;}
"="											{printf ("=: %s\n", yytext);numCol++;return T_IGUAL;}
"/"											{printf ("/: %s\n", yytext);numCol++;return T_DIVIDIR;}
"("											{printf ("(: %s\n", yytext);numCol++;return T_ABREPARENTESES;}
")"											{printf ("): %s\n", yytext);numCol++;return T_FECHAPARENTESES;}
"{"											{printf ("{: %s\n", yytext);numCol++;return T_ABRECHAVES;}
"}"											{printf ("}: %s\n", yytext);numCol++;return T_FECHACHAVES;}
","											{printf (",: %s\n", yytext);numCol++;return T_VIRGULA;}
";"											{printf (";: %s\n", yytext);numCol++;return T_PONTOEVIRGULA;}
"<"											{printf ("<: %s\n", yytext);numCol++;return T_MENOR;}
">"											{printf ("maior: %s\n", yytext);numCol++;return T_MAIOR;}
"<="										{printf ("<=: %s\n", yytext);numCol++;return T_MENORIGUAL;}
">="										{printf (">=: %s\n", yytext);numCol++;return T_MAIORIGUAL;}
"=="										{printf ("==: %s\n", yytext);numCol++;return T_IGUAL_IGUAL;}
"!=" 										{printf ("!=: %s\n", yytext);numCol++;return T_DIFERENTE;}
"&&" 										{printf ("&&: %s\n", yytext);numCol++;return T_E;}
"||" 										{printf ("||: %s\n", yytext);numCol++;return T_OU;}
"!"	 										{printf ("!: %s\n", yytext);numCol++;return T_NEGACAO;}
{id}       {strcpy(yylval.id, yytext); printf ("id: %s\n", yytext);return T_ID;}
{literal}({literal}|{id})* {strcpy(yylval.literal, yytext); printf ("literal: %s\n", yytext);return T_LITERAL;}
{num} {yylval.num = atoi(yytext);printf ("num: %s\n", yytext); return T_NUM;}

"{"[^}\n]*"}"     /* Lembre-se... comentários não tem utilidade! */
[ \t\n]+          /* Lembre-se... espaços em branco não tem utilidade! */
<<EOF>> 		return(EOF);
.			{
				printf("Caractere invalido na linha %d: coluna: %d  -  %s\n", numLinha, numCol, yytext);
                                erroOrigem=0;
				exit(1);
			}



%%
