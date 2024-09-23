#include <stdint.h>

#define UART_BASE_ADDR 0x40011000
#define UART_CR1 (*(volatile uint32_t *)(UART_BASE_ADDR + 0x00)) // Control register
#define UART_BRR (*(volatile uint32_t *)(UART_BASE_ADDR + 0x0C)) // Baud rate register

void UART_Init(uint32_t baudrate) {
    UART_BRR = 8000000 / baudrate; // Configure baudrate
    UART_CR1 = 0x200C; // Activar UART, habilitar transmisión y recepción
}

int main() {
    UART_Init(9600); // Inicializar UART a 9600 bps
    // Código que utiliza UART...
    return 0;
}
