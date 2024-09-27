#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

// Excepción personalizada para errores críticos en el GPIO
class GPIOAccessException : public runtime_error {
public:
    explicit GPIOAccessException(const string& message) 
        : runtime_error("GPIO Access Error: " + message) {}
};

// Clase para manejar el periférico GPIO
class GPIO {
private:
    int pinNumber;
    bool isInitialized;

public:
    // Constructor
    GPIO(int pin) : pinNumber(pin), isInitialized(false) {}

    // Método para inicializar el pin GPIO
    void initialize() {
        // Simulamos la inicialización del pin
        if (pinNumber < 0 || pinNumber > 40) {
            throw GPIOAccessException("Número de pin inválido. Debe estar entre 0 y 40.");
        }
        
        // Si la inicialización es exitosa
        isInitialized = true;
        cout << "GPIO pin " << pinNumber << " inicializado correctamente." << endl;
    }

    // Método para escribir un valor en el pin
    bool write(int value) {
        // Comprobamos si el GPIO fue inicializado
        if (!isInitialized) {
            cerr << "Error: El pin GPIO no ha sido inicializado." << endl;
            return false;  // Manejado con condicional porque es parte del flujo normal
        }

        // Verificamos que el valor sea válido (0 o 1)
        if (value != 0 && value != 1) {
            cerr << "Error: Valor inválido para escribir en el pin GPIO. Solo se permiten 0 o 1." << endl;
            return false;  // Condicional porque es un error predecible y parte del flujo normal
        }

        // Simulamos la escritura del valor
        cout << "Escribiendo valor " << value << " en el pin " << pinNumber << endl;
        return true;
    }

    // Método para leer el valor del pin
    int read() {
        if (!isInitialized) {
            cerr << "Error: El pin GPIO no ha sido inicializado." << endl;
            return -1;  // Retornamos -1 como valor "nulo" para representar un error no crítico
        }

        // Simulamos la lectura de un valor desde el pin (ej. retorna 1 o 0)
        int readValue = 1;  // Ejemplo de valor leído
        cout << "Leyendo valor " << readValue << " del pin " << pinNumber << endl;
        return readValue;
    }

    // Método para liberar el pin GPIO
    void release() {
        if (!isInitialized) {
            cerr << "Advertencia: El pin GPIO no estaba inicializado, no es necesario liberarlo." << endl;
            return;  // Advertencia, pero no es un error crítico
        }

        // Simulamos la liberación del pin
        isInitialized = false;
        cout << "GPIO pin " << pinNumber << " liberado correctamente." << endl;
    }
};

int main() {
    try {
        // Crear un objeto GPIO con un pin válido
        GPIO gpio1(21);

        // Inicializamos el GPIO
        gpio1.initialize();

        // Intentamos escribir un valor válido
        if (!gpio1.write(1)) {
            cerr << "No se pudo escribir el valor en el GPIO." << endl;
        }

        // Intentamos leer el valor del GPIO
        int value = gpio1.read();
        if (value == -1) {
            cerr << "No se pudo leer el valor del GPIO." << endl;
        }

        // Intentamos escribir un valor inválido
        if (!gpio1.write(2)) {
            cerr << "No se pudo escribir el valor inválido en el GPIO." << endl;
        }

        // Liberamos el GPIO
        gpio1.release();

        // Intentamos usar un pin no válido para provocar una excepción
        GPIO gpio2(50);  // Número de pin inválido
        gpio2.initialize();  // Esto lanzará una excepción

    } catch (const GPIOAccessException& e) {
        cerr << e.what() << endl;

    } catch (const exception& e) {
        cerr << "Ocurrió un error inesperado: " << e.what() << endl;
    }

    return 0;
}
