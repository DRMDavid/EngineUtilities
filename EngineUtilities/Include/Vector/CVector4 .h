// CVector4.h - Vector 4D con operaciones básicas y utilidades


#pragma once
#include "../Utilities/EngineMath.h"
#include <ostream>

/// Clase para representar un vector en 4D con operaciones matemáticas comunes.
class CVector4 {
public:
  float x, y, z, w;

  /// Constructor por defecto. Inicializa el vector en (0, 0, 0, 0).
  CVector4() : x(0), y(0), z(0), w(0) {}

  /// Constructor con valores personalizados.
  /// @param x Valor en el eje X.
  /// @param y Valor en el eje Y.
  /// @param z Valor en el eje Z.
  /// @param w Valor en el eje W.
  CVector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

  // --- Operadores aritméticos ---

  /// Suma dos vectores.
  CVector4 operator+(const CVector4& other) const;

  /// Resta dos vectores.
  CVector4 operator-(const CVector4& other) const;

  /// Multiplica el vector por un escalar.
  CVector4 operator*(float scalar) const;

  /// Divide el vector entre un escalar.
  CVector4 operator/(float scalar) const;

  // --- Asignaciones compuestas ---

  /// Suma otro vector al actual.
  CVector4& operator+=(const CVector4& other);

  /// Resta otro vector al actual.
  CVector4& operator-=(const CVector4& other);

  /// Multiplica el vector actual por un escalar.
  CVector4& operator*=(float scalar);

  /// Divide el vector actual entre un escalar.
  CVector4& operator/=(float scalar);

  // --- Comparaciones ---

  /// Compara si dos vectores son aproximadamente iguales.
  bool operator==(const CVector4& other) const;

  /// Compara si dos vectores son diferentes.
  bool operator!=(const CVector4& other) const;

  // --- Acceso por índice ---

  /// Accede a una componente por índice (0: X, 1: Y, 2: Z, 3: W).
  float& operator[](int index);

  /// Accede a una componente por índice (0: X, 1: Y, 2: Z, 3: W) (versión constante).
  const float& operator[](int index) const;

  // --- Magnitud y operaciones vectoriales ---

  /// Retorna la longitud al cuadrado del vector.
  float lengthSquare() const;

  /// Retorna la magnitud (longitud) del vector.
  float length() const;

  /// Calcula el producto punto entre dos vectores.
  float dot(const CVector4& other) const;

  /// Retorna una copia normalizada del vector (longitud = 1).
  CVector4 normalized() const;

  /// Normaliza el vector actual (lo convierte en unitario).
  void normalize();

  // --- Funciones estáticas ---

  /// Calcula la distancia entre dos vectores.
  static float distance(const CVector4& a, const CVector4& b);

  /// Realiza una interpolación lineal entre dos vectores.
  /// @param t Valor entre 0 y 1.
  static CVector4 lerp(const CVector4& a, const CVector4& b, float t);

  /// Retorna el vector (0, 0, 0, 0).
  static CVector4 zero();

  /// Retorna el vector (1, 1, 1, 1).
  static CVector4 one();

  // --- Impresión del vector ---

  /// Imprime el vector en consola en formato CVector4(x, y, z, w).
  friend std::ostream& operator<<(std::ostream& os, const CVector4& v);
};
