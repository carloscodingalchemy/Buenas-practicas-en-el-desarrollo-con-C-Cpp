#include <iostream>
#include <stdexcept>  // Para std::runtime_error y otras excepciones estándar
#include <string>

// Clase base para todas las excepciones SPI
class SPIError : public std::runtime_error {
public:
    explicit SPIError(const std::string& message) : std::runtime_error(message) {}
};

// Excepción para errores de configuración de SPI
class SPIConfigurationError : public SPIError {
public:
    explicit SPIConfigurationError(const std::string& message)
        : SPIError("SPI Configuration Error: " + message) {}
};

// Excepción para errores de tiempo de espera (timeout)
class SPITimeoutError : public SPIError {
public:
    explicit SPITimeoutError(const std::string& message)
        : SPIError("SPI Timeout Error: " + message) {}
};

// Excepción para errores de transmisión
class SPITransmissionError : public SPIError {
public:
    explicit SPITransmissionError(const std::string& message)
        : SPIError("SPI Transmission Error: " + message) {}
};

// Excepción para errores de dispositivo no encontrado
class SPIDeviceNotFoundError : public SPIError {
public:
    explicit SPIDeviceNotFoundError(const std::string& message)
        : SPIError("SPI Device Not Found Error: " + message) {}
};

// Ejemplo de una clase que modela el SPI master
class SPIMaster {
public:
    // Configura el SPI con frecuencia, modo, etc.
    void configure(int clock_speed, int mode) {
        if (clock_speed <= 0) {
            throw SPIConfigurationError("Invalid clock speed: " + std::to_string(clock_speed));
        }
        if (mode < 0 || mode > 3) {
            throw SPIConfigurationError("Invalid mode: " + std::to_string(mode));
        }
        std::cout << "SPI configured with clock speed " << clock_speed << " Hz and mode " << mode << std::endl;
    }

    // Envía datos al dispositivo esclavo
    void send_data(const std::string& data) {
        if (data.empty()) {
            throw SPITransmissionError("Cannot send empty data.");
        }
        // Simula la transmisión de datos
        std::cout << "Sending data: " << data << std::endl;
    }

    // Simula la recepción de datos desde el esclavo
    std::string receive_data() {
        // Simula un timeout si no se reciben datos en el tiempo esperado
        bool timeout_occurred = false; // Cambiar a 'true' para simular timeout
        if (timeout_occurred) {
            throw SPITimeoutError("No data received within the expected time.");
        }
        // Simula la recepción exitosa de datos
        return "Data from slave device";
    }

    // Simula la selección de un dispositivo esclavo
    void select_slave_device(int device_id) {
        if (device_id != 1) {  // Suponiendo que el dispositivo con ID 1 es el único válido
            throw SPIDeviceNotFoundError("Device with ID " + std::to_string(device_id) + " not found.");
        }
        std::cout << "Slave device " << device_id << " selected." << std::endl;
    }
};

int main() {
    SPIMaster spi_master;

    try {
        spi_master.configure(1000000, 1);  // Configura SPI con 1 MHz, modo 1
        spi_master.select_slave_device(2);  // Error, no existe dispositivo con ID 2
        spi_master.send_data("Hello");
        std::string response = spi_master.receive_data();
        std::cout << "Received: " << response << std::endl;

    } catch (const SPIError& e) {
        std::cerr << "SPI Error: " << e.what() << std::endl;
    }

    return 0;
}
