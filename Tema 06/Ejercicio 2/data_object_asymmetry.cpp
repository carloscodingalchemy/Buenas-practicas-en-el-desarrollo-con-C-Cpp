#include <iostream>
#include <string>

// EJERCICIO: Añadir un nuevo tipo de sensor (light) y modificar el código necesario para implementar la funcionalidad adecuada.

// Definir los posibles tipos de sensores
enum class SensorType {
    TEMPERATURE_SENSOR,
    PRESSURE_SENSOR,
    HUMIDITY_SENSOR
};

// Clase base abstracta Sensor
class Sensor {
protected:
    uint8_t data;          // Dato del sensor (valor leído)
    uint32_t readPeriod;   // Período de lectura en milisegundos

public:
    Sensor(uint32_t readPeriod) : readPeriod(readPeriod), data(0) {}

    virtual ~Sensor() {}

    // Método para inicializar el sensor (abstracto)
    virtual void init() = 0;

    // Método para leer datos del sensor (abstracto)
    virtual void read() = 0;

    // Método para obtener una descripción del sensor (abstracto)
    virtual std::string getDescription() const = 0;

    // Método para configurar el período de lectura
    void setReadPeriod(uint32_t newPeriod) {
        readPeriod = newPeriod;
        std::cout << "Nuevo período de lectura establecido: " << readPeriod << " ms\n";
    }

    // Método para obtener el valor del sensor
    uint8_t getData() const {
        return data;
    }

    // Método para obtener el período de lectura
    uint32_t getReadPeriod() const {
        return readPeriod;
    }
};

// Clase derivada para el sensor de temperatura
class TemperatureSensor : public Sensor {
public:
    TemperatureSensor(uint32_t readPeriod) : Sensor(readPeriod) {}

    void init() override {
        std::cout << "Inicializando Sensor de Temperatura\n";
        // Aquí podría ir el código de inicialización del hardware
    }

    void read() override {
        // Simular la lectura de temperatura
        data = 25;  // Simulación de lectura: 25°C
        std::cout << "Leyendo temperatura: " << static_cast<int>(data) << "°C\n";
    }

    std::string getDescription() const override {
        return "Sensor de Temperatura";
    }
};

// Clase derivada para el sensor de presión
class PressureSensor : public Sensor {
public:
    PressureSensor(uint32_t readPeriod) : Sensor(readPeriod) {}

    void init() override {
        std::cout << "Inicializando Sensor de Presión\n";
        // Aquí podría ir el código de inicialización del hardware
    }

    void read() override {
        // Simular la lectura de presión
        data = 101;  // Simulación de lectura: 101 kPa
        std::cout << "Leyendo presión: " << static_cast<int>(data) << " kPa\n";
    }

    std::string getDescription() const override {
        return "Sensor de Presión";
    }
};

// Clase derivada para el sensor de humedad
class HumiditySensor : public Sensor {
public:
    HumiditySensor(uint32_t readPeriod) : Sensor(readPeriod) {}

    void init() override {
        std::cout << "Inicializando Sensor de Humedad\n";
        // Aquí podría ir el código de inicialización del hardware
    }

    void read() override {
        // Simular la lectura de humedad
        data = 60;  // Simulación de lectura: 60%
        std::cout << "Leyendo humedad: " << static_cast<int>(data) << "%\n";
    }

    std::string getDescription() const override {
        return "Sensor de Humedad";
    }
};


class SensorManager
{
    private:
    std::vector<Sensor&> sensors;

    public:
    SensorManager() {}

    addSensor(Sensor& sensor) {
        sensors.push_back(sensor);
    }
}

// Programa principal
int main() {
    // Crear un sensor de temperatura con un período de lectura de 1000 ms
    TemperatureSensor tempSensor(1000);
    tempSensor.init();
    tempSensor.read();

    // Crear un sensor de presión con un período de lectura de 500 ms
    PressureSensor pressureSensor(500);
    pressureSensor.init();
    pressureSensor.read();

    // Crear un sensor de humedad con un período de lectura de 750 ms
    HumiditySensor humiditySensor(750);
    humiditySensor.init();
    humiditySensor.read();

    // Cambiar el período de lectura del sensor de temperatura
    tempSensor.setReadPeriod(2000);

    // Obtener descripciones
    std::cout << tempSensor.getDescription() << " tiene un período de lectura de " << tempSensor.getReadPeriod() << " ms\n";
    std::cout << pressureSensor.getDescription() << " tiene un período de lectura de " << pressureSensor.getReadPeriod() << " ms\n";
    std::cout << humiditySensor.getDescription() << " tiene un período de lectura de " << humiditySensor.getReadPeriod() << " ms\n";

    return 0;
}
