# Universidad de La Laguna
# Escuela Superior de Ingeniería y Tecnología
# Grado en Ingeniería Informática 2026-2027
# Asignatura: Complejidad Computacional
# Autor: Francisco Gabriel Ruiz Ruiz
# Fecha de última modificación: 24/10/2026

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./include

# Nombre del ejecutable
TARGET = p03-fpr

# --- DIRECTORIOS ---
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build

# --- DETECCIÓN AUTOMÁTICA DE ARCHIVOS ---
# Busca todos los .cc en src y sus subdirectorios
SRCS = $(shell find $(SRC_DIR) -name "*.cc")

# Busca todos los .h en include y sus subdirectorios para las dependencias
HEADERS = $(shell find $(INCLUDE_DIR) -name "*.h")

# Genera la lista de objetos redirigiéndolos a la carpeta build/
OBJS = $(SRCS:$(SRC_DIR)/%.cc=$(BUILD_DIR)/%.o)

# --- REGLAS ---

all: $(TARGET)

# Crear ejecutable enlazando los objetos de build/
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilar archivos objeto y guardarlos en build/ (crea subdirectorios si es necesario)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cc $(HEADERS)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpiar archivos temporales y la carpeta build
clean:
	rm -f $(TARGET)
	find $(BUILD_DIR) -type f -name "*.o" -delete

# Debug: sirve para ver qué archivos está detectando el Makefile
debug:
	@echo "Fuentes detectadas: $(SRCS)"
	@echo "Cabeceras detectadas: $(HEADERS)"
	@echo "Objetos a generar: $(OBJS)"

.PHONY: all clean debug