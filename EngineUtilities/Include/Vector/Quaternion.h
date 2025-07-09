// CQuaternion.h - Cuaterni�n para rotaciones en 3D
// Autor: David S�nchez | Fecha: [Fecha de creaci�n]

#pragma once

#include "../Utilities/EngineMath.h"
#include "CVector3.h"

/// Clase que representa un cuaterni�n, �til para rotaciones en 3D sin gimbal lock.
class CQuaternion {
public:
  float x, y, z, w;

  /// Constructor por defecto. Inicializa como cuaterni�n identidad.
  CQuaternion() : x(0), y(0), z(0), w(1) {}

  /// Constructor con valores personalizados.
  /// @param x Componente X.
  /// @param y Componente Y.
  /// @param z Componente Z.
  /// @param w Componente W.
  CQuaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

  // --- Operaciones b�sicas ---

  /// Multiplicaci�n entre cuaterniones.
  CQuaternion operator*(const CQuaternion& q) const;

  /// Multiplicaci�n por un escalar.
  CQuaternion operator*(float escalar) const;

  /// Suma de cuaterniones.
  CQuaternion operator+(const CQuaternion& q) const;

  /// Resta de cuaterniones.
  CQuaternion operator-(const CQuaternion& q) const;

  // --- M�todos de normalizaci�n ---

  /// Normaliza el cuaterni�n actual (modifica el objeto).
  void normalize();

  /// Retorna una copia normalizada del cuaterni�n.
  CQuaternion normalized() const;

  // --- Otras operaciones ---

  /// Retorna el conjugado del cuaterni�n.
  CQuaternion conjugate() const;

  /// Rota un vector 3D usando el cuaterni�n actual.
  CVector3 rotate(const CVector3& v) const;

  // --- M�todos est�ticos ---

  /// Crea un cuaterni�n a partir de un eje y un �ngulo (en radianes).
  /// El eje debe estar normalizado.
  static CQuaternion fromAxisAngle(const CVector3& eje, float anguloRad);

  /// Interpolaci�n esf�rica (SLERP) entre dos cuaterniones.
  /// @param a Cuaterni�n inicial.
  /// @param b Cuaterni�n final.
  /// @param t Valor de interpolaci�n (entre 0 y 1).
  static CQuaternion slerp(const CQuaternion& a, const CQuaternion& b, float t);

  // --- Impresi�n ---

  /// Imprime el cuaterni�n en consola con el formato CQuaternion(x, y, z, w).
  friend std::ostream& operator<<(std::ostream& os, const CQuaternion& q);
};
