/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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




/* Copy the first part of user declarations.  */
#line 8 "patito.y"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include "cuadruplos.hpp"
#include "maquina_virtual.hpp"

/*
 * TIPO_NULA está definido en semantica.hpp (=3) pero Bison también genera
 * un token NULA desde patito.tab.h. El #undef/redefine evita la colisión.
 */
#undef NULA
#include "dvirtual.hpp"
#define TIPO_NULA 3

/* Variables del analizador léxico */
extern int  yylineno;
extern int  errores_lexicos;
extern FILE *yyin;

void yyerror(const char *s);
int  yylex(void);

/* Contadores de errores sintácticos y semánticos del parse actual */
static int errsintx  = 0;
static int errsemant = 0;


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 41 "patito.y"
{ char sval[64]; int tval; }
/* Line 193 of yacc.c.  */
#line 173 "patito.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 186 "patito.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   152

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  36
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  43
/* YYNRULES -- Number of rules.  */
#define YYNRULES  76
/* YYNRULES -- Number of states.  */
#define YYNSTATES  141

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   278

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      31,    32,    25,    23,    30,    24,     2,    26,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    29,    28,
       2,    35,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    33,     2,    34,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    27
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     4,     5,    16,    18,    19,    22,    23,
      24,    33,    34,    35,    40,    41,    43,    45,    48,    49,
      51,    53,    54,    66,    67,    73,    74,    77,    78,    80,
      81,    85,    88,    89,    94,    95,   102,   104,   106,   108,
     112,   116,   120,   124,   128,   132,   136,   140,   143,   146,
     150,   151,   157,   159,   161,   163,   165,   166,   170,   171,
     172,   177,   178,   179,   180,   190,   191,   200,   201,   205,
     206,   212,   213,   217,   218,   222,   225
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      37,     0,    -1,    -1,    -1,     7,     3,    28,    38,    40,
      48,     9,    39,    56,    10,    -1,    41,    -1,    -1,     8,
      42,    -1,    -1,    -1,     3,    43,    45,    29,    47,    28,
      44,    42,    -1,    -1,    -1,    30,     3,    46,    45,    -1,
      -1,    17,    -1,    18,    -1,    50,    48,    -1,    -1,    16,
      -1,    47,    -1,    -1,    49,     3,    51,    31,    52,    32,
      33,    55,    56,    34,    28,    -1,    -1,     3,    29,    47,
      53,    54,    -1,    -1,    30,    52,    -1,    -1,    41,    -1,
      -1,    33,    57,    34,    -1,    58,    57,    -1,    -1,     3,
      35,    60,    28,    -1,    -1,     3,    31,    59,    63,    32,
      28,    -1,    70,    -1,    67,    -1,    74,    -1,    60,    23,
      60,    -1,    60,    24,    60,    -1,    60,    25,    60,    -1,
      60,    26,    60,    -1,    60,    21,    60,    -1,    60,    22,
      60,    -1,    60,    19,    60,    -1,    60,    20,    60,    -1,
      24,    60,    -1,    23,    60,    -1,    31,    60,    32,    -1,
      -1,     3,    31,    61,    63,    32,    -1,     3,    -1,    62,
      -1,     4,    -1,     5,    -1,    -1,    60,    64,    65,    -1,
      -1,    -1,    30,    60,    66,    65,    -1,    -1,    -1,    -1,
      13,    68,    31,    60,    32,    69,    14,    56,    28,    -1,
      -1,    11,    31,    60,    32,    71,    56,    72,    28,    -1,
      -1,    12,    73,    56,    -1,    -1,    15,    31,    75,    32,
      28,    -1,    -1,     6,    76,    78,    -1,    -1,    60,    77,
      78,    -1,    30,    75,    -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    69,    69,    95,    68,   123,   123,   124,   133,   138,
     132,   161,   166,   165,   171,   176,   177,   185,   186,   191,
     192,   197,   196,   246,   245,   262,   265,   265,   266,   266,
     272,   273,   273,   276,   302,   301,   322,   323,   324,   335,
     352,   369,   386,   399,   416,   433,   445,   457,   471,   479,
     487,   486,   517,   536,   542,   552,   567,   566,   579,   584,
     583,   592,   601,   609,   600,   639,   638,   654,   653,   676,
     691,   696,   695,   707,   706,   720,   721
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "CTE_ENT", "CTE_FLT", "LETRERO",
  "PROGRAM", "VARS", "INICIO", "FIN", "SI", "SINO", "MIENTRAS", "HAZ",
  "ESCRIBE", "NULA", "ENTERO", "FLOTANTE", "OPEQ", "OPNEQ", "OPGT", "OPLT",
  "'+'", "'-'", "'*'", "'/'", "UMINUS", "';'", "':'", "','", "'('", "')'",
  "'{'", "'}'", "'='", "$accept", "programa", "@1", "@2", "opc_var",
  "vars", "mas_vars", "@3", "@4", "decl_id", "@5", "tipo",
  "list_funciones", "func_tipo", "funcs", "@6", "list_func_def", "@7",
  "cont_lista", "hay_var", "cuerpo", "bloq_cuerpo", "estatuto", "@8",
  "expresion", "@9", "cte", "argum", "@10", "lista_exp", "@11", "ciclo",
  "@12", "@13", "condicion", "@14", "condicional_sino", "@15", "imprime",
  "conte_imprimir", "@16", "@17", "mas_imp", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,    43,    45,    42,    47,   278,    59,    58,
      44,    40,    41,   123,   125,    61
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    36,    38,    39,    37,    40,    40,    41,    43,    44,
      42,    42,    46,    45,    45,    47,    47,    48,    48,    49,
      49,    51,    50,    53,    52,    52,    54,    54,    55,    55,
      56,    57,    57,    58,    59,    58,    58,    58,    58,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      61,    60,    60,    60,    62,    62,    64,    63,    63,    66,
      65,    65,    68,    69,    67,    71,    70,    73,    72,    72,
      74,    76,    75,    77,    75,    78,    78
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     0,    10,     1,     0,     2,     0,     0,
       8,     0,     0,     4,     0,     1,     1,     2,     0,     1,
       1,     0,    11,     0,     5,     0,     2,     0,     1,     0,
       3,     2,     0,     4,     0,     6,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     2,     3,
       0,     5,     1,     1,     1,     1,     0,     3,     0,     0,
       4,     0,     0,     0,     9,     0,     8,     0,     3,     0,
       5,     0,     3,     0,     3,     2,     0
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     2,     6,    11,    18,     5,
       8,     7,    19,    15,    16,    20,     0,     0,    18,    14,
       3,    21,    17,     0,     0,     0,     0,    12,     0,    32,
       0,    25,    14,     0,     0,     0,    62,     0,     0,    32,
      37,    36,    38,     4,     0,     0,    13,     9,    34,     0,
       0,     0,     0,    30,    31,     0,     0,    11,    58,    52,
      54,    55,     0,     0,     0,     0,    53,     0,     0,    71,
      73,     0,    23,    29,    10,    56,     0,    50,    48,    47,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    33,
      65,     0,    76,    76,     0,    27,    28,     0,    61,     0,
      58,    49,    45,    46,    43,    44,    39,    40,    41,    42,
       0,    63,     0,    72,    74,    70,    25,    24,     0,     0,
      57,    35,     0,    69,     0,    75,    26,     0,    59,    51,
      67,     0,     0,    22,    61,     0,    66,     0,    60,    68,
      64
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     6,    25,     8,     9,    11,    19,    57,    24,
      32,    15,    16,    17,    18,    26,    45,    95,   117,    97,
      30,    38,    39,    58,    70,   100,    66,    76,    98,   120,
     134,    40,    51,   124,    41,   110,   131,   135,    42,    71,
      92,    93,   113
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -93
static const yytype_int8 yypact[] =
{
      -3,     3,     8,    -8,   -93,   -93,    20,    41,    -6,   -93,
     -93,   -93,   -93,   -93,   -93,   -93,    38,    45,    -6,    36,
     -93,   -93,   -93,    47,    23,    46,    37,   -93,    -1,    90,
      59,    77,    36,    53,   -28,    51,   -93,    63,    49,    90,
     -93,   -93,   -93,   -93,    67,    65,   -93,   -93,   -93,    22,
      22,    64,    18,   -93,   -93,    -1,    69,    41,    22,    68,
     -93,   -93,    22,    22,    22,    87,   -93,    35,    22,   -93,
      97,    72,   -93,    20,   -93,    97,    82,   -93,   -93,   -93,
      52,    22,    22,    22,    22,    22,    22,    22,    22,   -93,
     -93,    66,    70,    70,   102,   101,   -93,    46,   104,   105,
      22,   -93,   103,   103,    39,    39,     5,     5,   -93,   -93,
      46,   -93,    18,   -93,   -93,   -93,    77,   -93,    98,    22,
     -93,   -93,   106,   123,   122,   -93,   -93,   109,    97,   -93,
     -93,   111,    46,   -93,   104,    46,   -93,   112,   -93,   -93,
     -93
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -93,   -93,   -93,   -93,   -93,    71,    84,   -93,   -93,   110,
     -93,   -26,   125,   -93,   -93,   -93,    29,   -93,   -93,   -93,
     -92,   107,   -93,   -93,   -49,   -93,   -93,    48,   -93,    13,
     -93,   -93,   -93,   -93,   -93,   -93,   -93,   -93,   -93,    40,
     -93,   -93,    56
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      65,    67,    33,    48,     1,   118,     3,    49,     4,    75,
      12,    13,    14,    78,    79,    80,    13,    14,   123,    91,
       5,    59,    60,    61,    69,    59,    60,    61,     7,    72,
      87,    88,   102,   103,   104,   105,   106,   107,   108,   109,
     137,    62,    63,   139,    10,    62,    63,    20,    21,    64,
      27,    75,    28,    64,    81,    82,    83,    84,    85,    86,
      87,    88,    85,    86,    87,    88,    23,    90,    31,    43,
     128,    81,    82,    83,    84,    85,    86,    87,    88,    29,
      44,    47,    50,    53,   101,    81,    82,    83,    84,    85,
      86,    87,    88,    34,    52,    68,    55,    56,   111,    77,
     112,    35,    73,    36,    94,    37,    81,    82,    83,    84,
      85,    86,    87,    88,    99,    89,    81,    82,    83,    84,
      85,    86,    87,    88,    83,    84,    85,    86,    87,    88,
     115,   116,   127,   121,   119,   130,   132,   133,   129,   136,
     140,    74,    46,    22,    96,   126,    54,   138,   122,   114,
       0,     0,   125
};

