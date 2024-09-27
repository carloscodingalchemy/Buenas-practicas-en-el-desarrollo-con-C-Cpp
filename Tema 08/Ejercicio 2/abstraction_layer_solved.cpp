
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


class SensorManager
{
    private:
    Sensor &m_temperatureSensor;
    Sensor &m_humiditySensor;
    Sensor &m_windSpeedSensor;
    
    public:
    
    SensorManager(Sensor& tempSensorImpl, Sensor& humiditySensorImpl, Sendor& windSpeedSensorImpl) : 
        m_temperatureSensor(tempSensorImpl),
        m_humiditySensor(humiditySensorImpl),
        m_windSpeedSensor(windSpeedSensorImpl)
    {
        m_temperatureSensor.init();
        m_humiditySensor.init();
        m_windSpeedSensor.init();
    }

    // Método que delega la lectura de datos al sensor
    SensorData getSensorData() {
        SensorData data;
        data.temperature = m_temperatureSensor.read();
        data.humidity = m_humiditySensor.read();
        data.wind_speed = m_windSpeedSensor.read();

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

    SensorManager manager(temperatureSensor, humiditySensor, windSpeedSensor);

    LoRaFake lora;

    lora.init();

    SensorData avg_data = {0};
    int samples = 0;

    while (true) {
        // Leer sensores cada 5 minutos
        SensorData current_data = manager.getSensorData();


        lora.send(current_data);



        std::this_thread::sleep_for(std::chrono::minutes(5));  // Esperar 5 minutos
    }

    return 0;
}

