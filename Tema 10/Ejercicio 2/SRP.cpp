#include <iostream>
#include <string>

#define FPGA_MEMORY_ADDRESS 0x40000000  // Dirección base del dispositivo FPGA

class SensorSystem {
public:
    // Constructor que simula la conexión al dispositivo mapeado en memoria
    SensorSystem() : baseAddress((volatile uint32_t*)FPGA_MEMORY_ADDRESS) {}

    // Leer valores desde la FPGA (memoria mapeada)
    void readValues() {
        current = baseAddress[0];        // Corriente
        voltage = baseAddress[1];        // Voltaje
        activePower = baseAddress[2];    // Potencia activa
        reactivePower = baseAddress[3];  // Potencia reactiva
    }

    // Calcular potencia aparente
    double calculateApparentPower() {
        return sqrt(activePower * activePower + reactivePower * reactivePower);
    }

    // Mostrar los valores en consola
    void displayValues() {
        std::cout << "Current: " << current << " A\n";
        std::cout << "Voltage: " << voltage << " V\n";
        std::cout << "Active Power: " << activePower << " W\n";
        std::cout << "Reactive Power: " << reactivePower << " VAR\n";
        std::cout << "Apparent Power: " << calculateApparentPower() << " VA\n";
    }

    // Guardar los valores en algún almacenamiento (simulación)
    void saveToDatabase() {
        std::cout << "Saving values to database...\n";
        // Simulación de almacenamiento de datos
    }

private:
    volatile uint32_t* baseAddress;  // Puntero al dispositivo FPGA mapeado en memoria
    double current;
    double voltage;
    double activePower;
    double reactivePower;
};
