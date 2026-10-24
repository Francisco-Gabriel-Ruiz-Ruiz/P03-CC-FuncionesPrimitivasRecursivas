# Práctica 3: Implementación de Funciones Primitivas Recursivas de Números Naturales



Universidad de La Laguna

Escuela Superior de Ingeniería y Tecnología

Grado en Ingeniería Informática

**Complejidad Computacional (Curso 2026-2027)**

Alumno: Francisco Gabriel Ruiz Ruiz

## Descripción del Proyecto

Este proyecto consiste en el desarrollo en **C++** de un sistema formal para la definición, combinación y evaluación de **Funciones Primitivas Recursivas (FPR)** sobre el conjunto de los números naturales ($\mathbb{N}$) aplicando un diseño orientado a objetos. El objetivo central del programa es calcular la función matemática de la **potencia** ($x^y$) de forma constructiva a partir de las funciones primitivas básicas (Cero, Sucesor y Proyecciones) y los esquemas de combinación, composición y recursión primitiva.

El programa permite recibir los valores naturales de la base ($x$) y el exponente ($y$) tanto mediante argumentos por línea de comandos como de forma interactiva por teclado, mostrando como salida el resultado final obtenido y el cómputo exhaustivo del número de llamadas a funciones efectuadas a lo largo de toda la derivación recursiva.

### Fundamento Teórico y Esquemas Formales

Conforme a las definiciones formales explicadas en clase, la arquitectura se fundamenta en:

* **Funciones Básicas Predefinidas:**
* **Cero:** $Z(x) = 0$


* **Sucesor:** $S(x) = x + 1$


* **Proyecciones:** $P_i^n(x_1, \dots, x_n) = x_i$, para $1 \le i \le n$




* **Operadores Constructores:**
* **Composición / Combinación:** Dados $g: \mathbb{N}^m \to \mathbb{N}$ y $h_1, \dots, h_m: \mathbb{N}^k \to \mathbb{N}$, se define $f(\vec{x}) = g(h_1(\vec{x}), \dots, h_m(\vec{x}))$.


* **Recursión Primitiva:** Siguiendo la convención formal donde la **última variable es la de recursión** ($y$):


* Ecuación límite (caso base): $f(\vec{x}, 0) = g(\vec{x})$


* Paso recursivo: $f(\vec{x}, S(y)) = h(\vec{x}, y, f(\vec{x}, y))$






* **Cadena de Derivación Formal hasta la Potencia:**
1. **Suma:** $\text{suma}(x, y) = x + y$


* $\text{suma}(x, 0) = g(x) = P_1^1(x)$


* $\text{suma}(x, S(y)) = h(x, y, \text{suma}(x, y)) = S(P_3^3(x, y, \text{suma}(x, y)))$




2. **Multiplicación:** $\text{mult}(x, y) = x \cdot y$
* $\text{mult}(x, 0) = g(x) = Z(x) = 0$
* $\text{mult}(x, S(y)) = h(x, y, \text{mult}(x, y)) = \text{suma}(P_1^3, P_3^3)(x, y, \text{mult}(x, y))$


3. **Constante Uno:** $\text{uno}(x) = S(Z(x)) = 1$


4. **Potencia:** $\text{potencia}(x, y) = x^y$


* $\text{potencia}(x, 0) = g(x) = \text{uno}(x) = 1$


* $\text{potencia}(x, S(y)) = h(x, y, \text{potencia}(x, y)) = \text{mult}(P_1^3, P_3^3)(x, y, \text{potencia}(x, y))$





## Arquitectura y Diseño Orientado a Objetos

El diseño sigue una arquitectura modular en C++ estándar (`include/`, `src/`, `build/`), desacoplando responsabilidades entre sus componentes:

1. **`PrimitiveRecursiveFunction`**: Clase base abstracta pura que define la interfaz común de evaluación (`Evaluar()`), consulta de aridad (`Aridad()`) y el registro centralizado del contador de llamadas (`GetContadorLlamadas()`, `ReiniciarContadorLlamadas()`). Contiene además las implementaciones de los bloques básicos (`ZeroFunction`, `SuccessorFunction`, `ProjectionFunction`) y los operadores de orden superior (`CompositionFunction`, `PrimitiveRecursionFunction`).


2. **`SumFunction`**: Subclase no básica que encapsula la construcción por recursión primitiva de la operación de suma formal a partir de $P_1^1$ y $S \circ P_3^3$.


3. **`MultiplicationFunction`**: Subclase no básica que implementa la multiplicación formal reutilizando `SumFunction` mediante recursión primitiva a partir de $Z$ y $\text{suma} \circ (P_1^3 \times P_3^3)$.
4. **`PowerFunction`**: Clase principal que materializa la función $x^y$ componiendo la multiplicación recursivamente a partir del caso base $\text{uno}(x) = S(Z(x))$ y el paso $\text{mult} \circ (P_1^3 \times P_3^3)$.


