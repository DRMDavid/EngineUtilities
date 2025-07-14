#pragma once

namespace EngineMathLib {

  // Constantes matemáticas fundamentales
  constexpr double PI = 3.14159265358979323846;   ///< Constante pi
  constexpr double EULER = 2.71828182845904523536;///< Número de Euler
  constexpr double EPSILON = 1e-6;                 ///< Tolerancia para comparaciones

  // --- FUNCIONES BÁSICAS ---

  /**
   * @brief Calcula la raíz cuadrada mediante método de Newton-Raphson.
   * @param x Valor no negativo del cual obtener raíz cuadrada.
   * @return Raíz cuadrada de x o NAN si x < 0.
   */
  inline double raizCuadrada(double x) {
    if (x < 0.0) return NAN;
    if (x == 0.0) return 0.0;
    double estimacion = x / 2.0;
    for (int i = 0; i < 20; ++i) {
      estimacion = (estimacion + x / estimacion) / 2.0;
    }
    return estimacion;
  }

  /**
   * @brief Calcula el cuadrado de un número.
   * @param x Número a elevar al cuadrado.
   * @return x²
   */
  inline double cuadrado(double x) { return x * x; }

  /**
   * @brief Calcula el cubo de un número.
   * @param x Número a elevar al cubo.
   * @return x³
   */
  inline double cubo(double x) { return x * x * x; }

  /**
   * @brief Calcula la potencia aproximada de base elevado a exponente.
   * @param base Base no negativa.
   * @param exponente Exponente (puede ser fraccional).
   * @return base^exponente o NAN si base negativa o base=0 y exponente<=0.
   */
  inline double potencia(double base, double exponente) {
    if (base == 0.0) {
      if (exponente <= 0.0) return NAN;
      return 0.0;
    }
    if (exponente == 0.0) return 1.0;
    if (base < 0.0) return NAN;

    double resultado = 1.0;
    while (exponente >= 1.0) {
      resultado *= base;
      exponente -= 1.0;
    }

    double fraccion = exponente;
    if (fraccion > 0.0) {
      double parteFraccion = 1.0 + fraccion * (base - 1.0);
      resultado *= parteFraccion;
    }

    return resultado;
  }

  /**
   * @brief Valor absoluto de un número.
   * @param x Número real.
   * @return Valor absoluto de x.
   */
  inline double valorAbs(double x) { return x < 0.0 ? -x : x; }

  /**
   * @brief Devuelve el máximo entre dos números.
   * @param a Primer número.
   * @param b Segundo número.
   * @return Mayor de a y b.
   */
  inline double maximo(double a, double b) { return a > b ? a : b; }

  /**
   * @brief Devuelve el mínimo entre dos números.
   * @param a Primer número.
   * @param b Segundo número.
   * @return Menor de a y b.
   */
  inline double minimo(double a, double b) { return a < b ? a : b; }

  /**
   * @brief Redondea un número al entero más cercano.
   * @param x Número real.
   * @return Entero más cercano a x.
   */
  inline int redondear(double x) {
    return (x >= 0.0) ? static_cast<int>(x + 0.5) : static_cast<int>(x - 0.5);
  }

  /**
   * @brief Piso matemático, redondeo hacia abajo.
   * @param x Número real.
   * @return Mayor entero menor o igual que x.
   */
  inline int piso(double x) {
    int i = static_cast<int>(x);
    return (x < 0.0 && x != i) ? i - 1 : i;
  }

  /**
   * @brief Techo matemático, redondeo hacia arriba.
   * @param x Número real.
   * @return Menor entero mayor o igual que x.
   */
  inline int techo(double x) {
    int i = static_cast<int>(x);
    return (x > 0.0 && x != i) ? i + 1 : i;
  }

  /**
   * @brief Valor absoluto (redundante con valorAbs).
   * @param x Número real.
   * @return Valor absoluto de x.
   */
  inline double absoluto(double x) { return x < 0.0 ? -x : x; }

  /**
   * @brief Calcula el módulo (residuo) de a mod b.
   * @param a Dividendo.
   * @param b Divisor (no cero).
   * @return Residuo positivo o NAN si b=0.
   */
  inline double modulo(double a, double b) {
    if (b == 0.0) return NAN;
    while (a >= b) a -= b;
    while (a < 0) a += b;
    return a;
  }

