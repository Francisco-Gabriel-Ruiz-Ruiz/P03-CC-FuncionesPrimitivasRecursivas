/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional 2026-2027
 *
 * @file multiplication-function.cc
 * @author Francisco Gabriel Ruiz Ruiz
 * @date 24 Oct 2026
 * @brief Implementación formal de la multiplicación mult(x, y) como FPR a partir de
 *        mult(x, 0) = Z(x) y el paso mult(x, S(y)) = suma(x, mult(x, y)).
 */

#include "../include/multiplication-function.h"

#include <iostream>
#include <stdexcept>

MultiplicationFunction::MultiplicationFunction() {
  // Caso base: mult(x, 0) = g(x) = Z(x) = 0
  auto g_mult = std::make_shared<ZeroFunction>();

  // Caso recursivo: mult(x, S(y)) = h(x, y, mult(x, y)) = suma(x, mult(x, y))
  // Se formaliza como: suma o (P_1^3, P_3^3)(x, y, mult(x, y))
  auto p1_3 = std::make_shared<ProjectionFunction>(3, 1);
  auto p3_3 = std::make_shared<ProjectionFunction>(3, 3);
  auto suma = std::make_shared<SumFunction>();

  auto h_mult = std::make_shared<CompositionFunction>(
      suma, std::vector<std::shared_ptr<PrimitiveRecursiveFunction>>{p1_3, p3_3});

  // Esquema de recursión primitiva para multiplicación: N^2 -> N
  mult_fpr_ = std::make_shared<PrimitiveRecursionFunction>(g_mult, h_mult, 2);
}

Natural MultiplicationFunction::Evaluar(const std::vector<Natural>& args) {
  //std::cout << "MultiplicationFunction -> ";
  if (args.size() != Aridad()) {
    throw std::invalid_argument("MultiplicationFunction requiere exactamente 2 argumentos (x, y).");
  }
  return mult_fpr_->Evaluar(args);
}