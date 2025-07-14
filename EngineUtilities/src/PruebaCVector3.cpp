#include <iostream>
#include "../include/Vector/CVector3.h"
using namespace std;
using namespace EngineMathLib;

void testCVector3() {
  int option;
  double x1, y1, z1, x2, y2, z2, scalar;
  CVector3 v1, v2;

  do {
    cout << "\n=== Menu - Prueba de CVector3 ===\n";
    cout << "1. Ingresar vectores\n";
    cout << "2. Operadores basicos (+, -, *, /)\n";
    cout << "3. Operadores de asignacion (+=, -=, *=, /=)\n";
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
      cout << "Vector 1 (x y z): ";
      cin >> x1 >> y1 >> z1;
      v1 = CVector3(x1, y1, z1);

      cout << "Vector 2 (x y z): ";
      cin >> x2 >> y2 >> z2;
      v2 = CVector3(x2, y2, z2);

      cout << "v1 = " << v1 << "\nv2 = " << v2 << endl;
      break;

    case 2:
      cout << "Escalar para multiplicar/dividir: ";
      cin >> scalar;

      cout << "v1 + v2 = " << (v1 + v2) << endl;
      cout << "v1 - v2 = " << (v1 - v2) << endl;
      cout << "v1 * " << scalar << " = " << (v1 * scalar) << endl;
      if (scalar != 0.0)
        cout << "v1 / " << scalar << " = " << (v1 / scalar) << endl;
      else
        cout << "No se puede dividir por cero.\n";
      break;

    case 3:
      cout << "Escalar para asignaciones: ";
      cin >> scalar;

      {
        CVector3 temp = v1;
        temp += v2;
        cout << "v1 += v2 = " << temp << endl;

        temp = v1;
        temp -= v2;
        cout << "v1 -= v2 = " << temp << endl;

        temp = v1;
        temp *= scalar;
        cout << "v1 *= " << scalar << " = " << temp << endl;

        if (scalar != 0.0) {
          temp = v1;
          temp /= scalar;
          cout << "v1 /= " << scalar << " = " << temp << endl;
        }
        else {
          cout << "No se puede dividir por cero.\n";
        }
      }
      break;

    case 4:
      cout << "v1 == v2 -> " << (v1 == v2 ? "true" : "false") << endl;
      cout << "v1 != v2 -> " << (v1 != v2 ? "true" : "false") << endl;
      break;

    case 5: {
      int index;
      cout << "Indice [0=x, 1=y, 2=z]: ";
      cin >> index;
      if (index >= 0 && index <= 2)
        cout << "v1[" << index << "] = " << v1[index] << endl;
      else
        cout << "Indice invalido.\n";
      break;
    }

    case 6:
      cout << "lengthSquared(v1) = " << v1.lengthSquare() << endl;
      cout << "length(v1) = " << v1.length() << endl;
      break;

    case 7:
      cout << "dot(v1, v2) = " << v1.dot(v2) << endl;
      cout << "cross(v1, v2) = " << v1.cross(v2) << endl;
      break;

    case 8: {
      CVector3 copy = v1;
      copy.normalize();

      cout << "normalized(v1) = " << v1.normalized() << endl;
      cout << "normalized(v2) = " << v2.normalized() << endl;
      cout << "normalize(v1) = " << copy << endl;
      break;
    }

    case 9:
      cout << "distance(v1, v2) = " << CVector3::distance(v1, v2) << endl;
      cout << "lerp(v1, v2, 0.5) = " << CVector3::lerp(v1, v2, 0.5) << endl;
      cout << "zero() = " << CVector3::zero() << endl;
      cout << "one() = " << CVector3::one() << endl;
      break;

    case 10: {
      CVector3 position, offset, scale;

      cout << "Nueva posicion (x y z): ";
      cin >> position[0] >> position[1] >> position[2];
      v1.setPosition(position);
      cout << "setPosition -> v1 = " << v1 << endl;

      cout << "Desplazamiento (x y z): ";
      cin >> offset[0] >> offset[1] >> offset[2];
      v1.move(offset);
      cout << "move -> v1 = " << v1 << endl;

      cout << "Factores de escala (x y z): ";
      cin >> scale[0] >> scale[1] >> scale[2];
      v1.setScale(scale);
      cout << "setScale -> v1 = " << v1 << endl;

      v1.scale(scale);
      cout << "scale -> v1 = " << v1 << endl;
      break;
    }

    case 0:
      cout << "Saliendo...\n";
      break;

    default:
      cout << "Opcion no valida.\n";
    }

  } while (option != 0);
}
