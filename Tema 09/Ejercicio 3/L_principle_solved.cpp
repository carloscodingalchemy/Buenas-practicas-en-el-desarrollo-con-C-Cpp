#include <iostream>
#include <string>
#include <optional>  // Para usar std::optional

// Clase base Sensor
class Sensor {
public:
    virtual std::optional<float> readValue() const = 0; // Valor opcional
    virtual std::string getType() const = 0; // Método virtual puro
    virtual ~Sensor() = default; // Destructor virtual
};

// Subclase para un sensor de temperatura
class TemperatureSensor : public Sensor {
public:
    std::optional<float> readValue() const override {
        return 25.0f;  // Simulación de lectura de temperatura
    }

    std::string getType() const override {
        return "Temperature Sensor";
    }
};

// Subclase que representa un sensor que siempre falla
class ErrorSensor : public Sensor {
public:
    std::optional<float> readValue() const override {
        // Retornar std::nullopt para indicar un error
        return std::nullopt;  // Lectura fallida
    }

    std::string getType() const override {
        return "Error Sensor";
    }
};

// Función que espera un objeto de tipo Sensor y lee su valor
void displaySensorValue(Sensor& sensor) {
    auto value = sensor.readValue();
    if (value) {
        std::cout << sensor.getType() << ": " << *value << std::endl;  // Imprimir el valor
    } else {
        std::cout << sensor.getType() << ": Error reading sensor value" << std::endl;  // Mensaje de error
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
