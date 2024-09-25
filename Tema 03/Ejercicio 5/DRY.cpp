#include <iostream>
#include <string>

class Calculadora {
private:
    void imprimirResultado(const std::string& operacion, int a, int b, double resultado) {
        std::cout << "La " << operacion << " de " << a << " y " << b << " es " << resultado << std::endl;
    }

public:
    void suma(int a, int b) {
        imprimirResultado("suma", a, b, a + b);
    }

    void resta(int a, int b) {
        imprimirResultado("resta", a, b, a - b);
    }

    void multiplicacion(int a, int b) {
        imprimirResultado("multiplicación", a, b, a * b);
    }

    void division(int a, int b) {
        if (b != 0) {
            imprimirResultado("división", a, b, static_cast<double>(a) / b);
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
