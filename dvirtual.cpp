/*
 * dvirtual.cpp
 * Implementación del DirectorioVirtual: gestiona el espacio de
 * direcciones virtuales y el pool de constantes del compilador Patito.
 */

#include "dvirtual.hpp"
#include "semantica.hpp" 
#include <stdexcept>
#include <sstream>
#include <iomanip>
using namespace std;

// instancia global
DirectorioVirtual dirVirtual;

// directorio virtual

// Genera una clave única para identificar constantes en el pool.
// Parametros: valor, tipo.
// Return: clave con formato "valor|tipo".
string DirectorioVirtual::clavePool(const string& valor, int tipo) const {
    return valor + "|" + to_string(tipo);
}

// init
// Reinicia contadores y limpia el pool de constantes.
// se llama antes de iniciar un nuevo programa
void DirectorioVirtual::init() {
    cntGlobInt = cntGlobFlt = 0;
    cntLocInt  = cntLocFlt  = 0;
    cntTmpInt  = cntTmpFlt  = 0;
    cntCstInt  = cntCstFlt  = cntCstStr = 0;
    poolCtes.clear();   // limpiar constantes de compilaciones anteriores
}

// Asigna la siguiente dirección disponible del segmento global.
// Parametros: tipo de dato.
// Return: dirección virtual asignada.
int DirectorioVirtual::nextGlobalAddr(int tipo) {
    if (tipo == TIPO_FLT) {
        if (cntGlobFlt >= SEG_SIZE) {
            cerr << "Error: segmento global FLT lleno\n";
            return -1;
        }
        return BASE_GLOB_FLT + cntGlobFlt++;   // asignar y avanzar contador
    }
    // Por defecto: entero
    if (cntGlobInt >= SEG_SIZE) {
        cerr << "Error: segmento global INT lleno\n";
        return -1;
    }
    return BASE_GLOB_INT + cntGlobInt++;
}

// Asigna la siguiente dirección disponible del segmento local.
// Parametros: tipo de dato.
// Return: dirección virtual asignada.
int DirectorioVirtual::nextLocalAddr(int tipo) {
    if (tipo == TIPO_FLT) {
        if (cntLocFlt >= SEG_SIZE) {
            cerr << "Error: segmento local FLT lleno\n";
            return -1;
        }
        return BASE_LOC_FLT + cntLocFlt++;
    }
    if (cntLocInt >= SEG_SIZE) {
        cerr << "Error: segmento local INT lleno\n";
        return -1;
    }
    return BASE_LOC_INT + cntLocInt++;
}

// Asigna la siguiente dirección disponible del segmento temporal.
// Parametros: tipo de dato.
// Return: dirección virtual asignada.
// se reinicia con resetTempCounters() al iniciar una función o el main, los temporales no persisten entre llamadas
int DirectorioVirtual::nextTempAddr(int tipo) {
    if (tipo == TIPO_FLT) {
        if (cntTmpFlt >= SEG_SIZE) {
            cerr << "Error: segmento temporal FLT lleno\n";
            return -1;
        }
        return BASE_TMP_FLT + cntTmpFlt++;
    }
    if (cntTmpInt >= SEG_SIZE) {
        cerr << "Error: segmento temporal INT lleno\n";
        return -1;
    }
    return BASE_TMP_INT + cntTmpInt++;
}

// Reinicia los contadores de variables locales.
// permite reutilizar el espacio de direcciones para cada funcion
void DirectorioVirtual::resetLocalCounters() {
    cntLocInt = 0;
    cntLocFlt = 0;
}


//Reinicia los contadores de variables temporales.
// los temporales no persisten entre llamadas
void DirectorioVirtual::resetTempCounters() {
    cntTmpInt = 0;
    cntTmpFlt = 0;
}

// Obtiene la dirección de una constante; si ya existe, la reutiliza.
// Parametros: valor, tipo.
// Return: dirección virtual de la constante.
int DirectorioVirtual::getConstAddr(const string& valor, int tipo) {
    string clave = clavePool(valor, tipo);

    // Buscar si ya existe en el pool
    auto it = poolCtes.find(clave);
    if (it != poolCtes.end()) return it->second.dir;  // reutilizar dirección

    // Crear nueva entrada en el pool
    NodoCte nuevo;
    nuevo.valor = valor;
    nuevo.tipo  = tipo;

    // Asignar dirección según el tipo de la constante
    if (tipo == TIPO_FLT) {
        nuevo.dir = BASE_CST_FLT + cntCstFlt++;
    } else if (tipo == TIPO_NULA) {
        // TIPO_NULA se usa para strings / letreros en escribe(...)
        nuevo.dir = BASE_CST_STR + cntCstStr++;
    } else {
        // Entero por defecto
        nuevo.dir = BASE_CST_INT + cntCstInt++;
    }

    poolCtes[clave] = nuevo;
    return nuevo.dir;
}


// Muestra una tabla con la base, límite y cantidad de direcciones
// usadas en cada segmento del mapa de memoria virtual.
void DirectorioVirtual::imprimirMapa() const {
    cout << "\n---- MAPA DE MEMORIA VIRTUAL ----------\n";
    cout << "  Segmento           Base   Límite  Usadas\n";
    cout << "  ─────────────────  ─────  ──────  ──────\n";

    // Lambda auxiliar para imprimir una fila formateada
    auto fila = [](const string& nombre, int base, int usado) {
        cout << "  " << left  << setw(17) << nombre
                  << "  " << right << setw(5)  << base
                  << "  " << setw(6) << (base + SEG_SIZE - 1)
                  << "  " << setw(6) << usado << "\n";
    };

    fila("Global entero",   BASE_GLOB_INT, cntGlobInt);
    fila("Global flotante", BASE_GLOB_FLT, cntGlobFlt);
    fila("Local  entero",   BASE_LOC_INT,  cntLocInt);
    fila("Local  flotante", BASE_LOC_FLT,  cntLocFlt);
    fila("Temp   entero",   BASE_TMP_INT,  cntTmpInt);
    fila("Temp   flotante", BASE_TMP_FLT,  cntTmpFlt);
    fila("Const  entero",   BASE_CST_INT,  cntCstInt);
    fila("Const  flotante", BASE_CST_FLT,  cntCstFlt);
    fila("Const  string",   BASE_CST_STR,  cntCstStr);

    // Registros especiales de retorno (no son segmentos, solo referencias fijas)
    cout << "\n  Registro RET_INT : " << RET_INT << "  (retorno entero de función)\n";
    cout << "  Registro RET_FLT : " << RET_FLT << "  (retorno flotante de función)\n";
    cout << "------------------------------------------\n\n";
}
