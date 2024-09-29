#include <iostream>
#include <memory>  // Para std::unique_ptr
#include <string>

// Interfaz base para los sensores
class Sensor {
public:
    virtual void leer() const = 0;  // Método abstracto que debe implementar cada sensor
    virtual ~Sensor() = default;    // Destructor virtual
};

// Clase concreta para un Sensor de Temperatura
class SensorTemperatura : public Sensor {
public:
    void leer() const override {
        std::cout << "Leyendo datos del Sensor de Temperatura...\n";
    }
};

// Clase concreta para un Sensor de Humedad
class SensorHumedad : public Sensor {
public:
    void leer() const override {
        std::cout << "Leyendo datos del Sensor de Humedad...\n";
    }
};

// Clase Factory que crea los sensores según el tipo
class SensorFactory {
public:
    // Método estático para crear un sensor
    static std::unique_ptr<Sensor> crearSensor(const std::string& tipo) {
        if (tipo == "temperatura") {
            return std::make_unique<SensorTemperatura>();
        } else if (tipo == "humedad") {
            return std::make_unique<SensorHumedad>();
        } else {
            return nullptr;
        }
    }
};

// Función principal para demostrar el patrón Factory
int main() {
    // Crear un sensor de temperatura
    std::unique_ptr<Sensor> sensorTemp = SensorFactory::crearSensor("temperatura");
    if (sensorTemp) {
        sensorTemp->leer();
    }

    // Crear un sensor de humedad
    std::unique_ptr<Sensor> sensorHum = SensorFactory::crearSensor("humedad");
    if (sensorHum) {
        sensorHum->leer();
    }

    // Intentar crear un sensor no válido
    std::unique_ptr<Sensor> sensorInvalido = SensorFactory::crearSensor("invalido");
    if (sensorInvalido == nullptr) {
        std::cout << "Tipo de sensor no válido.\n";
    }

    return 0;
}