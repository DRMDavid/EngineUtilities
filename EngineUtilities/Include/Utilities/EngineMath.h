#pragma once

namespace EngineMathLib {

  // Constantes matemáticas fundamentales
  constexpr double PI = 3.14159265358979323846;
  constexpr double EULER = 2.71828182845904523536;
  constexpr double EPSILON = 1e-6;

  // --- FUNCIONES BÁSICAS ---

  inline double raizCuadrada(double x) {
    if (x < 0.0) return NAN;
    if (x == 0.0) return 0.0;
    double estimacion = x / 2.0;
    for (int i = 0; i < 20; ++i) {
      estimacion = (estimacion + x / estimacion) / 2.0;
    }
    return estimacion;
  }

  inline double cuadrado(double x) { return x * x; }
  inline double cubo(double x) { return x * x * x; }

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

  inline double valorAbs(double x) { return x < 0.0 ? -x : x; }
  inline double maximo(double a, double b) { return a > b ? a : b; }
  inline double minimo(double a, double b) { return a < b ? a : b; }

  inline int redondear(double x) {
    return (x >= 0.0) ? static_cast<int>(x + 0.5) : static_cast<int>(x - 0.5);
  }

  inline int piso(double x) {
    int i = static_cast<int>(x);
    return (x < 0.0 && x != i) ? i - 1 : i;
  }

  inline int techo(double x) {
    int i = static_cast<int>(x);
    return (x > 0.0 && x != i) ? i + 1 : i;
  }

  inline double absoluto(double x) { return x < 0.0 ? -x : x; }

  inline double modulo(double a, double b) {
    if (b == 0.0) return NAN;
    while (a >= b) a -= b;
    while (a < 0) a += b;
    return a;
  }

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

  inline double logBase10(double x) {
    constexpr double ln10 = 2.302585093;
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
      if (n > 1000) break;
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
      if (n > 1000) break;
    }
    return suma;
  }

  inline double tangente(double x) {
    double s = seno(x);
    double c = coseno(x);
    return (c != 0.0) ? s / c : INFINITY;
  }

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

  inline double arcCoseno(double x) {
    return PI / 2.0 - arcSeno(x);
  }

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

  inline double senoHiperbolico(double x) {
    return (exponencial(x) - exponencial(-x)) / 2.0;
  }

  inline double cosenoHiperbolico(double x) {
    return (exponencial(x) + exponencial(-x)) / 2.0;
  }

  inline double tangenteHiperbolica(double x) {
    double e2x = exponencial(2.0 * x);
    return (e2x - 1) / (e2x + 1);
  }

  // --- FUNCIONES GEOMÉTRICAS ---

  inline double areaCirculo(double radio) {
    return PI * radio * radio;
  }

  inline double perimetroCirculo(double radio) {
    return 2.0 * PI * radio;
  }

  inline double areaRectangulo(double ancho, double alto) {
    return ancho * alto;
  }

  inline double perimetroRectangulo(double ancho, double alto) {
    return 2.0 * (ancho + alto);
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
    if (n < 0) return NAN;
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
