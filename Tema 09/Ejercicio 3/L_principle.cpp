#include <iostream>
#include <string>

// Clase base Sensor
class Sensor {
public:
    virtual float readValue() const {
        return 0.0f;  // Valor predeterminado
    }

    virtual std::string getType() const {
        return "Generic Sensor";
    }

    virtual ~Sensor() = default;  // Destructor virtual
};

// Subclase para un sensor de temperatura
class TemperatureSensor : public Sensor {
public:
    float readValue() const override {
        return 25.0f;  // Simulación de lectura de temperatura
    }

    std::string getType() const override {
        return "Temperature Sensor";
    }
};

// Subclase que representa un sensor que siempre falla
class ErrorSensor : public Sensor {
public:
    float readValue() const override {
        // Simulación de un error en la lectura
        throw std::runtime_error("Error reading sensor value");
    }

    std::string getType() const override {
        return "Error Sensor";
    }
};

// Función que espera un objeto de tipo Sensor y lee su valor
void displaySensorValue(Sensor& sensor) {
    try {
        std::cout << sensor.getType() << ": " << sensor.readValue() << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << sensor.getType() << ": " << e.what() << std::endl;
    }
}

int main() {
    TemperatureSensor tempSensor;
    ErrorSensor errorSensor;

    // Leer y mostrar valores de los sensores
    displaySensorValue(tempSensor);  // "Temperature Sensor: 25"
    displaySensorValue(errorSensor);  // "Error Sensor: Error reading sensor value"

    return 0;
}
