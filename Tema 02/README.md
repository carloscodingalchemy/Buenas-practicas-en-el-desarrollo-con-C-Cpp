# TEMA 2 - LA IMPORTANCIA DEL NOMBRADO

## 2.1 El nombre debe revelar las intenciones
Los nombres de variables, funciones, clases y métodos deben ser **descriptivos y explicar claramente su propósito**.  
Un buen nombre permite que otro desarrollador entienda qué hace una entidad en el código sin necesidad de leer toda su implementación (o un comentario más largo que una clase de cálculo).


```C
#include <stdio.h>

// Función para leer el valor del sensor de humedad desde la dirección 0x70001C00
int a() {
    int *dirSensor = (int *)0x70001C00; // Dirección de memoria del sensor
    return *dirSensor; // Leer el valor de la dirección de memoria
}

// Función para enviar los datos usando LoRa, escribiendo en la dirección 0x70002000
void b(int x) {
    int *dirLoRa = (int *)0x70002000; // Dirección de memoria del modem LoRa
    *dirLoRa = x; // Enviar el valor escribiendo en la dirección de memoria
    printf("Dato enviado: %d\n", x);
}

int main() {
    int c; // Variable para almacenar el valor de humedad
    c = a(); // Leer valor del sensor
    b(c); // Enviar valor del sensor por LoRa
    return 0;
}
```

```C
#include <stdio.h>

typedef struct
{
  volatile uint32_t CR;         /*!< Control register,                 Address offset: 0x00 */
  volatile uint32_t TX;         /*!< TX register,                      Address offset: 0x04 */
  volatile uint32_t RX;         /*!< RX register,                      Address offset: 0x08 */
  volatile uint32_t SPEED;      /*!< Speed register,                   Address offset: 0x0C */
  volatile uint32_t CPOL;       /*!< Clok polarity register,           Address offset: 0x10 */
} SPI_TypeDef;

#define SPI_BASE   0X40000000UL

#define SPI1      ((SPI_TypeDef *) SPI_BASE)
#define SPI2      ((SPI_TypeDef *) SPI_BASE + 0X00001000)

void enviarDatosSPI(SPI_TypeDef *spi, uint32_t data) {
    // Escribir el dato en el registro TX para enviarlo
    spi->TX = data;

    // Esperar hasta que el SPI esté listo para enviar (chequear bit de estado en CR)
    // Asumimos que el bit 1 de CR indica si se puede enviar
    while (!(spi->CR & (1 << 1))) {
        // Esperar hasta que el bit 1 esté en alto (indica que se puede enviar)
    }
}


uint32_t recibirDatosSPI(SPI_TypeDef *spi) {
    // Esperar hasta que haya datos disponibles para leer (chequear bit de estado en CR)
    // Asumimos que el bit 2 de CR indica si hay datos disponibles para leer
    while (!(spi->CR & (1 << 2))) {
        // Esperar hasta que el bit 2 esté en alto (indica que hay datos para leer)
    }

    // Leer y devolver el dato desde el registro RX
    return spi->RX;
}


// Función para leer el valor del sensor de humedad desde la dirección 0x70001C00
int8_t leerHumedadDesdeSensor() {

    int8_t temperature = recibirDatosSPI(SPI1);

    return temperature; 
}

// Función para enviar los datos por LoRa escribiendo en la dirección 0x70002000
void enviarPorLoRa(int byte) {

    enviarDatosSPI(SPI2, byte);
    
}

int main() {
    int humedad; // Variable para almacenar el valor de la humedad
    humedad = leerHumedadDesdeSensor(); // Leer valor del sensor de humedad
    enviarPorLoRa(humedad); // Enviar el valor del sensor por LoRa
    return 0;
}
```


## 2.2 El problema de la desinformación involuntaria a través del nombrado
Ocurre cuando los nombres seleccionados inducen a errores o no reflejan con precisión lo que realmente representan. Este tipo de desinformación puede crear confusión y errores en el código.

```C
#include <stdio.h>

// Función que procesa el valor del argumento y lo imprime dependiendo del caso
void procesaDato(int dato) {
    switch(dato) {
        case 1:
            printf("El dato es 1\n");
            break;
        case 2:
            printf("El dato es 2\n");
            break;
        case 3:
            printf("El dato es 3\n");
            break;
        default:
            printf("El dato es desconocido\n");
            break;
    }
}

int main() {
    int datoEntrada = 2;  // Ejemplo de dato de entrada
    procesaDato(datoEntrada);  // Llamada a la función con el valor de entrada
    return 0;
}
```

## 2.3 Legibilidad y Búsqueda de nombres
La legibilidad es clave para que el código sea fácil de entender por otros desarrolladores (o por el mismo desarrollador en el futuro). Además, los nombres fáciles de buscar (que no sean demasiado comunes o genéricos) facilitan el mantenimiento del código.  

