#include <iostream>
#include "../include/Vector/CQuaternion.h"

using namespace std;
using namespace EngineMathLib;

void testCQuaternion() {
  int opcion;
  double w, x, y, z, escalar;
  CQuaternion q1, q2;

  do {
    cout << "\n=== Menu - Prueba de CQuaternion ===\n";
    cout << "1. Ingresar quaterniones\n";
    cout << "2. Suma y resta\n";
    cout << "3. Multiplicacion (quaternion y escalar)\n";
    cout << "4. Conjugado e inversa\n";
    cout << "5. Normalizacion y longitud\n";
    cout << "6. Comparacion (==, !=)\n";
    cout << "0. Salir\n";
    cout << "Seleccione una opcion: ";
    cin >> opcion;

    switch (opcion) {
    case 1:
      cout << "Quaternion 1 (w x y z): ";
      cin >> w >> x >> y >> z;
      q1 = CQuaternion(x, y, z, w);
      cout << "Quaternion 2 (w x y z): ";
      cin >> w >> x >> y >> z;
      q2 = CQuaternion(x, y, z, w);
      cout << "Quaterniones ingresados:\nq1 = " << q1 << "\nq2 = " << q2 << endl;
      break;

    case 2:
      cout << "q1 + q2 = " << (q1 + q2) << endl;
      cout << "q1 - q2 = " << (q1 - q2) << endl;
      break;

    case 3:
      cout << "Escalar para multiplicar q1: ";
      cin >> escalar;
      cout << "q1 * " << escalar << " = " << (q1 * escalar) << endl;
      cout << "q1 * q2 = " << (q1 * q2) << endl;
      break;

    case 4:
      cout << "Conjugado de q1 = " << q1.conjugate() << endl;
      if (q1.lengthSquared() > EPSILON) {
        cout << "Inversa de q1 = " << q1.inverse() << endl;
      }
      else {
        cout << "q1 no es invertible (longitud cero).\n";
      }
      break;

    case 5:
      cout << "Longitud de q1 = " << q1.length() << endl;
      cout << "q1 normalizado = " << q1.normalized() << endl;
      break;

    case 6:
      cout << "q1 == q2 -> " << (q1 == q2 ? "true" : "false") << endl;
      cout << "q1 != q2 -> " << (q1 != q2 ? "true" : "false") << endl;
      break;

    case 0:
      cout << "Saliendo...\n";
      break;

    default:
      cout << "Opcion no valida.\n";
      break;
    }
  } while (opcion != 0);
}
