#include <stdint.h>
#include <stddef.h>

#include "spi.h"
#include "unity.h"
// Prototipo de la función a testear
void spi_read(SPIPort* port, uint8_t* buffer);

// Variables globales para el mock
static uint8_t mock_read_value = 0;
static uint8_t read_value = 0;

// Función de escritura mock
void mock_write(uint8_t data) {
    // Aquí se puede agregar lógica para comprobar que el valor enviado es el esperado, si es necesario
}

// Función de lectura mock
uint8_t mock_read(void) {
    return mock_read_value; // Retorna el valor que hemos definido para simular la lectura
}

// Configuración inicial para las pruebas
void setUp(void) {
    mock_read_value = 0xAB; // Valor simulado que se espera leer del puerto SPI
}

// Finalización de las pruebas
void tearDown(void) {
    // Aquí puedes agregar limpieza si es necesario
}

// Test de la función spi_read
void test_spi_read(void) {
    SPIPort port = { .write = mock_write, .read = mock_read };
    uint8_t buffer = 0;

    spi_read(&port, &buffer);

    // Verifica que el buffer contenga el valor simulado
    TEST_ASSERT_EQUAL_UINT8(0xAB, buffer);
}

// Función principal para ejecutar pruebas
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_spi_read);
    return UNITY_END();
}
