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

// Función demasiado compleja que realiza múltiples tareas
void processSensorsAndSendData() {
    // Leer datos del sensor de temperatura y humedad
    float temperature = readTemperatureSensor();
    float humidity = readHumiditySensor();

    // Leer el sensor de luz
    uint16_t lightLevel = readLightSensor();

    // Formatear los datos en un mensaje para enviarlo
    char message[100];
    snprintf(message, sizeof(message), "T: %.2f C, H: %.2f %%, L: %d lux", temperature, humidity, lightLevel);

    // Enviar los datos a través de la UART
    UART_Send(message);

    // Esperar una respuesta del servidor
    char* response = UART_Receive();

    // Procesar la respuesta
    if (strcmp(response, "OK") == 0) {
        // Respuesta exitosa
        printf("Datos enviados correctamente.\n");
    } else {
        // Error en la respuesta
        printf("Error en el envío de datos.\n");
    }
}

int main() {
    // Ejecución de la función compleja
    processSensorsAndSendData();
    return 0;
}
