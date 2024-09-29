#include <iostream>
#include <vector>

// Clase que representa el bus I2C
class I2CBus {
public:
    // Constructor que toma la dirección I2C
    I2CBus(uint8_t address) 
        : i2cAddress(address) {}

    // Simula la lectura de datos desde un dispositivo I2C
    std::vector<uint8_t> read(size_t length) {
        std::vector<uint8_t> data(length, 0xFF);  // Simula que lee datos del dispositivo
        std::cout << "Reading " << length << " bytes from I2C device at address 0x" 
                  << std::hex << static_cast<int>(i2cAddress) << std::endl;
        return data;
    }

    // Simula la escritura de datos a un dispositivo I2C
    void write(const std::vector<uint8_t>& data) {
        std::cout << "Writing " << data.size() << " bytes to I2C device at address 0x" 
                  << std::hex << static_cast<int>(i2cAddress) << std::endl;
    }

private:
    uint8_t i2cAddress;  // Dirección I2C del dispositivo
};


// Clase Sensor que depende del I2CBus, pero no conoce la dirección I2C
class Sensor {
public:
    // El constructor recibe una referencia al bus I2C
    Sensor(I2CBus& bus) 
        : i2cBus(bus) {}

    // Método para leer datos desde el sensor
    void readSensorData() {
        // Lee 4 bytes del sensor a través del bus I2C
        std::vector<uint8_t> data = i2cBus.read(4);
        // Simula procesamiento de los datos leídos
        std::cout << "Sensor data read: ";
        for (auto byte : data) {
            std::cout << "0x" << std::hex << static_cast<int>(byte) << " ";
        }
        std::cout << std::endl;
    }

    // Método para escribir datos al sensor
    void writeSensorData(const std::vector<uint8_t>& data) {
        // Escribe datos al sensor a través del bus I2C
        i2cBus.write(data);
    }

private:
    I2CBus& i2cBus;  // Referencia a una instancia de I2CBus
};

