/* A Bison parser, made by GNU Bison 3.3.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_CALC_TAB_H_INCLUDED
# define YY_YY_CALC_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    T_FLOAT = 258,
    T_INT = 259,
    T_STRING = 260,
    T_VOID = 261,
    T_RETURN = 262,
    T_IF = 263,
    T_ELSE = 264,
    T_WHILE = 265,
    T_READ = 266,
    T_PRINT = 267,
    T_MAIS = 268,
    T_MENOS = 269,
    T_VEZES = 270,
    T_IGUAL = 271,
    T_DIVIDIR = 272,
    T_ABREPARENTESES = 273,
    T_FECHAPARENTESES = 274,
    T_ABRECHAVES = 275,
    T_FECHACHAVES = 276,
    T_PONTOEVIRGULA = 277,
    T_VIRGULA = 278,
    T_MENOR = 279,
    T_MAIOR = 280,
    T_MENORIGUAL = 281,
    T_MAIORIGUAL = 282,
    T_IGUAL_IGUAL = 283,
    T_DIFERENTE = 284,
    T_E = 285,
    T_OU = 286,
    T_NEGACAO = 287,
    T_NUM = 288,
    T_ID = 289,
    T_LITERAL = 290
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_CALC_TAB_H_INCLUDED  */
