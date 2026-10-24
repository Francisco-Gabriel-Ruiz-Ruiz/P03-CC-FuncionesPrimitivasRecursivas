/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional 2026-2027
 *
 * @file primitive-recursive-function.h
 * @author Francisco Gabriel Ruiz Ruiz
 * @date 24 Oct 2026
 * @brief Definición de la clase base abstracta para Funciones Primitives Recursivas (FPR)
 *        y de los componentes funcionales básicos (Cero, Sucesor, Proyecciones,
 *        Composición y Recursión Primitiva).
 */

#ifndef PRIMITIVE_RECURSIVE_FUNCTION_H
#define PRIMITIVE_RECURSIVE_FUNCTION_H

#include <memory>
#include <vector>

using Natural = unsigned long long;

/**
 * @brief Clase base abstracta para cualquier función primitiva recursiva.
 */
class PrimitiveRecursiveFunction {
 public:
  virtual ~PrimitiveRecursiveFunction() = default;

  /**
   * @brief Evalúa la función con el vector de argumentos naturales dado.
   * @param args Vector con los parámetros naturales (x_1, ..., x_n).
   * @return Natural Resultado de la evaluación.
   */
  virtual Natural Evaluar(const std::vector<Natural>& args) = 0;

  /**
   * @brief Devuelve la aridad (número de argumentos requeridos) de la función.
   * @return size_t Aridad de la función.
   */
  virtual size_t Aridad() const = 0;

  /**
   * @brief Reinicia el contador de llamadas a funciones.
   */
  static void ReiniciarContadorLlamadas() { contador_llamadas_ = 0; }

  /**
   * @brief Obtiene el total de llamadas a funciones realizadas durante los cálculos.
   * @return Natural Número de invocaciones.
   */
  static Natural GetContadorLlamadas() { return contador_llamadas_; }

 protected:
  /**
   * @brief Incrementa el registro global de invocaciones a funciones primitivas recursivas.
   */
  static void RegistrarLlamada() { ++contador_llamadas_; }

 private:
  static inline Natural contador_llamadas_{0};
};

/**
 * @brief Función básica Cero: Z(x) = 0.
 */
class ZeroFunction : public PrimitiveRecursiveFunction {
 public:
  Natural Evaluar(const std::vector<Natural>& args) override;
  size_t Aridad() const override { return 1; }
};

/**
 * @brief Función básica Sucesor: S(x) = x + 1.
 */
class SuccessorFunction : public PrimitiveRecursiveFunction {
 public:
  Natural Evaluar(const std::vector<Natural>& args) override;
  size_t Aridad() const override { return 1; }
};

/**
 * @brief Función básica Proyección: P_i^n(x_1, ..., x_n) = x_i (índice 1-based).
 */
class ProjectionFunction : public PrimitiveRecursiveFunction {
 public:
  ProjectionFunction(size_t aridad, size_t indice);
  Natural Evaluar(const std::vector<Natural>& args) override;
  size_t Aridad() const override { return aridad_; }

 private:
  size_t aridad_{1};
  size_t indice_{1};
};

/**
 * @brief Esquema de Composición: f(x) = g(h_1(x), ..., h_m(x)).
 */
class CompositionFunction : public PrimitiveRecursiveFunction {
 public:
  CompositionFunction(std::shared_ptr<PrimitiveRecursiveFunction> g,
                      std::vector<std::shared_ptr<PrimitiveRecursiveFunction>> h);
  Natural Evaluar(const std::vector<Natural>& args) override;
  size_t Aridad() const override { return aridad_; }

 private:
  std::shared_ptr<PrimitiveRecursiveFunction> g_;
  std::vector<std::shared_ptr<PrimitiveRecursiveFunction>> h_;
  size_t aridad_{0};
};

/**
 * @brief Esquema de Recursión Primitiva:
 *        f(x_1, ..., x_{n-1}, 0) = g(x_1, ..., x_{n-1})
 *        f(x_1, ..., x_{n-1}, S(y)) = h(x_1, ..., x_{n-1}, y, f(x_1, ..., x_{n-1}, y))
 *        La última variable es siempre la variable de recursión (y).
 */
class PrimitiveRecursionFunction : public PrimitiveRecursiveFunction {
 public:
  PrimitiveRecursionFunction(std::shared_ptr<PrimitiveRecursiveFunction> g,
                             std::shared_ptr<PrimitiveRecursiveFunction> h,
                             size_t aridad);
  Natural Evaluar(const std::vector<Natural>& args) override;
  size_t Aridad() const override { return aridad_; }

 private:
  std::shared_ptr<PrimitiveRecursiveFunction> g_;
  std::shared_ptr<PrimitiveRecursiveFunction> h_;
  size_t aridad_{1};
};

#endif  // PRIMITIVE_RECURSIVE_FUNCTION_H