#include <iostream>
#include <string>

class Sensor {
private:
    float temperature;
    bool isCalibrated;

public:
    Sensor() : temperature(0.0), isCalibrated(false) {}

    void initialize(void)
    {
        calibrate();
        // Otras tareas de inicializacion
    }

    // Esta función no sigue el principio de separación de consultas
    // porque no solo devuelve la temperatura, sino que también modifica el estado al calibrar.
    float getTemperature() {
 
        return temperature;
    }


    // Simula la actualización de la temperatura
    void updateTemperature(float temp) {
        temperature = temp;
    }

private:
    // Función para calibrar el sensor
    void calibrate() {
        std::cout << "Calibrando sensor..." << std::endl;
        isCalibrated = true;
    }

    bool isCalibrated(void)
    {
        return isCalibrated;
    }
};

int main() {
    Sensor sensor;

    sensor.initialize();

    

    // Obtener la temperatura del sensor
    std::cout << "La temperatura es: " << sensor.getTemperature() << " C" << std::endl;

    return 0;
}
