#include <iostream>
#include "../include/Vector/CVector2.h"

using namespace std;

void testCVector2() {
  int option;
  double x1 = 3.0, y1 = 4.0, x2 = 1.0, y2 = 2.0, scalar = 2.0, t = 0.5;
  EngineMathLib::CVector2 v1(x1, y1), v2(x2, y2);

  do {
    cout << "\n=== Menu - Prueba de CVector2 ===\n";
    cout << "1. Mostrar vectores actuales\n";
    cout << "2. Operadores basicos (+, -, *, /)\n";
    cout << "3. Operadores asignacion (+=, -=, *=, /=)\n";
    cout << "4. Comparacion (==, !=)\n";
    cout << "5. Acceso a elementos ([])\n";
    cout << "6. Longitud y magnitud\n";
    cout << "7. Producto punto y cruz\n";
    cout << "8. Normalizacion\n";
    cout << "9. Funciones estaticas (distance, lerp, zero, one)\n";
    cout << "10. Modificacion de posicion y escala\n";
    cout << "0. Salir\n";
    cout << "Seleccione una opcion: ";
    cin >> option;

    switch (option) {
    case 1:
      cout << "v1 = " << v1 << ", v2 = " << v2 << endl;
      break;

    case 2: {
      cout << "v1 + v2 = " << (v1 + v2) << endl;
      cout << "v1 - v2 = " << (v1 - v2) << endl;
      cout << "v1 * 2 = " << (v1 * 2.0) << endl;
      cout << "v1 / 2 = " << (v1 / 2.0) << endl;
      break;
    }

    case 3: {
      EngineMathLib::CVector2 tmp = v1;
      tmp += v2;
      cout << "v1 += v2: " << tmp << endl;
      tmp = v1; tmp -= v2;
      cout << "v1 -= v2: " << tmp << endl;
      tmp = v1; tmp *= scalar;
      cout << "v1 *= " << scalar << ": " << tmp << endl;
      tmp = v1; tmp /= scalar;
      cout << "v1 /= " << scalar << ": " << tmp << endl;
      break;
    }

    case 4:
      cout << "v1 == v2: " << (v1 == v2 ? "true" : "false") << endl;
      cout << "v1 != v2: " << (v1 != v2 ? "true" : "false") << endl;
      break;

    case 5:
      cout << "v1[0] = " << v1[0] << ", v1[1] = " << v1[1] << endl;
      break;

    case 6:
      cout << "lengthSquare(v1) = " << v1.lengthSquare() << endl;
      cout << "length(v1) = " << v1.length() << endl;
      break;

    case 7:
      cout << "dot(v1, v2) = " << v1.dot(v2) << endl;
      cout << "cross(v1, v2) = " << v1.cross(v2) << endl;
      break;

    case 8: {
      cout << "normalized(v1) = " << v1.normalized() << endl;
      EngineMathLib::CVector2 norm = v1;
      norm.normalize();
      cout << "normalize() aplicado a v1: " << norm << endl;
      break;
    }

    case 9:
      cout << "distance(v1, v2) = " << EngineMathLib::CVector2::distance(v1, v2) << endl;
      cout << "lerp(v1, v2, 0.5) = " << EngineMathLib::CVector2::lerp(v1, v2, 0.5) << endl;
      cout << "zero() = " << EngineMathLib::CVector2::zero() << endl;
      cout << "one() = " << EngineMathLib::CVector2::one() << endl;
      break;

    case 10: {
      EngineMathLib::CVector2 offset(1, 1);
      v1.setPosition(v2);
      cout << "setPosition(v2) -> v1 = " << v1 << endl;
      v1.move(offset);
      cout << "move(offset) -> v1 = " << v1 << endl;
      v1.setScale(offset);
      cout << "setScale(offset) -> v1 = " << v1 << endl;
      v1.scale(offset);
      cout << "scale(offset) -> v1 = " << v1 << endl;
      break;
    }

    case 0:
      cout << "Saliendo del test.\n";
      break;

    default:
      cout << "Opcion invalida.\n";
    }
  } while (option != 0);
}
