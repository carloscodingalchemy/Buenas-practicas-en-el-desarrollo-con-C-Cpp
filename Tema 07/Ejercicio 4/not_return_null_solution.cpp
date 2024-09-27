#include <iostream>
#include <memory>
#include <string>

using namespace std;

// Clase base para representar un sensor
class Sensor {
public:
    virtual ~Sensor() = default;

    // Métodos virtuales que pueden ser sobrecargados por clases derivadas
    virtual void readData() const = 0;
    virtual string getName() const = 0;
};

// Clase que representa un sensor real
class RealSensor : public Sensor {
private:
    string name;
public:
    RealSensor(const string& name) : name(name) {}

    void readData() const override {
        cout << "Leyendo datos del sensor: " << name << endl;
    }

    string getName() const override {
        return name;
    }
};

// Clase que representa un sensor nulo (no hace nada)
class NullSensor : public Sensor {
public:
    // Implementación de métodos vacíos
    void readData() const override {
        // No hace nada
    }

    string getName() const override {
        return "Sensor Nulo";
    }
};

// Clase para gestionar múltiples sensores
class SensorManager {
private:
    shared_ptr<Sensor> nullSensor;  // Usaremos un único objeto NullSensor

public:
    SensorManager() : nullSensor(make_shared<NullSensor>()) {}

    // Método para obtener un sensor. Si no existe, devuelve el objeto NullSensor.
    shared_ptr<Sensor> getSensor(const string& sensorName) {
        // Simulamos que solo hay un sensor disponible llamado "Temperatura"
        if (sensorName == "Temperatura") {
            return make_shared<RealSensor>("Temperatura");
        } else {
            // En lugar de devolver nullptr, devolvemos el objeto NullSensor
            return nullSensor;
        }
    }
};

int main() {
    SensorManager manager;

    // Intentamos obtener un sensor que existe
    shared_ptr<Sensor> sensor1 = manager.getSensor("Temperatura");
    cout << "Sensor encontrado: " << sensor1->getName() << endl;
    sensor1->readData();

    // Intentamos obtener un sensor que no existe
    shared_ptr<Sensor> sensor2 = manager.getSensor("Presion");
    cout << "Sensor encontrado: " << sensor2->getName() << endl;  // No se necesita verificar nullptr
    sensor2->readData();  // No hará nada

    return 0;
}
