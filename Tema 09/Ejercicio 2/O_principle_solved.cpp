// C++ program to demonstrate shared_ptr 
#include <iostream>
#include <string>
#include <vector>
#include <memory>  // Para smart pointers

// Clase abstracta Sensor, abierta para extensión, cerrada para modificación
class Sensor {
public:
    // Método virtual puro para leer el valor del sensor
    virtual float readValue() const = 0;
    
    // Método virtual para obtener el nombre del sensor
    virtual std::string getName() const = 0;

    // Destructor virtual
    virtual ~Sensor() = default;
};

// Clase para un sensor de temperatura
class TemperatureSensor : public Sensor {
public:
    float readValue() const override {
        // Simulación de la lectura de un valor de temperatura
        return 23.5;  // Temperatura simulada en grados Celsius
    }

    std::string getName() const override {
        return "Temperature Sensor";
    }
};

// Clase para un sensor de humedad
class HumiditySensor : public Sensor {
public:
    float readValue() const override {
        // Simulación de la lectura de un valor de humedad
        return 60.2;  // Humedad simulada en porcentaje
    }

    std::string getName() const override {
        return "Humidity Sensor";
    }
};

// Clase para un sensor de presión
class PressureSensor : public Sensor {
public:
    float readValue() const override {
        // Simulación de la lectura de un valor de presión
        return 1012.8;  // Presión simulada en hPa
    }

    std::string getName() const override {
        return "Pressure Sensor";
    }
};

// Clase que maneja múltiples sensores
class SensorManager {
private:
    std::vector<std::unique_ptr<Sensor>> sensors;  // Usamos smart pointers en lugar de punteros crudos

public:
    // Agregar sensores al manager
    void addSensor(std::unique_ptr<Sensor> sensor) {
        sensors.push_back(std::move(sensor));  // Mover el smart pointer a la colección
    }

    // Leer valores de todos los sensores
    void readAllSensors() const {
        for (const auto& sensor : sensors) {
            std::cout << sensor->getName() << ": " << sensor->readValue() << std::endl;
        }
    }
};

int main() {
    // Crear el manager de sensores
    SensorManager sensorManager;

    // Agregar varios tipos de sensores usando smart pointers
    sensorManager.addSensor(std::unique_ptr<Sensor>(new TemperatureSensor));
    sensorManager.addSensor(std::unique_ptr<Sensor>(new HumiditySensor));
    sensorManager.addSensor(std::unique_ptr<Sensor>(new PressureSensor));

    // Leer valores de todos los sensores
    sensorManager.readAllSensors();

    return 0;
}