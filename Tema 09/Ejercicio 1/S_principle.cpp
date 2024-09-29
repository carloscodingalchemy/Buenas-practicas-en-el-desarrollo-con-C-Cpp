#include <iostream>
#include <string>

// Clase que incumple el SRP al manejar tanto la UART como la lógica del módem LoRa
class LoRaModem {
public:
    // Método para enviar datos a través de la UART
    void sendToUart(const std::string& data) {
        // Simulación del envío de datos a través de la UART
        std::cout << "[UART] Enviando: " << data << std::endl;
    }

    // Método para recibir datos de la UART
    std::string receiveFromUart() {
        // Simulación de la recepción de datos de la UART
        std::string receivedData = "OK";
        std::cout << "[UART] Recibiendo: " << receivedData << std::endl;
        return receivedData;
    }

    // Método para inicializar el módem LoRa
    void initialize() {
        std::string atCommand = "AT+INIT";
        std::cout << "[LoRaModem] Inicializando módem con comando: " << atCommand << std::endl;
        sendToUart(atCommand);
        std::string response = receiveFromUart();
        if (response == "OK") {
            std::cout << "[LoRaModem] Módem inicializado correctamente." << std::endl;
        } else {
            std::cout << "[LoRaModem] Error en la inicialización del módem." << std::endl;
        }
    }

    // Método para configurar la frecuencia del módem LoRa
    void setFrequency(const std::string& frequency) {
        std::string atCommand = "AT+FREQ=" + frequency;
        std::cout << "[LoRaModem] Configurando frecuencia con comando: " << atCommand << std::endl;
        sendToUart(atCommand);
        std::string response = receiveFromUart();
        if (response == "OK") {
            std::cout << "[LoRaModem] Frecuencia configurada correctamente." << std::endl;
        } else {
            std::cout << "[LoRaModem] Error al configurar la frecuencia." << std::endl;
        }
    }

    // Otros métodos que mezclan la lógica del módem con la gestión UART...
};

int main() {
    // Crear una instancia del módem LoRa
    LoRaModem loraModem;

    // Inicializar el módem LoRa
    loraModem.initialize();

    // Configurar una frecuencia en el módem LoRa
    loraModem.setFrequency("868.1");

    return 0;
}
