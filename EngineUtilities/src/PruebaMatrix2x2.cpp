#include <iostream>
#include "../include/Matrix/Matrix2x2.h"

using namespace std;
using namespace EngineMathLib;

void testMatrix2x2() {
  int option;
  Matrix2x2 m1, m2;
  double scalar;

  do {
    cout << "\n=== Menú - Prueba de Matrix2x2 ===\n";
    cout << "1. Ingresar matrices\n";
    cout << "2. Operaciones aritméticas (+, -, *, escalares)\n";
    cout << "3. Operadores de asignación (+=, -=, *=)\n";
    cout << "4. Determinante\n";
    cout << "5. Transpuesta\n";
    cout << "6. Inversa\n";
    cout << "7. Comparación (==, !=)\n";
    cout << "8. Salir\n";
    cout << "Seleccione una opción: ";
    cin >> option;

    switch (option) {
    case 1:
      cout << "Ingrese 4 elementos para la matriz 1 (fila por fila):\n";
      for (int i = 0; i < 4; ++i) {
        cout << "Elemento [" << i / 2 << "," << i % 2 << "]: ";
        cin >> m1[i];
      }
      cout << "Ingrese 4 elementos para la matriz 2 (fila por fila):\n";
      for (int i = 0; i < 4; ++i) {
        cout << "Elemento [" << i / 2 << "," << i % 2 << "]: ";
        cin >> m2[i];
      }
      cout << "Matrices ingresadas:\nM1 =\n" << m1 << "\nM2 =\n" << m2 << endl;
      break;

    case 2:
      cout << "M1 + M2 =\n" << (m1 + m2) << endl;
      cout << "M1 - M2 =\n" << (m1 - m2) << endl;
      cout << "Ingrese escalar para multiplicar M1: ";
      cin >> scalar;
      cout << "M1 * " << scalar << " =\n" << (m1 * scalar) << endl;
      cout << "M1 * M2 =\n" << (m1 * m2) << endl;
      break;

    case 3:
      m1 += m2;
      cout << "M1 += M2 -> M1 =\n" << m1 << endl;
      m1 -= m2;
      cout << "M1 -= M2 -> M1 =\n" << m1 << endl;
      cout << "Ingrese escalar para M1 *= escalar: ";
      cin >> scalar;
      m1 *= scalar;
      cout << "M1 *= " << scalar << " -> M1 =\n" << m1 << endl;
      break;

    case 4:
      cout << "Determinante de M1 = " << m1.Determinante() << endl;
      break;

    case 5:
      cout << "Transpuesta de M1 =\n" << m1.Transpuesta() << endl;
      break;

    case 6:
      if (m1.isInvertible()) {
        cout << "Inversa de M1 =\n" << m1.Inversa() << endl;
      }
      else {
        cout << "M1 no es invertible.\n";
      }
      break;

    case 7:
      cout << "M1 == M2 -> " << (m1 == m2 ? "true" : "false") << endl;
      cout << "M1 != M2 -> " << (m1 != m2 ? "true" : "false") << endl;
      break;

    case 8:
      cout << "Saliendo de la prueba de Matrix2x2...\n";
      break;

    default:
      cout << "Opción no válida.\n";
      break;
    }
  } while (option != 8);
}
