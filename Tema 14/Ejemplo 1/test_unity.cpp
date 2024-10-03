#include <stdint.h>

#define SENSOR_READ_VALUE_CMD 0x00

typedef struct {
    void (*write)(uint8_t data);
    uint8_t (*read)(void);
} SPIPort;


void readSensor(SPIPort* port, uint8_t* buffer) {
    // Enviar un comando para leer (puede ser 0x00 o cualquier otro según el protocolo)
    port->write(SENSOR_READ_VALUE_CMD);
    // Leer el valor y almacenarlo en el buffer
    *buffer = port->read();
}
