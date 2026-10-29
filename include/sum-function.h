/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional 2026-2027
 *
 * @file sum-function.h
 * @author Francisco Gabriel Ruiz Ruiz
 * @date 24 Oct 2026 (Modificado)
 * @brief Fichero de cabecera que define la clase SumFunction para la operación suma(x, y)
 *        como una Función Primitiva Recursiva no básica.
 */

#ifndef SUM_FUNCTION_H
#define SUM_FUNCTION_H

#include <memory>
#include <vector>

#include "primitive-recursive-function.h"

/**
 * @brief Clase que implementa la función suma(x, y) = x + y mediante Recursión Primitiva.
 */
class SumFunction : public PrimitiveRecursiveFunction {
 public:
  /**
   * @brief Constructor por defecto que ensambla formalmente la función suma como FPR.
   */
  SumFunction();

  /**
   * @brief Evalúa la suma de dos números naturales mediante su FPR interna.
   * @param args Vector con los dos operandos naturales (x, y).
   * @return Natural Resultado de la suma x + y.
   */
  Natural Evaluar(const std::vector<Natural>& args) override;

  /**
   * @brief Devuelve la aridad requerida por la función suma.
   * @return size_t Aridad fija 2.
   */
  size_t Aridad() const override { return 2; }

 private:
  std::shared_ptr<PrimitiveRecursiveFunction> suma_fpr_;
};

#endif  // SUM_FUNCTION_H