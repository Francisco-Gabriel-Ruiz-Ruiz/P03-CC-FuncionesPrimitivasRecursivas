/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional 2026-2027
 *
 * @file primitive-recursive-function.cc
 * @author Francisco Gabriel Ruiz Ruiz
 * @date 24 Oct 2026 (Modificado)
 * @brief Implementación de las funciones básicas y los esquemas formales
 *        de combinación/composición y recursión primitiva.
 */

#include "../include/primitive-recursive-function.h"

#include <iostream>
#include <stdexcept>

// =============================================================================
// FUNCIÓN CERO: Z(x) = 0
// =============================================================================

/**
 * @brief Evalúa la función elemental Cero Z(x) = 0.
 * @param args Vector con los argumentos de entrada. Requiere exactamente 1 argumento.
 * @return Natural Siempre 0.
 * @throw std::invalid_argument Si la cantidad de argumentos difiere de 1.
 */
Natural ZeroFunction::Evaluar(const std::vector<Natural>& args) {
  RegistrarLlamada();
  //std::cout << "ZeroFunction  es la nº " << GetContadorLlamadas() << std::endl;
  if (args.size() != Aridad()) {
    throw std::invalid_argument("ZeroFunction requiere exactamente 1 argumento.");
  }
  return 0;
}

// =============================================================================
// FUNCIÓN SUCESOR: S(x) = x + 1
// =============================================================================

/**
 * @brief Evalúa la función elemental Sucesor S(x) = x + 1.
 * @param args Vector con los argumentos de entrada. Requiere exactamente 1 argumento.
 * @return Natural El valor natural incrementado en uno.
 * @throw std::invalid_argument Si la cantidad de argumentos difiere de 1.
 */
Natural SuccessorFunction::Evaluar(const std::vector<Natural>& args) {
  RegistrarLlamada();
  //std::cout << "SuccessorFunction  es la nº " << GetContadorLlamadas() << std::endl;
  if (args.size() != Aridad()) {
    throw std::invalid_argument("SuccessorFunction requiere exactamente 1 argumento.");
  }
  return args[0] + 1;
}

// =============================================================================
// FUNCIÓN PROYECCIÓN: P_i^n(x_1, ..., x_n) = x_i
// =============================================================================

/**
 * @brief Construye una función Proyección verificando que los índices respeten 1 <= indice <= aridad.
 * @param aridad Número total de parámetros de la función (n >= 1).
 * @param indice Índice 1-based del parámetro a proyectar (i).
 * @throw std::invalid_argument Si aridad es 0 o si el índice no pertenece al intervalo [1, aridad].
 */
ProjectionFunction::ProjectionFunction(size_t aridad, size_t indice)
    : aridad_{aridad}, indice_{indice} {
  if (aridad == 0 || indice == 0 || indice > aridad) {
    throw std::invalid_argument("Parámetros de proyección inválidos: 1 <= indice <= aridad.");
  }
}

/**
 * @brief Evalúa la función Proyección devolviendo el elemento en la posición configurada.
 * @param args Vector con los parámetros naturales (longitud esperada: aridad_).
 * @return Natural Valor del parámetro args[indice_ - 1].
 * @throw std::invalid_argument Si el tamaño del vector args no coincide con aridad_.
 */
Natural ProjectionFunction::Evaluar(const std::vector<Natural>& args) {
  RegistrarLlamada();
  //std::cout << "ProjectionFunction  es la nº " << GetContadorLlamadas() << std::endl;
  if (args.size() != aridad_) {
    throw std::invalid_argument("Número de argumentos no coincide con la aridad de la proyección.");
  }
  return args[indice_ - 1];
}

// =============================================================================
// ESQUEMA DE COMPOSICIÓN: f(x) = g(h_1(x), ..., h_m(x))
// =============================================================================

/**
 * @brief Construye el esquema formal de composición comprobando la validez y correspondencia dimensional de g y {h_i}.
 * @param g Función exterior receptora de los resultados intermedios.
 * @param h Vector de funciones interiores generadoras de los parámetros para g.
 * @throw std::invalid_argument Si algún puntero es nulo, h está vacío, la aridad de g no coincide con el tamaño de h,
 *                              o alguna de las funciones en h difiere en aridad con respecto a las demás.
 */
