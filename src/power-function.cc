/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional 2026-2027
 *
 * @file power-function.cc
 * @author Francisco Gabriel Ruiz Ruiz
 * @date 24 Oct 2026 (Modificado)
 * @brief Implementación de la función potencia como FPR a partir de la
 *        multiplicación y la función constante uno.
 */

#include "../include/power-function.h"
#include "../include/multiplication-function.h"

#include <iostream>
#include <stdexcept>

/**
 * @brief Construye la función potencia configurando el caso base uno(x) = S(Z(x))
 *        y el paso inductivo h(x, y, potencia(x, y)) = mult o (P_1^3, P_3^3)(x, y, potencia(x, y)).
 */
PowerFunction::PowerFunction() {
  // Caso base: potencia(x, 0) = uno(x) = S(Z(x)) = 1
  auto zero = std::make_shared<ZeroFunction>();
  auto suc = std::make_shared<SuccessorFunction>();
  auto funcion_uno = std::make_shared<CompositionFunction>(
      suc, std::vector<std::shared_ptr<PrimitiveRecursiveFunction>>{zero});

  // Caso recursivo: potencia(x, S(y)) = mult(x, potencia(x, y))
  // Se formaliza como: mult o (P_1^3, P_3^3)(x, y, potencia(x, y))
  auto p1_3 = std::make_shared<ProjectionFunction>(3, 1);
  auto p3_3 = std::make_shared<ProjectionFunction>(3, 3);
  auto multiplicacion = std::make_shared<MultiplicationFunction>();

  auto h_potencia = std::make_shared<CompositionFunction>(
      multiplicacion, std::vector<std::shared_ptr<PrimitiveRecursiveFunction>>{p1_3, p3_3});

  // Esquema de recursión primitiva para potencia: N^2 -> N
  potencia_fpr_ = std::make_shared<PrimitiveRecursionFunction>(funcion_uno, h_potencia, 2);
}

/**
 * @brief Evalúa la función potencia comprobando la aridad y delegando el cómputo en potencia_fpr_.
 * @param args Vector de argumentos naturales. Debe contener exactamente 2 valores: (base, exponente).
 * @return Natural Resultado de la potencia.
 * @throw std::invalid_argument Si la cantidad de argumentos difiere de 2.
 */
Natural PowerFunction::Evaluar(const std::vector<Natural>& args) {
  //std::cout << "PowerFunction -> ";
  if (args.size() != Aridad()) {
    throw std::invalid_argument("PowerFunction requiere 2 argumentos: (base, exponente).");
  }
  return potencia_fpr_->Evaluar(args);
}