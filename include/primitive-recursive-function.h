/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional 2026-2027
 *
 * @file primitive-recursive-function.h
 * @author Francisco Gabriel Ruiz Ruiz
 * @date 24 Oct 2026 (Modificado)
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
  /**
   * @brief Destructor virtual por defecto para permitir la destrucción polimórfica.
   */
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
  /**
   * @brief Evalúa la función Cero para el argumento proporcionado: Z(x) = 0.
   * @param args Vector de argumentos (debe contener exactamente 1 argumento natural).
   * @return Natural Siempre devuelve 0.
   */
  Natural Evaluar(const std::vector<Natural>& args) override;

  /**
   * @brief Devuelve la aridad de la función Cero.
   * @return size_t Aridad fija 1.
   */
  size_t Aridad() const override { return 1; }
};

/**
 * @brief Función básica Sucesor: S(x) = x + 1.
 */
class SuccessorFunction : public PrimitiveRecursiveFunction {
 public:
  /**
   * @brief Evalúa la función Sucesor: S(x) = x + 1.
   * @param args Vector de argumentos (debe contener exactamente 1 argumento natural).
   * @return Natural Valor del argumento incrementado en 1.
   */
  Natural Evaluar(const std::vector<Natural>& args) override;

  /**
   * @brief Devuelve la aridad de la función Sucesor.
   * @return size_t Aridad fija 1.
   */
  size_t Aridad() const override { return 1; }
};

/**
 * @brief Función básica Proyección: P_i^n(x_1, ..., x_n) = x_i (índice 1-based).
 */
class ProjectionFunction : public PrimitiveRecursiveFunction {
 public:
  /**
   * @brief Constructor que inicializa la función Proyección con su aridad e índice selector.
   * @param aridad Número total de argumentos que recibirá la función (n >= 1).
   * @param indice Posición 1-based del argumento a proyectar (1 <= indice <= aridad).
   */
  ProjectionFunction(size_t aridad, size_t indice);

  /**
   * @brief Evalúa la proyección seleccionando el argumento en la posición fijada.
   * @param args Vector de parámetros naturales (longitud igual a aridad_).
   * @return Natural Valor del argumento proyectado.
   */
  Natural Evaluar(const std::vector<Natural>& args) override;

  /**
   * @brief Devuelve la aridad configurada de la proyección.
   * @return size_t Número de argumentos esperados.
   */
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
  /**
   * @brief Constructor del esquema de composición a partir de una función exterior y un vector de funciones interiores.
   * @param g Puntero a la función exterior g de aridad m.
   * @param h Vector con las m funciones interiores h_i, todas con idéntica aridad k.
   */
  CompositionFunction(std::shared_ptr<PrimitiveRecursiveFunction> g,
                      std::vector<std::shared_ptr<PrimitiveRecursiveFunction>> h);

  /**
   * @brief Evalúa la composición calculando previamente las funciones interiores y aplicando g sobre los resultados.
   * @param args Vector de argumentos naturales con aridad coincidente con las funciones h_i.
   * @return Natural Resultado final de evaluar g sobre los resultados intermedios.
   */
  Natural Evaluar(const std::vector<Natural>& args) override;

  /**
   * @brief Devuelve la aridad común que deben tener los argumentos de entrada.
   * @return size_t Aridad de las funciones interiores h_i.
   */
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
  /**
   * @brief Constructor del esquema de recursión primitiva validando la consistencia dimensional de g y h.
   * @param g Puntero a la función del caso base (aridad n - 1).
   * @param h Puntero a la función del paso inductivo (aridad n + 1).
   * @param aridad Aridad de la función construida f (n >= 1).
   */
  PrimitiveRecursionFunction(std::shared_ptr<PrimitiveRecursiveFunction> g,
                             std::shared_ptr<PrimitiveRecursiveFunction> h,
                             size_t aridad);

  /**
   * @brief Evalúa la función mediante recursión primitiva sobre el último argumento del vector.
   * @param args Vector de argumentos naturales (longitud igual a aridad_).
   * @return Natural Resultado obtenido tras resolver el caso base o el paso inductivo.
   */
  Natural Evaluar(const std::vector<Natural>& args) override;

  /**
   * @brief Devuelve la aridad total de la función recursiva primitiva.
   * @return size_t Aridad configurada n.
   */
  size_t Aridad() const override { return aridad_; }

 private:
  std::shared_ptr<PrimitiveRecursiveFunction> g_;
  std::shared_ptr<PrimitiveRecursiveFunction> h_;
  size_t aridad_{1};
};

#endif  // PRIMITIVE_RECURSIVE_FUNCTION_H