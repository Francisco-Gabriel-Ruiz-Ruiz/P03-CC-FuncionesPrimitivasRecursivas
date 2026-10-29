# Práctica 3: Implementación de Funciones Primitivas Recursivas de Números Naturales

Universidad de La Laguna  
Escuela Superior de Ingeniería y Tecnología  
Grado en Ingeniería Informática  
**Complejidad Computacional (Curso 2026-2027)**  
Alumno: Francisco Gabriel Ruiz Ruiz  

## Descripción del Proyecto

Este proyecto consiste en el desarrollo en **C++** de un sistema formal para la definición, combinación y evaluación de **Funciones Primitivas Recursivas (FPR)** sobre el conjunto de los números naturales ($\mathbb{N}$) aplicando un diseño orientado a objetos. El objetivo central del programa es calcular la función matemática de la **potencia** ($x^y$) de forma constructiva a partir de las funciones primitivas iniciales (Cero, Sucesor y Proyecciones) y los esquemas de combinación/composición y recursión primitiva.

El programa permite recibir los valores naturales de la base ($x$) y el exponente ($y$) mediante argumentos por línea de comandos o de forma interactiva por teclado, mostrando como salida el resultado final obtenido y el cómputo exhaustivo de las llamadas a funciones primitivas recursivas realizadas a lo largo de toda la derivación.

### Fundamento Teórico y Esquemas Formales

Conforme a las definiciones formales de la teoría de la computabilidad, la arquitectura se fundamenta en:

* **Funciones Básicas Iniciales:**
  * **Cero:** $Z(x) = 0$
  * **Sucesor:** $S(x) = x + 1$
  * **Proyecciones:** $P_i^n(x_1, \dots, x_n) = x_i$, para $1 \le i \le n$

* **Operadores de Clausura:**
  * **Composición / Combinación:** Dados $g: \mathbb{N}^m \to \mathbb{N}$ y $h_1, \dots, h_m: \mathbb{N}^k \to \mathbb{N}$, se define:
    $$f(\vec{x}) = g(h_1(\vec{x}), \dots, h_m(\vec{x}))$$
  * **Recursión Primitiva:** Siguiendo la convención formal donde la **última variable es la de recursión** ($y$):
    * Ecuación límite (caso base): $f(\vec{x}, 0) = g(\vec{x})$
    * Paso inductivo: $f(\vec{x}, S(y)) = h(\vec{x}, y, f(\vec{x}, y))$

* **Cadena de Derivación Formal hasta la Potencia:**
  1. **Suma:** $\text{suma}(x, y) = x + y$
     * $\text{suma}(x, 0) = g(x) = P_1^1(x)$
     * $\text{suma}(x, S(y)) = h(x, y, \text{suma}(x, y)) = S \circ P_3^3(x, y, \text{suma}(x, y))$
  2. **Multiplicación:** $\text{mult}(x, y) = x \cdot y$
     * $\text{mult}(x, 0) = g(x) = Z(x) = 0$
     * $\text{mult}(x, S(y)) = h(x, y, \text{mult}(x, y)) = \text{suma} \circ (P_1^3 \times P_3^3)(x, y, \text{mult}(x, y))$
  3. **Potencia:** $\text{potencia}(x, y) = x^y$
     * $\text{potencia}(x, 0) = g(x) = S \circ Z(x)$
     * $\text{potencia}(x, S(y)) = h(x, y, \text{potencia}(x, y)) = \text{mult} \circ (P_1^3 \times P_3^3)(x, y, \text{potencia}(x, y))$

### Nota Teórica sobre el Operador de Composición / Combinación

Desde una perspectiva formal en la teoría de la computabilidad, la **composición** no es una función primitiva recursiva en sí misma, sino un **operador de clausura** que transforma una tupla de funciones $(g, h_1, \dots, h_m)$ en una nueva función resultante $f$.

En el diseño orientado a objetos implementado:
1. **Patrón Composite:** La clase `CompositionFunction` materializa la función resultante generada por dicho operador. Por ello, hereda de la interfaz abstracta `PrimitiveRecursiveFunction`, permitiendo que la función compuesta resultante posea aridad propia y pueda ser evaluada o suministrada a su vez como componente base o de paso en esquemas de recursión primitiva.
2. **Criterio de Evaluación:** Si bien representa estructuralmente un operador, su invocación en el modelo computacional coordina la bifurcación de parámetros hacia las funciones interiores $h_i$ y la redirección de resultados hacia la función exterior $g$.

## Arquitectura y Modelo de Conteo de Llamadas

### Criterio de Registro de Llamadas
Para que el cómputo de llamadas a funciones coincida con la teoría matemática formal y evite duplicados innecesarios:
1. **El conteo se centraliza en `PrimitiveRecursionFunction`:** En el formalismo matemático, el objeto que define y ejecuta las ecuaciones de recursión ($f(\vec{x}, y)$ y la llamada interna recursiva $f(\vec{x}, y-1)$) **es** la función primitiva recursiva. Por ello, `RegistrarLlamada()` se invoca al inicio de `PrimitiveRecursionFunction::Evaluar()`.
2. **Las clases `PowerFunction`, `MultiplicationFunction` y `SumFunction` actúan como fachadas (*wrappers*):** Estas clases únicamente configuran el grafo funcional en su constructor y delegan la ejecución a su puntero interno `shared_ptr<PrimitiveRecursiveFunction>`. Por ende, no registran llamadas adicionales en su método `Evaluar()`, evitando duplicar el conteo sobre la misma invocación matemática.
3. **Funciones iniciales y composición:** `ZeroFunction`, `SuccessorFunction`, `ProjectionFunction` y `CompositionFunction` registran cada una su correspondiente llamada al ser evaluadas.

