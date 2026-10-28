/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional 2026-2027
 *
 * @file primitive-recursive-function.cc
 * @author Francisco Gabriel Ruiz Ruiz
 * @date 24 Oct 2026
 * @brief Implementación de las funciones básicas y los esquemas formales
 *        de combinación/composición y recursión primitiva.
 */

#include "../include/primitive-recursive-function.h"

#include <iostream>
#include <stdexcept>

// =============================================================================
// FUNCIÓN CERO: Z(x) = 0
// =============================================================================

Natural ZeroFunction::Evaluar(const std::vector<Natural>& args) {
  RegistrarLlamada();
  std::cout << "ZeroFunction  es la nº " << GetContadorLlamadas() << std::endl;
  if (args.size() != Aridad()) {
    throw std::invalid_argument("ZeroFunction requiere exactamente 1 argumento.");
  }
  return 0;
}

// =============================================================================
// FUNCIÓN SUCESOR: S(x) = x + 1
// =============================================================================

Natural SuccessorFunction::Evaluar(const std::vector<Natural>& args) {
  RegistrarLlamada();
  std::cout << "SuccessorFunction  es la nº " << GetContadorLlamadas() << std::endl;
  if (args.size() != Aridad()) {
    throw std::invalid_argument("SuccessorFunction requiere exactamente 1 argumento.");
  }
  return args[0] + 1;
}

// =============================================================================
// FUNCIÓN PROYECCIÓN: P_i^n(x_1, ..., x_n) = x_i
// =============================================================================

ProjectionFunction::ProjectionFunction(size_t aridad, size_t indice)
    : aridad_{aridad}, indice_{indice} {
  if (aridad == 0 || indice == 0 || indice > aridad) {
    throw std::invalid_argument("Parámetros de proyección inválidos: 1 <= indice <= aridad.");
  }
}

Natural ProjectionFunction::Evaluar(const std::vector<Natural>& args) {
  RegistrarLlamada();
  std::cout << "ProjectionFunction  es la nº " << GetContadorLlamadas() << std::endl;
  if (args.size() != aridad_) {
    throw std::invalid_argument("Número de argumentos no coincide con la aridad de la proyección.");
  }
  return args[indice_ - 1];
}

// =============================================================================
// ESQUEMA DE COMPOSICIÓN: f(x) = g(h_1(x), ..., h_m(x))
// =============================================================================

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

Natural CompositionFunction::Evaluar(const std::vector<Natural>& args) {
  RegistrarLlamada();
  std::cout << "CompositionFunction  es la nº " << GetContadorLlamadas() << std::endl;
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

Natural PrimitiveRecursionFunction::Evaluar(const std::vector<Natural>& args) {
  RegistrarLlamada();
  std::cout << " (PrimitiveRecursionFunction) es la nº " << GetContadorLlamadas() << std::endl;
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