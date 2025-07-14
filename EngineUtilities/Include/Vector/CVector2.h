#pragma once
#include "../Utilities/EngineMath.h"
#include <ostream>

namespace EngineMathLib {

  /**
   * @class CVector2
   * @brief Representa un vector 2D con operaciones básicas y utilidades.
   *
   * La clase soporta operaciones aritméticas, comparaciones, normalización,
   * cálculo de magnitud, producto punto y cruz, así como funciones estáticas
   * útiles como distancia y interpolación lineal.
   */
  class CVector2 {
  private:
    double x; ///< Componente X del vector
    double y; ///< Componente Y del vector

  public:
    // --- Constructores ---

    /**
     * @brief Constructor por defecto que inicializa el vector a (0,0).
     */
    CVector2() : x(0.0), y(0.0) {}

    /**
     * @brief Constructor que inicializa el vector con valores específicos.
     * @param xVal Valor para la componente X.
     * @param yVal Valor para la componente Y.
     */
    CVector2(double xVal, double yVal) : x(xVal), y(yVal) {}

    // --- Operadores aritméticos ---

    /**
     * @brief Suma de vectores.
     * @param o Vector a sumar.
     * @return Nuevo vector resultado de la suma.
     */
    CVector2 operator+(const CVector2& o) const {
      return CVector2(x + o.x, y + o.y);
    }

    /**
     * @brief Resta de vectores.
     * @param o Vector a restar.
     * @return Nuevo vector resultado de la resta.
     */
    CVector2 operator-(const CVector2& o) const {
      return CVector2(x - o.x, y - o.y);
    }

    /**
     * @brief Multiplicación por un escalar.
     * @param escalar Valor escalar.
     * @return Nuevo vector escalado.
     */
    CVector2 operator*(double escalar) const {
      return CVector2(x * escalar, y * escalar);
    }

    /**
     * @brief División por un escalar.
     * @param escalar Valor escalar.
     * @return Nuevo vector dividido, o vector cero si el escalar es 0.
     */
    CVector2 operator/(double escalar) const {
      return (escalar != 0.0) ? CVector2(x / escalar, y / escalar) : CVector2(0.0, 0.0);
    }

    // --- Asignación compuesta ---

    /**
     * @brief Suma y asigna otro vector.
     * @param o Vector a sumar.
     * @return Referencia al vector modificado.
     */
    CVector2& operator+=(const CVector2& o) {
      x += o.x; y += o.y; return *this;
    }

    /**
     * @brief Resta y asigna otro vector.
     * @param o Vector a restar.
     * @return Referencia al vector modificado.
     */
    CVector2& operator-=(const CVector2& o) {
      x -= o.x; y -= o.y; return *this;
    }

    /**
     * @brief Multiplica y asigna por un escalar.
     * @param escalar Valor escalar.
     * @return Referencia al vector modificado.
     */
    CVector2& operator*=(double escalar) {
      x *= escalar; y *= escalar; return *this;
    }

    /**
     * @brief Divide y asigna por un escalar.
     * @param escalar Valor escalar.
     * @return Referencia al vector modificado.
     */
    CVector2& operator/=(double escalar) {
      if (escalar != 0.0) { x /= escalar; y /= escalar; }
      return *this;
    }

    // --- Comparaciones ---

    /**
     * @brief Compara igualdad aproximada con otro vector.
     * @param o Vector para comparar.
     * @return true si ambos vectores son iguales dentro de una tolerancia.
     */
    bool operator==(const CVector2& o) const {
      return EngineMathLib::iguales(x, o.x) && EngineMathLib::iguales(y, o.y);
    }

    /**
     * @brief Compara desigualdad con otro vector.
     * @param o Vector para comparar.
     * @return true si los vectores son diferentes.
     */
    bool operator!=(const CVector2& o) const {
      return !(*this == o);
    }

    // --- Acceso por índice ---

    /**
     * @brief Acceso mutable a componentes por índice (0 = x, 1 = y).
     * @param i Índice (0 o 1).
     * @return Referencia a la componente correspondiente.
     */
    double& operator[](int i) {
      return (i == 0) ? x : y;
    }

    /**
     * @brief Acceso constante a componentes por índice (0 = x, 1 = y).
     * @param i Índice (0 o 1).
     * @return Referencia constante a la componente correspondiente.
     */
    const double& operator[](int i) const {
      return (i == 0) ? x : y;
    }

