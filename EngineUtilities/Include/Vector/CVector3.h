// CVector3.h - Vector 3D con operaciones básicas y utilidades

#pragma once
#include "../Utilities/EngineMath.h"
#include <ostream>

/// Clase para representar un vector en 3D con operaciones matemáticas comunes.
class CVector3 {
public:
  float x, y, z;

  /// Constructor por defecto. Inicializa el vector en (0, 0, 0).
  CVector3() : x(0), y(0), z(0) {}

  /// Constructor con valores personalizados.
  /// @param x Valor en el eje X.
  /// @param y Valor en el eje Y.
  /// @param z Valor en el eje Z.
  CVector3(float x, float y, float z) : x(x), y(y), z(z) {}

  // --- Operadores aritméticos ---

  /// Suma dos vectores.
  CVector3 operator+(const CVector3& other) const;

  /// Resta dos vectores.
  CVector3 operator-(const CVector3& other) const;

  /// Multiplica el vector por un escalar.
  CVector3 operator*(float scalar) const;

  /// Divide el vector entre un escalar.
  CVector3 operator/(float scalar) const;

  // --- Asignaciones compuestas ---

  /// Suma otro vector al actual.
  CVector3& operator+=(const CVector3& other);

  /// Resta otro vector al actual.
  CVector3& operator-=(const CVector3& other);

  /// Multiplica el vector actual por un escalar.
  CVector3& operator*=(float scalar);

  /// Divide el vector actual entre un escalar.
  CVector3& operator/=(float scalar);

  // --- Comparaciones ---

  /// Compara si dos vectores son aproximadamente iguales.
  bool operator==(const CVector3& other) const;

  /// Compara si dos vectores son diferentes.
  bool operator!=(const CVector3& other) const;

  // --- Acceso por índice ---

  /// Accede a una componente por índice (0: X, 1: Y, 2: Z).
  float& operator[](int index);

  /// Accede a una componente por índice (0: X, 1: Y, 2: Z) (versión constante).
  const float& operator[](int index) const;

  // --- Magnitud y operaciones vectoriales ---

  /// Retorna la longitud al cuadrado del vector.
  float lengthSquare() const;

  /// Retorna la magnitud (longitud) del vector.
  float length() const;

  /// Calcula el producto punto entre dos vectores.
  float dot(const CVector3& other) const;

  /// Calcula el producto cruzado entre dos vectores.
  CVector3 cross(const CVector3& other) const;

  /// Retorna una copia normalizada del vector (longitud = 1).
  CVector3 normalized() const;

  /// Normaliza el vector actual (lo convierte en unitario).
  void normalize();

  // --- Funciones estáticas ---

  /// Calcula la distancia entre dos vectores.
  static float distance(const CVector3& a, const CVector3& b);

  /// Realiza una interpolación lineal entre dos vectores.
  /// @param t Valor entre 0 y 1.
  static CVector3 lerp(const CVector3& a, const CVector3& b, float t);

  /// Retorna el vector (0, 0, 0).
  static CVector3 zero();

  /// Retorna el vector (1, 1, 1).
  static CVector3 one();

  // --- Impresión del vector ---

  /// Imprime el vector en consola en formato CVector3(x, y, z).
  friend std::ostream& operator<<(std::ostream& os, const CVector3& v);
};