## Justificación y Trazas Formales de Conteo

Siguiendo la notación manuscrita desarrollada durante el análisis de la práctica, se detallan las derivaciones formales paso a paso para verificar el conteo exacto de llamadas.

*Nota: para poder ver los mensajes que emite el programa similar a los detallados a continuación, se puede descomentar los std::couts en los ficheros `multiplication-function.cc`, `power-function.cc`. `primitive-recursive-function.cc` y `sum-function.cc`.*

### 1. Traza para `potencia(2, 0)` -> 3 Llamadas

Definición formal:

```text
         1                      3     2
         ↓                      ↓     ↓
        power(2, 0) = g(2)  =   S  ∘  Z(2)

```

* **Llamada 1:** `PowerFunction -> PrimitiveRecursionFunction` sobre `(2, 0)`. Al ser $y = 0$, se dirige inmediatamente a la ecuación límite $g(2)$.
* **Llamada 2:** `ZeroFunction` evaluada en $Z(2)$, devolviendo $0$.
* **Llamada 3:** `SuccessorFunction` evaluada en la función exterior $S(0)$, devolviendo $1$.

**Total de llamadas:** 3.

### 2. Traza para `potencia(2, 1)` -> 13 Llamadas

Definición formal dividida en sus dos ramas (caso recursivo y caso base de cada función involucrada):

```text
 1             7        5       6
 ↓             ↓        ↓       ↓
power(2, 1) = mult  ∘  (P_1^3 × P_3^3)(2, 0, power(2, 0))
                                               ↓ (Llamada 2)
                                           power(2, 0) = S  ∘  Z(2)
                                                         ↓     ↓
                                                         4     3

 7             12       10      11
 ↓             ↓        ↓       ↓
mult(2, 1)  = suma  ∘  (P_1^3 × P_3^3)(2, 0, mult(2, 0))
                                               ↓ (Llamada 8)
                                           mult(2, 0)  = Z(2)
                                                         ↓
                                                         9

 12           13
 ↓            ↓
suma(2, 0)  = P_1^1(2)
```

Desglose cronológico de ejecución:

* **Llamada 1:** `PowerFunction -> PrimitiveRecursionFunction` evalúa `(2, 1)`. Para calcular el paso inductivo requiere previamente el valor del acumulador anterior $\text{potencia}(2, 0)$.
* **Llamada 2:** `PrimitiveRecursionFunction` evalúa recursivamente `(2, 0)`. Como $y = 0$, evalúa su ecuación límite $g(2) = (S \circ Z)(2)$.
* **Llamada 3:** `ZeroFunction` calcula $Z(2) = 0$.
* **Llamada 4:** `SuccessorFunction` calcula $S(0) = 1$. (Fin del caso base: $\text{potencia}(2, 0) = 1$).
* **Llamada 5:** `ProjectionFunction` ($P_1^3$) sobre $(2, 0, 1)$ devuelve $2$.
* **Llamada 6:** `ProjectionFunction` ($P_3^3$) sobre $(2, 0, 1)$ devuelve $1$.
* **Llamada 7:** `MultiplicationFunction -> PrimitiveRecursionFunction` evalúa `(2, 1)`. Requiere primero el acumulador $\text{mult}(2, 0)$.
* **Llamada 8:** `PrimitiveRecursionFunction` evalúa recursivamente `(2, 0)`. Como $y = 0$, evalúa su ecuación límite $g(2) = Z(2)$.
* **Llamada 9:** `ZeroFunction` calcula $Z(2) = 0$. (Fin del caso base: $\text{mult}(2, 0) = 0$).
* **Llamada 10:** `ProjectionFunction` ($P_1^3$) sobre $(2, 0, 0)$ devuelve $2$.
* **Llamada 11:** `ProjectionFunction` ($P_3^3$) sobre $(2, 0, 0)$ devuelve $0$.
* **Llamada 12:** `SumFunction -> PrimitiveRecursionFunction` evalúa `(2, 0)`. Como $y = 0$, invoca su ecuación límite $g(2) = P_1^1(2)$.
* **Llamada 13:** `ProjectionFunction` ($P_1^1$) evalúa $\{2\}$ y devuelve $2$.

**Total de llamadas:** 13.

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
├── Makefile               # Automatización de la compilación
├── ejecutar_pruebas.sh    # Script que ejecuta una serie de pruebas
└── README.md              # Documentación del proyecto
```

## Compilación

El proyecto se compila mediante `make` utilizando las directivas estándar C++17:

```bash
make

```

Esto generará el ejecutable `p03-fpr` en la raíz del proyecto. Para limpiar binarios previos:

```bash
make clean

```

## Modo de Uso y Opciones de Línea de Comandos

```bash
./p03-fpr [-x <base>] [-y <exponente>]

```

### Descripción de Opciones:

* **`-x <n>`** *(Opcional)*: Número natural correspondiente a la base.


* **`-y <n>`** *(Opcional)*: Número natural correspondiente al exponente.


* **`--help`**: Despliega el manual de ayuda de la aplicación.



> Si se omite alguna de las opciones, el programa solicitará interactivamente por consola los valores naturales restantes.
> 
> 

### Ejemplos de Ejecución:

```bash
./p03-fpr -x 2 -y 0
./p03-fpr -x 2 -y 1
./p03-fpr -x 2 -y 4
```