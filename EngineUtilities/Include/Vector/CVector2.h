// CVector2.h - Vector 2D con operaciones básicas y utilidades


#pragma once
#include "../Utilities/EngineMath.h"
#include <ostream>

namespace EngineMath {

  /// Clase para representar un vector en 2D con operaciones matemáticas comunes.
  class CVector2 {
  private:
    float x, y;

  public:
    /// Constructor por defecto. Crea un vector (0, 0).
    CVector2() : x(0), y(0) {}

    /// Constructor con valores personalizados.
    /// @param xVal Valor en el eje X.
    /// @param yVal Valor en el eje Y.
    CVector2(float xVal, float yVal) : x(xVal), y(yVal) {}

    // --- Operadores aritméticos ---

    /// Suma dos vectores.
    CVector2 operator+(const CVector2& o) const;

    /// Resta dos vectores.
    CVector2 operator-(const CVector2& o) const;

    /// Multiplica el vector por un escalar.
    CVector2 operator*(float escalar) const;

    /// Divide el vector entre un escalar.
    CVector2 operator/(float escalar) const;

    // --- Asignaciones compuestas ---

    /// Suma otro vector al actual.
    CVector2& operator+=(const CVector2& o);

    /// Resta otro vector al actual.
    CVector2& operator-=(const CVector2& o);

    /// Multiplica el vector actual por un escalar.
    CVector2& operator*=(float escalar);

    /// Divide el vector actual entre un escalar.
    CVector2& operator/=(float escalar);

    // --- Comparaciones ---

    /// Compara si dos vectores son aproximadamente iguales.
    bool operator==(const CVector2& o) const;

    /// Compara si dos vectores son diferentes.
    bool operator!=(const CVector2& o) const;

    // --- Acceso por índice ---

    /// Accede a una componente por índice (0: X, 1: Y).
    float& operator[](int i);

    /// Accede a una componente por índice (0: X, 1: Y) (versión constante).
    const float& operator[](int i) const;

    // --- Magnitud y operaciones vectoriales ---

    /// Retorna la longitud al cuadrado del vector.
    float lengthSquare() const;

    /// Retorna la magnitud (longitud) del vector.
    float length() const;

    /// Calcula el producto punto entre dos vectores.
    float dot(const CVector2& o) const;

    /// Calcula el producto cruzado escalar (z) entre dos vectores 2D.
    float cross(const CVector2& o) const;

    /// Retorna una copia normalizada del vector (longitud = 1).
    CVector2 normalized() const;

    /// Normaliza el vector actual (lo convierte en unitario).
    void normalize();

    // --- Funciones estáticas ---

    /// Calcula la distancia entre dos vectores.
    static float distance(const CVector2& a, const CVector2& b);

    /// Realiza una interpolación lineal entre dos vectores.
    /// @param t Valor entre 0 y 1.
    static CVector2 lerp(const CVector2& a, const CVector2& b, float t);

    /// Retorna el vector (0, 0).
    static CVector2 zero();

    /// Retorna el vector (1, 1).
    static CVector2 one();

    // --- Manipulación del vector ---

    /// Asigna una nueva posición al vector.
    void setPosition(const CVector2& pos);

    /// Desplaza el vector por un desplazamiento dado.
    void move(const CVector2& offset);

    /// Escala el vector usando factores dados.
    void setScale(const CVector2& factors);

    /// Escala el vector multiplicando por factores dados.
    void scale(const CVector2& factors);

    /// Asigna un nuevo origen al vector.
    void setOrigin(const CVector2& origin);

    // --- Impresión del vector ---

    /// Imprime el vector en la consola en formato CVector2(x, y).
    friend std::ostream& operator<<(std::ostream& os, const CVector2& v);
  };

} 
