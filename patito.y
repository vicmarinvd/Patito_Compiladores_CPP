/*
 * patito.y
 * Gramática y acciones semánticas del compilador Patito,
 * usa las clases CuboSemantico, TablaVariables,
 * DirectorioFunciones, DirectorioVirtual y GeneradorCuad.
 */

%{
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
%}

/* ── Unión de atributos semánticos ──────────────────────────────────
 * sval: cadena de texto (IDs, constantes, direcciones virtuales)
 * tval: valor entero    (tipo de dato)
 */
%union { char sval[64]; int tval; }

/* ── Tokens con atributo de cadena ── */
%token <sval> ID CTE_ENT CTE_FLT LETRERO

/* ── Tokens sin atributo (palabras reservadas y operadores) ── */
%token PROGRAM VARS INICIO FIN SI SINO MIENTRAS HAZ ESCRIBE NULA ENTERO FLOTANTE
%token OPEQ OPNEQ OPGT OPLT

/* ── Precedencia de operadores (menor a mayor) ── */
%left  OPEQ OPNEQ          /* == !=  (menor precedencia) */
%left  OPGT OPLT           /* >  <  */
%left  '+' '-'             /* suma y resta */
%left  '*' '/'             /* multiplicación y división */
%right UMINUS              /* menos unario (mayor precedencia) */

/* ── Tipos de las no-terminales ── */
%type <sval> expresion cte
%type <tval> tipo func_tipo

%%

/* ═════════════════════════════════════════════════════════════════════
 * PROGRAMA
 * ═════════════════════════════════════════════════════════════════════ */

programa
    : PROGRAM ID ';'
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
        std::cout << "Compilando: " << $2 << "\n";

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
      }
      opc_var list_funciones INICIO
      {
        /*
         * PN-INICIO: Se conoce ahora el índice del primer cuadruplo de main.
         * Backpatch el GOTO inicial (cuadruplo 0) para que apunte aquí.
         * Luego resetear temporales para empezar desde t0 en el cuerpo principal.
         */
        int gotoMain = gen.pilaJumps.pop();
        gen.fila.fillJump(gotoMain, gen.fila.count());
        dirVirtual.resetTempCounters();
      }
      cuerpo FIN
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
      }
    ;

/* ═════════════════════════════════════════════════════════════════════
 * VARIABLES
 * ═════════════════════════════════════════════════════════════════════ */

opc_var  : vars | /* epsilon: sin declaraciones */ ;
vars     : VARS mas_vars ;

/*
 * mas_vars: procesa una o más declaraciones del estilo
 *   ID, ID, ID : tipo ;
 * Primero apila todos los IDs, luego (al conocer el tipo) los registra.
 */
mas_vars
    : ID
      {
        /* PN-2: acumular el primer identificador de la declaración */
        pilaIDs.push($1);
      }
      decl_id ':' tipo ';'
      {
        /*
         * PN-3: vaciar la pila de IDs, insertar cada uno en la tabla activa
         * y asignarle una dirección virtual según el scope (global o local).
         */
        while (!pilaIDs.empty()) {
            std::string nombre = pilaIDs.pop();

            if (tablaActual->insertar(nombre, $5) == 0) {
                /* Inserción exitosa: asignar dirección virtual */
                Variable* v = tablaActual->buscar(nombre);
                v->dir = (tablaActual == &tablaGlobal)
                         ? dirVirtual.nextGlobalAddr($5)
                         : dirVirtual.nextLocalAddr($5);
            } else {
                /* Variable ya declarada en este scope */
                std::cerr << "Error Semántico: variable doblemente declarada '"
                          << nombre << "'\n";
                errsemant++;
            }
        }
      }
      mas_vars
    | /* epsilon: fin de declaraciones */
    ;

decl_id
    : ',' ID
      {
        /* PN-4: acumular identificadores adicionales separados por coma */
        pilaIDs.push($2);
      }
      decl_id
    | /* epsilon */
    ;

/* Tipos de datos del lenguaje */
tipo
    : ENTERO   { $$ = TIPO_INT; }
    | FLOTANTE { $$ = TIPO_FLT; }
    ;

/* ═════════════════════════════════════════════════════════════════════
 * FUNCIONES
 * ═════════════════════════════════════════════════════════════════════ */

list_funciones
    : funcs list_funciones
    | /* epsilon: sin funciones */
    ;

/* El tipo de retorno puede ser entero, flotante o nula (void) */
func_tipo
    : NULA { $$ = TIPO_NULA; }
    | tipo { $$ = $1; }
    ;

