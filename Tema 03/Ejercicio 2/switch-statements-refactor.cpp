#include <iostream>
#include <memory>  // Para std::unique_ptr

// Clase base para los sensores de temperatura
class TemperatureSensor {
public:
    virtual void initialize() = 0;        // Método virtual puro para inicializar
    virtual void readTemperature() = 0;   // Método virtual puro para leer temperatura
    virtual ~TemperatureSensor() = default;  // Destructor virtual
};

// Sensor específico: Modelo A
class TemperatureSensorModelA : public TemperatureSensor {
public:
    void initialize() override {
        std::cout << "Inicializando sensor Modelo A...\n";
        // Simulación de inicialización para el Modelo A
    }

    void readTemperature() override {
        std::cout << "Leyendo temperatura del sensor Modelo A: 25°C\n";
    }
};

// Sensor específico: Modelo B
class TemperatureSensorModelB : public TemperatureSensor {
public:
    void initialize() override {
        std::cout << "Inicializando sensor Modelo B...\n";
        // Simulación de inicialización para el Modelo B
    }

    void readTemperature() override {
        std::cout << "Leyendo temperatura del sensor Modelo B: 30°C\n";
    }
};

// Sensor específico: Modelo C
class TemperatureSensorModelC : public TemperatureSensor {
public:
    void initialize() override {
        std::cout << "Inicializando sensor Modelo C...\n";
        // Simulación de inicialización para el Modelo C
    }

    void readTemperature() override {
        std::cout << "Leyendo temperatura del sensor Modelo C: 28°C\n";
    }
};

// Enum que representa los diferentes tipos de sensores
enum class SensorType {
    ModelA,
    ModelB,
    ModelC
};

// Fábrica que selecciona el sensor adecuado (único uso del switch)
std::unique_ptr<TemperatureSensor> createTemperatureSensor(SensorType type) {
    switch (type) {
        case SensorType::ModelA:
            return std::make_unique<TemperatureSensorModelA>();
        case SensorType::ModelB:
            return std::make_unique<TemperatureSensorModelB>();
        case SensorType::ModelC:
            return std::make_unique<TemperatureSensorModelC>();
        default:
            throw std::invalid_argument("Tipo de sensor no soportado.");
    }
}

// Función que inicializa y lee la temperatura usando el sensor adecuado
void monitorTemperature(SensorType type) {
    // Creación del sensor a través de la fábrica
    std::unique_ptr<TemperatureSensor> sensor = createTemperatureSensor(type);
    
    // Inicializar el sensor
    sensor->initialize();

    // Leer la temperatura del sensor
    sensor->readTemperature();
}

int main() {
    
    // Simulación de diferentes sensores montados en la placa
    std::unique_ptr<TemperatureSensor> sensor = createTemperatureSensor(SensorType::ModelA);  // Inicializar y leer el sensor Modelo A
    std::cout << "--------------------------\n";

    // Inicializar el sensor
    sensor->initialize();

    // Leer la temperatura del sensor
    sensor->readTemperature();


    return 0;
}
