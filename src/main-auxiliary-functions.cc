/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional 2026-2027
 *
 * @file main-auxiliary-functions.cc
 * @author Francisco Gabriel Ruiz Ruiz
 * @date 24 Oct 2026
 * @brief Fichero que contiene la implementación de las funciones auxiliares
 *        usadas en el programa cliente de la práctica de Funciones Primitivas Recursivas.
 */

#include "../include/main-auxiliary-functions.h"

#include <iostream>
#include <limits>

/**
 * @brief Muestra por pantalla la ayuda y el modo de empleo del programa.
 */
void PrintHelp() {
  std::cout << "====================================================================\n";
  std::cout << "   CALCULADORA DE FUNCIONES PRIMITIVAS RECURSIVAS (POTENCIA)        \n";
  std::cout << "====================================================================\n";
  std::cout << "Modo de empleo:\n";
  std::cout << "  ./p03-fpr [-x <n>] [-y <n>]\n\n";
  std::cout << "Opciones por línea de comandos:\n";
  std::cout << "  -x <n>         Número natural que actúa como la base de la potencia.\n";
  std::cout << "  -y <n>         Número natural que actúa como el exponente de la potencia.\n";
  std::cout << "  --help         Muestra este mensaje de ayuda y finaliza la ejecución.\n\n";
  std::cout << "Nota:\n";
  std::cout << "  Si se omiten -x o -y, el programa los solicitará interactivamente por teclado.\n";
  std::cout << "====================================================================\n";
}

/**
 * @brief Solicita por teclado los valores naturales de x y/o y si no se especificaron por comandos.
 * @param options Estructura de opciones del programa para actualizar con los valores obtenidos.
 */
void SolicitarValoresFaltantes(ProgramOptions& options) {
  if (!options.base_set) {
    while (true) {
      std::cout << "Introduce el valor natural de la base (x >= 0): ";
      if (std::cin >> options.base_x) {
        options.base_set = true;
        break;
      }
      std::cerr << "Error: Entrada no válida. Introduce un número natural.\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  if (!options.exponente_set) {
    while (true) {
      std::cout << "Introduce el valor natural del exponente (y >= 0): ";
      if (std::cin >> options.exponente_y) {
        options.exponente_set = true;
        break;
      }
      std::cerr << "Error: Entrada no válida. Introduce un número natural.\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
}

/**
 * @brief Muestra los resultados obtenidos por el cálculo de la función primitiva recursiva.
 * @param base Valor natural de la base x.
 * @param exponente Valor natural del exponente y.
 * @param resultado Valor calculado x^y.
 * @param llamadas_totales Número total de invocaciones a funciones primitivas recursivas realizadas.
 */
void ImprimirResultados(unsigned long long base, unsigned long long exponente,
                        unsigned long long resultado, unsigned long long llamadas_totales) {
  std::cout << "\n=== RESULTADOS DEL CÁLCULO (FPR) ===\n";
  std::cout << "  Operación:             potencia(" << base << ", " << exponente << ") = " << base << "^" << exponente << "\n";
  std::cout << "  Resultado obtenido:    " << resultado << "\n";
  std::cout << "  Llamadas a funciones:  " << llamadas_totales << "\n";
  std::cout << "====================================\n";
}