Ejemplo: un nombre genérico como ``buffer`` es difícil de buscar y contextualizar, mientras que ``received_bytes`` es mucho más claro.

## 2.4 Prefijos, interfaces, implementaciones y notación húngara
Los prefijos y notaciones son técnicas que pueden ayudar a aclarar el rol de una variable o función. Por ejemplo, la notación húngara añade un prefijo que indica el tipo o propósito de una variable.


```C
void write_byte(uint8_t byte)
{
    uint8_t u16Slot;


 // More later...

    u16Slot = getNextSlot();

// El valor que se leia se truncaba porque la variable solo tenía 8 bits, en lugar de 16 bits.

// Una semana de debug después, 

}

```


```cpp
#include <iostream>
#include <string>

// Define the UART interface using an abstract class
class ISerial {
public:
    // Pure virtual method for initializing the UART
    virtual void initialize(int baudRate) = 0;

    // Pure virtual method for sending a byte of data
    virtual void sendByte(uint8_t data) = 0;

    // Pure virtual method for receiving a byte of data
    virtual uint8_t receiveByte() = 0;

    // Pure virtual method for sending a string
    virtual void sendString(const std::string& str) = 0;

    // Virtual destructor to ensure proper cleanup of derived classes
    virtual ~ISerial() {}
};

// Class that implements the IUART interface
class Serial : public ISerial {
private:
    int baudRate;
public:
    // Implementation of the initialize method
    void initialize(int baudRate) override {
        this->baudRate = baudRate;
        std::cout << "UART initialized at " << baudRate << " baud rate." << std::endl;
    }

    // Implementation of the sendByte method
    void sendByte(uint8_t data) override {
        std::cout << "Sending byte: " << static_cast<int>(data) << std::endl;
    }

    // Implementation of the receiveByte method
    uint8_t receiveByte() override {
        uint8_t data = 42;  // Simulate receiving a byte
        std::cout << "Receiving byte: " << static_cast<int>(data) << std::endl;
        return data;
    }

    // Implementation of the sendString method
    void sendString(const std::string& str) override {
        std::cout << "Sending string: " << str << std::endl;
    }
};
```
Una excepción para la notación hungara:

Es bastante común, dentro de las clases, añadir un prefijo ``m``, ``_`` o ``m_`` para identificar univocamente a los miembros de la clase.
De esta forma, evitamos ambiguedades con otras variables locales dentro de metodos. Y además, evitamos utilizar el operador ``this->``.

Recomendación: Si vas a usar prefijos para tus miembros, usa ``m_``. Es un prefijo mucho más sencillo de buscar con grep/find que los otros.

```cpp
#include <iostream>
#include <string>

class Sensor {
private:
    int m_id;              // Miembro para almacenar el ID del sensor
    float m_value;         // Miembro para almacenar el valor de lectura del sensor
    std::string m_type;    // Miembro para almacenar el tipo de sensor (e.g., temperatura, humedad)

public:
    // Constructor
    Sensor(int id, const std::string& type) 
        : m_id(id), m_value(0.0), m_type(type) {}

    // Método para establecer el valor de lectura del sensor
    void setValue(float value) {
        m_value = value;
    }

    // Método para obtener el valor de lectura del sensor
    float getValue() const {
        return m_value;
    }

    // Método para obtener el ID del sensor
    int getId() const {
        return m_id;
    }

    // Método para obtener el tipo del sensor
    std::string getType() const {
        return m_type;
    }

    // Método para mostrar la información del sensor
    void displayInfo() const {
        std::cout << "Sensor ID: " << m_id << "\n";
        std::cout << "Sensor Type: " << m_type << "\n";
        std::cout << "Sensor Value: " << m_value << "\n";
    }
};
```

**CURIOSIDAD**: El framework Qt, utiliza el prefijo Q en todas sus clases. Eso permite, a cualquiera que vea un código que utiliza su framework, saber rapidamente que está hecho en Qt. Sirve más a un proposito de marca que de código.

## 2.5 El problema de la asignación mental (complejidad cognitiva)
Este problema ocurre cuando el desarrollador o el lector del código tiene que realizar demasiados pasos mentales para comprender el propósito de una variable o función. Los nombres vagos o mal elegidos imponen una carga cognitiva innecesaria.
Ejemplo: el uso de variables como x1, x2, en lugar de nombres descriptivos, obliga a los lectores a recordar qué significa cada una.

