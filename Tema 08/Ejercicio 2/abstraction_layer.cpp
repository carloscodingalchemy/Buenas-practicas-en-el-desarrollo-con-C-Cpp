
struct SensorData {
    float temperature;
    float humidity;
    float wind_speed;
};

// Clase abstracta para representar un sensor genérico
class Sensor {
public:
    virtual ~Sensor() = default;
    virtual void init() = 0;
    virtual SensorData read() = 0;
};


// Clase abstracta para representar un módulo LoRa
class LoRa {
public:
    virtual ~LoRa() = default;
    virtual void init() = 0;
    virtual void send(const std::vector<uint8_t>& data) = 0;
};



class TemperatureSensorFake : public Sensor {
public:
    void init() override {
        std::srand((unsigned) std::time(nullptr));
    }

    float read() override {
        float temperature;
        temperature = (std::rand() % 3000) / 100.0f;  // 0.0 a 30.0 grados

        return temperature;
    }
};

class HumiditySensorFake : public Sensor {
public:
    void init() override {
        std::srand((unsigned) std::time(nullptr));
    }

    float read() override {
        float humidity;
        humidity = (std::rand() % 10000) / 100.0f;    // 0.0 a 100.0%
        return data;
    }
};

class WindSpeedSensorFake : public Sensor {
public:
    void init() override {
        std::srand((unsigned) std::time(nullptr));
    }

    float read() override {
        float wind_speed;
        wind_speed = (std::rand() % 5000) / 100.0f;   // 0.0 a 50.0 km/h
        return wind_speed;
    }
};


class LoRaFake : public LoRa {
public:
    void init() override {
        std::cout << "LoRa module initialized (Mock)" << std::endl;
    }

    void send(const SensorData& data) override {
        std::cout << "LoRa sending data: Temp=" << data.temperature
                  << ", Humidity=" << data.humidity
                  << ", WindSpeed=" << data.wind_speed << std::endl;
    }
};

// EJERCICIO: Crear una clase SensorManager que maneje los sensores y permita aislar el código de la aplicación de la lógica de los sensores.
class SensorManager
{
    private:
    
    public:
    SensorManager();

    // Método que delega la lectura de datos al sensor
    SensorData getSensorData() {

        return data;
    }
};



#include "Sensor.h"
#include "LoRa.h"
#include "SensorFake.h"
#include "LoRaFake.h"
#include <thread>
#include <chrono>

int main() {
    TemperatureSensorFake temperatureSensor;
    HumiditySensorFake humiditySensor;
    WindSpeedSensorFake windSpeedSensor;

    SensorManager sensor(temperatureSensor, humiditySensor, windSpeedSensor);

    LoRaFake lora;

    sensor.init();
    lora.init();

    SensorData avg_data = {0};
    int samples = 0;

    while (true) {
        // Leer sensores cada 5 minutos
        SensorData current_data = sensor.read();
        avg_data.temperature += current_data.temperature;
        avg_data.humidity += current_data.humidity;
        avg_data.wind_speed += current_data.wind_speed;
        samples++;

        // Cada hora, enviar los valores medios por LoRa
        if (samples >= 12) {
            avg_data.temperature /= samples;
            avg_data.humidity /= samples;
            avg_data.wind_speed /= samples;

            lora.send(avg_data);

            // Reiniciar acumuladores
            avg_data = {0};
            samples = 0;
        }

        std::this_thread::sleep_for(std::chrono::minutes(5));  // Esperar 5 minutos
    }

    return 0;
}

