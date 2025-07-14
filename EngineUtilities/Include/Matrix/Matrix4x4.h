#pragma once
#include "../Utilities/EngineMath.h"
#include <iostream>
#include <stdexcept>

namespace EngineMathLib {

  class Matrix4x4 {
  public:
    double m[4][4];  ///< Elementos de la matriz (fila, columna)

    Matrix4x4() {
      for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
          m[i][j] = (i == j) ? 1.0 : 0.0;
    }

    Matrix4x4(double a00, double a01, double a02, double a03,
      double a10, double a11, double a12, double a13,
      double a20, double a21, double a22, double a23,
      double a30, double a31, double a32, double a33) {
      m[0][0] = a00; m[0][1] = a01; m[0][2] = a02; m[0][3] = a03;
      m[1][0] = a10; m[1][1] = a11; m[1][2] = a12; m[1][3] = a13;
      m[2][0] = a20; m[2][1] = a21; m[2][2] = a22; m[2][3] = a23;
      m[3][0] = a30; m[3][1] = a31; m[3][2] = a32; m[3][3] = a33;
    }

    // Acceso por índice plano [0..15]
    double& operator[](int index) {
      if (index < 0 || index >= 16)
        throw std::out_of_range("Índice fuera de rango Matrix4x4");
      return m[index / 4][index % 4];
    }
    const double& operator[](int index) const {
      if (index < 0 || index >= 16)
        throw std::out_of_range("Índice fuera de rango Matrix4x4");
      return m[index / 4][index % 4];
    }

    Matrix4x4& operator+=(const Matrix4x4& o) {
      for (int i = 0; i < 16; ++i)
        (*this)[i] += o[i];
      return *this;
    }

    Matrix4x4& operator-=(const Matrix4x4& o) {
      for (int i = 0; i < 16; ++i)
        (*this)[i] -= o[i];
      return *this;
    }

    Matrix4x4& operator*=(double s) {
      for (int i = 0; i < 16; ++i)
        (*this)[i] *= s;
      return *this;
    }

    Matrix4x4 Transpuesta() const {
      Matrix4x4 r;
      for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
          r.m[i][j] = m[j][i];
      return r;
    }

    bool isInvertible() const {
      return EngineMathLib::valorAbs(Determinante()) >= EngineMathLib::EPSILON;
    }

    double Determinante() const {
      double det = 0.0;
      for (int i = 0; i < 4; ++i) {
        double submat[3][3];
        for (int r = 1; r < 4; ++r) {
          int cIndex = 0;
          for (int c = 0; c < 4; ++c) {
            if (c == i) continue;
            submat[r - 1][cIndex++] = m[r][c];
          }
        }
        double subdet = subDeterminante3x3(submat);
        double signo = (i % 2 == 0) ? 1.0 : -1.0;
        det += signo * m[0][i] * subdet;
      }
      return det;
    }

    Matrix4x4 Inversa() const {
      double det = Determinante();
      if (EngineMathLib::valorAbs(det) < EngineMathLib::EPSILON)
        return Matrix4x4();

      Matrix4x4 adj = Adjunta();
      return adj / det;
    }

    Matrix4x4 operator*(const Matrix4x4& o) const {
      Matrix4x4 r;
      for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j) {
          r.m[i][j] = 0.0;
          for (int k = 0; k < 4; ++k)
            r.m[i][j] += m[i][k] * o.m[k][j];
        }
      return r;
    }

    Matrix4x4 operator+(const Matrix4x4& o) const {
      Matrix4x4 r;
      for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
          r.m[i][j] = m[i][j] + o.m[i][j];
      return r;
    }

    Matrix4x4 operator-(const Matrix4x4& o) const {
      Matrix4x4 r;
      for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
          r.m[i][j] = m[i][j] - o.m[i][j];
      return r;
    }

    Matrix4x4 operator*(double s) const {
      Matrix4x4 r;
      for (int i = 0; i < 16; ++i)
        r[i] = (*this)[i] * s;
      return r;
    }

    Matrix4x4 operator/(double s) const {
      if (EngineMathLib::valorAbs(s) < EngineMathLib::EPSILON)
        return Matrix4x4();
      double inv = 1.0 / s;
      return (*this) * inv;
    }

    bool operator==(const Matrix4x4& o) const {
      for (int i = 0; i < 16; ++i)
        if (EngineMathLib::valorAbs((*this)[i] - o[i]) >= EngineMathLib::EPSILON)
          return false;
      return true;
    }

    bool operator!=(const Matrix4x4& o) const {
      return !(*this == o);
    }

    friend std::ostream& operator<<(std::ostream& os, const Matrix4x4& mat) {
      os << "[\n";
      for (int i = 0; i < 4; ++i) {
        os << "  [ ";
        for (int j = 0; j < 4; ++j) {
          os << mat.m[i][j];
          if (j < 3) os << ", ";
        }
        os << " ]";
        if (i < 3) os << ",";
        os << "\n";
      }
      os << "]";
      return os;
    }

  private:
    static double subDeterminante3x3(const double mat[3][3]) {
      return mat[0][0] * (mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1])
        - mat[0][1] * (mat[1][0] * mat[2][2] - mat[1][2] * mat[2][0])
        + mat[0][2] * (mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0]);
    }

    Matrix4x4 Adjunta() const {
      Matrix4x4 adj;
      for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
          double submat[3][3];
          int subi = 0;
          for (int r = 0; r < 4; ++r) {
            if (r == i) continue;
            int subj = 0;
            for (int c = 0; c < 4; ++c) {
              if (c == j) continue;
              submat[subi][subj++] = m[r][c];
            }
            subi++;
          }
          double signo = ((i + j) % 2 == 0) ? 1.0 : -1.0;
          adj.m[j][i] = signo * subDeterminante3x3(submat);
        }
      }
      return adj;
    }
  };

} 
