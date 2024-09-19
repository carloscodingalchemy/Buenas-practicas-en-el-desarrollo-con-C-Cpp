#include <iostream>
#include <stdint.h>

// Enum que representa los diferentes tipos de sensores
enum class SensorType {
    ModelA,
    ModelB,
    ModelC
};

// Clase que gestiona múltiples tipos de sensores de temperatura
class TemperatureSensor {
private:
    SensorType sensorType;  // Tipo de sensor que se va a manejar

public:
    // Constructor que recibe el tipo de sensor
    TemperatureSensor(SensorType type) : sensorType(type) {}

    // Método para inicializar el sensor dependiendo del modelo
    void initialize() {
        switch (sensorType) {
            case SensorType::ModelA:
                std::cout << "Inicializando sensor Modelo A...\n";
                // Simulación de la inicialización del modelo A
                break;
            case SensorType::ModelB:
                std::cout << "Inicializando sensor Modelo B...\n";
                // Simulación de la inicialización del modelo B
                break;
            case SensorType::ModelC:
                std::cout << "Inicializando sensor Modelo C...\n";
                // Simulación de la inicialización del modelo C
                break;
            default:
                std::cout << "Tipo de sensor no soportado.\n";
                break;
        }
    }

    // Método para leer la temperatura según el tipo de sensor
    void readTemperature() {
        switch (sensorType) {
            case SensorType::ModelA:
                std::cout << "Leyendo temperatura del sensor Modelo A: 25°C\n";
                // Simulación de lectura de temperatura del modelo A
                break;
            case SensorType::ModelB:
                std::cout << "Leyendo temperatura del sensor Modelo B: 30°C\n";
                // Simulación de lectura de temperatura del modelo B
                break;
            case SensorType::ModelC:
                std::cout << "Leyendo temperatura del sensor Modelo C: 28°C\n";
                // Simulación de lectura de temperatura del modelo C
                break;
            default:
                std::cout << "Tipo de sensor no soportado.\n";
                break;
        }
    }
};

// Función principal para simular el uso de la clase TemperatureSensor
int main() {
    // Creando una instancia de sensor para el Modelo A
    TemperatureSensor sensorA(SensorType::ModelA);
    sensorA.initialize();      // Inicializar el sensor Modelo A
    sensorA.readTemperature(); // Leer la temperatura del sensor Modelo A

    std::cout << "--------------------------\n";

    // Creando una instancia de sensor para el Modelo B
    TemperatureSensor sensorB(SensorType::ModelB);
    sensorB.initialize();      // Inicializar el sensor Modelo B
    sensorB.readTemperature(); // Leer la temperatura del sensor Modelo B

    std::cout << "--------------------------\n";

    // Creando una instancia de sensor para el Modelo C
    TemperatureSensor sensorC(SensorType::ModelC);
    sensorC.initialize();      // Inicializar el sensor Modelo C
    sensorC.readTemperature(); // Leer la temperatura del sensor Modelo C

    return 0;
}
