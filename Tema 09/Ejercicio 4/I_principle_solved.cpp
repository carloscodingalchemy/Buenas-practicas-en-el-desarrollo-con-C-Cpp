#include <iostream>
#include <string>

// Interfaz ISensor para sensores
class ISensor {
public:
    virtual float readValue() const = 0; // Método para leer valores
    virtual std::string getType() const = 0; // Obtener el tipo de sensor
    virtual ~ISensor() = default; // Destructor virtual
};

// Interfaz IActuator para actuadores
class IActuator {
public:
    virtual void activate() = 0; // Método para activar el actuador
    virtual void deactivate() = 0; // Método para desactivar el actuador
    virtual std::string getType() const = 0; // Obtener el tipo de actuador
    virtual ~IActuator() = default; // Destructor virtual
};

// Clase que implementa ISensor (sensor de temperatura)
class TemperatureSensor : public ISensor {
public:
    float readValue() const override {
        return 25.0f;  // Simulación de lectura de temperatura
    }

    std::string getType() const override {
        return "Temperature Sensor";
    }
};

// Clase que implementa ISensor (sensor de luz)
class LightSensor : public ISensor {
public:
    float readValue() const override {
        return 300.0f; // Simulación de lectura de luz en lúmenes
    }

    std::string getType() const override {
        return "Light Sensor";
    }
};

// Clase que implementa IActuator (ventilador)
class Fan : public IActuator {
public:
    void activate() override {
        std::cout << "Fan activated." << std::endl;
    }

    void deactivate() override {
        std::cout << "Fan deactivated." << std::endl;
    }

    std::string getType() const override {
        return "Fan";
    }
};

// Clase que implementa IActuator (luz)
class Light : public IActuator {
public:
    void activate() override {
        std::cout << "Light turned on." << std::endl;
    }

    void deactivate() override {
        std::cout << "Light turned off." << std::endl;
    }

    std::string getType() const override {
        return "Light";
    }
};

// Función para mostrar la lectura de un sensor
void displaySensorValue(ISensor& sensor) {
    std::cout << sensor.getType() << ": " << sensor.readValue() << std::endl;
}

// Función para activar y desactivar un actuador
void controlActuator(IActuator& actuator, bool activate) {
    if (activate) {
        actuator.activate();
    } else {
        actuator.deactivate();
    }
}

int main() {
    // Crear instancias de sensores y actuadores
    TemperatureSensor tempSensor;
    LightSensor lightSensor;
    Fan fan;
    Light light;

    // Mostrar valores de los sensores
    displaySensorValue(tempSensor);   // "Temperature Sensor: 25"
    displaySensorValue(lightSensor);   // "Light Sensor: 300"

    // Controlar actuadores
    controlActuator(fan, true);        // "Fan activated."
    controlActuator(light, false);     // "Light turned off."

    return 0;
}
