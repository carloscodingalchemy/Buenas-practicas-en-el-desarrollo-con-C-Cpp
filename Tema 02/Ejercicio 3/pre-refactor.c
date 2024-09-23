
#include <stdint.h>

#define UART_BASE_ADDR      0x40011000
#define UART_CTRL_REG       (UART_BASE_ADDR + 0X00)
#define UART_BAUDRATE_REG   (UART_BASE_ADDR + 0x0C)
#define UART_TX_REG         (UART_BASE_ADDR + 0x10)

#define SYSTEM_CLOCK        8000000 // System clock 8MHz

#define BAUDRATE_9600       9600

#define ENABLE_UART         (13 << 1)
#define ENABLE_TX           (2 << 1)
#define ENABLE_RX           (3 << 1)


void initUART(uint32_t baudrate)
{
    // Configurando UART directamente sin comentarios ni modularización
    volatile uint32_t * baudrateReg = UART_BAUDRATE_REG;
    volatile uint32_t * uartCtrlReg = UART_CTRL_REG;

    *baudrateReg = SYSTEM_CLOCK / baudrate; // Configuración de baudrate
    *uartCtrlReg = ENABLE_UART | ENABLE_TX | ENABLE_RX; // Activar UART
}

void sendByte(uint8_t byte)
{
    volatile uint32_t * uartTxReg = UART_TX_REG;

    *uartTxReg = byte;
}

int main() {

    initUART(BAUDRATE_9600);

    while(true)
    {
        uint8_t sensorTemp;
        
        sensorTemp = readSensor();

        sendByte(sensorTemp);

        sleep(1);
    }

    return 0;
}
