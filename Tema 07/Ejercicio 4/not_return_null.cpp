#include <iostream>
#include <memory>
#include <string>

using namespace std;

// Clase para representar un sensor
class Sensor {
private:
    string name;
public:
    Sensor(const string& name) : name(name) {}

    void readData() {
        cout << "Leyendo datos del sensor: " << name << endl;
    }

    string getName() const {
        return name;
    }
};

// Clase para gestionar múltiples sensores
class SensorManager {
public:
    // Método para obtener un sensor. Si no existe, devuelve nullptr.
    shared_ptr<Sensor> getSensor(const string& sensorName) {
        // Simulamos que solo hay un sensor disponible llamado "Temperatura"
        if (sensorName == "Temperatura") {
            return make_shared<Sensor>("Temperatura");
        } else {
            // Si el sensor no existe, devolvemos nullptr
            return nullptr;
        }
    }
};

int main() {
    SensorManager manager;

    // Intentamos obtener un sensor que existe
    shared_ptr<Sensor> sensor1 = manager.getSensor("Temperatura");
    
    if (sensor1) {  // Verificamos si es nullptr
        cout << "Sensor encontrado: " << sensor1->getName() << endl;
        sensor1->readData();
    } else {
        cout << "Error: El sensor 'Temperatura' no está disponible." << endl;
    }

    // Intentamos obtener un sensor que no existe
    shared_ptr<Sensor> sensor2 = manager.getSensor("Presion");

    if (sensor2) {  // Verificamos si es nullptr
        cout << "Sensor encontrado: " << sensor2->getName() << endl;
        sensor2->readData();
    } else {
        cout << "Error: El sensor 'Presion' no está disponible." << endl;
    }

    return 0;
}
