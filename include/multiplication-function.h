/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional 2026-2027
 *
 * @file multiplication-function.h
 * @author Francisco Gabriel Ruiz Ruiz
 * @date 24 Oct 2026
 * @brief Fichero de cabecera que define la clase MultiplicationFunction para la operación
 *        mult(x, y) = x * y como una Función Primitiva Recursiva no básica.
 */

#ifndef MULTIPLICATION_FUNCTION_H
#define MULTIPLICATION_FUNCTION_H

#include <memory>
#include <vector>

#include "primitive-recursive-function.h"
#include "sum-function.h"

/**
 * @brief Clase que implementa la función mult(x, y) = x * y mediante Recursión Primitiva y SumFunction.
 */
class MultiplicationFunction : public PrimitiveRecursiveFunction {
 public:
  MultiplicationFunction();
  Natural Evaluar(const std::vector<Natural>& args) override;
  size_t Aridad() const override { return 2; }

 private:
  std::shared_ptr<PrimitiveRecursiveFunction> mult_fpr_;
};

#endif  // MULTIPLICATION_FUNCTION_H