funcs
    : func_tipo ID
      {
        /*
         * PN-5: registrar la función en el directorio, abrir el scope local
         * y resetear contadores de direcciones locales y temporales.
         */
        if (dirFunciones.insertar($2, $1) != 0) {
            std::cerr << "Error Semántico: función doblemente declarada '"
                      << $2 << "'\n";
            errsemant++;
            funcionActual = nullptr;
        } else {
            funcionActual = dirFunciones.buscar($2);
            funcionActual->startQuad = gen.fila.count(); /* primer cuadruplo */
            funcionActual->numParams = 0;
            tablaActual = &funcionActual->locales;       /* abrir scope local */
            dirVirtual.resetLocalCounters();
            dirVirtual.resetTempCounters();
        }
      }
      '(' list_func_def ')' '{' hay_var cuerpo '}' ';'
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
      }
    ;

/*
 * list_func_def: lista de parámetros formales de la función.
 * Cada parámetro se registra como variable local y se le asigna
 * una dirección en el segmento local.
 */
list_func_def
    : ID ':' tipo
      {
        /* PN-7: registrar el primer parámetro formal */
        if (funcionActual) {
            if (funcionActual->locales.insertar($1, $3) == 0) {
                Variable* v = funcionActual->locales.buscar($1);
                v->dir = dirVirtual.nextLocalAddr($3);
                funcionActual->numParams++;
                /* Guardar dir en orden para que GOSUB de la MV copie args correctamente */
                funcionActual->paramDirs.push_back(v->dir);
            } else {
                std::cerr << "Error Semántico: parámetro duplicado '" << $1 << "'\n";
                errsemant++;
            }
        }
      }
      cont_lista
    | /* epsilon: función sin parámetros */
    ;

cont_lista : ',' list_func_def | /* epsilon */ ;
hay_var    : vars | /* epsilon */ ;

/* ═════════════════════════════════════════════════════════════════════
 * CUERPO Y ESTATUTOS
 * ═════════════════════════════════════════════════════════════════════ */

cuerpo     : '{' bloq_cuerpo '}' ;
bloq_cuerpo: estatuto bloq_cuerpo | /* epsilon */ ;

estatuto
    : ID '=' expresion ';'
      {
        /*
         * PN-8: asignación.
         * 1. Verificar que la variable esté declarada.
         * 2. Consultar el cubo semántico para validar los tipos.
         * 3. Generar cuadruplo de asignación con direcciones virtuales.
         */
        int t_expr  = gen.pilaTipos.pop();
        int dir_var = gen.getDirVar($1);
        int t_var   = gen.getTipoVar($1);

        if (dir_var < 0) {
            std::cerr << "Error Semántico: variable no declarada '" << $1 << "'\n";
            errsemant++;
        } else if (cuboSemantico.consultar(t_var, t_expr, OP_ASG) == TIPO_ERR) {
            std::cerr << "Error Semántico: asignación incompatible "
                      << tipoToString(t_var) << " = " << tipoToString(t_expr) << "\n";
            errsemant++;
        }
        /* Generar: resultado = expresion */
        gen.generar("=", $3, "_", std::to_string(dir_var));
        gen.lastAssignedDir = dir_var; /* recordar para posible RETURN */
      }

    | ID '('
      {
        /*
         * PN-9a: llamada a función como estatuto (resultado descartado).
         * ERA (Establish Runtime Activation): reserva espacio de activación.
         */
        gen.contadorArgs = 0;
        gen.funcCallBuf  = $1;
        gen.generar("ERA", $1, "_", "_");
      }
      argum ')' ';'
      {
        /*
         * PN-9b: GOSUB salta al primer cuadruplo de la función.
         * El índice startQuad se obtiene del directorio de funciones.
         */
        Funcion* f = dirFunciones.buscar(gen.funcCallBuf);
        std::string startQ = std::to_string(f ? f->startQuad : -1);
        gen.generar("GOSUB", gen.funcCallBuf, startQ, "_");
      }

    | condicion
    | ciclo
    | imprime
    ;

/* ═════════════════════════════════════════════════════════════════════
 * EXPRESIONES
 * Las expresiones empujan su dirección virtual (como string) en $$
 * y su tipo en gen.pilaTipos para que el estatuto padre pueda usarlos.
 * ═════════════════════════════════════════════════════════════════════ */