  /**
   * @brief Calcula la exponencial e^x usando serie de Taylor.
   * @param x Exponente.
   * @return e elevado a x.
   */
  inline double exponencial(double x) {
    double resultado = 1.0;
    double termino = 1.0;
    int n = 1;
    while (absoluto(termino) > EPSILON) {
      termino *= x / n++;
      resultado += termino;
      if (n > 1000) break;
    }
    return resultado;
  }

  /**
   * @brief Calcula el logaritmo natural ln(x) usando serie de Taylor.
   * @param x Número positivo.
   * @return ln(x) o NAN si x <= 0.
   */
  inline double logNatural(double x) {
    if (x <= 0.0) return NAN;
    double y = (x - 1.0) / (x + 1.0);
    double suma = 0.0;
    double termino = y;
    int n = 1;
    while (absoluto(termino) > EPSILON) {
      suma += termino / (2 * n - 1);
      termino *= y * y;
      ++n;
      if (n > 1000) break;
    }
    return 2.0 * suma;
  }

  /**
   * @brief Calcula el logaritmo base 10.
   * @param x Número positivo.
   * @return log10(x) o NAN si x <= 0.
   */
  inline double logBase10(double x) {
    constexpr double ln10 = 2.302585093;
    return logNatural(x) / ln10;
  }

  // --- FUNCIONES TRIGONOMÉTRICAS ---

  /**
   * @brief Convierte grados a radianes.
   * @param grados Ángulo en grados.
   * @return Ángulo en radianes.
   */
  inline double aRadianes(double grados) {
    return grados * (PI / 180.0);
  }

  /**
   * @brief Convierte radianes a grados.
   * @param radianes Ángulo en radianes.
   * @return Ángulo en grados.
   */
  inline double aGrados(double radianes) {
    return radianes * (180.0 / PI);
  }

  /**
   * @brief Calcula el seno usando serie de Taylor.
   * @param x Ángulo en radianes.
   * @return seno(x).
   */
  inline double seno(double x) {
    x = modulo(x, 2 * PI);
    double suma = x, termino = x;
    int n = 1;
    while (absoluto(termino) > EPSILON) {
      termino *= -x * x / ((2 * n) * (2 * n + 1));
      suma += termino;
      ++n;
      if (n > 1000) break;
    }
    return suma;
  }

  /**
   * @brief Calcula el coseno usando serie de Taylor.
   * @param x Ángulo en radianes.
   * @return coseno(x).
   */
  inline double coseno(double x) {
    x = modulo(x, 2 * PI);
    double suma = 1.0, termino = 1.0;
    int n = 1;
    while (absoluto(termino) > EPSILON) {
      termino *= -x * x / ((2 * n - 1) * (2 * n));
      suma += termino;
      ++n;
      if (n > 1000) break;
    }
    return suma;
  }

  /**
   * @brief Calcula la tangente como seno/coseno.
   * @param x Ángulo en radianes.
   * @return tangente(x) o INFINITY si coseno=0.
   */
  inline double tangente(double x) {
    double s = seno(x);
    double c = coseno(x);
    return (c != 0.0) ? s / c : INFINITY;
  }

  /**
   * @brief Calcula el arco seno usando serie de Taylor.
   * @param x Valor entre -1 y 1.
   * @return arc seno de x o NAN si fuera de rango.
   */
  inline double arcSeno(double x) {
    if (x < -1.0 || x > 1.0) return NAN;
    double suma = x, termino = x;
    int n = 1;
    while (absoluto(termino) > EPSILON) {
      termino *= (2.0 * n - 1) * (2.0 * n - 1) * x * x /
        ((2.0 * n) * (2.0 * n + 1));
      suma += termino;
      ++n;
      if (n > 1000) break;
    }
    return suma;
  }

  /**
   * @brief Calcula el arco coseno como pi/2 - arcSeno(x).
   * @param x Valor entre -1 y 1.
   * @return arc coseno de x o NAN si fuera de rango.
   */
  inline double arcCoseno(double x) {
    return PI / 2.0 - arcSeno(x);
  }

