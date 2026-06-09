#pragma once

/*
 * cuadruplos.hpp
 *
 * Módulos:
 *   - Cuadruplo       : estructura de código de tres direcciones
 *   - Pila<T>         : pila (template) para operandos, tipos, etc.
 *   - FilaCuadruplos  : lista de cuadruplos generados (vector indexado)
 *   - GeneradorCuad   : agrupa todas las pilas y la fila; lógica de generación
 * ─────────────────────────────────────────────────────────────────────
 */

#include "semantica.hpp"
#include "dvirtual.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;


// cuadruplo (op, arg1, arg2, resultado)
// argumentos son direcciones virtuales (tipo string)
// resultado puede ser dirección virtual, etiqueta de salto (número de cuadruplo) o "_"
struct Cuadruplo {
    string op;       // operador o instrucción ("+", "=", "GOSUB", ...)
    string arg1;     // primer operando (dirección virtual o "_")
    string arg2;     // segundo operando (dirección virtual o "_")
    string result;   // resultado (dirección destino, etiqueta de salto o "_")
};



//template de pila, se usa para PilaOperandos, PilaTipos, PilaOperadores, PilaJumps
template<typename T>
class Pila {
    vector<T> datos;     // almacenamiento interno (crece dinámicamente)
    string    nombre;    // nombre descriptivo para mensajes de error

public:
    // constructor, recibe el nombre de la pila para mensajes 
    explicit Pila(const string& nombre = "Pila") : nombre(nombre) {}

    //añade un elemento
    void push(const T& val) {
        datos.push_back(val);
    }

    // quita un elemento y retorna el del tope
    T pop() {
        if (datos.empty()) {
            cerr << nombre << ": underflow (pop en pila vacía)\n";
            return T{};
        }
        T val = datos.back();
        datos.pop_back();
        return val;
    }

    //retorna el top sin eliminarlo
    T top() const {
        if (datos.empty()) {
            cerr << nombre << ": top en pila vacía\n";
            return T{};
        }
        return datos.back();
    }

    // indica si la pila no tiene elementos
    bool empty() const { return datos.empty(); }

    // número de elementos en la pila
    int size() const { return static_cast<int>(datos.size()); }
};

// Fila de cuadruplos
// los cuadruplos se almacenan en un vector por indice
// se utiliza para fillJump y poder modificar el campo de result de un goto cuando aun no se conoce
class FilaCuadruplos {
    vector<Cuadruplo> cuads;   // vector indexado de cuadruplos

public:
    // Agrega un nuevo cuadruplo al final de la lista
    void encolar(const string& op,
                 const string& arg1,
                 const string& arg2,
                 const string& result);

    // Rellena el campo 'result' de un cuadruplo ya generado.
    // Se usa para completar GOTOs y GOTOFs cuyo destino se conoce después.
    void fillJump(int quadIdx, int dest);

    // Número de cuadruplos generados hasta ahora (sirve como "siguiente índice")
    int count() const;

    // Imprime todos los cuadruplos en formato tabular
    void imprimir() const;

    // Acceso de solo lectura al vector de cuadruplos (para la MV)
    const vector<Cuadruplo>& getCuads() const { return cuads; }
};

// Generador de cuadruplos
// Encapsula todas las pilas y fila de cuadruplos, se genera aqui
class GeneradorCuad {

public:
    //Pilas 
    Pila<string> pilaOperandos;    // direcciones virtuales de operandos
    Pila<int>         pilaTipos;        // tipo de cada operando en pilaOperandos
    Pila<string> pilaOperadores;   // operadores pendientes de procesar
    Pila<int>         pilaJumps;        // índices de cuadruplos con salto pendiente

    //Lista de cuadruplos generados
    FilaCuadruplos    fila;

    //Estado de llamada a función
    int         contadorArgs  = 0;    // número de argumentos pasados en la llamada actual
    string funcCallBuf;          // nombre de la función llamada (para ERA/GOSUB)
    int         lastAssignedDir = -1; // última dirección asignada (para generar RETURN)

    // Constructor: inicializa las pilas con nombres descriptivos
    GeneradorCuad()
        : pilaOperandos("PilaOperandos"),
          pilaTipos("PilaTipos"),
          pilaOperadores("PilaOperadores"),
          pilaJumps("PilaJumps") {}

    // Generación de cuadruplos 

    // Encola un cuadruplo (wrapper directo a FilaCuadruplos::encolar)
    void generar(const string& op,
                 const string& arg1,
                 const string& arg2,
                 const string& result);

    // Crea un temporal del tipo dado y retorna su dirección virtual como string
    string nuevoTemp(int tipo);

    // Busca el tipo de una variable (primero en locales, luego en globales)
    int getTipoVar(const string& nombre);

    // Busca la dirección virtual de una variable (locales antes que globales)
    int getDirVar(const string& nombre);
};

// Instancia Global
extern GeneradorCuad gen;
