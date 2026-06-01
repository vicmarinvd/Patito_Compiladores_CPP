%{
/*
 * patito.l Analizador lexico del lenguaje Patito (Flex)
 *
 * Reconoce:
 *   - Palabras reservadas: programa, vars, inicio, fin, si, sino,
 *                          mientras, haz, escribe, entero, flotante, nula
 *   - Identificadores (ID), constantes enteras y flotantes, strings (LETRERO)
 *   - Operadores aritmeticos y relacionales, delimitadores
 */

#include "patito.tab.h"
#include <cstdio>
#include <cstring>

extern int yylineno;
int errores_lexicos = 0;
%}

%option yylineno

digito      [0-9]
letra       [a-zA-Z]
guion       [_]
ID          ({letra}|{guion})({letra}|{digito}|{guion})*
CTE_ENT     {digito}+
CTE_FLT     {digito}+\.{digito}+
LETRERO     \"[^\"\n]*\"
BLANCOS     [ \t\n\r]+

%%

"programa"   { return PROGRAM;  }
"vars"       { return VARS;     }
"inicio"     { return INICIO;   }
"fin"        { return FIN;      }
"si"         { return SI;       }
"sino"       { return SINO;     }
"mientras"   { return MIENTRAS; }
"haz"        { return HAZ;      }
"escribe"    { return ESCRIBE;  }
"entero"     { return ENTERO;   }
"flotante"   { return FLOTANTE; }
"nula"       { return NULA;     }

{CTE_FLT} {
    /* constante flotante: va antes que CTE_ENT para capturar decimales */
    strncpy(yylval.sval, yytext, 63);
    yylval.sval[63] = '\0';
    return CTE_FLT;
}

{CTE_ENT} {
    /* constante entera */
    strncpy(yylval.sval, yytext, 63);
    yylval.sval[63] = '\0';
    return CTE_ENT;
}

{ID} {
    /* identificador: va despues de palabras reservadas para que tengan prioridad */
    strncpy(yylval.sval, yytext, 63);
    yylval.sval[63] = '\0';
    return ID;
}

{LETRERO} {
    strncpy(yylval.sval, yytext, 63);
    yylval.sval[63] = '\0';
    return LETRERO;
}

"=="  { return OPEQ;  }
"!="  { return OPNEQ; }
">"   { return OPGT;  }
"<"   { return OPLT;  }
"+"   { return '+';   }
"-"   { return '-';   }
"*"   { return '*';   }
"/"   { return '/';   }
"="   { return '=';   }
";"   { return ';';   }
","   { return ',';   }
"("   { return '(';   }
")"   { return ')';   }
"{"   { return '{';   }
"}"   { return '}';   }
":"   { return ':';   }

{BLANCOS} { /* ignorar espacios, tabs y saltos de linea */ }

. {
    /* caracter no reconocido: reportar error lexico */
    fprintf(stderr,
        "[Error Lexico] Linea %d: caracter no reconocido '%s'\n",
        yylineno, yytext);
    errores_lexicos++;
}

%%

/* yywrap: retornar 1 indica fin de entrada (no hay mas archivos) */
int yywrap(void) { return 1; }
