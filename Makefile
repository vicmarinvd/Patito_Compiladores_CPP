# ─────────────────────────────────────────────────────────────────────
# Makefile — Compilador Patito (versión C++)
# ─────────────────────────────────────────────────────────────────────
#
# Herramientas requeridas:
#   - flex   (analizador léxico)
#   - bison  (analizador sintáctico)
#   - g++    (compilador C++17)
#
# Uso:
#   make            compila el compilador (genera el ejecutable 'patito')
#   make run F=archivo.txt  compila y ejecuta con un archivo de prueba
#   make clean       elimina todos los archivos generados
#
# ─────────────────────────────────────────────────────────────────────

# Compilador y flags
CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

# Ejecutable de salida
TARGET   = patito

# Archivos fuente C++ escritos a mano
CPP_SRCS = semantica.cpp dvirtual.cpp cuadruplos.cpp maquina_virtual.cpp

# Archivos generados por Flex y Bison
LEX_SRC  = lex.yy.c
YACC_SRC = patito.tab.c
YACC_HDR = patito.tab.h

# Todos los objetos que se compilarán
OBJS = $(CPP_SRCS:.cpp=.o) $(LEX_SRC:.c=.o) $(YACC_SRC:.c=.o)

# ─── Regla principal ──────────────────────────────────────────────────

all: $(TARGET)

# Enlazar todos los objetos en el ejecutable final
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo "Compilador '$(TARGET)' generado exitosamente."

# ─── Compilar archivos .cpp propios ──────────────────────────────────

semantica.o: semantica.cpp semantica.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

dvirtual.o: dvirtual.cpp dvirtual.hpp semantica.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

cuadruplos.o: cuadruplos.cpp cuadruplos.hpp semantica.hpp dvirtual.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

maquina_virtual.o: maquina_virtual.cpp maquina_virtual.hpp cuadruplos.hpp dvirtual.hpp semantica.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ─── Generar y compilar el parser (Bison) ────────────────────────────

# Bison genera patito.tab.c y patito.tab.h desde patito.y
# -d genera el encabezado con los tokens
$(YACC_SRC) $(YACC_HDR): patito.y
	bison -d patito.y

# Compilar el parser generado como C++ (para usar std::string, etc.)
patito.tab.o: $(YACC_SRC) $(YACC_HDR)
	$(CXX) $(CXXFLAGS) -c $(YACC_SRC) -o $@

# ─── Generar y compilar el lexer (Flex) ──────────────────────────────

# Flex genera lex.yy.c desde patito.l
$(LEX_SRC): patito.l $(YACC_HDR)
	flex patito.l

# Compilar el lexer generado como C++
lex.yy.o: $(LEX_SRC)
	$(CXX) $(CXXFLAGS) -c $(LEX_SRC) -o $@

# ─── Ejecutar con un archivo de prueba ───────────────────────────────

run: $(TARGET)
	./$(TARGET) $(F)

# ─── Limpiar archivos generados ──────────────────────────────────────

clean:
	rm -f $(TARGET) $(OBJS) $(LEX_SRC) $(YACC_SRC) $(YACC_HDR)
	@echo "Archivos generados eliminados."

.PHONY: all run clean