CompositionFunction::CompositionFunction(
    std::shared_ptr<PrimitiveRecursiveFunction> g,
    std::vector<std::shared_ptr<PrimitiveRecursiveFunction>> h)
    : g_{g}, h_{h} {
  if (!g_ || h_.empty()) {
    throw std::invalid_argument("La composición requiere funciones no nulas.");
  }
  if (g_->Aridad() != h_.size()) {
    throw std::invalid_argument("La aridad de g debe coincidir con el número de funciones h_i.");
  }
  aridad_ = h_[0]->Aridad();
  for (const auto& func : h_) {
    if (!func || func->Aridad() != aridad_) {
      throw std::invalid_argument("Todas las funciones h_i deben tener la misma aridad.");
    }
  }
}

/**
 * @brief Evalúa la composición ejecutando primero cada función interior y suministrando sus salidas a la función g.
 * @param args Vector de argumentos naturales con aridad coincidente con aridad_.
 * @return Natural Resultado de la evaluación g(h_1(args), ..., h_m(args)).
 * @throw std::invalid_argument Si la aridad de args no coincide con la aridad configurada.
 */
Natural CompositionFunction::Evaluar(const std::vector<Natural>& args) {
  RegistrarLlamada();
  //std::cout << "CompositionFunction  es la nº " << GetContadorLlamadas() << std::endl;
  if (args.size() != aridad_) {
    throw std::invalid_argument("Número de argumentos incorrecto en CompositionFunction.");
  }
  std::vector<Natural> intermediate_results;
  intermediate_results.reserve(h_.size());
  for (auto& func : h_) {
    intermediate_results.push_back(func->Evaluar(args));
  }
  return g_->Evaluar(intermediate_results);
}

// =============================================================================
// ESQUEMA DE RECURSIÓN PRIMITIVA
// =============================================================================

/**
 * @brief Construye el esquema de recursión primitiva validando las aridades exigidas por la definición formal.
 * @param g Función base para la ecuación límite cuando la última variable es 0 (aridad n - 1).
 * @param h Función de paso inductivo (aridad n + 1).
 * @param aridad Aridad global de la función que se define (n >= 1).
 * @throw std::invalid_argument Si la aridad es 0 o si las aridades de g o h no satisfacen el esquema formal.
 */
PrimitiveRecursionFunction::PrimitiveRecursionFunction(
    std::shared_ptr<PrimitiveRecursiveFunction> g,
    std::shared_ptr<PrimitiveRecursiveFunction> h,
    size_t aridad)
    : g_{g}, h_{h}, aridad_{aridad} {
  if (aridad_ == 0) {
    throw std::invalid_argument("La aridad en recursión primitiva debe ser >= 1.");
  }
  if (aridad_ == 1) {
    // Si la función es unaria f(y): g no toma argumentos o es constante
    if (h_->Aridad() != 2) {
      throw std::invalid_argument("Para aridad 1, el paso h debe tener aridad 2: h(y, f(y)).");
    }
  } else {
    if (g_->Aridad() != aridad_ - 1) {
      throw std::invalid_argument("La función caso base g debe tener aridad (n - 1).");
    }
    if (h_->Aridad() != aridad_ + 1) {
      throw std::invalid_argument("La función paso h debe tener aridad (n + 1).");
    }
  }
}

/**
 * @brief Evalúa la función por recursión primitiva sobre la última componente de args (variable y).
 * @param args Vector con los argumentos naturales (longitud coincidente con aridad_).
 * @return Natural Resultado devuelto por el caso base g o por la aplicación del paso recursivo h.
 * @throw std::invalid_argument Si el tamaño del vector args no es igual a aridad_.
 */
Natural PrimitiveRecursionFunction::Evaluar(const std::vector<Natural>& args) {
  RegistrarLlamada();
  //std::cout << " PrimitiveRecursionFunction es la nº " << GetContadorLlamadas() << std::endl;
  if (args.size() != aridad_) {
    throw std::invalid_argument("Número de argumentos incorrecto en PrimitiveRecursionFunction.");
  }

  // La última variable es siempre la variable de recursión y
  Natural y = args.back();
  std::vector<Natural> params_fijos(args.begin(), args.end() - 1);

  if (y == 0) {
    // Ecuación límite (caso base)
    if (aridad_ == 1) {
      return g_ ? g_->Evaluar({}) : 0;
    }
    return g_->Evaluar(params_fijos);
  }

  // f(x, y - 1)
  std::vector<Natural> recursive_args = args;
  recursive_args.back() = y - 1;
  Natural resultado_anterior = Evaluar(recursive_args);

  // Paso h: h(x_1, ..., x_{n-1}, y - 1, resultado_anterior)
  std::vector<Natural> h_args = params_fijos;
  h_args.push_back(y - 1);
  h_args.push_back(resultado_anterior);

  return h_->Evaluar(h_args);
}