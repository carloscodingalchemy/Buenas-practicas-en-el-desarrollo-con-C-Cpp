#include <iostream>
#include <string>

class Calculadora {
public:
    void suma(int a, int b) {
        std::cout << "La suma de " << a << " y " << b << " es " << a + b << std::endl;
    }

    void resta(int a, int b) {
        std::cout << "La resta de " << a << " y " << b << " es " << a - b << std::endl;
    }

    void multiplicacion(int a, int b) {
        std::cout << "La multiplicación de " << a << " y " << b << " es " << a * b << std::endl;
    }

    void division(int a, int b) {
        if (b != 0) {
            std::cout << "La división de " << a << " y " << b << " es " << a / b << std::endl;
        } else {
            std::cout << "Error: División por cero no permitida" << std::endl;
        }
    }
};

int main() {
    Calculadora calc;
    calc.suma(10, 5);
    calc.resta(10, 5);
    calc.multiplicacion(10, 5);
    calc.division(10, 5);
    
    return 0;
}
