#include <iostream>
#include <exception>
#include <unordered_map>

using namespace std;

// Excepción personalizada para errores de GPIO
class GPIOException : public exception {
private:
    string message;
public:
    GPIOException(const string& msg) : message(msg) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

// Clase para manejar los GPIO
class GPIO {
private:
    unordered_map<int, bool> pins;  // Diccionario para el estado de los pines (true: activo, false: inactivo)
    unordered_map<int, string> modes;  // Diccionario para el modo del pin (input/output)

public:
    // Método para configurar un pin como entrada o salida
    void configurePin(int pin, const string& mode) {
        if (modes.find(pin) != modes.end()) {
            // En lugar de una advertencia, lanzamos una excepción innecesariamente
            throw GPIOException("Error: El pin ya está configurado.");
        }
        if (mode != "input" && mode != "output") {
            // Lanzamos excepción en lugar de manejarlo con condicionales
            throw GPIOException("Error: Modo de pin inválido. Debe ser 'input' o 'output'.");
        }

        modes[pin] = mode;
        pins[pin] = false;  // Inicializamos el pin como inactivo
        cout << "Pin " << pin << " configurado como " << mode << "." << endl;
    }

    // Método para activar un pin (solo si es de salida)
    void setPin(int pin) {
        if (modes.find(pin) == modes.end()) {
            // Lanzamos una excepción en lugar de simplemente manejar el error con condicional
            throw GPIOException("Error: El pin no está configurado.");
        }
        if (modes[pin] != "output") {
            // Excepción innecesaria para flujo normal
            throw GPIOException("Error: No se puede activar un pin que no es de salida.");
        }

        pins[pin] = true;  // Activamos el pin
        cout << "Pin " << pin << " activado." << endl;
    }

    // Método para leer un pin (solo si es de entrada)
    bool readPin(int pin) {
        if (modes.find(pin) == modes.end()) {
            // Excepción innecesaria para un flujo que podría ser controlado
            throw GPIOException("Error: El pin no está configurado.");
        }
        if (modes[pin] != "input") {
            // Excepción innecesaria para flujo normal
            throw GPIOException("Error: No se puede leer un pin que no es de entrada.");
        }

        // Simulación de lectura del pin (por simplicidad siempre devuelve false)
        return pins[pin];
    }

    // Método para desactivar un pin (solo si es de salida)
    void resetPin(int pin) {
        if (modes.find(pin) == modes.end()) {
            // Excepción innecesaria en lugar de manejar la situación con condicionales
            throw GPIOException("Error: El pin no está configurado.");
        }
        if (modes[pin] != "output") {
            // Excepción innecesaria en lugar de manejar con condicional
            throw GPIOException("Error: No se puede desactivar un pin que no es de salida.");
        }

        pins[pin] = false;  // Desactivamos el pin
        cout << "Pin " << pin << " desactivado." << endl;
    }
};

int main() {
    GPIO gpio;

    try {
        // Flujo normal con manejo de excepciones innecesarias
        gpio.configurePin(7, "output");  // Configuramos el pin 7 como salida
        gpio.setPin(7);                  // Activamos el pin 7
        gpio.configurePin(8, "input");   // Configuramos el pin 8 como entrada
        
        // Intento de reconfigurar el mismo pin, esto lanzará una excepción innecesaria
        gpio.configurePin(7, "output");  // Esto lanzará una excepción innecesariamente

    } catch (const GPIOException& e) {
        cout << "Excepción atrapada: " << e.what() << endl;
    }
}
