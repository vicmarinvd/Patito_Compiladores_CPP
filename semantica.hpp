#pragma once

/*
 * semantica.hpp
 * ─────────────────────────────────────────────────────────────────────
 * Declaraciones de todas las estructuras de análisis semántico del
 * compilador Patito. 
 *
 * Módulos:
 *   - Tipos y operadores (enums)
 *   - CuboSemantico   : verifica compatibilidad de tipos en operaciones
 *   - TablaVariables  : tabla hash de variables (nombre - Variable)
 *   - DirectorioFunciones : tabla hash de funciones (nombre - Funcion)
 *   - StackIDs        : pila auxiliar de identificadores
 */

#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <memory>   

// tipos de datos definidos por un numero para los cuadruplos
enum Tipo {
    TIPO_ERR  = 0,   // inválido/incompatible
    TIPO_INT  = 1,   // entero
    TIPO_FLT  = 2,   // flotante
    TIPO_NULA = 3    // nulo/no return
};

// operadores validos 
enum Operador {
    OP_ADD = 0,   // suma           (+)
    OP_SUB = 1,   // resta          (-)
    OP_MUL = 2,   // multiplicación (*)
    OP_DIV = 3,   // división       (/)
    OP_GT  = 4,   // mayor que      (>)
    OP_LT  = 5,   // menor que      (<)
    OP_EQ  = 6,   // igual          (==)
    OP_NEQ = 7,   // diferente      (!=)
    OP_ASG = 8    // asignación     (=)
};

constexpr int NUM_TYPES = 4;   // número de tipos distintos
constexpr int NUM_OPS   = 9;   // número de operadores

// Convierte un tipo entero a su nombre como string (para mensajes de error)
std::string tipoToString(int tipo);

// Cubo semantico, es una tabla con tres dimensiones (datos) [tipo iz][tipo der][op]- [tipo res]
// en caso de  no ser valido es TIPO_ERR, se inicializa en el constructor con todas las combinaciones validas 
class CuboSemantico {
    int cubo[NUM_TYPES][NUM_TYPES][NUM_OPS];

public:
    // constructor: llena todas las entradas del cubo
    CuboSemantico();

    // consulta el tipo resultante de aplicar 'op' entre 'izq' y 'der'
    // retorna TIPO_ERR si la combinación es inválida
    int consultar(int izq, int der, int op) const;
};

// Variable, recibe la variable declarada en el programa, con su nombre, tipo y direccion
struct Variable {
    std::string nombre;   
    int         tipo;     
    int         dir;      // dirección en el mapa de memoria virtual
};

// Tabla de variables, hash map que mapea el nombre de la variable a la estrcutura Variable
// Usa unique_ptr para garantizar que los pointers se mantengan aunque crezca el mapa
class TablaVariables {
    // unique_ptr garantiza que el objeto Variable no se mueva de memoria
    std::unordered_map<std::string, std::unique_ptr<Variable>> tabla;

public:
    // Inserta una variable con nombre, tipo y dirección.
    // Retorna  0 si se insertó correctamente.
    // Retorna -1 si el nombre ya existe (declaración duplicada).
    int insertar(const std::string& nombre, int tipo, int dir = -1);

    // Busca una variable por nombre.
    // Retorna pointer a la Variable, o nullptr si no existe.
    Variable* buscar(const std::string& nombre);

    // Imprime todas las variables de la tabla 
    void imprimir() const;
};

// Funcion, directorio de funciones
struct Funcion {
    std::string    nombre;        // nombre de la función
    int            tipoRetorno;   // TIPO_INT, TIPO_FLT o TIPO_NULA
    int            startQuad;     // índice del primer cuadruplo de la función (para referencia en llamadas)
    int            numParams;     // número de parámetros 
    TablaVariables locales;       // tabla de variables locales y parámetros
};

// Directorio de funciones, mapa hash con nombre (string) y un mapeo a la estructura funcion 
class DirectorioFunciones {
    // unique_ptr para estabilidad de punteros (igual que TablaVariables)
    std::unordered_map<std::string, std::unique_ptr<Funcion>> directorio;

public:
    // Registra una nueva función.
    // Retorna  0 si se insertó correctamente.
    // Retorna -1 si el nombre ya estaba registrado (función duplicada).
    int insertar(const std::string& nombre, int tipo);

    // Busca una función por nombre.
    // Retorna puntero a la Funcion, o nullptr si no existe.
    Funcion* buscar(const std::string& nombre);

    // Imprime el directorio completo con variables locales de cada función
    void imprimir() const;
};

// Pila IDs, acumula nombres de variables antes de conocer su tipo
class StackIDs {
    std::vector<std::string> datos;   // vector como pila (push_back / pop_back)

public:
    // Agrega un nombre a la pila
    void push(const std::string& nombre);

    // Desapila y retorna el identificador en el tope
    std::string pop();

    // Retorna true si la pila está vacía
    bool empty() const;
};

// Instancias globales para patito.y 
extern CuboSemantico       cuboSemantico;     // cubo semántico global
extern TablaVariables      tablaGlobal;       // tabla de variables globales
extern TablaVariables*     tablaActual;       // apunta a global o a locales
extern DirectorioFunciones dirFunciones;      // directorio de funciones
extern Funcion*            funcionActual;     // función que se está parseando
extern StackIDs            pilaIDs;           // IDs pendientes de declarar
