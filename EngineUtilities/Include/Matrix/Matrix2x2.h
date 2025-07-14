#pragma once
#include "../Utilities/EngineMath.h"
#include <iostream>

namespace EngineMathLib {

  /**
   * @class Matrix2x2
   * @brief Representa una matriz 2x2 para transformaciones en 2D.
   *
   * Esta clase permite realizar operaciones básicas con matrices 2x2,
   * como suma, resta, multiplicación (con matrices y escalares),
   * transposición, cálculo del determinante e inversión.
   * También permite construir matrices para rotar o escalar objetos
   * en 2D.
   */
  class Matrix2x2 {
  public:
    double m00, m01, m10, m11;

    // --- Constructores ---
    Matrix2x2() : m00(1.0), m01(0.0), m10(0.0), m11(1.0) {}
    Matrix2x2(double a, double b, double c, double d) : m00(a), m01(b), m10(c), m11(d) {}

    // --- Constructores estáticos ---
    static Matrix2x2 Escalar(double sx, double sy) {
      return Matrix2x2(sx, 0.0, 0.0, sy);
    }
    static Matrix2x2 Rotar(double angulo) {
      double c = EngineMathLib::coseno(angulo);
      double s = EngineMathLib::seno(angulo);
      return Matrix2x2(c, -s, s, c);
    }

    // --- Acceso por índice ---
    /**
     * @brief Accede a los elementos como arreglo [0..3].
     * @param index Índice (0 a 3).
     * @return Referencia al elemento.
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

    const double& operator[](int index) const {
      switch (index) {
      case 0: return m00;
      case 1: return m01;
      case 2: return m10;
      case 3: return m11;
      default: throw std::out_of_range("Índice fuera de rango Matrix2x2");
      }
    }

    // --- Operadores compuestos ---
    Matrix2x2& operator+=(const Matrix2x2& o) {
      m00 += o.m00; m01 += o.m01;
      m10 += o.m10; m11 += o.m11;
      return *this;
    }

    Matrix2x2& operator-=(const Matrix2x2& o) {
      m00 -= o.m00; m01 -= o.m01;
      m10 -= o.m10; m11 -= o.m11;
      return *this;
    }

    Matrix2x2& operator*=(double s) {
      m00 *= s; m01 *= s;
      m10 *= s; m11 *= s;
      return *this;
    }

    // --- Métodos existentes ---
    Matrix2x2 Transpuesta() const {
      return Matrix2x2(m00, m10, m01, m11);
    }

    double Determinante() const {
      return m00 * m11 - m01 * m10;
    }

    bool isInvertible() const {
      return EngineMathLib::valorAbs(Determinante()) >= EngineMathLib::EPSILON;
    }

    Matrix2x2 Inversa() const {
      double det = Determinante();
      if (EngineMathLib::valorAbs(det) < EngineMathLib::EPSILON)
        return Matrix2x2(); // identidad fallback
      double invDet = 1.0 / det;
      return Matrix2x2(m11 * invDet, -m01 * invDet,
        -m10 * invDet, m00 * invDet);
    }

    // --- Operadores normales ---
    Matrix2x2 operator*(const Matrix2x2& o) const {
      return Matrix2x2(
        m00 * o.m00 + m01 * o.m10,
        m00 * o.m01 + m01 * o.m11,
        m10 * o.m00 + m11 * o.m10,
        m10 * o.m01 + m11 * o.m11
      );
    }

    Matrix2x2 operator+(const Matrix2x2& o) const {
      return Matrix2x2(
        m00 + o.m00, m01 + o.m01,
        m10 + o.m10, m11 + o.m11
      );
    }

    Matrix2x2 operator-(const Matrix2x2& o) const {
      return Matrix2x2(
        m00 - o.m00, m01 - o.m01,
        m10 - o.m10, m11 - o.m11
      );
    }

    Matrix2x2 operator*(double s) const {
      return Matrix2x2(m00 * s, m01 * s, m10 * s, m11 * s);
    }

    Matrix2x2 operator/(double s) const {
      if (EngineMathLib::valorAbs(s) < EngineMathLib::EPSILON)
        return Matrix2x2();
      double inv = 1.0 / s;
      return (*this) * inv;
    }

    // --- Comparaciones ---
    bool operator==(const Matrix2x2& o) const {
      return EngineMathLib::valorAbs(m00 - o.m00) < EngineMathLib::EPSILON &&
        EngineMathLib::valorAbs(m01 - o.m01) < EngineMathLib::EPSILON &&
        EngineMathLib::valorAbs(m10 - o.m10) < EngineMathLib::EPSILON &&
        EngineMathLib::valorAbs(m11 - o.m11) < EngineMathLib::EPSILON;
    }

    bool operator!=(const Matrix2x2& o) const {
      return !(*this == o);
    }

    // --- Impresión ---
    friend std::ostream& operator<<(std::ostream& os, const Matrix2x2& mat) {
      os << "[[" << mat.m00 << ", " << mat.m01 << "],\n"
        << " [" << mat.m10 << ", " << mat.m11 << "]]";
      return os;
    }
  };

} 
