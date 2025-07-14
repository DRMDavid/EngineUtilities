#include <iostream>

// Declaración de funciones definidas en los archivos PruebaCVectorX.cpp y similares
void testCVector2();
void testCVector3();
void testCVector4();
void testMatrix2x2();
void testMatrix3x3();
void testMatrix4x4();
void testCQuaternion();

int main() {
  int opcion;

  do {
    std::cout << "\n===== Menú Principal - Pruebas Matematicas =====\n";
    std::cout << "1. Prueba de CVector2\n";
    std::cout << "2. Prueba de CVector3\n";
    std::cout << "3. Prueba de CVector4\n";
    std::cout << "4. Prueba de Matrix2x2\n";
    std::cout << "5. Prueba de Matrix3x3\n";
    std::cout << "6. Prueba de Matrix4x4\n";
    std::cout << "7. Prueba de CQuaternion\n";
    std::cout << "0. Salir\n";
    std::cout << "Seleccione una opcion: ";
    std::cin >> opcion;

    switch (opcion) {
    case 1: testCVector2(); break;
    case 2: testCVector3(); break;
    case 3: testCVector4(); break;
    case 4: testMatrix2x2(); break;
    case 5: testMatrix3x3(); break;
    case 6: testMatrix4x4(); break;
    case 7: testCQuaternion(); break;
    case 0: std::cout << "Saliendo del programa...\n"; break;
    default: std::cout << "Opción no válida. Intente de nuevo.\n"; break;
    }
  } while (opcion != 0);

  return 0;
}
