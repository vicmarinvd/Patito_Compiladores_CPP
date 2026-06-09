/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ID = 258,
     CTE_ENT = 259,
     CTE_FLT = 260,
     LETRERO = 261,
     PROGRAM = 262,
     VARS = 263,
     INICIO = 264,
     FIN = 265,
     SI = 266,
     SINO = 267,
     MIENTRAS = 268,
     HAZ = 269,
     ESCRIBE = 270,
     NULA = 271,
     ENTERO = 272,
     FLOTANTE = 273,
     OPEQ = 274,
     OPNEQ = 275,
     OPGT = 276,
     OPLT = 277,
     UMINUS = 278
   };
#endif
/* Tokens.  */
#define ID 258
#define CTE_ENT 259
#define CTE_FLT 260
#define LETRERO 261
#define PROGRAM 262
#define VARS 263
#define INICIO 264
#define FIN 265
#define SI 266
#define SINO 267
#define MIENTRAS 268
#define HAZ 269
#define ESCRIBE 270
#define NULA 271
#define ENTERO 272
#define FLOTANTE 273
#define OPEQ 274
#define OPNEQ 275
#define OPGT 276
#define OPLT 277
#define UMINUS 278




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 42 "patito.y"
{ char sval[64]; int tval; }
/* Line 1529 of yacc.c.  */
#line 97 "patito.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

