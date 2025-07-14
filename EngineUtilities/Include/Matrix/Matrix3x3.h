#pragma once
#include "../Utilities/EngineMath.h"
#include <iostream>

namespace EngineMathLib {

  /**
   * @class Matrix3x3
   * @brief Representa una matriz 3x3 para transformaciones en 2D y 3D.
   *
   * Permite realizar operaciones como suma, resta, multiplicación
   * entre matrices y con escalares, transposición, determinante,
   * inversa y construcción de matrices especiales de escalado y rotación.
   */
  class Matrix3x3 {
  public:
    double m[3][3];  ///< Elementos de la matriz, accesibles por índices [fila][columna]

    // --- Constructores ---
    Matrix3x3() {
      for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
          m[i][j] = (i == j) ? 1.0 : 0.0;
    }

    Matrix3x3(double a00, double a01, double a02,
      double a10, double a11, double a12,
      double a20, double a21, double a22) {
      m[0][0] = a00; m[0][1] = a01; m[0][2] = a02;
      m[1][0] = a10; m[1][1] = a11; m[1][2] = a12;
      m[2][0] = a20; m[2][1] = a21; m[2][2] = a22;
    }

    // --- Constructores estáticos ---
    static Matrix3x3 Escalar(double sx, double sy) {
      return Matrix3x3(sx, 0, 0,
        0, sy, 0,
        0, 0, 1);
    }

    static Matrix3x3 Rotar(double angulo) {
      double c = EngineMathLib::coseno(angulo);
      double s = EngineMathLib::seno(angulo);
      return Matrix3x3(c, -s, 0,
        s, c, 0,
        0, 0, 1);
    }

    // --- Acceso por índice ---
    /**
     * @brief Acceso mutable a elementos usando índices planos 0..8.
     * @param index Índice en rango [0..8].
     * @return Referencia al elemento.
     * @throws std::out_of_range si índice inválido.
     */
    double& operator[](int index) {
      if (index < 0 || index >= 9)
        throw std::out_of_range("Índice fuera de rango Matrix3x3");
      return m[index / 3][index % 3];
    }

    /**
     * @brief Acceso constante a elementos usando índices planos 0..8.
     * @param index Índice en rango [0..8].
     * @return Referencia constante al elemento.
     * @throws std::out_of_range si índice inválido.
     */
    const double& operator[](int index) const {
      if (index < 0 || index >= 9)
        throw std::out_of_range("Índice fuera de rango Matrix3x3");
      return m[index / 3][index % 3];
    }

    // --- Operadores compuestos ---
    Matrix3x3& operator+=(const Matrix3x3& o) {
      for (int i = 0; i < 9; ++i)
        (*this)[i] += o[i];
      return *this;
    }

    Matrix3x3& operator-=(const Matrix3x3& o) {
      for (int i = 0; i < 9; ++i)
        (*this)[i] -= o[i];
      return *this;
    }

    Matrix3x3& operator*=(double s) {
      for (int i = 0; i < 9; ++i)
        (*this)[i] *= s;
      return *this;
    }

    // --- Métodos existentes ---
    Matrix3x3 Transpuesta() const {
      Matrix3x3 r;
      for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
          r.m[i][j] = m[j][i];
      return r;
    }

    double Determinante() const {
      return m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1])
        - m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0])
        + m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
    }

    bool isInvertible() const {
      return EngineMathLib::valorAbs(Determinante()) >= EngineMathLib::EPSILON;
    }

    Matrix3x3 Inversa() const {
      double det = Determinante();
      if (EngineMathLib::valorAbs(det) < EngineMathLib::EPSILON)
        return Matrix3x3();

      double inv = 1.0 / det;
      Matrix3x3 r;

      r.m[0][0] = (m[1][1] * m[2][2] - m[1][2] * m[2][1]) * inv;
      r.m[0][1] = -(m[0][1] * m[2][2] - m[0][2] * m[2][1]) * inv;
      r.m[0][2] = (m[0][1] * m[1][2] - m[0][2] * m[1][1]) * inv;

      r.m[1][0] = -(m[1][0] * m[2][2] - m[1][2] * m[2][0]) * inv;
      r.m[1][1] = (m[0][0] * m[2][2] - m[0][2] * m[2][0]) * inv;
      r.m[1][2] = -(m[0][0] * m[1][2] - m[0][2] * m[1][0]) * inv;

      r.m[2][0] = (m[1][0] * m[2][1] - m[1][1] * m[2][0]) * inv;
      r.m[2][1] = -(m[0][0] * m[2][1] - m[0][1] * m[2][0]) * inv;
      r.m[2][2] = (m[0][0] * m[1][1] - m[0][1] * m[1][0]) * inv;

      return r;
    }

    // --- Operadores normales ---
    Matrix3x3 operator*(const Matrix3x3& o) const {
      Matrix3x3 r;
      for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
          r.m[i][j] = m[i][0] * o.m[0][j] + m[i][1] * o.m[1][j] + m[i][2] * o.m[2][j];
      return r;
    }

    Matrix3x3 operator+(const Matrix3x3& o) const {
      Matrix3x3 r;
      for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
          r.m[i][j] = m[i][j] + o.m[i][j];
      return r;
    }

    Matrix3x3 operator-(const Matrix3x3& o) const {
      Matrix3x3 r;
      for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
          r.m[i][j] = m[i][j] - o.m[i][j];
      return r;
    }

    Matrix3x3 operator*(double s) const {
      Matrix3x3 r;
      for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
          r.m[i][j] = m[i][j] * s;
      return r;
    }

    Matrix3x3 operator/(double s) const {
      if (EngineMathLib::valorAbs(s) < EngineMathLib::EPSILON)
        return Matrix3x3();
      double inv = 1.0 / s;
      return (*this) * inv;
    }

    // --- Comparaciones ---
    bool operator==(const Matrix3x3& o) const {
      for (int i = 0; i < 9; ++i)
        if (EngineMathLib::valorAbs((*this)[i] - o[i]) >= EngineMathLib::EPSILON)
          return false;
      return true;
    }

    bool operator!=(const Matrix3x3& o) const {
      return !(*this == o);
    }

    // --- Impresión ---
    friend std::ostream& operator<<(std::ostream& os, const Matrix3x3& mat) {
      os << "[\n";
      for (int i = 0; i < 3; ++i) {
        os << "  [ ";
        for (int j = 0; j < 3; ++j) {
          os << mat.m[i][j];
          if (j < 2) os << ", ";
        }
        os << " ]";
        if (i < 2) os << ",";
        os << "\n";
      }
      os << "]";
      return os;
    }
  };

} 
