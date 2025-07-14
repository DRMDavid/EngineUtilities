#pragma once
#include "../Utilities/EngineMath.h"
#include <iostream>

namespace EngineMathLib {

  /**
   * @class Matrix2x2
   * @brief Representa una matriz 2x2 para transformaciones y operaciones lineales en 2D.
   *
   * Esta clase proporciona funcionalidades para manejar matrices 2x2, incluyendo:
   * - Construcción de matrices identidad, escala y rotación.
   * - Operaciones aritméticas básicas (suma, resta, multiplicación y división por escalar).
   * - Cálculo de determinante, transpuesta e inversa.
   * - Comparación con tolerancia a errores numéricos (EPSILON).
   * - Acceso a elementos mediante operador índice.
   */
  class Matrix2x2 {
  public:
    // Elementos de la matriz dispuestos en fila por columna:
    // [m00 m01]
    // [m10 m11]
    double m00, m01, m10, m11;

    /// Constructor por defecto (matriz identidad)
    Matrix2x2() : m00(1.0), m01(0.0), m10(0.0), m11(1.0) {}

    /// Constructor con elementos específicos
    Matrix2x2(double a, double b, double c, double d) : m00(a), m01(b), m10(c), m11(d) {}

    /// Crea una matriz de escala con factores sx y sy
    static Matrix2x2 Escalar(double sx, double sy) {
      return Matrix2x2(sx, 0.0, 0.0, sy);
    }

    /// Crea una matriz de rotación para un ángulo dado en radianes
    static Matrix2x2 Rotar(double angulo) {
      double c = EngineMathLib::coseno(angulo);
      double s = EngineMathLib::seno(angulo);
      return Matrix2x2(c, -s, s, c);
    }

    /**
     * @brief Acceso a los elementos por índice [0..3] en orden fila principal.
     * @param index Índice del elemento (0 a 3).
     * @return Referencia al elemento para lectura o escritura.
     * @throws std::out_of_range si index no está en [0,3].
     */
    double& operator[](int index) {
      switch (index) {
      case 0: return m00;
      case 1: return m01;
      case 2: return m10;
      case 3: return m11;
      default: throw std::out_of_range("Índice fuera de rango Matrix2x2");
      }
    }

    /// Versión constante para acceso a elementos (lectura)
    const double& operator[](int index) const {
      switch (index) {
      case 0: return m00;
      case 1: return m01;
      case 2: return m10;
      case 3: return m11;
      default: throw std::out_of_range("Índice fuera de rango Matrix2x2");
      }
    }

    /// Suma compuesta: añade otra matriz a esta
    Matrix2x2& operator+=(const Matrix2x2& o) {
      m00 += o.m00; m01 += o.m01;
      m10 += o.m10; m11 += o.m11;
      return *this;
    }

    /// Resta compuesta: resta otra matriz a esta
    Matrix2x2& operator-=(const Matrix2x2& o) {
      m00 -= o.m00; m01 -= o.m01;
      m10 -= o.m10; m11 -= o.m11;
      return *this;
    }

    /// Multiplicación compuesta por un escalar
    Matrix2x2& operator*=(double s) {
      m00 *= s; m01 *= s;
      m10 *= s; m11 *= s;
      return *this;
    }

    /// Devuelve la matriz transpuesta (filas por columnas intercambiadas)
    Matrix2x2 Transpuesta() const {
      return Matrix2x2(m00, m10, m01, m11);
    }

    /// Calcula el determinante de la matriz
    double Determinante() const {
      return m00 * m11 - m01 * m10;
    }

    /// Verifica si la matriz es invertible (determinante no cercano a cero)
    bool isInvertible() const {
      return EngineMathLib::valorAbs(Determinante()) >= EngineMathLib::EPSILON;
    }

    /**
     * @brief Calcula la matriz inversa si es posible.
     * @return Matriz inversa o matriz identidad si no es invertible.
     */
    Matrix2x2 Inversa() const {
      double det = Determinante();
      if (EngineMathLib::valorAbs(det) < EngineMathLib::EPSILON)
        return Matrix2x2(); // fallback a identidad
      double invDet = 1.0 / det;
      return Matrix2x2(m11 * invDet, -m01 * invDet,
        -m10 * invDet, m00 * invDet);
    }

    /// Multiplicación de matrices
    Matrix2x2 operator*(const Matrix2x2& o) const {
      return Matrix2x2(
        m00 * o.m00 + m01 * o.m10,
        m00 * o.m01 + m01 * o.m11,
        m10 * o.m00 + m11 * o.m10,
        m10 * o.m01 + m11 * o.m11
      );
    }

    /// Suma de matrices
    Matrix2x2 operator+(const Matrix2x2& o) const {
      return Matrix2x2(
        m00 + o.m00, m01 + o.m01,
        m10 + o.m10, m11 + o.m11
      );
    }

    /// Resta de matrices
    Matrix2x2 operator-(const Matrix2x2& o) const {
      return Matrix2x2(
        m00 - o.m00, m01 - o.m01,
        m10 - o.m10, m11 - o.m11
      );
    }

    /// Multiplicación por escalar
    Matrix2x2 operator*(double s) const {
      return Matrix2x2(m00 * s, m01 * s, m10 * s, m11 * s);
    }

    /**
     * @brief División por escalar con protección contra división por cero.
     * @param s Escalar divisor.
     * @return Matriz dividida o identidad si s es cero.
     */
    Matrix2x2 operator/(double s) const {
      if (EngineMathLib::valorAbs(s) < EngineMathLib::EPSILON)
        return Matrix2x2();
      double inv = 1.0 / s;
      return (*this) * inv;
    }

    /// Comparación con tolerancia EPSILON
    bool operator==(const Matrix2x2& o) const {
      return EngineMathLib::valorAbs(m00 - o.m00) < EngineMathLib::EPSILON &&
        EngineMathLib::valorAbs(m01 - o.m01) < EngineMathLib::EPSILON &&
        EngineMathLib::valorAbs(m10 - o.m10) < EngineMathLib::EPSILON &&
        EngineMathLib::valorAbs(m11 - o.m11) < EngineMathLib::EPSILON;
    }

    /// Negación de la comparación ==
    bool operator!=(const Matrix2x2& o) const {
      return !(*this == o);
    }

    /// Imprime la matriz en formato legible
    friend std::ostream& operator<<(std::ostream& os, const Matrix2x2& mat) {
      os << "[[" << mat.m00 << ", " << mat.m01 << "],\n"
        << " [" << mat.m10 << ", " << mat.m11 << "]]";
      return os;
    }
  };

}