    // --- Magnitud y operaciones vectoriales ---

    /**
     * @brief Calcula el cuadrado de la longitud del vector.
     * @return Suma de los cuadrados de las componentes.
     */
    double lengthSquare() const {
      return x * x + y * y;
    }

    /**
     * @brief Calcula la longitud (magnitud) del vector.
     * @return Raíz cuadrada de la suma de los cuadrados de las componentes.
     */
    double length() const {
      return EngineMathLib::raizCuadrada(lengthSquare());
    }

    /**
     * @brief Producto punto con otro vector.
     * @param o Vector con el cual calcular el producto punto.
     * @return Escalar resultado del producto punto.
     */
    double dot(const CVector2& o) const {
      return x * o.x + y * o.y;
    }

    /**
     * @brief Producto cruzado (escalares en 2D).
     * @param o Vector con el cual calcular el producto cruzado.
     * @return Escalar resultado del producto cruzado.
     */
    double cross(const CVector2& o) const {
      return x * o.y - y * o.x;
    }

    /**
     * @brief Retorna un vector normalizado (longitud 1).
     * @return Vector normalizado, o vector cero si la longitud es 0.
     */
    CVector2 normalized() const {
      double len = length();
      return (len > 0.0) ? (*this / len) : CVector2(0.0, 0.0);
    }

    /**
     * @brief Normaliza el vector actual (lo hace unitario).
     */
    void normalize() {
      double len = length();
      if (len > 0.0) {
        x /= len;
        y /= len;
      }
    }

    // --- Funciones estáticas ---

    /**
     * @brief Calcula la distancia euclidiana entre dos vectores.
     * @param a Primer vector.
     * @param b Segundo vector.
     * @return Distancia entre ambos vectores.
     */
    static double distance(const CVector2& a, const CVector2& b) {
      return EngineMathLib::distancia(a.x, a.y, b.x, b.y);
    }

    /**
     * @brief Interpolación lineal entre dos vectores.
     * @param a Vector inicial.
     * @param b Vector final.
     * @param t Parámetro de interpolación entre 0 y 1.
     * @return Vector interpolado.
     */
    static CVector2 lerp(const CVector2& a, const CVector2& b, double t) {
      return CVector2(
        EngineMathLib::interpolacion(a.x, b.x, t),
        EngineMathLib::interpolacion(a.y, b.y, t)
      );
    }

    /**
     * @brief Vector nulo (0,0).
     * @return Vector con ambas componentes en cero.
     */
    static CVector2 zero() {
      return CVector2(0.0, 0.0);
    }

    /**
     * @brief Vector con ambas componentes en uno (1,1).
     * @return Vector con ambas componentes en uno.
     */
    static CVector2 one() {
      return CVector2(1.0, 1.0);
    }

    // --- Transformaciones ---

    /**
     * @brief Establece la posición del vector.
     * @param pos Vector con la posición deseada.
     */
    void setPosition(const CVector2& pos) {
      x = pos.x;
      y = pos.y;
    }

    /**
     * @brief Mueve el vector por un desplazamiento.
     * @param offset Vector que indica el desplazamiento.
     */
    void move(const CVector2& offset) {
      x += offset.x;
      y += offset.y;
    }

    /**
     * @brief Establece la escala del vector.
     * @param factors Vector con los factores de escala para cada componente.
     */
    void setScale(const CVector2& factors) {
      x = factors.x;
      y = factors.y;
    }

    /**
     * @brief Escala el vector multiplicando por factores.
     * @param factors Vector con los factores de escala para cada componente.
     */
    void scale(const CVector2& factors) {
      x *= factors.x;
      y *= factors.y;
    }

    /**
     * @brief Establece el origen del vector.
     * @param origin Vector con la posición del origen.
     */
    void setOrigin(const CVector2& origin) {
      x = origin.x;
      y = origin.y;
    }

    // --- Impresión ---

    /**
     * @brief Sobrecarga del operador de inserción para salida a streams.
     * @param os Stream de salida.
     * @param v Vector a imprimir.
     * @return Referencia al stream de salida.
     */
    friend std::ostream& operator<<(std::ostream& os, const CVector2& v) {
      os << "CVector2(" << v.x << ", " << v.y << ")";
      return os;
    }
  };

}