expresion
    /* ── Suma ── */
    : expresion '+' expresion
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
        gen.generar("+", $1, $3, tmp);
        strcpy($$, tmp.c_str());
        gen.pilaTipos.push(t_res);
      }

    /* ── Resta ── */
    | expresion '-' expresion
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
        gen.generar("-", $1, $3, tmp);
        strcpy($$, tmp.c_str());
        gen.pilaTipos.push(t_res);
      }

    /* ── Multiplicación ── */
    | expresion '*' expresion
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
        gen.generar("*", $1, $3, tmp);
        strcpy($$, tmp.c_str());
        gen.pilaTipos.push(t_res);
      }

    /* ── División (resultado siempre flotante) ── */
    | expresion '/' expresion
      {
        /* PN-E4: división; el cubo siempre devuelve TIPO_FLT */
        int t_der = gen.pilaTipos.pop();
        int t_izq = gen.pilaTipos.pop();
        int t_res = cuboSemantico.consultar(t_izq, t_der, OP_DIV);
        std::string tmp = gen.nuevoTemp(t_res);
        gen.generar("/", $1, $3, tmp);
        strcpy($$, tmp.c_str());
        gen.pilaTipos.push(t_res);
      }

    /* ── Mayor que ── */
    | expresion OPGT expresion
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
        gen.generar(">", $1, $3, tmp);
        strcpy($$, tmp.c_str());
        gen.pilaTipos.push(TIPO_INT);
      }

    /* ── Menor que ── */
    | expresion OPLT expresion
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
        gen.generar("<", $1, $3, tmp);
        strcpy($$, tmp.c_str());
        gen.pilaTipos.push(TIPO_INT);
      }

    /* ── Igual ── */
    | expresion OPEQ expresion
      {
        /* PN-E7: relacional ==; consume tipos pero no los valida estrictamente */
        gen.pilaTipos.pop();
        gen.pilaTipos.pop();
        std::string tmp = gen.nuevoTemp(TIPO_INT);
        gen.generar("==", $1, $3, tmp);
        strcpy($$, tmp.c_str());
        gen.pilaTipos.push(TIPO_INT);
      }

    /* ── Diferente ── */
    | expresion OPNEQ expresion
      {
        /* PN-E8: relacional != */
        gen.pilaTipos.pop();
        gen.pilaTipos.pop();
        std::string tmp = gen.nuevoTemp(TIPO_INT);
        gen.generar("!=", $1, $3, tmp);
        strcpy($$, tmp.c_str());
        gen.pilaTipos.push(TIPO_INT);
      }

    /* ── Negación unaria ── */
    | '-' expresion %prec UMINUS
      {
        /*
         * PN-E9: UMINUS; conserva el tipo del operando.
         * El cuadruplo UMINUS niega el valor en tiempo de ejecución.
         */
        int t = gen.pilaTipos.pop();
        std::string tmp = gen.nuevoTemp(t);
        gen.generar("UMINUS", $2, "_", tmp);
        strcpy($$, tmp.c_str());
        gen.pilaTipos.push(t);
      }

    /* ── Positivo unario (no-op) ── */
    | '+' expresion %prec UMINUS
      {
        /* PN-E10: +expr no cambia el valor; propagar la dirección */
        strcpy($$, $2);
        /* el tipo ya está en la pila, no hacer nada */
      }

    /* ── Paréntesis ── */
    | '(' expresion ')'
      {
        /* PN-E11: los paréntesis sólo afectan la precedencia (ya manejada por Bison) */
        strcpy($$, $2);
      }

    /* ── Llamada a función como expresión ── */
    | ID '('
      {
        /*
         * PN-E12a: ERA antes de los argumentos de la función.
         * Guardar el nombre para el GOSUB posterior.
         */
        gen.contadorArgs = 0;
        gen.funcCallBuf  = $1;
        gen.generar("ERA", $1, "_", "_");
      }
      argum ')'
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
        strcpy($$, tmp.c_str());
        gen.pilaTipos.push(retTipo);
      }

    /* ── Variable: empujar su dirección virtual ── */
    | ID
      {
        /*
         * PN-E13: obtener la dirección virtual de la variable y su tipo.
         * Si no está declarada, reportar error semántico.
         */
        int dir = gen.getDirVar($1);
        int t   = gen.getTipoVar($1);
        if (dir < 0) {
            std::cerr << "Error Semántico: variable no declarada '" << $1 << "'\n";
            errsemant++;
            sprintf($$, "-1");
        } else {
            sprintf($$, "%d", dir);
        }
        gen.pilaTipos.push(t);
      }

    /* ── Constante ── */
    | cte
      { strcpy($$, $1); }
    ;

/* ── Constantes literales ── */
cte
    : CTE_ENT
      {
        /*
         * PN-E14: constante entera → registrarla en el pool y
         * obtener su dirección virtual en el segmento de constantes.
         */
        int addr = dirVirtual.getConstAddr($1, TIPO_INT);
        sprintf($$, "%d", addr);
        gen.pilaTipos.push(TIPO_INT);
      }
    | CTE_FLT
      {
        /* PN-E15: constante flotante → igual pero en segmento de constantes float */
        int addr = dirVirtual.getConstAddr($1, TIPO_FLT);
        sprintf($$, "%d", addr);
        gen.pilaTipos.push(TIPO_FLT);
      }
    ;

