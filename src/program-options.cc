/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional 2026-2027
 *
 * @file program-options.cc
 * @author Francisco Gabriel Ruiz Ruiz
 * @date 24 Oct 2026
 * @brief Implementación del análisis y validación de los parámetros de la línea de comandos.
 */

#include "../include/program-options.h"

#include <iostream>
#include <stdexcept>
#include <string>

/**
 * @brief Analiza y valida los argumentos pasados por la línea de comandos.
 * @param argc Número de argumentos.
 * @param argv Vector de argumentos.
 * @return ProgramOptions Estructura con las opciones de ejecución configuradas.
 */
ProgramOptions ParseArguments(int argc, char* argv[]) {
  const std::string kBaseLiteral{"-x"};
  const std::string kExponenteLiteral{"-y"};

  ProgramOptions options;

  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];

    if (arg == kBaseLiteral) {
      if (options.base_set) {
        throw std::runtime_error("La opción -x está duplicada.");
      }
      if (i + 1 < argc && argv[i + 1][0] != '-') {
        std::string valor_str = argv[++i];
        try {
          size_t idx = 0;
          unsigned long long valor = std::stoull(valor_str, &idx);
          if (idx != valor_str.size()) {
            throw std::invalid_argument("Caracteres no numéricos detectados.");
          }
          options.base_x = valor;
          options.base_set = true;
        } catch (const std::exception&) {
          throw std::runtime_error("El valor para -x debe ser un número natural válido (>= 0).");
        }
      } else {
        throw std::runtime_error("La opción -x requiere un valor numérico natural.");
      }
    } else if (arg == kExponenteLiteral) {
      if (options.exponente_set) {
        throw std::runtime_error("La opción -y está duplicada.");
      }
      if (i + 1 < argc && argv[i + 1][0] != '-') {
        std::string valor_str = argv[++i];
        try {
          size_t idx = 0;
          unsigned long long valor = std::stoull(valor_str, &idx);
          if (idx != valor_str.size()) {
            throw std::invalid_argument("Caracteres no numéricos detectados.");
          }
          options.exponente_y = valor;
          options.exponente_set = true;
        } catch (const std::exception&) {
          throw std::runtime_error("El valor para -y debe ser un número natural válido (>= 0).");
        }
      } else {
        throw std::runtime_error("La opción -y requiere un valor numérico natural.");
      }
    } else {
      throw std::runtime_error("Opción desconocida o malformada: " + arg);
    }
  }

  return options;
}