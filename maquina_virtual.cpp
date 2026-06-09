/*
 * maquina_virtual.cpp
 * Implementacion de la Maquina Virtual del compilador Patito.
 * Interpreta cada cuadruplo operando sobre el mapa de memoria virtual.
 */

#include "maquina_virtual.hpp"
#include <iomanip>
#include <cstdlib>   // stoi, stof
using namespace std;

// CONSTRUCTOR
// Guarda referencias a los cuadruplos y al directorio de funciones.
// Empuja el frame del cuerpo principal (main) para que los temporales
// del cuerpo global tengan donde almacenarse.
MaquinaVirtual::MaquinaVirtual(const FilaCuadruplos& fila, DirectorioFunciones& df)
    : quads(fila.getCuads()), dirFunc(df)
{
    // Frame sintetico del cuerpo principal: sus temps usan este frame
    callStack.push_back(Frame{});
    callStack.back().funcName = "__main__";
    frameActual = &callStack.back();
}

// cargarConstantes
// Lee el pool de constantes del compilador y llena cstInt/cstFlt/cstStr.
// Debe llamarse ANTES de ejecutar() para que las constantes esten listas.
void MaquinaVirtual::cargarConstantes(const DirectorioVirtual& dv) {
    for (const auto& [clave, nodo] : dv.getPool()) {
        if (nodo.tipo == TIPO_FLT) {
            // Constante flotante
            int idx = nodo.dir - BASE_CST_FLT;
            if (idx >= 0 && idx < SEG_SIZE)
                cstFlt[idx] = stof(nodo.valor);

        } else if (nodo.tipo == TIPO_NULA) {
            // String literal: quitar las comillas incluidas por el lexer
            int idx = nodo.dir - BASE_CST_STR;
            string s = nodo.valor;
            if (s.size() >= 2 && s.front() == '"' && s.back() == '"')
                s = s.substr(1, s.size() - 2);
            if (idx >= 0 && idx < SEG_SIZE)
                cstStr[idx] = s;

        } else {
            // Constante entera
            int idx = nodo.dir - BASE_CST_INT;
            if (idx >= 0 && idx < SEG_SIZE)
                cstInt[idx] = stoi(nodo.valor);
        }
    }
}

// HELPERS DE CLASIFICACION Y ACCESO A MEMORIA

// Retorna true si la direccion virtual pertenece a un segmento flotante
bool MaquinaVirtual::esFlt(int addr) const {
    return (addr >= BASE_GLOB_FLT && addr < BASE_GLOB_FLT + SEG_SIZE) ||
           (addr >= BASE_LOC_FLT  && addr < BASE_LOC_FLT  + SEG_SIZE) ||
           (addr >= BASE_TMP_FLT  && addr < BASE_TMP_FLT  + SEG_SIZE) ||
           (addr >= BASE_CST_FLT  && addr < BASE_CST_FLT  + SEG_SIZE) ||
           addr == RET_FLT;
}

// Convierte un string de cuadruplo a direccion virtual entera.
// Retorna -1 si es "_", vacio, o un nombre de funcion (no numerico).
// Algunos cuadruplos como ERA y GOSUB usan arg1 como nombre de funcion,
// no como direccion; en esos casos toAddr devuelve -1 sin fallar.
int MaquinaVirtual::toAddr(const string& s) const {
    if (s.empty() || s == "_") return -1;
    // Verificar que el string sea un numero (puede tener signo negativo)
    const char* p = s.c_str();
    if (*p == '-') p++;
    if (!*p) return -1;
    while (*p) {
        if (!isdigit((unsigned char)*p)) return -1;  // es un nombre, no una dir
        p++;
    }
    return stoi(s);
}

// Lee un entero desde la direccion virtual dada
int MaquinaVirtual::getInt(int addr) const {
    if (addr == RET_INT)
        return retInt;
    if (addr >= BASE_GLOB_INT && addr < BASE_GLOB_INT + SEG_SIZE)
        return globInt[addr - BASE_GLOB_INT];
    if (addr >= BASE_LOC_INT  && addr < BASE_LOC_INT  + SEG_SIZE)
        return frameActual->locInt[addr - BASE_LOC_INT];
    if (addr >= BASE_TMP_INT  && addr < BASE_TMP_INT  + SEG_SIZE)
        return frameActual->tmpInt[addr - BASE_TMP_INT];
    if (addr >= BASE_CST_INT  && addr < BASE_CST_INT  + SEG_SIZE)
        return cstInt[addr - BASE_CST_INT];
    cerr << "MV getInt: dir invalida " << addr << "\n";
    return 0;
}