/* ═════════════════════════════════════════════════════════════════════
 * ARGUMENTOS DE LLAMADA A FUNCIÓN
 * ═════════════════════════════════════════════════════════════════════ */

argum
    : expresion
      {
        /*
         * PN-A1: generar cuadruplo ARG para el primer argumento.
         * El índice (0, 1, 2...) indica la posición del argumento
         * para que el ejecutor sepa dónde colocarlo en el frame.
         */
        std::string idx = std::to_string(gen.contadorArgs);
        gen.generar("ARG", $1, idx, "_");
        gen.pilaTipos.pop();   /* consumir el tipo del argumento */
        gen.contadorArgs++;
      }
      lista_exp
    | /* epsilon: llamada sin argumentos */
    ;

lista_exp
    : ',' expresion
      {
        /* PN-A2: argumentos adicionales (separados por coma) */
        std::string idx = std::to_string(gen.contadorArgs);
        gen.generar("ARG", $2, idx, "_");
        gen.pilaTipos.pop();
        gen.contadorArgs++;
      }
      lista_exp
    | /* epsilon */
    ;

/* ═════════════════════════════════════════════════════════════════════
 * CICLO MIENTRAS ... HAZ
 * ═════════════════════════════════════════════════════════════════════ */

ciclo
    : MIENTRAS
      {
        /*
         * PN-C1: guardar el índice actual como "punto de retorno" del ciclo.
         * Al final del cuerpo se generará un GOTO a esta posición.
         */
        gen.pilaJumps.push(gen.fila.count());
      }
      '(' expresion ')'
      {
        /*
         * PN-C2: la condición ya se evaluó y su dirección está en $4.
         * Generar GOTOF (goto if false): si la condición es falsa, saltar al fin.
         * El destino se rellena con backpatch cuando se conoce la posición fin.
         */
        gen.pilaTipos.pop();   /* consumir tipo de la condición */
        gen.generar("GOTOF", $4, "_", "???");
        gen.pilaJumps.push(gen.fila.count() - 1); /* guardar índice del GOTOF */
      }
      HAZ cuerpo ';'
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
      }
    ;

/* ═════════════════════════════════════════════════════════════════════
 * CONDICIONAL SI [/ SINO]
 * ═════════════════════════════════════════════════════════════════════ */

condicion
    : SI '(' expresion ')'
      {
        /*
         * PN-IF1: condición evaluada.
         * GOTOF salta al bloque SINO (o al fin del SI si no hay SINO).
         * Destino pendiente: se rellena con backpatch.
         */
        gen.pilaTipos.pop();
        gen.generar("GOTOF", $3, "_", "???");
        gen.pilaJumps.push(gen.fila.count() - 1); /* guardar índice del GOTOF */
      }
      cuerpo condicional_sino ';'
    ;

condicional_sino
    : SINO
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
      }
      cuerpo
      {
        /*
         * PN-IF3: fin del bloque SINO.
         * Backpatch el GOTO generado en PN-IF2 con la posición actual (post-SI).
         */
        int fin = gen.pilaJumps.pop();
        gen.fila.fillJump(fin, gen.fila.count());
      }

    | /* epsilon: no hay SINO */
      {
        /*
         * PN-IF-END: condicional sin SINO.
         * Backpatch el GOTOF con la posición actual (fin del bloque SI).
         */
        int fin = gen.pilaJumps.pop();
        gen.fila.fillJump(fin, gen.fila.count());
      }
    ;

/* ═════════════════════════════════════════════════════════════════════
 * INSTRUCCIÓN ESCRIBE
 * ═════════════════════════════════════════════════════════════════════ */

imprime
    : ESCRIBE '(' conte_imprimir ')' ';'
    ;

conte_imprimir
    : LETRERO
      {
        /*
         * PN-P1: imprimir un string literal.
         * Registrar el string en el pool de constantes (TIPO_NULA = string)
         * y generar cuadruplo PRINT con su dirección virtual.
         */
        int addr = dirVirtual.getConstAddr($1, TIPO_NULA);
        gen.generar("PRINT", std::to_string(addr), "_", "_");
      }
      mas_imp
    | expresion
      {
        /*
         * PN-P2: imprimir el valor de una expresión.
         * La dirección virtual de la expresión viene en $1.
         */
        gen.generar("PRINT", $1, "_", "_");
        gen.pilaTipos.pop();   /* consumir el tipo de la expresión */
      }
      mas_imp
    ;

/* Permite escribe("msg", expr, ...) con múltiples elementos */
mas_imp
    : ',' conte_imprimir
    | /* epsilon */
    ;

%%

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
