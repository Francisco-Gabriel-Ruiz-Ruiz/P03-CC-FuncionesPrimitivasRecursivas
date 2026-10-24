/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional 2026-2027
 *
 * @file client-main.cc
 * @author Francisco Gabriel Ruiz Ruiz
 * @date 24 Oct 2026
 * @brief Programa principal que coordina la recepción de parámetros, la solicitud
 *        de valores interactivos y la ejecución de la Función Primitiva Recursiva (potencia).
 */

#include <iostream>
#include <string>

#include "../include/main-auxiliary-functions.h"
#include "../include/power-function.h"
#include "../include/primitive-recursive-function.h"
#include "../include/program-options.h"

/**
 * @brief Función principal del programa que gestiona los argumentos por línea de comandos,
 *        la interacción con el usuario y la ejecución de la función potencia.
 * @param argc Número de argumentos pasados por línea de comandos.
 * @param argv Vector con los argumentos de línea de comandos.
 * @return int Código de salida del programa (0 si éxito, distinto de 0 en caso de error).
 */
int main(int argc, char* argv[]) {
  const std::string kHelpLiteral{"--help"};

  // Comprobar solicitud de ayuda
  if (argc == 2 && argv[1] == kHelpLiteral) {
    PrintHelp();
    return 0;
  }

  ProgramOptions options;
  try {
    options = ParseArguments(argc, argv);
  } catch (const std::exception& e) {
    std::cerr << "Error de argumentos: " << e.what() << "\n\n";
    PrintHelp();
    return 1;
  }

  // Solicitar interactivamente los valores que no se hayan pasado como flag
  SolicitarValoresFaltantes(options);

  // Resumen de parámetros configurados
  std::cout << "\n=== Parámetros de ejecución configurados ===" << std::endl;
  std::cout << "  - Base (x):      " << options.base_x << std::endl;
  std::cout << "  - Exponente (y): " << options.exponente_y << std::endl;
  std::cout << "============================================" << std::endl;

  try {
    // Reiniciar contador global de llamadas a FPR
    PrimitiveRecursiveFunction::ReiniciarContadorLlamadas();

    // Instanciar la función potencia como FPR
    PowerFunction potencia;

    // Evaluar la potencia con base (x) y exponente (y)
    Natural resultado = potencia.Evaluar({options.base_x, options.exponente_y});
    Natural llamadas_totales = PrimitiveRecursiveFunction::GetContadorLlamadas();

    // Imprimir los resultados requeridos en la práctica
    ImprimirResultados(options.base_x, options.exponente_y, resultado, llamadas_totales);

  } catch (const std::exception& e) {
    std::cerr << "Excepción capturada durante el cálculo: " << e.what() << "\n";
    return 1;
  }

  return 0;
}