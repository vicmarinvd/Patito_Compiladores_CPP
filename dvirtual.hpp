#pragma once

/*
 * dvirtual.hpp
 *
 * Mapa de memoria:
 *   Segmento         Base    Límite  Capacidad
 *   Global  entero   1000    1999    1000 vars
 *   Global  flotante 2000    2999    1000 vars
 *   Local   entero   3000    3999    1000 vars/params
 *   Local   flotante 4000    4999    1000 vars/params
 *   Temp    entero   5000    5999    1000 temporales
 *   Temp    flotante 6000    6999    1000 temporales
 *   Const   entero   7000    7999    1000 constantes
 *   Const   flotante 8000    8999    1000 constantes
 *   Const   string   9000    9999    1000 constantes
 *
 *   Registros especiales de retorno:
 *   RET_INT  100   (entero de retorno de función)
 *   RET_FLT  101   (flotante de retorno de función)
 * ─────────────────────────────────────────────────────────────────────
 */

#include <string>
#include <unordered_map>
#include <iostream>

// bases y tamaños 
constexpr int BASE_GLOB_INT = 1000;   // variables globales enteras
constexpr int BASE_GLOB_FLT = 2000;   // variables globales flotantes
constexpr int BASE_LOC_INT  = 3000;   // variables locales enteras
constexpr int BASE_LOC_FLT  = 4000;   // variables locales flotantes
constexpr int BASE_TMP_INT  = 5000;   // temporales enteros
constexpr int BASE_TMP_FLT  = 6000;   // temporales flotantes
constexpr int BASE_CST_INT  = 7000;   // constantes enteras
constexpr int BASE_CST_FLT  = 8000;   // constantes flotantes
constexpr int BASE_CST_STR  = 9000;   // constantes string (letreros)
constexpr int SEG_SIZE      = 1000;   // capacidad de cada segmento

// Registros especiales para valor de retorno de funciones
constexpr int RET_INT = 100;
constexpr int RET_FLT = 101;


// Nodo para almacenar constantes registradas
struct NodoCte {
    std::string valor;   // representación textual de la constante
    int         tipo;    // TIPO_INT, TIPO_FLT o TIPO_NULA (string)
    int         dir;     // dirección virtual asignada
};

// Gestiona la asignación de memoria virtual y el pool de constantes.
class DirectorioVirtual {

    // Contadores de asignación por segmento 
    int cntGlobInt = 0, cntGlobFlt = 0;   // globales
    int cntLocInt  = 0, cntLocFlt  = 0;   // locales
    int cntTmpInt  = 0, cntTmpFlt  = 0;   // temporales
    int cntCstInt  = 0, cntCstFlt  = 0, cntCstStr = 0;  // constantes

    // Pool de constantes
    // Clave: "valor|tipo" - NodoCte  (evita duplicados)
    std::unordered_map<std::string, NodoCte> poolCtes;

    // Construye la clave única para buscar en el pool
    std::string clavePool(const std::string& valor, int tipo) const;

public:
    // Reinicia todos los contadores (llamar al inicio del programa)
    void init();

    // Asignación de direcciones 

    // Siguiente dirección libre en el segmento global del tipo dado
    int nextGlobalAddr(int tipo);

    // Siguiente dirección libre en el segmento local del tipo dado
    int nextLocalAddr(int tipo);

    // Siguiente dirección libre en el segmento de temporales del tipo dado
    int nextTempAddr(int tipo);

    // Busca la constante en el pool; si no existe la registra.
    // Retorna su dirección virtual (reutiliza si ya estaba registrada)
    int getConstAddr(const std::string& valor, int tipo);

    // Reset parcial

    // Reinicia contadores locales (al iniciar el análisis de una función)
    void resetLocalCounters();

    // Reinicia contadores de temporales (al iniciar función o cuerpo principal)
    void resetTempCounters();

    // Imprime el mapa de memoria con la ocupación actual de cada segmento
    void imprimirMapa() const;

    // Expone el pool de constantes a la MV para inicializar su memoria de constantes
    const std::unordered_map<std::string, NodoCte>& getPool() const { return poolCtes; }
};

//Instancia global
extern DirectorioVirtual dirVirtual;
