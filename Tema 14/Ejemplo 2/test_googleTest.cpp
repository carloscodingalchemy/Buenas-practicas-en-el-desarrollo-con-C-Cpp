#ifndef UART_H
#define UART_H

#include <iostream>

// Implementacion real de la UART
class UART {
public:
    // Método para inicializar el UART
    void init() {
        std::cout << "UART inicializado." << std::endl;
    }

    // Método para enviar datos
    void send(const char* data) {
        std::cout << "Enviando por UART: " << data << std::endl;
    }

    // Método para recibir datos (simulado)
    const char* receive() {
        return "Datos recibidos"; // Simula la recepción de datos
    }
};

#endif // UART_H


#ifndef CONSOLE_H
#define CONSOLE_H

#include "UART.h"

class Console {
public:
    Console(UART& uart) : uartDevice(uart) {
        uartDevice.init(); // Inicializa el UART al crear la consola
    }

    void printMessage(const char* message) {
        uartDevice.send(message); // Envía un mensaje a través del UART
    }

    const char* readInput() {
        return uartDevice.receive(); // Recibe datos del UART
    }

private:
    UART& uartDevice; // Referencia al dispositivo UART
};

#endif // CONSOLE_H