// Lee un flotante desde la direccion virtual dada
float MaquinaVirtual::getFlt(int addr) const {
    if (addr == RET_FLT)
        return retFlt;
    if (addr >= BASE_GLOB_FLT && addr < BASE_GLOB_FLT + SEG_SIZE)
        return globFlt[addr - BASE_GLOB_FLT];
    if (addr >= BASE_LOC_FLT  && addr < BASE_LOC_FLT  + SEG_SIZE)
        return frameActual->locFlt[addr - BASE_LOC_FLT];
    if (addr >= BASE_TMP_FLT  && addr < BASE_TMP_FLT  + SEG_SIZE)
        return frameActual->tmpFlt[addr - BASE_TMP_FLT];
    if (addr >= BASE_CST_FLT  && addr < BASE_CST_FLT  + SEG_SIZE)
        return cstFlt[addr - BASE_CST_FLT];
    cerr << "MV getFlt: dir invalida " << addr << "\n";
    return 0.0f;
}

// Lee un string desde el segmento de constantes
string MaquinaVirtual::getStr(int addr) const {
    if (addr >= BASE_CST_STR && addr < BASE_CST_STR + SEG_SIZE)
        return cstStr[addr - BASE_CST_STR];
    cerr << "MV getStr: dir invalida " << addr << "\n";
    return "";
}

// Escribe un entero en la direccion virtual dada
void MaquinaVirtual::setInt(int addr, int val) {
    if (addr == RET_INT)
        { retInt = val; return; }
    if (addr >= BASE_GLOB_INT && addr < BASE_GLOB_INT + SEG_SIZE)
        { globInt[addr - BASE_GLOB_INT] = val; return; }
    if (addr >= BASE_LOC_INT  && addr < BASE_LOC_INT  + SEG_SIZE)
        { frameActual->locInt[addr - BASE_LOC_INT]  = val; return; }
    if (addr >= BASE_TMP_INT  && addr < BASE_TMP_INT  + SEG_SIZE)
        { frameActual->tmpInt[addr - BASE_TMP_INT]  = val; return; }
    cerr << "MV setInt: dir invalida " << addr << "\n";
}

// Escribe un flotante en la direccion virtual dada
void MaquinaVirtual::setFlt(int addr, float val) {
    if (addr == RET_FLT)
        { retFlt = val; return; }
    if (addr >= BASE_GLOB_FLT && addr < BASE_GLOB_FLT + SEG_SIZE)
        { globFlt[addr - BASE_GLOB_FLT] = val; return; }
    if (addr >= BASE_LOC_FLT  && addr < BASE_LOC_FLT  + SEG_SIZE)
        { frameActual->locFlt[addr - BASE_LOC_FLT]  = val; return; }
    if (addr >= BASE_TMP_FLT  && addr < BASE_TMP_FLT  + SEG_SIZE)
        { frameActual->tmpFlt[addr - BASE_TMP_FLT]  = val; return; }
    cerr << "MV setFlt: dir invalida " << addr << "\n";
}

// Devuelve el valor en addr como float (promueve int si es necesario)
float MaquinaVirtual::getAsFloat(int addr) const {
    return esFlt(addr) ? getFlt(addr) : static_cast<float>(getInt(addr));
}

// Devuelve el valor en addr como int (trunca float si es necesario)
int MaquinaVirtual::getAsInt(int addr) const {
    return esFlt(addr) ? static_cast<int>(getFlt(addr)) : getInt(addr);
}

