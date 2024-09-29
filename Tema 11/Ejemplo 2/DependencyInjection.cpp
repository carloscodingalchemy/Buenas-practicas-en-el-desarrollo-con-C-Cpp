#include <iostream>
#include <vector>

// Clase que representa el bus I2C
class I2CBus {
public:
    // Simula la lectura de datos desde un dispositivo I2C
    std::vector<uint8_t> read(uint8_t address, size_t length) {
        std::vector<uint8_t> data(length, 0xFF);  // Simula que lee datos del dispositivo
        std::cout << "Reading " << length << " bytes from I2C device at address 0x" 
                  << std::hex << static_cast<int>(address) << std::endl;
        return data;
    }

    // Simula la escritura de datos a un dispositivo I2C
    void write(uint8_t address, const std::vector<uint8_t>& data) {
        std::cout << "Writing " << data.size() << " bytes to I2C device at address 0x" 
                  << std::hex << static_cast<int>(address) << std::endl;
    }
};



// Clase Sensor que crea y maneja su propia instancia de I2CBus
class Sensor {
public:
    // El constructor ahora solo recibe la dirección I2C del sensor
    Sensor(uint8_t address) 
        : i2cAddress(address) {
        i2cBus = new I2CBus();  // Crea una nueva instancia de I2CBus
    }

    // Destructor para liberar la instancia de I2CBus
    ~Sensor() {
        delete i2cBus;
    }

    // Método para leer datos desde el sensor
    void readSensorData() {
        // Lee 4 bytes del sensor a través del bus I2C
        std::vector<uint8_t> data = i2cBus->read(i2cAddress, 4);
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
        i2cBus->write(i2cAddress, data);
    }

private:
    I2CBus* i2cBus;  // Puntero a una instancia de I2CBus
    uint8_t i2cAddress;  // Dirección I2C del sensor
};
