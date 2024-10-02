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

// Función principal para demostrar el código sin patrón Factory
int main() {
    // Crear directamente un sensor de temperatura
    std::unique_ptr<Sensor> sensorTemp = std::make_unique<SensorTemperatura>();
    sensorTemp->leer();

    // Crear directamente un sensor de humedad
    std::unique_ptr<Sensor> sensorHum = std::make_unique<SensorHumedad>();
    sensorHum->leer();

    // En este caso, no hay necesidad de manejar sensores no válidos, ya que se crean directamente
    // sin necesidad de verificar un tipo como en el patrón Factory.

    return 0;
}
