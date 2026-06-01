/*
 * semantica.cpp
 */

#include "semantica.hpp"

//Instancias globales

CuboSemantico       cuboSemantico;            // inicializado en su constructor
TablaVariables      tablaGlobal;              // variables del scope global
TablaVariables*     tablaActual   = nullptr;  // scope activo (global o local)
DirectorioFunciones dirFunciones;             // registro de todas las funciones
Funcion*            funcionActual = nullptr;  // función que se está procesando
StackIDs            pilaIDs;                  // IDs acumulados en declaraciones


// convierte el enum del Tipo a una cadena (tipo) para errores
std::string tipoToString(int tipo) {
    switch (tipo) {
        case TIPO_INT:  return "entero";
        case TIPO_FLT:  return "flotante";
        case TIPO_NULA: return "nula";
        default:        return "error";
    }
}

// Cubo semantico

 //Constructor, inicia con todos TIPO_ERR y luego se llenan con las validas
CuboSemantico::CuboSemantico() {

    // Inicializar todo como error por defecto
    for (int i = 0; i < NUM_TYPES; i++)
        for (int j = 0; j < NUM_TYPES; j++)
            for (int k = 0; k < NUM_OPS; k++)
                cubo[i][j][k] = TIPO_ERR;

    // Suma (+): entero+entero=entero, cualquier combinación con float = float
    cubo[TIPO_INT][TIPO_INT][OP_ADD] = TIPO_INT;
    cubo[TIPO_INT][TIPO_FLT][OP_ADD] = TIPO_FLT;
    cubo[TIPO_FLT][TIPO_INT][OP_ADD] = TIPO_FLT;
    cubo[TIPO_FLT][TIPO_FLT][OP_ADD] = TIPO_FLT;

    // Resta (-): mismas reglas que la suma
    cubo[TIPO_INT][TIPO_INT][OP_SUB] = TIPO_INT;
    cubo[TIPO_INT][TIPO_FLT][OP_SUB] = TIPO_FLT;
    cubo[TIPO_FLT][TIPO_INT][OP_SUB] = TIPO_FLT;
    cubo[TIPO_FLT][TIPO_FLT][OP_SUB] = TIPO_FLT;

    // Multiplicación (*): mismas reglas que la suma
    cubo[TIPO_INT][TIPO_INT][OP_MUL] = TIPO_INT;
    cubo[TIPO_INT][TIPO_FLT][OP_MUL] = TIPO_FLT;
    cubo[TIPO_FLT][TIPO_INT][OP_MUL] = TIPO_FLT;
    cubo[TIPO_FLT][TIPO_FLT][OP_MUL] = TIPO_FLT;

    // División (/): siempre produce flotante 
    cubo[TIPO_INT][TIPO_INT][OP_DIV] = TIPO_FLT;
    cubo[TIPO_INT][TIPO_FLT][OP_DIV] = TIPO_FLT;
    cubo[TIPO_FLT][TIPO_INT][OP_DIV] = TIPO_FLT;
    cubo[TIPO_FLT][TIPO_FLT][OP_DIV] = TIPO_FLT;

    // Operadores relacionales: resultado siempre es entero (0=falso, 1=verdadero)
    cubo[TIPO_INT][TIPO_INT][OP_GT]  = TIPO_INT;
    cubo[TIPO_INT][TIPO_INT][OP_LT]  = TIPO_INT;
    cubo[TIPO_INT][TIPO_INT][OP_EQ]  = TIPO_INT;
    cubo[TIPO_INT][TIPO_INT][OP_NEQ] = TIPO_INT;

    cubo[TIPO_FLT][TIPO_FLT][OP_GT]  = TIPO_INT;
    cubo[TIPO_FLT][TIPO_FLT][OP_LT]  = TIPO_INT;
    cubo[TIPO_FLT][TIPO_FLT][OP_EQ]  = TIPO_INT;
    cubo[TIPO_FLT][TIPO_FLT][OP_NEQ] = TIPO_INT;

    // Comparación mixta (solo > y <)
    cubo[TIPO_INT][TIPO_FLT][OP_GT] = TIPO_INT;
    cubo[TIPO_INT][TIPO_FLT][OP_LT] = TIPO_INT;
    cubo[TIPO_FLT][TIPO_INT][OP_GT] = TIPO_INT;
    cubo[TIPO_FLT][TIPO_INT][OP_LT] = TIPO_INT;

    // Asignación (=): compatible si es mismo tipo, o si se asigna int a float
    cubo[TIPO_INT][TIPO_INT][OP_ASG] = TIPO_INT;   // entero = entero
    cubo[TIPO_FLT][TIPO_FLT][OP_ASG] = TIPO_FLT;   // flotante = flotante
    cubo[TIPO_FLT][TIPO_INT][OP_ASG] = TIPO_FLT;   // flotante = entero (conversión)
}

 // Consulta , retorna el tipo de resultado, tipo_err si es invalida
