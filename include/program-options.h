/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional 2026-2027
 *
 * @file program-options.h
 * @author Francisco Gabriel Ruiz Ruiz
 * @date 24 Oct 2026
 * @brief Fichero de cabecera que define la estructura de opciones y
 *        la función encargada de procesar los argumentos de la línea de comandos.
 */

#ifndef PROGRAM_OPTIONS_H
#define PROGRAM_OPTIONS_H

#include <string>

/**
 * @brief Estructura para almacenar los parámetros de ejecución del programa.
 */
struct ProgramOptions {
  unsigned long long base_x{0};       ///< Valor natural de la base (-x)
  unsigned long long exponente_y{0};  ///< Valor natural del exponente (-y)
  bool base_set{false};              ///< Indica si se especificó el parámetro -x
  bool exponente_set{false};         ///< Indica si se especificó el parámetro -y
};

/**
 * @brief Analiza y valida los argumentos pasados por la línea de comandos.
 * @param argc Número de argumentos.
 * @param argv Vector de argumentos.
 * @return ProgramOptions Estructura con las opciones de ejecución configuradas.
 */
ProgramOptions ParseArguments(int argc, char* argv[]);

#endif  // PROGRAM_OPTIONS_H