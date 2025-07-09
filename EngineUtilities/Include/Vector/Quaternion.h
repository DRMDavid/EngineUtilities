// CQuaternion.h - Cuaternión para rotaciones en 3D
// Autor: David Sánchez | Fecha: [Fecha de creación]

#pragma once

#include "../Utilities/EngineMath.h"
#include "CVector3.h"

/// Clase que representa un cuaternión, útil para rotaciones en 3D sin gimbal lock.
class CQuaternion {
public:
  float x, y, z, w;

  /// Constructor por defecto. Inicializa como cuaternión identidad.
  CQuaternion() : x(0), y(0), z(0), w(1) {}

  /// Constructor con valores personalizados.
  /// @param x Componente X.
  /// @param y Componente Y.
  /// @param z Componente Z.
  /// @param w Componente W.
  CQuaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

  // --- Operaciones básicas ---

  /// Multiplicación entre cuaterniones.
  CQuaternion operator*(const CQuaternion& q) const;

  /// Multiplicación por un escalar.
  CQuaternion operator*(float escalar) const;

  /// Suma de cuaterniones.
  CQuaternion operator+(const CQuaternion& q) const;

  /// Resta de cuaterniones.
  CQuaternion operator-(const CQuaternion& q) const;

  // --- Métodos de normalización ---

  /// Normaliza el cuaternión actual (modifica el objeto).
  void normalize();

  /// Retorna una copia normalizada del cuaternión.
  CQuaternion normalized() const;

  // --- Otras operaciones ---

  /// Retorna el conjugado del cuaternión.
  CQuaternion conjugate() const;

  /// Rota un vector 3D usando el cuaternión actual.
  CVector3 rotate(const CVector3& v) const;

  // --- Métodos estáticos ---

  /// Crea un cuaternión a partir de un eje y un ángulo (en radianes).
  /// El eje debe estar normalizado.
  static CQuaternion fromAxisAngle(const CVector3& eje, float anguloRad);

  /// Interpolación esférica (SLERP) entre dos cuaterniones.
  /// @param a Cuaternión inicial.
  /// @param b Cuaternión final.
  /// @param t Valor de interpolación (entre 0 y 1).
  static CQuaternion slerp(const CQuaternion& a, const CQuaternion& b, float t);

  // --- Impresión ---

  /// Imprime el cuaternión en consola con el formato CQuaternion(x, y, z, w).
  friend std::ostream& operator<<(std::ostream& os, const CQuaternion& q);
};