5. **`ProgramOptions`**: Estructura y módulo de parseo (`ParseArguments()`) encargado de procesar y validar rigurosamente las opciones de la línea de comandos (`-x` e `-y`) comprobando no negatividad y formatos numéricos naturales.


6. **`main-auxiliary-functions`**: Módulo con utilidades para el despliegue del manual de ayuda (`PrintHelp()`), la solicitud interactiva en caso de parámetros omitidos (`SolicitarValoresFaltantes()`) y el formateo de salida en consola (`ImprimirResultados()`).



## Estructura de Directorios

```text
.
├── build/                 # Ficheros objeto compilados (.o)
├── docs/                  # Documentación adicional y guion de la práctica
│   └── CC_2627_Practica3.pdf
├── include/               # Ficheros de cabecera (.h)
│   ├── main-auxiliary-functions.h
│   ├── multiplication-function.h
│   ├── power-function.h
│   ├── primitive-recursive-function.h
│   ├── program-options.h
│   └── sum-function.h
├── src/                   # Ficheros de implementación (.cc)
│   ├── client-main.cc
│   ├── main-auxiliary-functions.cc
│   ├── multiplication-function.cc
│   ├── power-function.cc
│   ├── primitive-recursive-function.cc
│   ├── program-options.cc
│   └── sum-function.cc
├── Makefile               # Fichero de automatización de la compilación
└── README.md              # Documentación del proyecto

```

## Compilación

El proyecto se compila mediante `make` utilizando las directivas de optimización y avisos estándar (`-std=c++17 -Wall -Wextra`):

```bash
make

```

Esto generará el ejecutable `p03-fpr` en la raíz del proyecto. Para eliminar los ficheros intermedios y reconstruir el proyecto:

```bash
make clean

```

## Modo de Uso y Opciones de Línea de Comandos

El programa principal acepta los parámetros de la operación por línea de comandos conforme al guion:

```bash
./p03-fpr [-x <base>] [-y <exponente>]

```

### Descripción de Opciones:

* **`-x <n>`** *(Opcional)*: Número natural correspondiente a la base de la potencia.


* **`-y <n>`** *(Opcional)*: Número natural correspondiente al exponente de la potencia.


* **`--help`**: Muestra el mensaje informativo de ayuda con la sintaxis y finaliza la ejecución.

> **Nota:** Si se omite alguna de las opciones (`-x` o `-y`), el programa solicitará interactivamente por teclado los valores numéricos naturales restantes antes de proceder a la evaluación.

### Ejemplos de Ejecución:

1. **Paso de parámetros completo por consola:**

```bash
./p03-fpr -x 2 -y 4

```

2. **Entrada interactiva por omisión de banderas:**

```bash
./p03-fpr
Introduce el valor natural de la base (x >= 0): 3
Introduce el valor natural del exponente (y >= 0): 2

```

3. **Ejecución parcial combinada:**

```bash
./p03-fpr -x 5
Introduce el valor natural del exponente (y >= 0): 3

```

## Ejemplo de Salida del Programa

Tras llevar a cabo la evaluación respetando la cadena formal de llamadas a funciones primitivas recursivas, el programa presenta la siguiente estructura de salida:

```text
=== Parámetros de ejecución configurados ===
  - Base (x):      2
  - Exponente (y): 4
============================================

=== RESULTADOS DEL CÁLCULO (FPR) ===
  Operación:             potencia(2, 4) = 2^4
  Resultado obtenido:    16
  Llamadas a funciones:  74
====================================

```

## Tratamiento y Control de Errores

El sistema cuenta con mecanismos de control y excepciones para garantizar la integridad de las ejecuciones matemáticas:

* **Validación de Línea de Comandos:** Detección de banderas duplicadas, ausencia de valores asociados o argumentos malformados no reconocidos.
* **Validación de Tipos Naturales:** Comprobación estricta de que las entradas pertenezcan a $\mathbb{N}$ (enteros no negativos), impidiendo valores con signo negativo o caracteres no alfanuméricos mediante control de conversiones numéricas (`std::stoull`).
* **Comprobación de Aridad en Composición y Recursión:** Verificación estricta de coherencia dimensional entre las entradas recibidas y la aridad declarada en cada nivel del árbol funcional ($g$, $h_i$).
* **Control de Flujo Interactivo:** Recuperación y limpieza de búfer (`std::cin.clear()`, `std::cin.ignore()`) ante entradas inválidas introducidas por teclado.