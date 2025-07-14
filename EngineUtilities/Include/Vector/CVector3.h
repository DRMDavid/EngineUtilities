#pragma once
#include "../Utilities/EngineMath.h"
#include <ostream>

namespace EngineMathLib {

  /**
   * @class CVector3
   * @brief Representa un vector 3D con operaciones básicas y utilidades.
   *
   * La clase soporta operaciones aritméticas, comparaciones, normalización,
   * cálculo de magnitud, producto punto y cruz, funciones estáticas útiles como
   * distancia e interpolación lineal, y transformaciones básicas.
   */
  class CVector3 {
  private:
    double x; ///< Componente X del vector
    double y; ///< Componente Y del vector
    double z; ///< Componente Z del vector

  public:
    // --- Constructores ---

    /**
     * @brief Constructor por defecto que inicializa el vector a (0,0,0).
     */
    CVector3() : x(0.0), y(0.0), z(0.0) {}

    /**
     * @brief Constructor que inicializa el vector con valores específicos.
     * @param xVal Valor para la componente X.
     * @param yVal Valor para la componente Y.
     * @param zVal Valor para la componente Z.
     */
    CVector3(double xVal, double yVal, double zVal) : x(xVal), y(yVal), z(zVal) {}

    // --- Operadores aritméticos ---

    CVector3 operator+(const CVector3& o) const {
      return CVector3(x + o.x, y + o.y, z + o.z);
    }

    CVector3 operator-(const CVector3& o) const {
      return CVector3(x - o.x, y - o.y, z - o.z);
    }

    CVector3 operator*(double escalar) const {
      return CVector3(x * escalar, y * escalar, z * escalar);
    }

    CVector3 operator/(double escalar) const {
      return (escalar != 0.0) ? CVector3(x / escalar, y / escalar, z / escalar) : CVector3(0.0, 0.0, 0.0);
    }

    // --- Asignación compuesta ---

    CVector3& operator+=(const CVector3& o) {
      x += o.x; y += o.y; z += o.z; return *this;
    }

    CVector3& operator-=(const CVector3& o) {
      x -= o.x; y -= o.y; z -= o.z; return *this;
    }

    CVector3& operator*=(double escalar) {
      x *= escalar; y *= escalar; z *= escalar; return *this;
    }

    CVector3& operator/=(double escalar) {
      if (escalar != 0.0) { x /= escalar; y /= escalar; z /= escalar; }
      return *this;
    }

    // --- Comparaciones ---

    bool operator==(const CVector3& o) const {
      return EngineMathLib::iguales(x, o.x) && EngineMathLib::iguales(y, o.y) && EngineMathLib::iguales(z, o.z);
    }

    bool operator!=(const CVector3& o) const {
      return !(*this == o);
    }

    // --- Acceso por índice ---

    double& operator[](int i) {
      if (i == 0) return x;
      if (i == 1) return y;
      return z; // índice 2 o por defecto
    }

    const double& operator[](int i) const {
      if (i == 0) return x;
      if (i == 1) return y;
      return z; // índice 2 o por defecto
    }

    // --- Magnitud y operaciones vectoriales ---

    double lengthSquare() const {
      return x * x + y * y + z * z;
    }

    double length() const {
      return EngineMathLib::raizCuadrada(lengthSquare());
    }

    double dot(const CVector3& o) const {
      return x * o.x + y * o.y + z * o.z;
    }

    CVector3 cross(const CVector3& o) const {
      return CVector3(
        y * o.z - z * o.y,
        z * o.x - x * o.z,
        x * o.y - y * o.x
      );
    }

    CVector3 normalized() const {
      double len = length();
      return (len > 0.0) ? (*this / len) : CVector3(0.0, 0.0, 0.0);
    }

    void normalize() {
      double len = length();
      if (len > 0.0) {
        x /= len; y /= len; z /= len;
      }
    }

    // --- Transformaciones ---

    /**
     * @brief Establece la posición del vector.
     * @param pos Vector con la posición deseada.
     */
    void setPosition(const CVector3& pos) {
      x = pos.x;
      y = pos.y;
      z = pos.z;
    }

    /**
     * @brief Mueve el vector por un desplazamiento.
     * @param offset Vector que indica el desplazamiento.
     */
    void move(const CVector3& offset) {
      x += offset.x;
      y += offset.y;
      z += offset.z;
    }

    /**
     * @brief Establece la escala del vector.
     * @param factors Vector con los factores de escala para cada componente.
     */
    void setScale(const CVector3& factors) {
      x = factors.x;
      y = factors.y;
      z = factors.z;
    }

    /**
     * @brief Escala el vector multiplicando por factores.
     * @param factors Vector con los factores de escala para cada componente.
     */
    void scale(const CVector3& factors) {
      x *= factors.x;
      y *= factors.y;
      z *= factors.z;
    }

    // --- Funciones estáticas ---

    /**
     * @brief Calcula la distancia euclidiana entre dos vectores 3D.
     * @param a Primer vector 3D.
     * @param b Segundo vector 3D.
     * @return Distancia entre los vectores a y b.
     */
    static double distance(const CVector3& a, const CVector3& b) {
      double dx = a.x - b.x;
      double dy = a.y - b.y;
      double dz = a.z - b.z;
      return EngineMathLib::raizCuadrada(dx * dx + dy * dy + dz * dz);
    }

    /**
     * @brief Interpolación lineal entre dos vectores 3D.
     * @param a Vector inicial.
     * @param b Vector final.
     * @param t Parámetro de interpolación entre 0 y 1.
     * @return Vector interpolado.
     */
    static CVector3 lerp(const CVector3& a, const CVector3& b, double t) {
      return CVector3(
        EngineMathLib::interpolacion(a.x, b.x, t),
        EngineMathLib::interpolacion(a.y, b.y, t),
        EngineMathLib::interpolacion(a.z, b.z, t)
      );
    }

    /**
     * @brief Vector nulo (0,0,0).
     * @return Vector con todas las componentes en cero.
     */
    static CVector3 zero() {
      return CVector3(0.0, 0.0, 0.0);
    }

    /**
     * @brief Vector con todas las componentes en uno (1,1,1).
     * @return Vector con todas las componentes en uno.
     */
    static CVector3 one() {
      return CVector3(1.0, 1.0, 1.0);
    }

    // --- Impresión ---

    friend std::ostream& operator<<(std::ostream& os, const CVector3& v) {
      os << "CVector3(" << v.x << ", " << v.y << ", " << v.z << ")";
      return os;
    }
  };

} 
