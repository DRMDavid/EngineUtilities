// engine_mathlib_es.h
// Biblioteca matemática básica para proyectos de ingeniería y videojuegos

#pragma once

namespace EngineMathLib {

  // Constantes matemáticas fundamentales
  const double PI = 3.14159265358979323846;     // Número PI
  const double EULER = 2.71828182845904523536;  // Número de Euler
  const double EPSILON = 1e-6;                  // Tolerancia mínima para cálculos

  // --- FUNCIONES BÁSICAS ---

  /// Calcula la raíz cuadrada usando Newton-Raphson
  inline double raizCuadrada(double x) {
    if (x < 0.0) return -1.0 / 0.0;
    double estimacion = x / 2.0;
    for (int i = 0; i < 20; ++i) {
      estimacion = (estimacion + x / estimacion) / 2.0;
    }
    return estimacion;
  }

  /// Retorna el cuadrado de un número
  inline double cuadrado(double x) { return x * x; }

  /// Retorna el cubo de un número
  inline double cubo(double x) { return x * x * x; }

  /// Potencia base^exponente (aproximada)
  inline double potencia(double base, double exponente) {
    if (base == 0.0 && exponente <= 0.0) return 0.0;
    if (exponente == 0.0) return 1.0;

    bool negativo = exponente < 0.0;
    exponente = negativo ? -exponente : exponente;

    double resultado = 1.0;
    while (exponente >= 1.0) {
      resultado *= base;
      --exponente;
    }

    double fraccion = exponente;
    if (fraccion > 0.0) {
      double parteFraccion = 1.0 + fraccion * (base - 1.0);
      resultado *= parteFraccion;
    }

    return negativo ? 1.0 / resultado : resultado;
  }

  /// Valor absoluto
  inline double valorAbs(double x) { return x < 0 ? -x : x; }

  /// Máximo entre dos valores
  inline double maximo(double a, double b) { return a > b ? a : b; }

  /// Mínimo entre dos valores
  inline double minimo(double a, double b) { return a < b ? a : b; }

  /// Redondeo al entero más cercano
  inline int redondear(double x) {
    return (x >= 0.0) ? int(x + 0.5) : int(x - 0.5);
  }

  /// Piso: entero más pequeño <= x
  inline int piso(double x) {
    int i = int(x);
    return (x < 0.0 && x != i) ? i - 1 : i;
  }

  /// Techo: entero más grande >= x
  inline int techo(double x) {
    int i = int(x);
    return (x > 0.0 && x != i) ? i + 1 : i;
  }

  /// Valor absoluto en punto flotante
  inline double absoluto(double x) { return x < 0 ? -x : x; }

  /// Módulo real entre a y b
  inline double modulo(double a, double b) {
    while (a >= b) a -= b;
    while (a < 0) a += b;
    return a;
  }

  /// Aproximación de la función exponencial (e^x)
  inline double exponencial(double x) {
    double resultado = 1.0;
    double termino = 1.0;
    int n = 1;
    while (absoluto(termino) > EPSILON) {
      termino *= x / n++;
      resultado += termino;
    }
    return resultado;
  }

  /// Aproximación del logaritmo natural
  inline double logNatural(double x) {
    if (x <= 0) return -1.0 / 0.0;
    double y = (x - 1) / (x + 1);
    double suma = 0.0;
    double termino = y;
    int n = 1;
    while (absoluto(termino) > EPSILON) {
      suma += termino / (2 * n - 1);
      termino *= y * y;
      ++n;
    }
    return 2 * suma;
  }

  /// Logaritmo base 10
  inline double logBase10(double x) {
    const double ln10 = 2.302585093;
    return logNatural(x) / ln10;
  }

  // --- FUNCIONES TRIGONOMÉTRICAS ---

  inline double aRadianes(double grados) {
    return grados * (PI / 180.0);
  }

  inline double aGrados(double radianes) {
    return radianes * (180.0 / PI);
  }

  inline double seno(double x) {
    x = modulo(x, 2 * PI);
    double suma = x, termino = x;
    int n = 1;
    while (absoluto(termino) > EPSILON) {
      termino *= -x * x / ((2 * n) * (2 * n + 1));
      suma += termino;
      ++n;
    }
    return suma;
  }

  inline double coseno(double x) {
    x = modulo(x, 2 * PI);
    double suma = 1.0, termino = 1.0;
    int n = 1;
    while (absoluto(termino) > EPSILON) {
      termino *= -x * x / ((2 * n - 1) * (2 * n));
      suma += termino;
      ++n;
    }
    return suma;
  }

  inline double tangente(double x) {
    double s = seno(x);
    double c = coseno(x);
    return c != 0 ? s / c : 1.0 / 0.0;
  }

  inline double arcSeno(double x) {
    if (x < -1 || x > 1) return -1.0 / 0.0;
    double suma = x, termino = x;
    int n = 1;
    while (absoluto(termino) > EPSILON) {
      termino *= (2.0 * n - 1) * (2.0 * n - 1) * x * x /
        ((2.0 * n) * (2.0 * n + 1));
      suma += termino;
      ++n;
    }
    return suma;
  }

  inline double arcCoseno(double x) {
    return PI / 2 - arcSeno(x);
  }

  inline double arcTangente(double x) {
    double suma = x, termino = x;
    int n = 1;
    while (absoluto(termino) > EPSILON) {
      termino *= -x * x * (2.0 * n - 1) / (2.0 * n + 1);
      suma += termino;
      ++n;
    }
    return suma;
  }

  inline double senoHiperbolico(double x) {
    return (exponencial(x) - exponencial(-x)) / 2.0;
  }

  inline double cosenoHiperbolico(double x) {
    return (exponencial(x) + exponencial(-x)) / 2.0;
  }

  inline double tangenteHiperbolica(double x) {
    double e2x = exponencial(2 * x);
    return (e2x - 1) / (e2x + 1);
  }

  // --- FUNCIONES GEOMÉTRICAS ---

  inline double areaCirculo(double radio) {
    return PI * radio * radio;
  }

  inline double perimetroCirculo(double radio) {
    return 2 * PI * radio;
  }

  inline double areaRectangulo(double ancho, double alto) {
    return ancho * alto;
  }

  inline double perimetroRectangulo(double ancho, double alto) {
    return 2 * (ancho + alto);
  }

  inline double areaTriangulo(double base, double altura) {
    return 0.5 * base * altura;
  }

  inline double distancia(double x1, double y1, double x2, double y2) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    return raizCuadrada(dx * dx + dy * dy);
  }

  // --- FUNCIONES ADICIONALES ---

  inline double interpolacion(double a, double b, double t) {
    return a + (b - a) * t;
  }

  inline double factorial(int n) {
    if (n < 0) return -1.0 / 0.0;
    double resultado = 1.0;
    for (int i = 2; i <= n; ++i) {
      resultado *= i;
    }
    return resultado;
  }

  inline bool iguales(double a, double b, double epsilon = 1e-6) {
    return valorAbs(a - b) < epsilon;
  }

} 
