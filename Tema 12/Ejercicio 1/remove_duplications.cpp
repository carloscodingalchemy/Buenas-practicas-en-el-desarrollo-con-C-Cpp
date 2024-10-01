#include <iostream>
#include <fstream>
#include <cstdint>

// Definición de una estructura que puede tener padding
struct SensorData {
    uint32_t temperature; // 4 bytes
    uint16_t pressure;    // 2 bytes
    uint8_t padding[2];   // 2 bytes de padding para alineación
    float humidity;       // 4 bytes
    int64_t timestamp;    // 8 bytes
};


// Serializa la estructura a un archivo binario
void serialize(const SensorData& data, const std::string& filename) {
    std::ofstream ofs(filename, std::ios::binary);
    if (!ofs) {
        std::cerr << "Error al abrir el archivo para escritura." << std::endl;
        return;
    }

    // Serializar cada miembro individualmente
    ofs.write(reinterpret_cast<const char*>(&data.temperature), sizeof(data.temperature));
    ofs.write(reinterpret_cast<const char*>(&data.pressure), sizeof(data.pressure));
    ofs.write(reinterpret_cast<const char*>(&data.humidity), sizeof(data.humidity));
    ofs.write(reinterpret_cast<const char*>(&data.timestamp), sizeof(data.timestamp));

    ofs.close();
}

// Deserializa la estructura desde un archivo binario
void deserialize(SensorData& data, const std::string& filename) {
    std::ifstream ifs(filename, std::ios::binary);
    if (!ifs) {
        std::cerr << "Error al abrir el archivo para lectura." << std::endl;
        return;
    }

    // Deserializar cada miembro individualmente
    ifs.read(reinterpret_cast<char*>(&data.temperature), sizeof(data.temperature));
    ifs.read(reinterpret_cast<char*>(&data.pressure), sizeof(data.pressure));
    ifs.read(reinterpret_cast<char*>(&data.humidity), sizeof(data.humidity));
    ifs.read(reinterpret_cast<char*>(&data.timestamp), sizeof(data.timestamp));

    ifs.close();
}