  /**
   * @brief Calcula el arco tangente usando serie de Taylor.
   * @param x Valor real.
   * @return arc tangente de x.
   */
  inline double arcTangente(double x) {
    double suma = x, termino = x;
    int n = 1;
    while (absoluto(termino) > EPSILON) {
      termino *= -x * x * (2.0 * n - 1) / (2.0 * n + 1);
      suma += termino;
      ++n;
      if (n > 1000) break;
    }
    return suma;
  }

  /**
   * @brief Calcula seno hiperbólico.
   * @param x Valor real.
   * @return seno hiperbólico de x.
   */
  inline double senoHiperbolico(double x) {
    return (exponencial(x) - exponencial(-x)) / 2.0;
  }

  /**
   * @brief Calcula coseno hiperbólico.
   * @param x Valor real.
   * @return coseno hiperbólico de x.
   */
  inline double cosenoHiperbolico(double x) {
    return (exponencial(x) + exponencial(-x)) / 2.0;
  }

  /**
   * @brief Calcula tangente hiperbólica.
   * @param x Valor real.
   * @return tangente hiperbólica de x.
   */
  inline double tangenteHiperbolica(double x) {
    double e2x = exponencial(2.0 * x);
    return (e2x - 1) / (e2x + 1);
  }

  // --- FUNCIONES GEOMÉTRICAS ---

  /**
   * @brief Calcula el área de un círculo.
   * @param radio Radio del círculo.
   * @return Área del círculo.
   */
  inline double areaCirculo(double radio) {
    return PI * radio * radio;
  }

  /**
   * @brief Calcula el perímetro de un círculo.
   * @param radio Radio del círculo.
   * @return Perímetro del círculo.
   */
  inline double perimetroCirculo(double radio) {
    return 2.0 * PI * radio;
  }

  /**
   * @brief Calcula el área de un rectángulo.
   * @param ancho Ancho del rectángulo.
   * @param alto Alto del rectángulo.
   * @return Área del rectángulo.
   */
  inline double areaRectangulo(double ancho, double alto) {
    return ancho * alto;
  }

  /**
   * @brief Calcula el perímetro de un rectángulo.
   * @param ancho Ancho del rectángulo.
   * @param alto Alto del rectángulo.
   * @return Perímetro del rectángulo.
   */
  inline double perimetroRectangulo(double ancho, double alto) {
    return 2.0 * (ancho + alto);
  }

  /**
   * @brief Calcula el área de un triángulo.
   * @param base Base del triángulo.
   * @param altura Altura del triángulo.
   * @return Área del triángulo.
   */
  inline double areaTriangulo(double base, double altura) {
    return 0.5 * base * altura;
  }

  /**
   * @brief Calcula la distancia euclidiana entre dos puntos 2D.
   * @param x1 Coordenada x del primer punto.
   * @param y1 Coordenada y del primer punto.
   * @param x2 Coordenada x del segundo punto.
   * @param y2 Coordenada y del segundo punto.
   * @return Distancia entre los dos puntos.
   */
  inline double distancia(double x1, double y1, double x2, double y2) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    return raizCuadrada(dx * dx + dy * dy);
  }

  // --- FUNCIONES ADICIONALES ---

  /**
   * @brief Interpolación lineal entre a y b.
   * @param a Valor inicial.
   * @param b Valor final.
   * @param t Parámetro entre 0 y 1.
   * @return Valor interpolado.
   */
  inline double interpolacion(double a, double b, double t) {
    return a + (b - a) * t;
  }

  /**
   * @brief Calcula factorial de n (n!).
   * @param n Entero no negativo.
   * @return Factorial de n o NAN si n < 0.
   */
  inline double factorial(int n) {
    if (n < 0) return NAN;
    double resultado = 1.0;
    for (int i = 2; i <= n; ++i) {
      resultado *= i;
    }
    return resultado;
  }

  /**
   * @brief Compara dos valores con una tolerancia epsilon.
   * @param a Primer valor.
   * @param b Segundo valor.
   * @param epsilon Tolerancia para comparación.
   * @return true si a y b son iguales dentro de epsilon.
   */
  inline bool iguales(double a, double b, double epsilon = 1e-6) {
    return valorAbs(a - b) < epsilon;
  }

}
