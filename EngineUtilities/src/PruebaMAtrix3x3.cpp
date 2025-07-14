#include <iostream>
#include "../include/Matrix/Matrix3x3.h"

using namespace std;
using namespace EngineMathLib;

void testMatrix3x3() {
  cout << "=== Test Matrix3x3 ===\n";

  Matrix3x3 m1; // identidad
  Matrix3x3 m2 = Matrix3x3::Escalar(2.0, 3.0);
  Matrix3x3 m3 = Matrix3x3::Rotar(3.14159265358979323846 / 4); // 45 grados

  cout << "Matriz identidad:\n";
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j)
      cout << m1.m[i][j] << " ";
    cout << "\n";
  }

  cout << "Matriz escalado (2,3):\n";
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j)
      cout << m2.m[i][j] << " ";
    cout << "\n";
  }

  cout << "Matriz rotación 45°:\n";
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j)
      cout << m3.m[i][j] << " ";
    cout << "\n";
  }

  Matrix3x3 suma = m2 + m3;
  cout << "Suma de escalado y rotación:\n";
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j)
      cout << suma.m[i][j] << " ";
    cout << "\n";
  }

  Matrix3x3 mul = m2 * m3;
  cout << "Multiplicación de escalado por rotación:\n";
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j)
      cout << mul.m[i][j] << " ";
    cout << "\n";
  }

  cout << "Determinante de rotación: " << m3.Determinante() << "\n";

  Matrix3x3 inv = m3.Inversa();
  cout << "Matriz inversa de rotación:\n";
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j)
      cout << inv.m[i][j] << " ";
    cout << "\n";
  }

  Matrix3x3 trans = m3.Transpuesta();
  cout << "Matriz transpuesta de rotación:\n";
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j)
      cout << trans.m[i][j] << " ";
    cout << "\n";
  }
  cout << "=======================\n";
}
