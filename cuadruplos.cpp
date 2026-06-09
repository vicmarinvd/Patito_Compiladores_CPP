/*
 * cuadruplos.cpp
 * Implementación de FilaCuadruplos y GeneradorCuad.
 */

#include "cuadruplos.hpp"
#include <sstream>
using namespace std;


// Instancia global
GeneradorCuad gen;

// Fila de cuadruplos

// Agrega un nuevo cuadruplo al final de la lista.
// El índice del cuadruplo es igual a su posición en el vector (base 0).
void FilaCuadruplos::encolar(const string& op,
                             const string& arg1,
                             const string& arg2,
                             const string& result) {
    cuads.push_back({op, arg1, arg2, result});
}

// regresa para rellenar el campo resultado cuando un cuadruplo ya se genero
// se usa para GOTO y GOTOF con destino desconocido ???, y posterior ya se sabe a donde saltar/
// parametros : indice del cuad a modificar, indice al destino de salto.
void FilaCuadruplos::fillJump(int quadIdx, int dest) {
    // Verificar que el índice sea válido
    if (quadIdx < 0 || quadIdx >= static_cast<int>(cuads.size())) {
        cerr << "fillJump: cuadruplo " << quadIdx << " fuera de rango\n";
        return;
    }
    cuads[quadIdx].result = to_string(dest);
}

// Retorna el número de cuadruplos generados hasta ahora.
// También equivale al índice que tendrá el PRÓXIMO cuadruplo.
int FilaCuadruplos::count() const {
    return static_cast<int>(cuads.size());
}

// Muestra todos los cuadruplos en una tabla formateada.
void FilaCuadruplos::imprimir() const {
    cout << "\n── FILA DE CUADRUPLOS (" << cuads.size() << ") ─────────────────────────\n";
    cout << "  " << left
              << setw(4)  << "Num"
              << "  " << setw(8)  << "Op"
              << "  " << setw(20) << "Arg1"
              << "  " << setw(20) << "Arg2"
              << "  " << setw(20) << "Resultado"
              << "\n";
    cout << "  " << string(4,'-')
              << "  " << string(8,'-')
              << "  " << string(20,'-')
              << "  " << string(20,'-')
              << "  " << string(20,'-') << "\n";

    for (int i = 0; i < static_cast<int>(cuads.size()); i++) {
        const Cuadruplo& q = cuads[i];
        cout << "  " << left
                  << setw(4)  << i
                  << "  " << setw(8)  << q.op
                  << "  " << setw(20) << q.arg1
                  << "  " << setw(20) << q.arg2
                  << "  " << setw(20) << q.result
                  << "\n";
    }
    cout << "───────────────────────────────────────────────────\n\n";
}

// Generador de cuadruplos

// encola un cuadruplo en la fila, se usa desde las acciones semanticas del parser.
void GeneradorCuad::generar(const string& op,
                            const string& arg1,
                            const string& arg2,
                            const string& result) {
    fila.encolar(op, arg1, arg2, result);
}


// Solicita una nueva dirección temporal al directorio virtual según el tipo,
// y la retorna como string para usarla directamente en un cuadruplo.
// parametros: tipo y retorna dir virtual
string GeneradorCuad::nuevoTemp(int tipo) {
    int addr = dirVirtual.nextTempAddr(tipo);
    return to_string(addr);
}

// Busca el tipo de una variable.
// Primero busca en el scope local (si hay una función activa),
// y si no la encuentra, busca en el scope global.
// parametro: nombre de la variable, retorna tipo o err
int GeneradorCuad::getTipoVar(const string& nombre) {
    // Intentar en el scope local primero
    if (funcionActual) {
        Variable* v = funcionActual->locales.buscar(nombre);
        if (v) return v->tipo;
    }
    // Caer al scope global
    Variable* v = tablaGlobal.buscar(nombre);
    return v ? v->tipo : TIPO_ERR;
}

// Busca la dirección virtual de una variable con las mismas reglas
// de scoping que getTipoVar (local antes que global).
// parametro: id/nombre de la variable, retorna la dir virtual.
int GeneradorCuad::getDirVar(const string& nombre) {
    // Buscar en scope local
    if (funcionActual) {
        Variable* v = funcionActual->locales.buscar(nombre);
        if (v) return v->dir;
    }
    // Buscar en scope global
    Variable* v = tablaGlobal.buscar(nombre);
    return v ? v->dir : -1;
}
