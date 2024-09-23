#include <stdint.h>

#define UART_BASE_ADDR 0x40011000
#define UART_CR1 (*(volatile uint32_t *)(UART_BASE_ADDR + 0x00)) // Control register
#define UART_BRR (*(volatile uint32_t *)(UART_BASE_ADDR + 0x0C)) // Baud rate register

#define SYSTEM_CLOCK    (8000000U)
#define UART_ENABLE     (13 << 1)
#define TX_ENABLE       (3 << 1)
#define RX_ENABLE       (2 << 1)

#define BAUDRATE_9600   9600
#define BAUDRATE_19200  19200

/** |x|x|UART ENEBALE|x|      ...         |tx enable|rx enable| */

void UART_Init(uint32_t baudrate) {
    /** El baudrate se calcula como el cociente entre el system clock y el baudrate */
    UART_BRR = SYSTEM_CLOCK / baudrate; // Configure baudrate
    UART_CR1 = UART_ENABLE | TX_ENABLE | RX_ENABLE; // Activar UART, habilitar transmisión y recepción
}

int main() {
    UART_Init(BAUDRATE_9600); // Inicializar UART a 9600 bps
    // Código que utiliza UART...
    return 0;
}
