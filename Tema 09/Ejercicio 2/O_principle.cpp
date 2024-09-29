#include <iostream>
#include <string>
#include <vector>

// Clase concreta para un sensor de temperatura
class TemperatureSensor {
public:
    float readValue() const {
        // Simulación de la lectura de un valor de temperatura
        return 23.5;  // Temperatura simulada en grados Celsius
    }

    std::string getName() const {
        return "Temperature Sensor";
    }
};

// Clase concreta para un sensor de humedad
class HumiditySensor {
public:
    float readValue() const {
        // Simulación de la lectura de un valor de humedad
        return 60.2;  // Humedad simulada en porcentaje
    }

    std::string getName() const {
        return "Humidity Sensor";
    }
};

// Clase concreta para un sensor de presión
class PressureSensor {
public:
    float readValue() const {
        // Simulación de la lectura de un valor de presión
        return 1012.8;  // Presión simulada en hPa
    }

    std::string getName() const {
        return "Pressure Sensor";
    }
};

// Clase concreta para un sensor de luz
class LightSensor {
public:
    float readValue() const {
        // Simulación de la lectura de un valor de luz
        return 300.5;  // Luz simulada en lux
    }

    std::string getName() const {
        return "Light Sensor";
    }
};

// Clase que maneja múltiples sensores
class SensorManager {
private:
    TemperatureSensor tempSensor;
    HumiditySensor humiditySensor;
    PressureSensor pressureSensor;
    LightSensor lightSensor;

public:
    // Método para leer y mostrar todos los valores de los sensores
    void readAllSensors() const {
        // Lectura de cada sensor de forma individual
        std::cout << tempSensor.getName() << ": " << tempSensor.readValue() << " C" << std::endl;
        std::cout << humiditySensor.getName() << ": " << humiditySensor.readValue() << " %" << std::endl;
        std::cout << pressureSensor.getName() << ": " << pressureSensor.readValue() << " hPa" << std::endl;
        std::cout << lightSensor.getName() << ": " << lightSensor.readValue() << " lux" << std::endl;
    }
};

int main() {
    // Crear el manager de sensores
    SensorManager sensorManager;

    // Leer valores de todos los sensores
    sensorManager.readAllSensors();

    return 0;
}
