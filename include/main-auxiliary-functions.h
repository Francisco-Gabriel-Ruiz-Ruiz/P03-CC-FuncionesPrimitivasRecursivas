/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional 2026-2027
 *
 * @file main-auxiliary-functions.h
 * @author Francisco Gabriel Ruiz Ruiz
 * @date 24 Oct 2026
 * @brief Fichero de cabecera que contiene la declaración de las funciones
 *        auxiliares utilizadas en el programa cliente de Funciones Primitivas Recursivas.
 */

#ifndef MAIN_AUXILIARY_FUNCTIONS_H
#define MAIN_AUXILIARY_FUNCTIONS_H

#include "program-options.h"

/**
 * @brief Muestra por pantalla la ayuda y el modo de empleo del programa.
 */
void PrintHelp();

/**
 * @brief Solicita por teclado los valores naturales de x y/o y si no se especificaron por comandos.
 * @param options Estructura de opciones del programa para actualizar con los valores obtenidos.
 */
void SolicitarValoresFaltantes(ProgramOptions& options);

/**
 * @brief Muestra los resultados obtenidos por el cálculo de la función primitiva recursiva.
 * @param base Valor natural de la base x.
 * @param exponente Valor natural del exponente y.
 * @param resultado Valor calculado x^y.
 * @param llamadas_totales Número total de invocaciones a funciones primitivas recursivas realizadas.
 */
void ImprimirResultados(unsigned long long base, unsigned long long exponente,
                        unsigned long long resultado, unsigned long long llamadas_totales);

#endif  // MAIN_AUXILIARY_FUNCTIONS_H