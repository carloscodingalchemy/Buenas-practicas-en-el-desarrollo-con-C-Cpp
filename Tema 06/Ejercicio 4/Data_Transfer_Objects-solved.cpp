#include <iostream>
#include <vector>
#include <iomanip>  // For hexadecimal formatting
#include <cstdint>

// DTO class to contain the streetlight sensor data
class streetLightDTO {
public:
    float current;    // Average current of the streetlight in Amperes
    float rmsVoltage; // RMS voltage of the streetlight in Volts
    float brightness; // Brightness of the streetlight in Lumens

    // Constructor to initialize streetlight data
    streetLightDTO(float current, float rmsVoltage, float brightness)
        : current(current), rmsVoltage(rmsVoltage), brightness(brightness) {}

    // Method to serialize the data into a binary format (byte vector)
    std::vector<uint8_t> serialize() const {
        std::vector<uint8_t> buffer;

        // Serialize current (4 bytes)
        buffer.insert(buffer.end(), 
                      reinterpret_cast<const uint8_t*>(&current), 
                      reinterpret_cast<const uint8_t*>(&current) + sizeof(current));

        // Serialize RMS voltage (4 bytes)
        buffer.insert(buffer.end(), 
                      reinterpret_cast<const uint8_t*>(&rmsVoltage), 
                      reinterpret_cast<const uint8_t*>(&rmsVoltage) + sizeof(rmsVoltage));

        // Serialize brightness (4 bytes)
        buffer.insert(buffer.end(), 
                      reinterpret_cast<const uint8_t*>(&brightness), 
                      reinterpret_cast<const uint8_t*>(&brightness) + sizeof(brightness));

        return buffer;
    }
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
