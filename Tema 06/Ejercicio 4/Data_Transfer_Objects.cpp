#include <iostream>
#include <vector>
#include <iomanip>  // For hexadecimal formatting

// EJERCICIO: Implementar la clase DTO StreetLightDTO

// DTO class to contain the streetlight sensor data
class streetLightDTO {

};

// Simulated LoRa modem class
class LoRaModem {
public:
    // Method to send binary data
    void send(const std::vector<uint8_t>& data) {
        std::cout << "[LoRa] Sending binary data: ";
        for (uint8_t byte : data) {
            std::cout << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(byte) << " ";
        }
        std::cout << std::endl;
    }
};

// Function to simulate data collection from streetlight sensors
streetLightDTO collectStreetlightData() {
    float current = 1.5f;    // Simulated current (in Amperes)
    float rmsVoltage = 220.0f; // Simulated RMS voltage (in Volts)
    float brightness = 750.0f; // Simulated brightness (in Lumens)

    // Return a DTO with the simulated data
    return streetLightDTO(current, rmsVoltage, brightness);
}

int main() {
    // Create an instance of the LoRa modem
    LoRaModem modem;

    // Collect streetlight data
    streetLightDTO data = collectStreetlightData();

    // Serialize the data into binary format
    std::vector<uint8_t> binaryData = data.serialize();

    // Send the serialized data via the LoRa modem
    modem.send(binaryData);

    return 0;
}