```cpp
#include <iostream>
#include <string>
#include <vector>

class Sensor {
public:
    std::string type;
    float value;

    Sensor(const std::string& type, float value) : type(type), value(value) {}
};

class SensorManager {
private:
    std::vector<Sensor> sensors;

public:

    void addSensor(const std::string& type, float value) {
        sensors.push_back(Sensor(type, value));
    }

    // Función compleja para procesar los sensores
    void processSensors() {
        for (size_t i = 0; i < sensors.size(); ++i) {
            if (sensors[i].type == "Temperature") {
                if (sensors[i].value > 40.0) {
                    std::cout << "Warning: High temperature detected!\n";
                    if (sensors[i].value > 45.0) {
                        std::cout << "Critical temperature! Immediate action required!\n";
                        if (sensors[i].value > 50.0) {
                            std::cout << "Emergency shutdown due to extreme temperature!\n";
                        }
                    } else {
                        std::cout << "Temperature is above normal, but manageable.\n";
                    }
                } else if (sensors[i].value < 5.0) {
                    std::cout << "Warning: Low temperature detected!\n";
                    if (sensors[i].value < 0.0) {
                        std::cout << "Critical low temperature! Freezing hazard!\n";
                        if (sensors[i].value < -10.0) {
                            std::cout << "Extreme low temperature! System freeze imminent!\n";
                        }
                    }
                }
            } else if (sensors[i].type == "Humidity") {
                if (sensors[i].value > 70.0) {
                    std::cout << "Warning: High humidity detected!\n";
                    if (sensors[i].value > 80.0) {
                        std::cout << "Critical humidity level! Possible damage to equipment.\n";
                    }
                } else if (sensors[i].value < 30.0) {
                    std::cout << "Warning: Low humidity detected!\n";
                    if (sensors[i].value < 20.0) {
                        std::cout << "Critical low humidity! Risk of electrostatic discharge.\n";
                    }
                }
            } else if (sensors[i].type == "Pressure") {
                if (sensors[i].value > 100.0) {
                    std::cout << "Warning: High pressure detected!\n";
                    if (sensors[i].value > 110.0) {
                        std::cout << "Critical pressure! System overload imminent.\n";
                    }
                } else if (sensors[i].value < 50.0) {
                    std::cout << "Warning: Low pressure detected!\n";
                    if (sensors[i].value < 40.0) {
                        std::cout << "Critical low pressure! System failure possible.\n";
                    }
                }
            } else {
                std::cout << "Unknown sensor type: " << sensors[i].type << "\n";
            }
        }
    }
};
```

## 2.6 Nombrado de clases y métodos
Los nombres de clases deben ser sustantivos o nombres que representen una entidad o concepto dentro del dominio del problema, mientras que los métodos deben describir acciones o comportamientos que dicha entidad puede realizar.  

Ejemplo: una clase podría llamarse ``UART`` y un método ``sendByte``.


## 2.7 Un concepto, una palabra
Consiste en mantener **consistencia** en el uso de nombres a lo largo del código. 

Si un concepto se representa de una manera en una parte del código, debe seguir representándose de la misma manera en otras partes.
Ejemplo: si se usa ``get`` para obtener valores, no mezclarlo con ``fetch`` o ``retrieve`` en otros lugares.



## 2.8 Juegos de palabras, un error a evitar
Utilizar juegos de palabras, abreviaturas confusas o nombres creativos que no son inmediatamente comprensibles puede dificultar la lectura y comprensión del código.`

Ejemplo: llamar a una variable ``flatWrite()`` en lugar de ``write()`` puede confundir a los desarrolladores que lean el código más tarde.

## 2.9 Nombrado de dominios de problemas y soluciones

Cuando el código que estás escribiendo, hace uso de artefactos propios de la programación (colas, arrays, listas, vectores, "patron factory", etc) lo recomendable es utilizar esos terminos en el nombrado de las variables.

```Cpp
std::queue<std::string> messageQueue;
```

```C
uint32_t temperatureSensorArray[NUM_SENSORS];
```

Cuando no se están manejando conceptos propios dela programación, es importante que los nombres reflejen correctamente los conceptos del dominio del problema que el código está tratando de resolver. 

```C
int temp;  // Se refiere a "patient temperature"
```
```C
int patientTemperature;
```

## 2.10 Contextos innecesarios, una distracción a evitar
Añadir contexto innecesario en los nombres puede resultar en una mayor verbosidad que distrae. Los nombres deben ser concisos y evitar redundancias innecesarias.


```cpp

class clasePuertoSerie 
{

}
```

```cpp

class PuertoSerie 
{

}
```

Sin embargo en otros casos la falta de contexto hace dificil entender el propósito de la variable. 

```C
int value;  // ¿Qué tipo de valor? ¿De qué sistema o componente?
```

```C
int temperatureValue;  // ¿Qué tipo de valor? ¿De qué sistema o componente?
```

