/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional 2026-2027
 *
 * @file sum-function.cc
 * @author Francisco Gabriel Ruiz Ruiz
 * @date 24 Oct 2026
 * @brief Implementación formal de la función suma(x, y) como FPR a partir de
 *        la ecuación límite suma(x, 0) = P_1^1(x) y el paso suma(x, S(y)) = S(P_3^3(x, y, suma(x, y))).
 */

#include "../include/sum-function.h"

#include <iostream>
#include <stdexcept>

SumFunction::SumFunction() {
  // Caso base: suma(x, 0) = g(x) = P_1^1(x)
  auto g_suma = std::make_shared<ProjectionFunction>(1, 1);

  // Caso recursivo: suma(x, S(y)) = h(x, y, suma(x, y)) = S(P_3^3(x, y, suma(x, y)))
  auto p3_3 = std::make_shared<ProjectionFunction>(3, 3);
  auto suc = std::make_shared<SuccessorFunction>();
  auto h_suma = std::make_shared<CompositionFunction>(
      suc, std::vector<std::shared_ptr<PrimitiveRecursiveFunction>>{p3_3});

  // Esquema de recursión primitiva para suma: N^2 -> N
  suma_fpr_ = std::make_shared<PrimitiveRecursionFunction>(g_suma, h_suma, 2);
}

Natural SumFunction::Evaluar(const std::vector<Natural>& args) {
  //RegistrarLlamada();
  std::cout << "SumFunction";
  if (args.size() != Aridad()) {
    throw std::invalid_argument("SumFunction requiere exactamente 2 argumentos (x, y).");
  }
  return suma_fpr_->Evaluar(args);
}