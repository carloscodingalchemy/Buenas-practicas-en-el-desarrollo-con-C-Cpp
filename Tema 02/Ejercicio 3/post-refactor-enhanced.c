#include <stdint.h>

typedef struct
{
  volatile uint32_t SR;         /*!< USART Status register,                   Address offset: 0x00 */
  volatile uint32_t DR;         /*!< USART Data register,                     Address offset: 0x04 */
  volatile uint32_t BRR;        /*!< USART Baud rate register,                Address offset: 0x08 */
  volatile uint32_t CR;         /*!< USART Control register,                  Address offset: 0x0C */
} UART_TypeDef;

#define UART_BASE   0X40000000UL
#define USART2      ((UART_TypeDef *) UART_BASE)

#define CLOCK_FREQ    16000000UL // 16MHz
#define PREESCALER    8
#define BAUDRATE_9600 9600

/** |X|X|FLOW CONTROL|ENABLE|X|X|X|X| */
#define UART_ENABLE         (4 << 1)
#define UART_FLOW_CONTROL   (5 << 1)



void UART_init(uint32_t baudrate)
{
    UART_BASE->CR = UART_ENABLE | UART_FLOW_CONTROL;
    UART_BASE->BRR = CLOCK_FREQ / (baudrate * PREESCALER);
}

int main() {
    
    UART_init(BAUDRATE_9600);

    // Transmitir y recibir datos aquí...

    return 0;
}