static const yytype_int16 yycheck[] =
{
      49,    50,    28,    31,     7,    97,     3,    35,     0,    58,
      16,    17,    18,    62,    63,    64,    17,    18,   110,    68,
      28,     3,     4,     5,     6,     3,     4,     5,     8,    55,
      25,    26,    81,    82,    83,    84,    85,    86,    87,    88,
     132,    23,    24,   135,     3,    23,    24,     9,     3,    31,
       3,   100,    29,    31,    19,    20,    21,    22,    23,    24,
      25,    26,    23,    24,    25,    26,    30,    32,    31,    10,
     119,    19,    20,    21,    22,    23,    24,    25,    26,    33,
       3,    28,    31,    34,    32,    19,    20,    21,    22,    23,
      24,    25,    26,     3,    31,    31,    29,    32,    32,    31,
      30,    11,    33,    13,    32,    15,    19,    20,    21,    22,
      23,    24,    25,    26,    32,    28,    19,    20,    21,    22,
      23,    24,    25,    26,    21,    22,    23,    24,    25,    26,
      28,    30,    34,    28,    30,    12,    14,    28,    32,    28,
      28,    57,    32,    18,    73,   116,    39,   134,   100,    93,
      -1,    -1,   112
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     7,    37,     3,     0,    28,    38,     8,    40,    41,
       3,    42,    16,    17,    18,    47,    48,    49,    50,    43,
       9,     3,    48,    30,    45,    39,    51,     3,    29,    33,
      56,    31,    46,    47,     3,    11,    13,    15,    57,    58,
      67,    70,    74,    10,     3,    52,    45,    28,    31,    35,
      31,    68,    31,    34,    57,    29,    32,    44,    59,     3,
       4,     5,    23,    24,    31,    60,    62,    60,    31,     6,
      60,    75,    47,    33,    42,    60,    63,    31,    60,    60,
      60,    19,    20,    21,    22,    23,    24,    25,    26,    28,
      32,    60,    76,    77,    32,    53,    41,    55,    64,    32,
      61,    32,    60,    60,    60,    60,    60,    60,    60,    60,
      71,    32,    30,    78,    78,    28,    30,    54,    56,    30,
      65,    28,    63,    56,    69,    75,    52,    34,    60,    32,
      12,    72,    14,    28,    66,    73,    28,    56,    65,    56,
      28
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 69 "patito.y"
    {
        /*
         * PN-1: Punto neurálgico de inicio.
         * Inicializar todas las estructuras del compilador:
         *   - Cubo semántico (ya inicializado en su constructor)
         *   - Tablas de variables y directorio de funciones
         *   - Pilas de compilación y fila de cuadruplos
         *   - Mapa de memoria virtual
         * Apuntar tablaActual al scope global.
         */
        dirVirtual.init();
        tablaActual = &tablaGlobal;
        std::cout << "Compilando: " << (yyvsp[(2) - (3)].sval) << "\n";

        /*
         * PN-1b: Emitir el cuadruplo 0: GOTO a main.
         * Las funciones se declaran antes de inicio, por lo que sus
         * cuadruplos vienen primero. Para que la ejecución empiece
         * en el cuerpo principal (main), el primer cuadruplo siempre
         * debe ser un salto a él. El destino se rellena con backpatch
         * cuando se alcanza el token INICIO y se conoce la posición.
         */
        gen.generar("GOTO", "_", "_", "???");
        gen.pilaJumps.push(0);  /* guardar índice del GOTO para backpatch */
      ;}
    break;

  case 3:
#line 95 "patito.y"
    {
        /*
         * PN-INICIO: Se conoce ahora el índice del primer cuadruplo de main.
         * Backpatch el GOTO inicial (cuadruplo 0) para que apunte aquí.
         * Luego resetear temporales para empezar desde t0 en el cuerpo principal.
         */
        int gotoMain = gen.pilaJumps.pop();
        gen.fila.fillJump(gotoMain, gen.fila.count());
        dirVirtual.resetTempCounters();
      ;}
    break;

  case 4:
#line 106 "patito.y"
    {
        /*
         * PN-FIN: El programa es sintáctica y semánticamente correcto.
         * Imprimir el mapa de memoria, el directorio de funciones
         * y la lista de cuadruplos generados.
         */
        std::cout << "\nPrograma Patito válido.\n";
        dirVirtual.imprimirMapa();
        dirFunciones.imprimir();
        gen.fila.imprimir();
      ;}
    break;

  case 8:
#line 133 "patito.y"
    {
        /* PN-2: acumular el primer identificador de la declaración */
        pilaIDs.push((yyvsp[(1) - (1)].sval));
      ;}
    break;

  case 9:
#line 138 "patito.y"
    {
        /*
         * PN-3: vaciar la pila de IDs, insertar cada uno en la tabla activa
         * y asignarle una dirección virtual según el scope (global o local).
         */
        while (!pilaIDs.empty()) {
            std::string nombre = pilaIDs.pop();

            if (tablaActual->insertar(nombre, (yyvsp[(5) - (6)].tval)) == 0) {
                /* Inserción exitosa: asignar dirección virtual */
                Variable* v = tablaActual->buscar(nombre);
                v->dir = (tablaActual == &tablaGlobal)
                         ? dirVirtual.nextGlobalAddr((yyvsp[(5) - (6)].tval))
                         : dirVirtual.nextLocalAddr((yyvsp[(5) - (6)].tval));
            } else {
                /* Variable ya declarada en este scope */
                std::cerr << "Error Semántico: variable doblemente declarada '"
                          << nombre << "'\n";
                errsemant++;
            }
        }
      ;}
    break;

  case 12:
#line 166 "patito.y"
    {
        /* PN-4: acumular identificadores adicionales separados por coma */
        pilaIDs.push((yyvsp[(2) - (2)].sval));
      ;}
    break;

  case 15:
#line 176 "patito.y"
    { (yyval.tval) = TIPO_INT; ;}
    break;

  case 16:
#line 177 "patito.y"
    { (yyval.tval) = TIPO_FLT; ;}
    break;

  case 19:
#line 191 "patito.y"
    { (yyval.tval) = TIPO_NULA; ;}
    break;

  case 20:
#line 192 "patito.y"
    { (yyval.tval) = (yyvsp[(1) - (1)].tval); ;}
    break;

  case 21:
#line 197 "patito.y"
    {
        /*
         * PN-5: registrar la función en el directorio, abrir el scope local
         * y resetear contadores de direcciones locales y temporales.
         */
        if (dirFunciones.insertar((yyvsp[(2) - (2)].sval), (yyvsp[(1) - (2)].tval)) != 0) {
            std::cerr << "Error Semántico: función doblemente declarada '"
                      << (yyvsp[(2) - (2)].sval) << "'\n";
            errsemant++;
            funcionActual = nullptr;
        } else {
            funcionActual = dirFunciones.buscar((yyvsp[(2) - (2)].sval));
            funcionActual->startQuad = gen.fila.count(); /* primer cuadruplo */
            funcionActual->numParams = 0;
            tablaActual = &funcionActual->locales;       /* abrir scope local */
            dirVirtual.resetLocalCounters();
            dirVirtual.resetTempCounters();
        }
      ;}
    break;

  case 22:
#line 217 "patito.y"
    {
        /*
         * PN-6: al cerrar la función:
         *   - Si retorna valor, generar RETURN con la última dirección asignada.
         *   - Generar ENDFUNC para marcar el final en tiempo de ejecución.
         *   - Restaurar el scope global.
         */
        if (funcionActual && funcionActual->tipoRetorno != TIPO_NULA) {
            /* Usar el registro especial de retorno según el tipo */
            int retReg = (funcionActual->tipoRetorno == TIPO_FLT) ? RET_FLT : RET_INT;
            std::string retDir = (gen.lastAssignedDir >= 0)
                                 ? std::to_string(gen.lastAssignedDir)
                                 : std::to_string(retReg);
            gen.generar("RETURN", retDir, "_", "_");
        }
        gen.generar("ENDFUNC", "_", "_", "_");
        gen.lastAssignedDir = -1;     /* resetear para la próxima función */
        funcionActual = nullptr;
        tablaActual   = &tablaGlobal; /* volver al scope global */
      ;}
    break;

  case 23:
#line 246 "patito.y"
    {
        /* PN-7: registrar el primer parámetro formal */
        if (funcionActual) {
            if (funcionActual->locales.insertar((yyvsp[(1) - (3)].sval), (yyvsp[(3) - (3)].tval)) == 0) {
                Variable* v = funcionActual->locales.buscar((yyvsp[(1) - (3)].sval));
                v->dir = dirVirtual.nextLocalAddr((yyvsp[(3) - (3)].tval));
                funcionActual->numParams++;
                /* Guardar dir en orden para que GOSUB de la MV copie args correctamente */
                funcionActual->paramDirs.push_back(v->dir);
            } else {
                std::cerr << "Error Semántico: parámetro duplicado '" << (yyvsp[(1) - (3)].sval) << "'\n";
                errsemant++;
            }
        }
      ;}
    break;

  case 33:
#line 277 "patito.y"
    {
        /*
         * PN-8: asignación.
         * 1. Verificar que la variable esté declarada.
         * 2. Consultar el cubo semántico para validar los tipos.
         * 3. Generar cuadruplo de asignación con direcciones virtuales.
         */
        int t_expr  = gen.pilaTipos.pop();
        int dir_var = gen.getDirVar((yyvsp[(1) - (4)].sval));
        int t_var   = gen.getTipoVar((yyvsp[(1) - (4)].sval));

        if (dir_var < 0) {
            std::cerr << "Error Semántico: variable no declarada '" << (yyvsp[(1) - (4)].sval) << "'\n";
            errsemant++;
        } else if (cuboSemantico.consultar(t_var, t_expr, OP_ASG) == TIPO_ERR) {
            std::cerr << "Error Semántico: asignación incompatible "
                      << tipoToString(t_var) << " = " << tipoToString(t_expr) << "\n";
            errsemant++;
        }
        /* Generar: resultado = expresion */
        gen.generar("=", (yyvsp[(3) - (4)].sval), "_", std::to_string(dir_var));
        gen.lastAssignedDir = dir_var; /* recordar para posible RETURN */
      ;}
    break;

  case 34:
#line 302 "patito.y"
    {
        /*
         * PN-9a: llamada a función como estatuto (resultado descartado).
         * ERA (Establish Runtime Activation): reserva espacio de activación.
         */
        gen.contadorArgs = 0;
        gen.funcCallBuf  = (yyvsp[(1) - (2)].sval);
        gen.generar("ERA", (yyvsp[(1) - (2)].sval), "_", "_");
      ;}
    break;

  case 35:
#line 312 "patito.y"
    {
        /*
         * PN-9b: GOSUB salta al primer cuadruplo de la función.
         * El índice startQuad se obtiene del directorio de funciones.
         */
        Funcion* f = dirFunciones.buscar(gen.funcCallBuf);
        std::string startQ = std::to_string(f ? f->startQuad : -1);
        gen.generar("GOSUB", gen.funcCallBuf, startQ, "_");
      ;}
    break;

  case 39:
#line 336 "patito.y"
    {
        /* PN-E1: consultar cubo, crear temporal, generar cuadruplo */
        int t_der = gen.pilaTipos.pop();
        int t_izq = gen.pilaTipos.pop();
        int t_res = cuboSemantico.consultar(t_izq, t_der, OP_ADD);
        if (t_res == TIPO_ERR) {
            std::cerr << "Error Semántico: tipos incompatibles en '+'\n";
            errsemant++;
        }
        std::string tmp = gen.nuevoTemp(t_res);
        gen.generar("+", (yyvsp[(1) - (3)].sval), (yyvsp[(3) - (3)].sval), tmp);
        strcpy((yyval.sval), tmp.c_str());
        gen.pilaTipos.push(t_res);
      ;}
    break;

  case 40:
#line 353 "patito.y"
    {
        /* PN-E2: resta; misma lógica que la suma */
        int t_der = gen.pilaTipos.pop();
        int t_izq = gen.pilaTipos.pop();
        int t_res = cuboSemantico.consultar(t_izq, t_der, OP_SUB);
        if (t_res == TIPO_ERR) {
            std::cerr << "Error Semántico: tipos incompatibles en '-'\n";
            errsemant++;
        }
        std::string tmp = gen.nuevoTemp(t_res);
        gen.generar("-", (yyvsp[(1) - (3)].sval), (yyvsp[(3) - (3)].sval), tmp);
        strcpy((yyval.sval), tmp.c_str());
        gen.pilaTipos.push(t_res);
      ;}
    break;

  case 41:
#line 370 "patito.y"
    {
        /* PN-E3: multiplicación */
        int t_der = gen.pilaTipos.pop();
        int t_izq = gen.pilaTipos.pop();
        int t_res = cuboSemantico.consultar(t_izq, t_der, OP_MUL);
        if (t_res == TIPO_ERR) {
            std::cerr << "Error Semántico: tipos incompatibles en '*'\n";
            errsemant++;
        }
        std::string tmp = gen.nuevoTemp(t_res);
        gen.generar("*", (yyvsp[(1) - (3)].sval), (yyvsp[(3) - (3)].sval), tmp);
        strcpy((yyval.sval), tmp.c_str());
        gen.pilaTipos.push(t_res);
      ;}
    break;

  case 42:
#line 387 "patito.y"
    {
        /* PN-E4: división; el cubo siempre devuelve TIPO_FLT */
        int t_der = gen.pilaTipos.pop();
        int t_izq = gen.pilaTipos.pop();
        int t_res = cuboSemantico.consultar(t_izq, t_der, OP_DIV);
        std::string tmp = gen.nuevoTemp(t_res);
        gen.generar("/", (yyvsp[(1) - (3)].sval), (yyvsp[(3) - (3)].sval), tmp);
        strcpy((yyval.sval), tmp.c_str());
        gen.pilaTipos.push(t_res);
      ;}
    break;

  case 43:
#line 400 "patito.y"
    {
        /* PN-E5: relacional >; resultado siempre INT (booleano 0/1) */
        int t_der = gen.pilaTipos.pop();
        int t_izq = gen.pilaTipos.pop();
        int t_res = cuboSemantico.consultar(t_izq, t_der, OP_GT);
        if (t_res == TIPO_ERR) {
            std::cerr << "Error Semántico: tipos incompatibles en '>'\n";
            errsemant++;
        }
        std::string tmp = gen.nuevoTemp(TIPO_INT);
        gen.generar(">", (yyvsp[(1) - (3)].sval), (yyvsp[(3) - (3)].sval), tmp);
        strcpy((yyval.sval), tmp.c_str());
        gen.pilaTipos.push(TIPO_INT);
      ;}
    break;

  case 44:
#line 417 "patito.y"
    {
        /* PN-E6: relacional < */
        int t_der = gen.pilaTipos.pop();
        int t_izq = gen.pilaTipos.pop();
        int t_res = cuboSemantico.consultar(t_izq, t_der, OP_LT);
        if (t_res == TIPO_ERR) {
            std::cerr << "Error Semántico: tipos incompatibles en '<'\n";
            errsemant++;
        }
        std::string tmp = gen.nuevoTemp(TIPO_INT);
        gen.generar("<", (yyvsp[(1) - (3)].sval), (yyvsp[(3) - (3)].sval), tmp);
        strcpy((yyval.sval), tmp.c_str());
        gen.pilaTipos.push(TIPO_INT);
      ;}
    break;

  case 45:
#line 434 "patito.y"
    {
        /* PN-E7: relacional ==; consume tipos pero no los valida estrictamente */
        gen.pilaTipos.pop();
        gen.pilaTipos.pop();
        std::string tmp = gen.nuevoTemp(TIPO_INT);
        gen.generar("==", (yyvsp[(1) - (3)].sval), (yyvsp[(3) - (3)].sval), tmp);
        strcpy((yyval.sval), tmp.c_str());
        gen.pilaTipos.push(TIPO_INT);
      ;}
    break;

  case 46:
#line 446 "patito.y"
    {
        /* PN-E8: relacional != */
        gen.pilaTipos.pop();
        gen.pilaTipos.pop();
        std::string tmp = gen.nuevoTemp(TIPO_INT);
        gen.generar("!=", (yyvsp[(1) - (3)].sval), (yyvsp[(3) - (3)].sval), tmp);
        strcpy((yyval.sval), tmp.c_str());
        gen.pilaTipos.push(TIPO_INT);
      ;}
    break;

  case 47:
#line 458 "patito.y"
    {
        /*
         * PN-E9: UMINUS; conserva el tipo del operando.
         * El cuadruplo UMINUS niega el valor en tiempo de ejecución.
         */
        int t = gen.pilaTipos.pop();
        std::string tmp = gen.nuevoTemp(t);
        gen.generar("UMINUS", (yyvsp[(2) - (2)].sval), "_", tmp);
        strcpy((yyval.sval), tmp.c_str());
        gen.pilaTipos.push(t);
      ;}
    break;

  case 48:
#line 472 "patito.y"
    {
        /* PN-E10: +expr no cambia el valor; propagar la dirección */
        strcpy((yyval.sval), (yyvsp[(2) - (2)].sval));
        /* el tipo ya está en la pila, no hacer nada */
      ;}
    break;

  case 49:
#line 480 "patito.y"
    {
        /* PN-E11: los paréntesis sólo afectan la precedencia (ya manejada por Bison) */
        strcpy((yyval.sval), (yyvsp[(2) - (3)].sval));
      ;}
    break;

  case 50:
#line 487 "patito.y"
    {
        /*
         * PN-E12a: ERA antes de los argumentos de la función.
         * Guardar el nombre para el GOSUB posterior.
         */
        gen.contadorArgs = 0;
        gen.funcCallBuf  = (yyvsp[(1) - (2)].sval);
        gen.generar("ERA", (yyvsp[(1) - (2)].sval), "_", "_");
      ;}
    break;

  case 51:
#line 497 "patito.y"
    {
        /*
         * PN-E12b: GOSUB; copiar el valor de retorno a un temporal.
         * Los registros especiales RET_INT/RET_FLT guardan el retorno.
         */
        Funcion* f = dirFunciones.buscar(gen.funcCallBuf);
        std::string startQ = std::to_string(f ? f->startQuad : -1);
        gen.generar("GOSUB", gen.funcCallBuf, startQ, "_");

        /* Copiar valor de retorno del registro especial al temporal */
        int retTipo = f ? f->tipoRetorno : TIPO_INT;
        int retReg  = (retTipo == TIPO_FLT) ? RET_FLT : RET_INT;
        std::string tmp    = gen.nuevoTemp(retTipo);
        std::string retStr = std::to_string(retReg);
        gen.generar("=", retStr, "_", tmp);
        strcpy((yyval.sval), tmp.c_str());
        gen.pilaTipos.push(retTipo);
      ;}
    break;

  case 52:
#line 518 "patito.y"
    {
        /*
         * PN-E13: obtener la dirección virtual de la variable y su tipo.
         * Si no está declarada, reportar error semántico.
         */
        int dir = gen.getDirVar((yyvsp[(1) - (1)].sval));
        int t   = gen.getTipoVar((yyvsp[(1) - (1)].sval));
        if (dir < 0) {
            std::cerr << "Error Semántico: variable no declarada '" << (yyvsp[(1) - (1)].sval) << "'\n";
            errsemant++;
            sprintf((yyval.sval), "-1");
        } else {
            sprintf((yyval.sval), "%d", dir);
        }
        gen.pilaTipos.push(t);
      ;}
    break;

  case 53:
#line 537 "patito.y"
    { strcpy((yyval.sval), (yyvsp[(1) - (1)].sval)); ;}
    break;

  case 54:
#line 543 "patito.y"
    {
        /*
         * PN-E14: constante entera → registrarla en el pool y
         * obtener su dirección virtual en el segmento de constantes.
         */
        int addr = dirVirtual.getConstAddr((yyvsp[(1) - (1)].sval), TIPO_INT);
        sprintf((yyval.sval), "%d", addr);
        gen.pilaTipos.push(TIPO_INT);
      ;}
    break;

  case 55:
#line 553 "patito.y"
    {
        /* PN-E15: constante flotante → igual pero en segmento de constantes float */
        int addr = dirVirtual.getConstAddr((yyvsp[(1) - (1)].sval), TIPO_FLT);
        sprintf((yyval.sval), "%d", addr);
        gen.pilaTipos.push(TIPO_FLT);
      ;}
    break;

  case 56:
#line 567 "patito.y"
    {
        /*
         * PN-A1: generar cuadruplo ARG para el primer argumento.
         * El índice (0, 1, 2...) indica la posición del argumento
         * para que el ejecutor sepa dónde colocarlo en el frame.
         */
        std::string idx = std::to_string(gen.contadorArgs);
        gen.generar("ARG", (yyvsp[(1) - (1)].sval), idx, "_");
        gen.pilaTipos.pop();   /* consumir el tipo del argumento */
        gen.contadorArgs++;
      ;}
    break;

  case 59:
#line 584 "patito.y"
    {
        /* PN-A2: argumentos adicionales (separados por coma) */
        std::string idx = std::to_string(gen.contadorArgs);
        gen.generar("ARG", (yyvsp[(2) - (2)].sval), idx, "_");
        gen.pilaTipos.pop();
        gen.contadorArgs++;
      ;}
    break;

  case 62:
#line 601 "patito.y"
    {
        /*
         * PN-C1: guardar el índice actual como "punto de retorno" del ciclo.
         * Al final del cuerpo se generará un GOTO a esta posición.
         */
        gen.pilaJumps.push(gen.fila.count());
      ;}
    break;

  case 63:
#line 609 "patito.y"
    {
        /*
         * PN-C2: la condición ya se evaluó y su dirección está en $4.
         * Generar GOTOF (goto if false): si la condición es falsa, saltar al fin.
         * El destino se rellena con backpatch cuando se conoce la posición fin.
         */
        gen.pilaTipos.pop();   /* consumir tipo de la condición */
        gen.generar("GOTOF", (yyvsp[(4) - (5)].sval), "_", "???");
        gen.pilaJumps.push(gen.fila.count() - 1); /* guardar índice del GOTOF */
      ;}
    break;

  case 64:
#line 620 "patito.y"
    {
        /*
         * PN-C3: fin del ciclo.
         *   1. Generar GOTO al inicio del ciclo (punto de retorno).
         *   2. Backpatch el GOTOF con la posición actual (post-ciclo).
         */
        int fin     = gen.pilaJumps.pop();   /* índice del GOTOF */
        int retorno = gen.pilaJumps.pop();   /* índice del inicio del ciclo */
        gen.generar("GOTO", "_", "_", std::to_string(retorno));
        gen.fila.fillJump(fin, gen.fila.count()); /* rellenar destino del GOTOF */
      ;}
    break;

  case 65:
#line 639 "patito.y"
    {
        /*
         * PN-IF1: condición evaluada.
         * GOTOF salta al bloque SINO (o al fin del SI si no hay SINO).
         * Destino pendiente: se rellena con backpatch.
         */
        gen.pilaTipos.pop();
        gen.generar("GOTOF", (yyvsp[(3) - (4)].sval), "_", "???");
        gen.pilaJumps.push(gen.fila.count() - 1); /* guardar índice del GOTOF */
      ;}
    break;

  case 67:
#line 654 "patito.y"
    {
        /*
         * PN-IF2: inicio del bloque SINO.
         *   1. Generar GOTO al fin del SI completo (saltarse el SINO).
         *   2. Backpatch el GOTOF anterior con la posición actual (inicio SINO).
         */
        gen.generar("GOTO", "_", "_", "???");
        int falso = gen.pilaJumps.pop();           /* índice del GOTOF del SI */
        gen.pilaJumps.push(gen.fila.count() - 1); /* guardar índice del GOTO */
        gen.fila.fillJump(falso, gen.fila.count()); /* GOTOF → aquí (inicio SINO) */
      ;}
    break;

  case 68:
#line 666 "patito.y"
    {
        /*
         * PN-IF3: fin del bloque SINO.
         * Backpatch el GOTO generado en PN-IF2 con la posición actual (post-SI).
         */
        int fin = gen.pilaJumps.pop();
        gen.fila.fillJump(fin, gen.fila.count());
      ;}
    break;

  case 69:
#line 676 "patito.y"
    {
        /*
         * PN-IF-END: condicional sin SINO.
         * Backpatch el GOTOF con la posición actual (fin del bloque SI).
         */
        int fin = gen.pilaJumps.pop();
        gen.fila.fillJump(fin, gen.fila.count());
      ;}
    break;

  case 71:
#line 696 "patito.y"
    {
        /*
         * PN-P1: imprimir un string literal.
         * Registrar el string en el pool de constantes (TIPO_NULA = string)
         * y generar cuadruplo PRINT con su dirección virtual.
         */
        int addr = dirVirtual.getConstAddr((yyvsp[(1) - (1)].sval), TIPO_NULA);
        gen.generar("PRINT", std::to_string(addr), "_", "_");
      ;}
    break;

  case 73:
#line 707 "patito.y"
    {
        /*
         * PN-P2: imprimir el valor de una expresión.
         * La dirección virtual de la expresión viene en $1.
         */
        gen.generar("PRINT", (yyvsp[(1) - (1)].sval), "_", "_");
        gen.pilaTipos.pop();   /* consumir el tipo de la expresión */
      ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2137 "patito.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 724 "patito.y"


/* ═════════════════════════════════════════════════════════════════════
 * FUNCIÓN DE ERROR Y MAIN
 * ═════════════════════════════════════════════════════════════════════ */

/**
 * yyerror
 * Bison llama a esta función cuando detecta un error sintáctico.
 * Imprime el número de línea y el mensaje de error.
 */
void yyerror(const char *s) {
    std::cerr << "Error Sintáctico, Línea " << yylineno << ": " << s << "\n";
    errsintx++;
}

/**
 * main
 * Punto de entrada del compilador.
 * Acepta un archivo de entrada opcional como primer argumento.
 * Si no se proporciona, lee desde stdin.
 */
int main(int argc, char *argv[]) {
    if (argc > 1) {
        /* Abrir archivo de entrada proporcionado por el usuario */
        FILE *f = fopen(argv[1], "r");
        if (!f) {
            std::cerr << "Error: no se pudo abrir '" << argv[1] << "'\n";
            return 1;
        }
        yyin = f;
    }

    /* Ejecutar el análisis léxico + sintáctico + semántico */
    yyparse();

    /* Reporte final de errores */
    std::cout << "\n── Reporte de errores ──────────────────────────────\n";
    std::cout << "  Errores léxicos    : " << errores_lexicos << "\n";
    std::cout << "  Errores sintácticos: " << errsintx        << "\n";
    std::cout << "  Errores semánticos : " << errsemant       << "\n";
    std::cout << "────────────────────────────────────────────────────\n";

    if (argc > 1) fclose(yyin);

    /* Ejecutar la MV solo si no hubo errores de compilación */
    if (errores_lexicos + errsintx + errsemant == 0) {
        std::cout << "\n── EJECUCION (Maquina Virtual) ──────────────────────\n";
        MaquinaVirtual vm(gen.fila, dirFunciones);
        vm.cargarConstantes(dirVirtual);
        vm.ejecutar();
        std::cout << "────────────────────────────────────────────────────\n";
    }

    return (errores_lexicos + errsintx + errsemant > 0) ? 1 : 0;
}

