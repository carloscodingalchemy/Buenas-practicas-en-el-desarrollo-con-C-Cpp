#include <stdio.h>
#include <stdint.h>
#include <string.h>

// EJERCICIO: Añadir un nuevo tipo de sensor (light) y modificar el código necesario para implementar la funcionalidad adecuada.

// Definir los tipos de sensor
typedef enum {
    TEMPERATURE_SENSOR,
    PRESSURE_SENSOR,
    HUMIDITY_SENSOR
} SensorType;

// Estructura para manejar el sensor
typedef struct {
    uint8_t data;          // Datos del sensor (en este caso, un byte de información)
    SensorType type;       // Tipo de sensor (temperatura, presión, humedad, etc.)
    uint32_t readPeriod;   // Período de lectura en milisegundos
} Sensor;

// Función para inicializar el sensor
void initSensor(Sensor *sensor, SensorType type, uint32_t readPeriod) {
    sensor->data = 0;  // Inicializar datos en 0
    sensor->type = type;
    sensor->readPeriod = readPeriod;
    printf("Sensor inicializado (Tipo: %d, Período de lectura: %u ms)\n", type, readPeriod);
}

// Función para leer los datos del sensor (simulación)
void readSensor(Sensor *sensor) {
    // Simular la lectura de diferentes tipos de sensores
    if (sensor->type == TEMPERATURE_SENSOR) {
        sensor->data = 25;  // Simula la lectura de temperatura
        printf("Leyendo temperatura: %d°C\n", sensor->data);
    } else if (sensor->type == PRESSURE_SENSOR) {
        sensor->data = 101;  // Simula la lectura de presión
        printf("Leyendo presión: %d kPa\n", sensor->data);
    } else if (sensor->type == HUMIDITY_SENSOR) {
        sensor->data = 60;  // Simula la lectura de humedad
        printf("Leyendo humedad: %d%%\n", sensor->data);
    }
}

// Función para configurar el período de lectura
void setReadPeriod(Sensor *sensor, uint32_t newPeriod) {
    sensor->readPeriod = newPeriod;
    printf("Nuevo período de lectura establecido: %u ms\n", newPeriod);
}

// Función para obtener una descripción del tipo de sensor
const char* getSensorTypeDescription(Sensor *sensor) {
    switch (sensor->type) {
        case TEMPERATURE_SENSOR:
            return "Sensor de temperatura";
        case PRESSURE_SENSOR:
            return "Sensor de presión";
        case HUMIDITY_SENSOR:
            return "Sensor de humedad";
        default:
            return "Sensor desconocido";
    }
}

int main() {
    // Crear un sensor de temperatura
    Sensor temperatureSensor;
    initSensor(&temperatureSensor, TEMPERATURE_SENSOR, 1000);  // Período de lectura de 1 segundo

    // Leer los datos del sensor
    readSensor(&temperatureSensor);

    // Configurar un nuevo período de lectura
    setReadPeriod(&temperatureSensor, 500);  // Cambiar a 500 ms

    // Obtener el tipo de sensor y mostrarlo
    printf("Tipo de sensor: %s\n", getSensorTypeDescription(&temperatureSensor));

    return 0;
}
