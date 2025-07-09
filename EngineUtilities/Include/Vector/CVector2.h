// CVector2.h - Vector 2D con operaciones básicas y utilidades
// Autor: [Tu Nombre] | Fecha: [Fecha de creación]

#pragma once
#include "../Utilities/EngineMath.h"
#include <ostream>

namespace EngineMath {

  class CVector2 {
  private:
    float x, y;

  public:
    // Constructores
    CVector2() : x(0), y(0) {}
    CVector2(float xVal, float yVal) : x(xVal), y(yVal) {}

    // Operadores aritméticos
    CVector2 operator+(const CVector2& o) const {
      return CVector2(x + o.x, y + o.y);
    }

    CVector2 operator-(const CVector2& o) const {
      return CVector2(x - o.x, y - o.y);
    }

    CVector2 operator*(float escalar) const {
      return CVector2(x * escalar, y * escalar);
    }

    CVector2 operator/(float escalar) const {
      return CVector2(x / escalar, y / escalar);
    }

    // Operadores de asignación compuesta
    CVector2& operator+=(const CVector2& o) {
      x += o.x; y += o.y; return *this;
    }

    CVector2& operator-=(const CVector2& o) {
      x -= o.x; y -= o.y; return *this;
    }

    CVector2& operator*=(float escalar) {
      x *= escalar; y *= escalar; return *this;
    }

    CVector2& operator/=(float escalar) {
      x /= escalar; y /= escalar; return *this;
    }

    // Comparaciones
    bool operator==(const CVector2& o) const {
      return EngineMathLib::approxEqual(x, o.x) &&
        EngineMathLib::approxEqual(y, o.y);
    }

    bool operator!=(const CVector2& o) const {
      return !(*this == o);
    }

    // Acceso por índice
    float& operator[](int i) {
      return (i == 0) ? x : y;
    }

    const float& operator[](int i) const {
      return (i == 0) ? x : y;
    }

    // Magnitud y operaciones vectoriales
    float lengthSquare() const { return x * x + y * y; }

    float length() const {
      return (float)EngineMathLib::sqrt(lengthSquare());
    }

    float dot(const CVector2& o) const {
      return x * o.x + y * o.y;
    }

    float cross(const CVector2& o) const {
      return x * o.y - y * o.x;
    }

    CVector2 normalized() const {
      float len = length();
      return (len == 0.f) ? CVector2(0.f, 0.f) : (*this) / len;
    }

    void normalize() {
      float len = length();
      if (len != 0.f) {
        x /= len; y /= len;
      }
      else {
        x = y = 0.f;
      }
    }

    // Funciones estáticas
    static float distance(const CVector2& a, const CVector2& b) {
      return (float)EngineMathLib::sqrt((b - a).lengthSquare());
    }

    static CVector2 lerp(const CVector2& a, const CVector2& b, float t) {
      return a + (b - a) * t;
    }

    static CVector2 zero() { return CVector2(0.f, 0.f); }

    static CVector2 one() { return CVector2(1.f, 1.f); }

    // Manipulación del vector
    void setPosition(const CVector2& pos) {
      x = pos.x; y = pos.y;
    }

    void move(const CVector2& offset) {
      x += offset.x; y += offset.y;
    }

    void setScale(const CVector2& factors) {
      x *= factors.x; y *= factors.y;
    }

    void scale(const CVector2& factors) {
      x *= factors.x; y *= factors.y;
    }

    void setOrigin(const CVector2& origin) {
      x = origin.x; y = origin.y;
    }

    // Impresión del vector en consola
    friend std::ostream& operator<<(std::ostream& os,
      const CVector2& v) {
      os << "CVector2(" << v.x << ", " << v.y << ")";
      return os;
    }
  };

} // namespace EngineMath