// EJECUTAR UN CUADRUPLO
bool MaquinaVirtual::ejecutarCuad(const Cuadruplo& q) {

    const string& op = q.op;

    // Convertir strings de argumento a direcciones virtuales
    int a1  = toAddr(q.arg1);
    int a2  = toAddr(q.arg2);
    int res = toAddr(q.result);

    // ── GOTO: salto incondicional ─────────────────────────────────────
    if (op == "GOTO") {
        ip = stoi(q.result) - 1;  // -1 porque el ciclo hace ip++ al final
        return true;
    }

    // ── GOTOF: salto si la condicion es falsa (==0) ───────────────────
    if (op == "GOTOF") {
        if (getAsInt(a1) == 0)
            ip = stoi(q.result) - 1;
        return true;
    }

    // ── ASIGNACION: result = arg1 ─────────────────────────────────────
    if (op == "=") {
        if (esFlt(res))
            setFlt(res, getAsFloat(a1));   // int→float si hace falta
        else
            setInt(res, getAsInt(a1));     // float→int si hace falta
        return true;
    }

    // ── SUMA ──────────────────────────────────────────────────────────
    if (op == "+") {
        if (esFlt(res)) setFlt(res, getAsFloat(a1) + getAsFloat(a2));
        else            setInt(res, getInt(a1)      + getInt(a2));
        return true;
    }

    // ── RESTA ─────────────────────────────────────────────────────────
    if (op == "-") {
        if (esFlt(res)) setFlt(res, getAsFloat(a1) - getAsFloat(a2));
        else            setInt(res, getInt(a1)      - getInt(a2));
        return true;
    }

    // ── MULTIPLICACION ────────────────────────────────────────────────
    if (op == "*") {
        if (esFlt(res)) setFlt(res, getAsFloat(a1) * getAsFloat(a2));
        else            setInt(res, getInt(a1)      * getInt(a2));
        return true;
    }

    // ── DIVISION (resultado siempre float) ────────────────────────────
    if (op == "/") {
        float div = getAsFloat(a2);
        if (div == 0.0f) { cerr << "MV: division por cero\n"; return true; }
        setFlt(res, getAsFloat(a1) / div);
        return true;
    }

    // ── NEGACION UNARIA ───────────────────────────────────────────────
    if (op == "UMINUS") {
        if (esFlt(res)) setFlt(res, -getAsFloat(a1));
        else            setInt(res, -getInt(a1));
        return true;
    }

    // ── RELACIONALES (resultado siempre entero: 1=verdad, 0=falso) ────
    if (op == ">")  { setInt(res, getAsFloat(a1) >  getAsFloat(a2) ? 1 : 0); return true; }
    if (op == "<")  { setInt(res, getAsFloat(a1) <  getAsFloat(a2) ? 1 : 0); return true; }
    if (op == "==") { setInt(res, getAsFloat(a1) == getAsFloat(a2) ? 1 : 0); return true; }
    if (op == "!=") { setInt(res, getAsFloat(a1) != getAsFloat(a2) ? 1 : 0); return true; }

    // ── PRINT: imprimir el valor en arg1 ─────────────────────────────
    if (op == "PRINT") {
        if (a1 >= BASE_CST_STR && a1 < BASE_CST_STR + SEG_SIZE) {
            // String literal
            cout << getStr(a1);
        } else if (esFlt(a1)) {
            cout << getFlt(a1);
        } else {
            cout << getInt(a1);
        }
        cout << " ";
        return true;
    }

    // ── ERA: preparar frame de staging para la llamada ────────────────
    if (op == "ERA") {
        stagingFrame = Frame{};
        stagingFrame.funcName = q.arg1;
        argsBuffer.clear();
        return true;
    }

    // ── ARG: guardar un argumento en el buffer ────────────────────────
    // arg1 = direccion del valor, arg2 = indice del argumento (0,1,2...)
    if (op == "ARG") {
        int idx = stoi(q.arg2);
        if (idx >= static_cast<int>(argsBuffer.size()))
            argsBuffer.resize(idx + 1);

        Argumento arg;
        arg.esFloat = esFlt(a1);
        if (arg.esFloat) arg.valFlt = getFlt(a1);
        else             arg.valInt = getInt(a1);
        argsBuffer[idx] = arg;
        return true;
    }

    // ── GOSUB: saltar a la funcion ────────────────────────────────────
    // 1. Copiar cada arg al local del parametro correspondiente (por paramDirs)
    // 2. Guardar retAddr en el frame
    // 3. Empujar el frame y saltar al primer cuadruplo de la funcion
    if (op == "GOSUB") {
        Funcion* f = dirFunc.buscar(q.arg1);
        if (!f) {
            cerr << "MV: funcion no encontrada '" << q.arg1 << "'\n";
            return true;
        }

        // Copiar argumentos a la memoria local del staging frame
        for (int i = 0; i < static_cast<int>(argsBuffer.size()) &&
                        i < static_cast<int>(f->paramDirs.size()); i++) {
            int pDir = f->paramDirs[i];
            const Argumento& arg = argsBuffer[i];

            if (esFlt(pDir)) {
                // Parametro flotante
                stagingFrame.locFlt[pDir - BASE_LOC_FLT] =
                    arg.esFloat ? arg.valFlt : static_cast<float>(arg.valInt);
            } else {
                // Parametro entero
                stagingFrame.locInt[pDir - BASE_LOC_INT] =
                    arg.esFloat ? static_cast<int>(arg.valFlt) : arg.valInt;
            }
        }

        stagingFrame.retAddr = ip + 1;   // donde volver cuando la funcion retorne

        // Empujar el frame y actualizar el puntero activo
        callStack.push_back(move(stagingFrame));
        frameActual = &callStack.back();

        // Saltar al primer cuadruplo de la funcion
        ip = stoi(q.arg2) - 1;
        return true;
    }

    // ── RETURN: guardar el valor de retorno en el registro especial ───
    // La ejecucion continua hasta ENDFUNC que le sigue
    if (op == "RETURN") {
        if (esFlt(a1)) retFlt = getFlt(a1);
        else           retInt = getInt(a1);
        return true;
    }

    // ── ENDFUNC: desapilar frame y volver al caller ───────────────────
    if (op == "ENDFUNC") {
        int retAddr = frameActual->retAddr;
        callStack.pop_back();

        if (callStack.empty()) {
            cerr << "MV: ENDFUNC con pila vacia\n";
            return false;
        }

        frameActual = &callStack.back();
        ip = retAddr - 1;   // -1 porque el ciclo hace ip++
        return true;
    }

    cerr << "MV: opcode desconocido '" << op << "' en cuadruplo " << ip << "\n";
    return true;
}

// EJECUTAR
// Ciclo principal: ejecuta cuadruplos desde ip=0 hasta el final.
void MaquinaVirtual::ejecutar() {
    ip = 0;
    int total = static_cast<int>(quads.size());

    while (ip < total) {
        bool continuar = ejecutarCuad(quads[ip]);
        if (!continuar) break;
        ip++;
    }

    // Nueva linea al terminar la salida de escribe(...)
    cout << "\n";
}