int CuboSemantico::consultar(int izq, int der, int op) const {
    // Verificar que los índices estén dentro de rango antes de acceder
    if (izq < 0 || izq >= NUM_TYPES ||
        der < 0 || der >= NUM_TYPES ||
        op  < 0 || op  >= NUM_OPS)
        return TIPO_ERR;
    return cubo[izq][der][op];
}

// Tabla de variables

// inserta, registra una nueva variable a la tabla, el unique_ptr asegura que la dir de mem de Variable no cambie
// retorna 0 si se inserta correctamente, -1 si ya existia (declaracion duplicada)
// si dir es -1, se asignará después (en la etapa de generación de código)
int TablaVariables::insertar(const std::string& nombre, int tipo, int dir) {
    // Si ya existe, no se puede redeclarar
    if (tabla.count(nombre)) return -1;

    // Crear la Variable en heap y guardar su unique_ptr
    tabla[nombre] = std::make_unique<Variable>(Variable{nombre, tipo, dir});
    return 0;
}

// busca una variable por su nombre y retorna el pointer a Variable
Variable* TablaVariables::buscar(const std::string& nombre) {
    auto it = tabla.find(nombre);
    return (it != tabla.end()) ? it->second.get() : nullptr;
}

// print todas las variables de la tabla con tipo y direccion
void TablaVariables::imprimir() const {
    for (const auto& [nombre, varPtr] : tabla) {
        std::cout << "    " << varPtr->nombre
                  << " : " << tipoToString(varPtr->tipo)
                  << " (dir=" << varPtr->dir << ")\n";
    }
}

// Directorio de Funciones

// inserta una nueva funcion, inicializa con startQuad = 0, numParams = 0  y tabla local vacia
// retorna 0 si exito y -1 si ya existe
int DirectorioFunciones::insertar(const std::string& nombre, int tipo) {
    if (directorio.count(nombre)) return -1;  // función duplicada

    // Construir la Funcion en heap con un unique_ptr
    auto f = std::make_unique<Funcion>();
    f->nombre      = nombre;
    f->tipoRetorno = tipo;
    f->startQuad   = 0;
    f->numParams   = 0;
    // locales se inicializa por default (mapa vacío)

    directorio[nombre] = std::move(f);
    return 0;
}

// busca una funcion por nombre, retorna un pointer a la Funcion
Funcion* DirectorioFunciones::buscar(const std::string& nombre) {
    auto it = directorio.find(nombre);
    return (it != directorio.end()) ? it->second.get() : nullptr;
}

//print directorio de funciones, da el directorio con los parametros y variables locales de cada funcion
void DirectorioFunciones::imprimir() const {
    std::cout << "\n── DIRECTORIO DE FUNCIONES ──────────────────────────\n";
    for (const auto& [nombre, fPtr] : directorio) {
        std::cout << "\n  Función : " << fPtr->nombre << "\n";
        std::cout << "  Retorno : " << tipoToString(fPtr->tipoRetorno) << "\n";
        std::cout << "  Params  : " << fPtr->numParams << "\n";
        std::cout << "  StartQ  : " << fPtr->startQuad << "\n";
        std::cout << "  Variables locales:\n";
        fPtr->locales.imprimir();
    }
    std::cout << "────────────────────────────────────────────────────\n";
}

// Pila IDs
//push, apila el nombre del ID
void StackIDs::push(const std::string& nombre) {
    datos.push_back(nombre);
}


//pop, quita de la pila el id en el tope, error si esta vacia.
std::string StackIDs::pop() {
    if (datos.empty()) {
        std::cerr << "StackIDs: underflow (pila vacía)\n";
        return "";
    }
    std::string val = datos.back();
    datos.pop_back();
    return val;
}

// retorna true si no tiene elemntos
bool StackIDs::empty() const {
    return datos.empty();
}
