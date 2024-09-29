#include <iostream>
#include <cmath>

// Dirección base del dispositivo FPGA
#define FPGA_MEMORY_ADDRESS 0x40000000

// Data Transfer Object (DTO) para almacenar los valores de potencia
struct PowerData {
    double current;
    double voltage;
    double activePower;
    double reactivePower;
};

// Interfaz para leer datos desde una fuente (como FPGA)
class IDataReader {
public:
    virtual ~IDataReader() = default;
    virtual void readValues(PowerData& data) = 0;
};

// Interfaz para cálculos de potencia
class IPowerCalculator {
public:
    virtual ~IPowerCalculator() = default;
    virtual double calculateApparentPower(const PowerData& data) = 0;
};

// Interfaz para mostrar los datos
class IDataDisplay {
public:
    virtual ~IDataDisplay() = default;
    virtual void display(const PowerData& data, double apparentPower) = 0;
};

// Interfaz para almacenar los datos
class IDataStorage {
public:
    virtual ~IDataStorage() = default;
    virtual void save(const PowerData& data) = 0;
};

// Implementación concreta para leer datos desde la FPGA
class FPGAReader : public IDataReader {
public:
    FPGAReader() : baseAddress((volatile uint32_t*)FPGA_MEMORY_ADDRESS) {}

    void readValues(PowerData& data) override {
        data.current = baseAddress[0];        // Corriente
        data.voltage = baseAddress[1];        // Voltaje
        data.activePower = baseAddress[2];    // Potencia activa
        data.reactivePower = baseAddress[3];  // Potencia reactiva
    }

private:
    volatile uint32_t* baseAddress;  // Puntero al dispositivo FPGA mapeado en memoria
};

// Implementación concreta para calcular la potencia
class PowerCalculator : public IPowerCalculator {
public:
    double calculateApparentPower(const PowerData& data) override {
        return std::sqrt(data.activePower * data.activePower + data.reactivePower * data.reactivePower);
    }
};

// Implementación concreta para mostrar los datos en consola
class ConsoleDisplay : public IDataDisplay {
public:
    void display(const PowerData& data, double apparentPower) override {
        std::cout << "Current: " << data.current << " A\n";
        std::cout << "Voltage: " << data.voltage << " V\n";
        std::cout << "Active Power: " << data.activePower << " W\n";
        std::cout << "Reactive Power: " << data.reactivePower << " VAR\n";
        std::cout << "Apparent Power: " << apparentPower << " VA\n";
    }
};

// Implementación concreta para guardar los datos (simulación de base de datos)
class DatabaseStorage : public IDataStorage {
public:
    void save(const PowerData& data) override {
        std::cout << "Saving values to database...\n";
        // Simulación de almacenamiento de datos
    }
};

// Clase principal que orquesta el sistema
class SensorSystem {
public:
    // Inyección de dependencias a través del constructor, pasando por referencia
    SensorSystem(IDataReader& reader, IPowerCalculator& calculator, IDataDisplay& display, IDataStorage& storage)
        : reader(reader), calculator(calculator), display(display), storage(storage) {}

    // Método para leer, calcular, mostrar y almacenar los datos
    void process() {
        // Leer los valores desde la FPGA (u otra fuente de datos)
        reader.readValues(data);

        // Calcular la potencia aparente
        double apparentPower = calculator.calculateApparentPower(data);

        // Mostrar los valores
        display.display(data, apparentPower);

        // Guardar los datos
        storage.save(data);
    }

private:
    IDataReader& reader;               // Interfaz para lectura de datos
    IPowerCalculator& calculator;      // Interfaz para cálculo de potencia
    IDataDisplay& display;             // Interfaz para mostrar datos
    IDataStorage& storage;             // Interfaz para almacenar datos

    PowerData data;                    // DTO que almacena los datos de la lectura
};

int main() {
    // Crear implementaciones concretas
    FPGAReader reader;
    PowerCalculator calculator;
    ConsoleDisplay display;
    DatabaseStorage storage;

    // Inyectar las dependencias en el sistema pasando por referencia
    SensorSystem system(reader, calculator, display, storage);

    // Procesar los datos
    system.process();

    return 0;
}
