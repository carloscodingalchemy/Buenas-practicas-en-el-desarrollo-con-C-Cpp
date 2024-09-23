#include <stdint.h>

#define UART_BASE_ADDR 0x40000000  // Dirección base de los registros UART

// Macros para los registros de configuración
#define UART_BAUD_RATE_REG (*(volatile uint32_t *)(UART_BASE_ADDR + 0x00))  // Registro de baud rate
#define UART_DATA_BITS_REG (*(volatile uint8_t *)(UART_BASE_ADDR + 0x04))   // Registro de bits de datos
#define UART_PARITY_REG    (*(volatile uint8_t *)(UART_BASE_ADDR + 0x08))   // Registro de paridad

typedef struct
{
    uint32_t baud_rate;
    uint8_t data_bits;
    char parity;
} UARTConfig_t;

// Función que configura la UART directamente escribiendo en los registros
void UART_Config(UARTConfig_t UARTConfigValues) {
    // Configurar el baud rate
    UART_BAUD_RATE_REG = UARTConfigValues.baud_rate;
    
    // Configurar el número de bits de datos
    UART_DATA_BITS_REG = UARTConfigValues.data_bits;
    
    // Configurar el tipo de paridad ('N' para ninguna, 'E' para par, 'O' para impar)
    switch (UARTConfigValues.parity) {
        case 'N':  // Sin paridad
            UART_PARITY_REG = 0x00;
            break;
        case 'E':  // Paridad par (Even)
            UART_PARITY_REG = 0x01;
            break;
        case 'O':  // Paridad impar (Odd)
            UART_PARITY_REG = 0x02;
            break;
        default:   // Si no se reconoce la paridad, configurar sin paridad
            UART_PARITY_REG = 0x00;
            break;
    }
}

// Main para probar la configuración de la UART
int main() {
    uint32_t baud_rate = 9600;  // Configuración del baud rate
    uint8_t data_bits = 8;      // Configuración de 8 bits de datos
    char parity = 'N';          // Sin paridad

    // Configurar la UART con los valores especificados
    UART_Config(baud_rate, data_bits, parity);

    return 0;
}
