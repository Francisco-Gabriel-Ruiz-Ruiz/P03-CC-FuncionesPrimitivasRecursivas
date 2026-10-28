#!/usr/bin/env bash

EXECUTABLE="./p03-fpr"
OUTPUT_FILE="resultados.txt"

# Comprobar que el ejecutable existe y tiene permisos de ejecución
if [[ ! -x "$EXECUTABLE" ]]; then
    echo "Error: No se encontró el ejecutable $EXECUTABLE o no tiene permisos de ejecución." >&2
    exit 1
fi

# Vaciar o crear el archivo de salida
> "$OUTPUT_FILE"

# Lista de pares (x, y) a evaluar
PARES=(
    "2 0"
    "3 0"
    "2 1"
    "2 2"
    "2 3"
    "2 7"
    "2 10"
    "2 12"
    "3 1"
    "3 2"
    "3 3"
    "3 7"
    "4 2"
    "4 5"
    "5 3"
    "5 5"
    "6 2"
    "6 5"
    "10 4"
    "1 40"
    "1 400"
    "1 4000"
    "1 8000"
)

echo "Ejecutando pruebas..."

for par in "${PARES[@]}"; do
    read -r x y <<< "$par"
    
    echo -n "Procesando x=$x, y=$y... "
    
    # Ejecuta el programa capturando la salida estándar
    salida=$("$EXECUTABLE" -x "$x" -y "$y" 2>/dev/null)
    
    # Extrae el número tras 'Llamadas a funciones:'
    llamadas=$(echo "$salida" | grep "Llamadas a funciones:" | awk -F: '{gsub(/^[ \t]+|[ \t]+$/, "", $2); print $2}')
    
    if [[ -n "$llamadas" ]]; then
        linea="x=$x, y=$y -> $llamadas llamadas"
        echo "$linea" >> "$OUTPUT_FILE"
        echo "OK ($llamadas llamadas)"
    else
        echo "Error o finalización anómala (Segmentation fault / timeout)"
        echo "x=$x, y=$y -> ERROR" >> "$OUTPUT_FILE"
    fi
done

echo ""
echo "Completado. Salida guardada en $OUTPUT_FILE"