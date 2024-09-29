#include <iostream>
#include <string>

// Interfaz monolítica IDevice para dispositivos que combina sensores y actuadores
class IDevice {
public:
    virtual float readValue() const = 0;   // Método para leer valores (solo para sensores)
    virtual void activate() = 0;            // Método para activar (solo para actuadores)
    virtual void deactivate() = 0;          // Método para desactivar (solo para actuadores)
    virtual std::string getType() const = 0; // Obtener el tipo de dispositivo
    virtual ~IDevice() = default;           // Destructor virtual
};

// Clase que implementa IDevice (sensor de temperatura)
class TemperatureSensor : public IDevice {
public:
    float readValue() const override {
        return 25.0f;  // Simulación de lectura de temperatura
    }

    void activate() override {
        // Implementación innecesaria para un sensor
        throw std::runtime_error("TemperatureSensor cannot be activated.");
    }

    void deactivate() override {
        // Implementación innecesaria para un sensor
        throw std::runtime_error("TemperatureSensor cannot be deactivated.");
    }

    std::string getType() const override {
        return "Temperature Sensor";
    }
};

// Clase que implementa IDevice (ventilador)
class Fan : public IDevice {
public:
    float readValue() const override {
        // Implementación innecesaria para un actuador
        throw std::runtime_error("Fan does not have a value to read.");
    }

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

// Función para mostrar la lectura de un dispositivo
void displayDeviceValue(IDevice& device) {
    try {
        std::cout << device.getType() << ": " << device.readValue() << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;  // Manejo del error
    }
}

// Función para activar y desactivar un actuador
void controlActuator(IDevice& actuator, bool activate) {
    if (activate) {
        actuator.activate();
    } else {
        actuator.deactivate();
    }
}

int main() {
    // Crear instancias de sensores y actuadores
    TemperatureSensor tempSensor;
    Fan fan;

    // Mostrar valores de los dispositivos
    displayDeviceValue(tempSensor);   // "TemperatureSensor cannot be activated."
    controlActuator(fan, true);       // "Fan activated."
    displayDeviceValue(fan);           // "Fan does not have a value to read."

    return 0;
}
