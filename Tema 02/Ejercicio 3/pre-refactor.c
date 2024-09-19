int main() {
    // Configurando UART directamente sin comentarios ni modularización
    *(volatile uint32_t *)0x4001100C = 8000000 / 9600; // Configuración de baudrate
    *(volatile uint32_t *)0x40011000 = 0x200C; // Activar UART

    // Transmitir y recibir datos aquí...

    return 0;
}
