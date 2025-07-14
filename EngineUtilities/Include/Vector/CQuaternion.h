#pragma once
#include "../Utilities/EngineMath.h"
#include <iostream> 

namespace EngineMathLib {

  /**
   * @class CQuaternion
   * @brief Representa un cuaternión para rotaciones y cálculos en 3D.
   *
   * Un cuaternión es una extensión de los números complejos que permite representar
   * rotaciones en 3D sin problemas como el gimbal lock que afectan a los ángulos de Euler.
   * Está compuesto por un vector (x, y, z) y un escalar w.
   */
  class CQuaternion {
  public:
    /// Componente x del vector
    double x;
    /// Componente y del vector
    double y;
    /// Componente z del vector
    double z;
    /// Componente escalar w
    double w;

    /**
     * @brief Constructor por defecto.
     * Inicializa el cuaternión identidad (sin rotación): (0, 0, 0, 1).
     */
    CQuaternion() : x(0), y(0), z(0), w(1) {}

    /**
     * @brief Constructor con valores explícitos.
     * @param _x Componente x.
     * @param _y Componente y.
     * @param _z Componente z.
     * @param _w Componente escalar w.
     */
    CQuaternion(double _x, double _y, double _z, double _w) : x(_x), y(_y), z(_z), w(_w) {}

    /**
     * @brief Calcula la longitud (norma) del cuaternión.
     * @return La norma sqrt(x² + y² + z² + w²).
     */
    double length() const {
      return EngineMathLib::raizCuadrada(x * x + y * y + z * z + w * w);
    }

    /**
     * @brief Calcula la longitud al cuadrado del cuaternión.
     * Útil para comparaciones sin hacer raíz cuadrada.
     * @return Norma al cuadrado.
     */
    double lengthSquared() const {
      return x * x + y * y + z * z + w * w;
    }

    /**
     * @brief Normaliza el cuaternión para que tenga longitud 1.
     * Modifica el objeto actual.
     */
    void normalize() {
      double len = length();
      if (len > EngineMathLib::EPSILON) {
        double invLen = 1.0 / len;
        x *= invLen; y *= invLen; z *= invLen; w *= invLen;
      }
    }

    /**
     * @brief Devuelve un cuaternión normalizado sin modificar el original.
     * @return Una copia normalizada del cuaternión.
     */
    CQuaternion normalized() const {
      CQuaternion q(*this);
      q.normalize();
      return q;
    }

    /**
     * @brief Calcula el conjugado del cuaternión.
     * Invierte el vector (x,y,z) y mantiene el escalar w.
     * @return El cuaternión conjugado.
     */
    CQuaternion conjugate() const {
      return CQuaternion(-x, -y, -z, w);
    }

    /**
     * @brief Calcula la inversa del cuaternión.
     * La inversa se usa para deshacer una rotación.
     * Si la longitud es muy pequeña, devuelve el cuaternión identidad para evitar errores.
     * @return El cuaternión inverso.
     */
    CQuaternion inverse() const {
      double lenSq = lengthSquared();
      if (lenSq < EngineMathLib::EPSILON)
        return CQuaternion(); // identidad
      CQuaternion conj = conjugate();
      double invLenSq = 1.0 / lenSq;
      return CQuaternion(conj.x * invLenSq, conj.y * invLenSq, conj.z * invLenSq, conj.w * invLenSq);
    }

    /**
     * @brief Indica si el cuaternión es invertible.
     * @return true si la longitud al cuadrado es mayor que EPSILON.
     */
    bool isInvertible() const {
      return lengthSquared() > EngineMathLib::EPSILON;
    }

    /**
     * @brief Suma de cuaterniones.
     * @param o Cuaternión a sumar.
     * @return Resultado de la suma.
     */
    CQuaternion operator+(const CQuaternion& o) const {
      return CQuaternion(x + o.x, y + o.y, z + o.z, w + o.w);
    }

    /**
     * @brief Resta de cuaterniones.
     * @param o Cuaternión a restar.
     * @return Resultado de la resta.
     */
    CQuaternion operator-(const CQuaternion& o) const {
      return CQuaternion(x - o.x, y - o.y, z - o.z, w - o.w);
    }

    /**
     * @brief Producto entre dos cuaterniones.
     * @param o Cuaternión derecho.
     * @return Producto de cuaterniones (composición de rotaciones).
     */
    CQuaternion operator*(const CQuaternion& o) const {
      return CQuaternion(
        w * o.x + x * o.w + y * o.z - z * o.y,
        w * o.y - x * o.z + y * o.w + z * o.x,
        w * o.z + x * o.y - y * o.x + z * o.w,
        w * o.w - x * o.x - y * o.y - z * o.z
      );
    }

    /**
     * @brief Multiplicación por escalar.
     * @param s Escalar.
     * @return Cuaternión escalado.
     */
    CQuaternion operator*(double s) const {
      return CQuaternion(x * s, y * s, z * s, w * s);
    }

    /**
     * @brief Compara igualdad entre cuaterniones (dentro de un margen EPSILON).
     * @param o Cuaternión a comparar.
     * @return true si son iguales dentro de EPSILON.
     */
    bool operator==(const CQuaternion& o) const {
      return EngineMathLib::valorAbs(x - o.x) < EngineMathLib::EPSILON &&
        EngineMathLib::valorAbs(y - o.y) < EngineMathLib::EPSILON &&
        EngineMathLib::valorAbs(z - o.z) < EngineMathLib::EPSILON &&
        EngineMathLib::valorAbs(w - o.w) < EngineMathLib::EPSILON;
    }

    /**
     * @brief Compara desigualdad entre cuaterniones.
     * @param o Cuaternión a comparar.
     * @return true si son diferentes.
     */
    bool operator!=(const CQuaternion& o) const {
      return !(*this == o);
    }

    /**
     * @brief Sobrecarga del operador de inserción para imprimir el cuaternión.
     * @param os Stream de salida.
     * @param q Cuaternión a imprimir.
     * @return Stream de salida.
     */
    friend std::ostream& operator<<(std::ostream& os, const CQuaternion& q) {
      os << "(" << q.x << ", " << q.y << ", " << q.z << ", " << q.w << ")";
      return os;
    }
  };

} 
