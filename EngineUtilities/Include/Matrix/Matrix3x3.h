#pragma once
#include "../Utilities/EngineMath.h"
#include <iostream>

namespace EngineMathLib {

  /**
   * @class Matrix3x3
   * @brief Representa una matriz 3x3 para transformaciones y operaciones en 2D y 3D.
   *
   * Proporciona operaciones básicas de matrices:
   * - Construcción de matrices identidad, escala y rotación.
   * - Operaciones aritméticas (suma, resta, multiplicación y división por escalar).
   * - Cálculo de determinante, transpuesta e inversa.
   * - Comparación con tolerancia a errores numéricos.
   * - Acceso mediante índice lineal.
   */
  class Matrix3x3 {
  public:
    /// Elementos accesibles como m[fila][columna]
    double m[3][3];

    /// Constructor por defecto que crea matriz identidad
    Matrix3x3() {
      for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
          m[i][j] = (i == j) ? 1.0 : 0.0;
    }

    /// Constructor con valores explícitos para cada elemento
    Matrix3x3(double a00, double a01, double a02,
      double a10, double a11, double a12,
      double a20, double a21, double a22) {
      m[0][0] = a00; m[0][1] = a01; m[0][2] = a02;
      m[1][0] = a10; m[1][1] = a11; m[1][2] = a12;
      m[2][0] = a20; m[2][1] = a21; m[2][2] = a22;
    }

    /**
     * @brief Crea matriz de escala 2D con factores sx y sy.
     * @param sx Factor escala en X.
     * @param sy Factor escala en Y.
     * @return Matriz3x3 de escala.
     */
    static Matrix3x3 Escalar(double sx, double sy) {
      return Matrix3x3(sx, 0, 0,
        0, sy, 0,
        0, 0, 1);
    }

    /**
     * @brief Crea matriz de rotación 2D para ángulo en radianes.
     * @param angulo Ángulo de rotación (radianes).
     * @return Matriz3x3 de rotación.
     */
    static Matrix3x3 Rotar(double angulo) {
      double c = EngineMathLib::coseno(angulo);
      double s = EngineMathLib::seno(angulo);
      return Matrix3x3(c, -s, 0,
        s, c, 0,
        0, 0, 1);
    }

    /**
     * @brief Acceso mutable a elemento usando índice lineal 0..8.
     * @param index Índice del elemento (0 a 8).
     * @return Referencia al elemento.
     * @throws std::out_of_range si índice inválido.
     */
    double& operator[](int index) {
      if (index < 0 || index >= 9)
        throw std::out_of_range("Índice fuera de rango Matrix3x3");
      return m[index / 3][index % 3];
    }

    /**
     * @brief Acceso constante a elemento usando índice lineal 0..8.
     * @param index Índice del elemento (0 a 8).
     * @return Referencia constante al elemento.
     * @throws std::out_of_range si índice inválido.
     */
    const double& operator[](int index) const {
      if (index < 0 || index >= 9)
        throw std::out_of_range("Índice fuera de rango Matrix3x3");
      return m[index / 3][index % 3];
    }

    /// Operador suma compuesta (+=)
    Matrix3x3& operator+=(const Matrix3x3& o) {
      for (int i = 0; i < 9; ++i)
        (*this)[i] += o[i];
      return *this;
    }

    /// Operador resta compuesta (-=)
    Matrix3x3& operator-=(const Matrix3x3& o) {
      for (int i = 0; i < 9; ++i)
        (*this)[i] -= o[i];
      return *this;
    }

    /// Multiplicación compuesta por escalar (*=)
    Matrix3x3& operator*=(double s) {
      for (int i = 0; i < 9; ++i)
        (*this)[i] *= s;
      return *this;
    }

    /// Devuelve la matriz transpuesta (filas ↔ columnas)
    Matrix3x3 Transpuesta() const {
      Matrix3x3 r;
      for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
          r.m[i][j] = m[j][i];
      return r;
    }

    /// Calcula el determinante de la matriz 3x3
    double Determinante() const {
      return m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1])
        - m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0])
        + m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
    }

    /// Verifica si la matriz es invertible (determinante no nulo)
    bool isInvertible() const {
      return EngineMathLib::valorAbs(Determinante()) >= EngineMathLib::EPSILON;
    }

    /**
     * @brief Calcula la matriz inversa si existe.
     * @return Matriz inversa o identidad si no es invertible.
     */
    Matrix3x3 Inversa() const {
      double det = Determinante();
      if (EngineMathLib::valorAbs(det) < EngineMathLib::EPSILON)
        return Matrix3x3(); // fallback identidad

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

    /// Multiplicación entre matrices
    Matrix3x3 operator*(const Matrix3x3& o) const {
      Matrix3x3 r;
      for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
          r.m[i][j] = m[i][0] * o.m[0][j] + m[i][1] * o.m[1][j] + m[i][2] * o.m[2][j];
      return r;
    }

    /// Suma entre matrices
    Matrix3x3 operator+(const Matrix3x3& o) const {
      Matrix3x3 r;
      for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
          r.m[i][j] = m[i][j] + o.m[i][j];
      return r;
    }

    /// Resta entre matrices
    Matrix3x3 operator-(const Matrix3x3& o) const {
      Matrix3x3 r;
      for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
          r.m[i][j] = m[i][j] - o.m[i][j];
      return r;
    }

    /// Multiplicación por escalar
    Matrix3x3 operator*(double s) const {
      Matrix3x3 r;
      for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
          r.m[i][j] = m[i][j] * s;
      return r;
    }

    /**
     * @brief División por escalar con protección contra división por cero.
     * @param s Escalar divisor.
     * @return Matriz dividida o identidad si s es cero.
     */
    Matrix3x3 operator/(double s) const {
      if (EngineMathLib::valorAbs(s) < EngineMathLib::EPSILON)
        return Matrix3x3();
      double inv = 1.0 / s;
      return (*this) * inv;
    }

    /// Comparación con tolerancia EPSILON
    bool operator==(const Matrix3x3& o) const {
      for (int i = 0; i < 9; ++i)
        if (EngineMathLib::valorAbs((*this)[i] - o[i]) >= EngineMathLib::EPSILON)
          return false;
      return true;
    }

    /// Negación de la comparación ==
    bool operator!=(const Matrix3x3& o) const {
      return !(*this == o);
    }

    /// Imprime la matriz en formato legible
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
