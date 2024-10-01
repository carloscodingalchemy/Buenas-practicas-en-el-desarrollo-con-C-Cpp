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


// Template para serializar un miembro de la estructura
template <typename T>
void serializeMember(std::ostream& os, const T& member) {
    os.write(reinterpret_cast<const char*>(&member), sizeof(T));
}

// Serializa la estructura a un archivo binario
void serialize(const SensorData& data, const std::string& filename) {
    std::ofstream ofs(filename, std::ios::binary);
    if (!ofs) {
        std::cerr << "Error al abrir el archivo para escritura." << std::endl;
        return;
    }

    // Serializar cada miembro usando el template
    serializeMember(ofs, data.temperature);
    serializeMember(ofs, data.pressure);
    serializeMember(ofs, data.humidity);
    serializeMember(ofs, data.timestamp);

    ofs.close();
}

// Deserializa un miembro de la estructura
template <typename T>
void deserializeMember(std::istream& is, T& member) {
    is.read(reinterpret_cast<char*>(&member), sizeof(T));
}

// Deserializa la estructura desde un archivo binario
void deserialize(SensorData& data, const std::string& filename) {
    std::ifstream ifs(filename, std::ios::binary);
    if (!ifs) {
        std::cerr << "Error al abrir el archivo para lectura." << std::endl;
        return;
    }

    // Deserializar cada miembro usando el template
    deserializeMember(ifs, data.temperature);
    deserializeMember(ifs, data.pressure);
    deserializeMember(ifs, data.humidity);
    deserializeMember(ifs, data.timestamp);

    ifs.close();
}