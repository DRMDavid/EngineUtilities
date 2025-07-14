#pragma once
#include "../Utilities/EngineMath.h"
#include <ostream>

namespace EngineMathLib {

  /**
   * @class CVector4
   * @brief Representa un vector 4D con operaciones básicas y utilidades.
   *
   * La clase soporta operaciones aritméticas, comparaciones, normalización,
   * cálculo de magnitud, producto punto, así como funciones estáticas
   * útiles como distancia y interpolación lineal.
   */
  class CVector4 {
  private:
    double x; ///< Componente X del vector
    double y; ///< Componente Y del vector
    double z; ///< Componente Z del vector
    double w; ///< Componente W del vector

  public:
    // --- Constructores ---

    /**
     * @brief Constructor por defecto que inicializa el vector a (0,0,0,0).
     */
    CVector4() : x(0.0), y(0.0), z(0.0), w(0.0) {}

    /**
     * @brief Constructor que inicializa el vector con valores específicos.
     * @param xVal Valor para la componente X.
     * @param yVal Valor para la componente Y.
     * @param zVal Valor para la componente Z.
     * @param wVal Valor para la componente W.
     */
    CVector4(double xVal, double yVal, double zVal, double wVal) : x(xVal), y(yVal), z(zVal), w(wVal) {}

    // --- Operadores aritméticos ---

    CVector4 operator+(const CVector4& o) const {
      return CVector4(x + o.x, y + o.y, z + o.z, w + o.w);
    }

    CVector4 operator-(const CVector4& o) const {
      return CVector4(x - o.x, y - o.y, z - o.z, w - o.w);
    }

    CVector4 operator*(double escalar) const {
      return CVector4(x * escalar, y * escalar, z * escalar, w * escalar);
    }

    CVector4 operator/(double escalar) const {
      return (escalar != 0.0) ? CVector4(x / escalar, y / escalar, z / escalar, w / escalar) : CVector4(0.0, 0.0, 0.0, 0.0);
    }

    // --- Asignación compuesta ---

    CVector4& operator+=(const CVector4& o) {
      x += o.x; y += o.y; z += o.z; w += o.w; return *this;
    }

    CVector4& operator-=(const CVector4& o) {
      x -= o.x; y -= o.y; z -= o.z; w -= o.w; return *this;
    }

    CVector4& operator*=(double escalar) {
      x *= escalar; y *= escalar; z *= escalar; w *= escalar; return *this;
    }

    CVector4& operator/=(double escalar) {
      if (escalar != 0.0) { x /= escalar; y /= escalar; z /= escalar; w /= escalar; }
      return *this;
    }

    // --- Comparaciones ---

    bool operator==(const CVector4& o) const {
      return EngineMathLib::iguales(x, o.x) && EngineMathLib::iguales(y, o.y) &&
        EngineMathLib::iguales(z, o.z) && EngineMathLib::iguales(w, o.w);
    }

    bool operator!=(const CVector4& o) const {
      return !(*this == o);
    }

    // --- Acceso por índice ---

    double& operator[](int i) {
      switch (i) {
      case 0: return x;
      case 1: return y;
      case 2: return z;
      case 3: return w;
      default: return x; // Por defecto retorna x si índice inválido
      }
    }

    const double& operator[](int i) const {
      switch (i) {
      case 0: return x;
      case 1: return y;
      case 2: return z;
      case 3: return w;
      default: return x; // Por defecto retorna x si índice inválido
      }
    }

    // --- Magnitud y operaciones vectoriales ---

    double lengthSquare() const {
      return x * x + y * y + z * z + w * w;
    }

    double length() const {
      return EngineMathLib::raizCuadrada(lengthSquare());
    }

    double dot(const CVector4& o) const {
      return x * o.x + y * o.y + z * o.z + w * o.w;
    }

    CVector4 normalized() const {
      double len = length();
      return (len > 0.0) ? (*this / len) : CVector4(0.0, 0.0, 0.0, 0.0);
    }

    void normalize() {
      double len = length();
      if (len > 0.0) {
        x /= len; y /= len; z /= len; w /= len;
      }
    }

    // --- Funciones estáticas ---

    /**
     * @brief Calcula la distancia euclidiana entre dos vectores 4D.
     * @param a Primer vector 4D.
     * @param b Segundo vector 4D.
     * @return Distancia euclidiana entre los vectores a y b.
     */
    static double distance(const CVector4& a, const CVector4& b) {
      double dx = a.x - b.x;
      double dy = a.y - b.y;
      double dz = a.z - b.z;
      double dw = a.w - b.w;
      return EngineMathLib::raizCuadrada(dx * dx + dy * dy + dz * dz + dw * dw);
    }

    static CVector4 lerp(const CVector4& a, const CVector4& b, double t) {
      return CVector4(
        EngineMathLib::interpolacion(a.x, b.x, t),
        EngineMathLib::interpolacion(a.y, b.y, t),
        EngineMathLib::interpolacion(a.z, b.z, t),
        EngineMathLib::interpolacion(a.w, b.w, t)
      );
    }

    static CVector4 zero() {
      return CVector4(0.0, 0.0, 0.0, 0.0);
    }

    static CVector4 one() {
      return CVector4(1.0, 1.0, 1.0, 1.0);
    }

    // --- Métodos de transformación ---

    /**
     * @brief Establece la posición del vector.
     * @param pos Vector con la posición deseada.
     */
    void setPosition(const CVector4& pos) {
      x = pos.x; y = pos.y; z = pos.z; w = pos.w;
    }

    /**
     * @brief Mueve el vector por un desplazamiento.
     * @param offset Vector que indica el desplazamiento.
     */
    void move(const CVector4& offset) {
      x += offset.x; y += offset.y; z += offset.z; w += offset.w;
    }

    /**
     * @brief Establece la escala del vector.
     * @param factors Vector con los factores de escala para cada componente.
     */
    void setScale(const CVector4& factors) {
      x = factors.x; y = factors.y; z = factors.z; w = factors.w;
    }

    /**
     * @brief Escala el vector multiplicando por factores.
     * @param factors Vector con los factores de escala para cada componente.
     */
    void scale(const CVector4& factors) {
      x *= factors.x; y *= factors.y; z *= factors.z; w *= factors.w;
    }

    // --- Impresión ---

    friend std::ostream& operator<<(std::ostream& os, const CVector4& v) {
      os << "CVector4(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
      return os;
    }
  };

}
