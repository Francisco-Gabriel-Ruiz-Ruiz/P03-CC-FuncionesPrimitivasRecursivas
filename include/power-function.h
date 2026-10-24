/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional 2026-2027
 *
 * @file power-function.h
 * @author Francisco Gabriel Ruiz Ruiz
 * @date 24 Oct 2026
 * @brief Definición de la clase PowerFunction, que construye formalmente
 *        suma, multiplicación y potencia respetando el esquema de FPR.
 */

#ifndef POWER_FUNCTION_H
#define POWER_FUNCTION_H

#include <memory>
#include <vector>

#include "primitive-recursive-function.h"

/**
 * @brief Implementación formal de la función potencia como FPR.
 */
class PowerFunction : public PrimitiveRecursiveFunction {
 public:
  PowerFunction();
  Natural Evaluar(const std::vector<Natural>& args) override;
  size_t Aridad() const override { return 2; }

 private:
  std::shared_ptr<PrimitiveRecursiveFunction> potencia_fpr_;
};

#endif  // POWER_FUNCTION_H