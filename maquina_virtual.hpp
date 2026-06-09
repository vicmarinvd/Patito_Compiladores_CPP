#pragma once

/*
 * maquina_virtual.hpp
 * ─────────────────────────────────────────────────────────────────────
 * Maquina Virtual (MV) del compilador Patito.
 * Interpreta la fila de cuadruplos generada por el compilador sobre
 * el mapa de memoria virtual definido en dvirtual.hpp.
 *
 * MAPA DE MEMORIA DE EJECUCION
 * ─────────────────────────────────────────────────────────────────────
 *  Segmento           Dir virtual    Estructura en la MV
 *  ─────────────────  ────────────   ─────────────────────────────────
 *  Global  entero     1000..1999     vector<int>    globInt
 *  Global  flotante   2000..2999     vector<float>  globFlt
 *  Local   entero     3000..3999     Frame::locInt  (por frame)
 *  Local   flotante   4000..4999     Frame::locFlt  (por frame)
 *  Temp    entero     5000..5999     Frame::tmpInt  (por frame)
 *  Temp    flotante   6000..6999     Frame::tmpFlt  (por frame)
 *  Const   entero     7000..7999     vector<int>    cstInt  (solo lectura)
 *  Const   flotante   8000..8999     vector<float>  cstFlt  (solo lectura)
 *  Const   string     9000..9999     vector<string> cstStr  (solo lectura)
 *  RET_INT            100            int  retInt
 *  RET_FLT            101            float retFlt
 *
 * PILA DE ACTIVACION
 * ─────────────────────────────────────────────────────────────────────
 *  Cada llamada a funcion (ERA/ARG/GOSUB) empuja un Frame con sus
 *  propios locales, temporales y direccion de retorno.
 *  ENDFUNC lo desapila y restaura el frame del caller.
 *
 * SECUENCIA DE LLAMADA A FUNCION
 * ─────────────────────────────────────────────────────────────────────
 *  ERA  func      → resetear frame de staging y buffer de args
 *  ARG  dir  idx  → guardar valor de 'dir' en argsBuffer[idx]
 *  GOSUB func Q   → copiar args a locales del frame segun paramDirs,
 *                   guardar retAddr = IP+1, saltar a cuadruplo Q
 *  RETURN src     → copiar valor a retInt o retFlt segun tipo
 *  ENDFUNC        → desapilar frame, IP = retAddr
 * ─────────────────────────────────────────────────────────────────────
 */

#include "cuadruplos.hpp"
#include "dvirtual.hpp"
#include "semantica.hpp"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

// FRAME DE ACTIVACION
// Se crea al llamar a una funcion y se destruye al retornar.
// Contiene memoria local + temporales independientes de otros frames.
struct Frame {
    vector<int>   locInt  = vector<int>  (SEG_SIZE, 0);    // locales enteros
    vector<float> locFlt  = vector<float>(SEG_SIZE, 0.0f); // locales flotantes
    vector<int>   tmpInt  = vector<int>  (SEG_SIZE, 0);    // temporales enteros
    vector<float> tmpFlt  = vector<float>(SEG_SIZE, 0.0f); // temporales flotantes
    int         retAddr  = 0;   // cuadruplo siguiente al GOSUB (donde volver)
    string funcName;       // nombre de la funcion (para mensajes de debug)
};

// BUFFER DE ARGUMENTOS (entre ERA y GOSUB)
// Guarda el valor y tipo de cada argumento antes de empujar el frame.
struct Argumento {
    bool  esFloat;   // true → usar valFlt; false → usar valInt
    int   valInt  = 0;
    float valFlt  = 0.0f;
};

// MAQUINA VIRTUAL
class MaquinaVirtual {

    // Memoria global (vive toda la ejecucion)
    vector<int>          globInt = vector<int>  (SEG_SIZE, 0);
    vector<float>        globFlt = vector<float>(SEG_SIZE, 0.0f);

    // Constantes (cargadas una vez al arrancar desde el pool del compilador)
    vector<int>          cstInt  = vector<int>  (SEG_SIZE, 0);
    vector<float>        cstFlt  = vector<float>(SEG_SIZE, 0.0f);
    vector<string>  cstStr  = vector<string>(SEG_SIZE);

    // Registros especiales de retorno de funcion
    int   retInt = 0;
    float retFlt = 0.0f;

    // Pila de frames (vector para acceder al tope con back() de forma estable)
    vector<Frame> callStack;
    Frame* frameActual = nullptr;   // puntero al frame del tope

    // Frame en preparacion entre ERA y GOSUB
    Frame              stagingFrame;
    vector<Argumento> argsBuffer;

    // Cuadruplos compilados (referencia, no copia)
    const vector<Cuadruplo>& quads;

    // Directorio de funciones (para obtener paramDirs en GOSUB)
    DirectorioFunciones& dirFunc;

    // Instruction Pointer
    int ip = 0;

    // Helpers de clasificacion
    bool  esFlt(int addr) const;

    // Lectura de memoria por direccion virtual
    int         getInt  (int addr) const;
    float       getFlt  (int addr) const;
    string getStr  (int addr) const;

    // Escritura de memoria por direccion virtual
    void setInt(int addr, int   val);
    void setFlt(int addr, float val);

    // Lectura con promocion/truncamiento para operaciones mixtas
    float getAsFloat(int addr) const;
    int   getAsInt  (int addr) const;

    // Convierte string de direccion a int; retorna -1 si es "_"
    int toAddr(const string& s) const;

    // Ejecuta un cuadruplo; retorna false para detener el ciclo
    bool ejecutarCuad(const Cuadruplo& q);

public:
    // Constructor: recibe cuadruplos y directorio de funciones
    MaquinaVirtual(const FilaCuadruplos& fila, DirectorioFunciones& df);

    // Carga el pool de constantes del compilador en cstInt/cstFlt/cstStr
    void cargarConstantes(const DirectorioVirtual& dv);

    // Inicia la ejecucion desde el cuadruplo 0
    void ejecutar();
};
