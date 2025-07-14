#include <iostream>
#include "../include/Matrix/Matrix4x4.h"

using namespace std;
using namespace EngineMathLib;

void testMatrix4x4() {
  cout << "=== Test Matrix4x4 ===\n";

  Matrix4x4 m1; // identidad
  Matrix4x4 m2(2, 0, 0, 0,
    0, 3, 0, 0,
    0, 0, 4, 0,
    0, 0, 0, 1);
  Matrix4x4 m3;
  double ang = 3.14159265358979323846 / 4; // 45 grados
  // Para simplificar la prueba, vamos a crear una matriz de rotación manual:
  // Ejemplo de rotación simple sobre eje Z (ignorar ejes para pruebas)
  m3 = Matrix4x4(
    cos(ang), -sin(ang), 0, 0,
    sin(ang), cos(ang), 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
  );

  cout << "Matriz identidad:\n";
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j)
      cout << m1.m[i][j] << " ";
    cout << "\n";
  }

  cout << "Matriz escalado:\n";
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j)
      cout << m2.m[i][j] << " ";
    cout << "\n";
  }

  cout << "Matriz rotación 45° eje Z:\n";
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j)
      cout << m3.m[i][j] << " ";
    cout << "\n";
  }

  Matrix4x4 suma = m2 + m3;
  cout << "Suma de escalado y rotación:\n";
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j)
      cout << suma.m[i][j] << " ";
    cout << "\n";
  }

  Matrix4x4 mul = m2 * m3;
  cout << "Multiplicación de escalado por rotación:\n";
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j)
      cout << mul.m[i][j] << " ";
    cout << "\n";
  }

  cout << "Determinante de rotación: " << m3.Determinante() << "\n";

  Matrix4x4 inv = m3.Inversa();
  cout << "Matriz inversa de rotación:\n";
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j)
      cout << inv.m[i][j] << " ";
    cout << "\n";
  }

  Matrix4x4 trans = m3.Transpuesta();
  cout << "Matriz transpuesta de rotación:\n";
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j)
      cout << trans.m[i][j] << " ";
    cout << "\n";
  }
  cout << "=======================\n";
}
