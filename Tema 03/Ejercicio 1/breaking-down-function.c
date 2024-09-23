#include <stdint.h>
#include <stdio.h>
#include <string.h>

// Funciones simuladas para la lectura de sensores y UART
float readTemperatureSensor() {
    // Simulación de la lectura de temperatura
    return 25.3;
}

float readHumiditySensor() {
    // Simulación de la lectura de humedad
    return 60.5;
}

uint16_t readLightSensor() {
    // Simulación de la lectura del sensor de luz
    return 500;
}

void UART_Send(const char* data) {
    // Simulación del envío de datos por UART
}

char* UART_Receive() {
    // Simulación de la recepción de datos por UART
    return "OK";
}

typedef struct
{
    float temperature;
    float humidity;
    uint16_t lightLevel;
}SensorsData_t;


readSensors(float * temperature, float *humidity, uint16_t * lightLevel)
{

}


SensorsData_t readSensors(void)
{
    SensorsData_t sensorsData;

    sensorsData.temperature = readTemperatureSensor();
    sensorsData.humidity = readHumiditySensor();
    sensorsData.lightLevel = readLightSensor();

    return sensorsData;
}


void createPayload(uint8_t * message, SensorsData_t SendorsData)
{
    // Formatear los datos en un mensaje para enviarlo
    snprintf(message, sizeof(message), "T: %.2f C, H: %.2f %%, L: %d lux", sensorData.temperature, sensorData.humidity, sensorData.lightLevel);

}

void processModemResponse(const char * response, char * expectedResponse)
{
    // Procesar la respuesta
    if (strcmp(response, expectedResponse) == 0) {
        // Respuesta exitosa
        printf("Datos enviados correctamente.\n");
    } else {
        // Error en la respuesta
        printf("Error en el envío de datos.\n");
    }
}

// Función demasiado compleja que realiza múltiples tareas
void processSensorsAndSendData() {


    SensorsData_t sensorData;
    sensorData = readSensors();

    // Formatear los datos en un mensaje para enviarlo
    char message[100];
    createPayload(uint8_t * message, SensorsData_t SendorsData);

    // Enviar los datos a través de la UART
    UART_Send(message);

    // Esperar una respuesta del servidor
    char* response = UART_Receive();

    processModemResponse(response, "OK");

}

int main() {
    // Ejecución de la función compleja
    SensorsData_t sensorData;
    sensorData = readSensors();

    // Formatear los datos en un mensaje para enviarlo
    char message[100];
    createPayload(uint8_t * message, SensorsData_t SendorsData);

    // Enviar los datos a través de la UART
    UART_Send(message);

    // Esperar una respuesta del servidor
    char* response = UART_Receive();

    processModemResponse(response, "OK");
    
    return 0;
}
