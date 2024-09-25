# TEMA 3 - LAS FUNCIONES EN EL CÓDIGO LIMPIO

## 3.1 El tamaño de las funciones importa
Las funciones deben ser **pequeñas**, idealmente tan cortas que se puedan leer en su totalidad sin necesidad de desplazarse.  
Esto mejora la legibilidad, facilita las pruebas y el mantenimiento, y permite que las funciones tengan una única responsabilidad.
El principio *"funciones cortas"* reduce la complejidad y hace que sea más fácil detectar errores.

## 3.2 La estructura de bloques y la indentación de las funciones
La indentación adecuada dentro de las funciones es esencial para la claridad. Un código correctamente estructurado y bien indentado permite al lector identificar rápidamente los diferentes bloques lógicos y las relaciones jerárquicas entre ellos.
Un nivel de indentación excesivo puede ser un indicio de que la función es demasiado compleja o hace demasiadas cosas.

**Nota**: La complejidad ciclomatica, es un valor que nos confirmará si una función es demasiado compleja.

```C

#include <stdint.h>
#include <stdbool.h>

#define SENSOR_OK         0
#define SENSOR_ERROR      1

// Simulación de funciones para leer el sensor
int readPressureSensor(uint16_t *pressureValue) {
    // Simulamos una lectura de sensor con un valor fijo
    *pressureValue = 1023;
    return SENSOR_OK; // Retorna un estado de operación correcta
}

bool isSensorConnected() {
    return true; // Simulamos que el sensor está conectado
}

bool isPressureWithinRange(uint16_t pressure) {
    return (pressure >= 900 && pressure <= 1100); // Rango válido
}

void processPressureData() {
    uint16_t pressureValue;

    // Verificamos si el sensor está conectado
    if (isSensorConnected()) {
        // Leemos el valor del sensor
        if (readPressureSensor(&pressureValue) == SENSOR_OK) {
            // Validamos que el valor del sensor esté dentro del rango aceptable
            if (isPressureWithinRange(pressureValue)) {
                // Procesamos el valor de presión (ej: guardarlo en memoria o enviarlo)
                if (pressureValue > 1000) {
                    // Si la presión es mayor a 1000, activamos una alarma
                    // Aquí podríamos llamar una función para activar la alarma
                    if (someOtherCondition()) {
                        // Otro condicional adicional para un proceso específico
                        // Algo se ejecuta aquí
                        if (yetAnotherCondition()) {
                            // Todavía más condicionales
                            // Realizar alguna acción
                        }
                    }
                } else {
                    // Si la presión es menor o igual a 1000, hacemos algo distinto
                    // Otra lógica aquí
                }
            } else {
                // Si el valor está fuera de rango, manejamos el error
                // Posible error de sensor fuera de rango
            }
        } else {
            // Si hubo un error al leer el sensor
            // Posible error de comunicación
        }
    } else {
        // Si el sensor no está conectado
        // Manejamos el error de desconexión
    }
}

```

## 3.3 Una función, una funcionalidad
Cada función debe tener una única responsabilidad. 
Esto significa que debe hacer **solo una cosa, pero hacerlo bien**. 
Este principio facilita la comprensión, depuración y modificación del código.

```C
#include <stdio.h>
#include <stdint.h>

#define MAX_TEMP 75               // Temperatura máxima antes de activar la alarma
#define TEMP_SENSOR_REG_ADDR 0x40001000  // Dirección del registro del sensor de temperatura

// Función que hace todo: leer el sensor, imprimir, y activar la alarma si es necesario
int readTemperatureSensor() {
    // Leer el valor del registro de temperatura
    volatile uint32_t *tempSensorReg = (uint32_t *)TEMP_SENSOR_REG_ADDR;
    uint32_t tempValue = *tempSensorReg;

    // Imprimir el valor de la temperatura
    printf("La temperatura actual es: %d°C\n", tempValue);

    // Verificar si la temperatura excede el máximo permitido
    if (tempValue > MAX_TEMP) {
        // Activar la alarma si la temperatura es demasiado alta
        printf("Alarma activada: ¡La temperatura ha excedido el límite!\n");
    }

    return 0; // Retornamos 0 para indicar que la lectura fue exitosa
}
```


## 3.4 La regla descendente y el nivel de abstracción único de las funciones
La regla descendente sugiere que una función debe comenzar con una llamada a otra función de mayor nivel de abstracción y seguir con llamadas a funciones de nivel más bajo. Además, dentro de una función, todo el código debe operar en el mismo nivel de abstracción.
Esto asegura que la función sea coherente y fácil de leer, ya que no mezcla diferentes niveles de detalle.

```C
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_TEMP 75               // Temperatura máxima permitida
#define TEMP_SENSOR_REG_ADDR 0x40001000  // Dirección del registro del sensor de temperatura

// Prototipos de funciones para mantener la estructura descendente
void monitorTemperature();
int readTemperatureSensor();
void processTemperature(uint32_t temperature);
void activateAlarm();
void printTemperature(uint32_t temperature);

// Función principal que sigue la regla descendente
int main() {
    monitorTemperature();
    return 0;
}

// Función de alto nivel que sigue la regla descendente
void monitorTemperature() {
    uint32_t temperature = readTemperatureSensor();
    processTemperature(temperature);
}

// Función que opera en el nivel de abstracción de lectura del sensor
int readTemperatureSensor() {
    volatile uint32_t *tempSensorReg = (uint32_t *)TEMP_SENSOR_REG_ADDR;
    return *tempSensorReg;  // Leemos el valor del registro del sensor
}

// Función que procesa la temperatura (nivel medio de abstracción)
void processTemperature(uint32_t temperature) {
    printTemperature(temperature);  // Imprimir la temperatura
    
    if (temperature > MAX_TEMP) {
        activateAlarm();  // Activar la alarma si la temperatura excede el límite
    }
}

// Función que imprime la temperatura (nivel bajo de abstracción)
void printTemperature(uint32_t temperature) {
    printf("La temperatura actual es: %d°C\n", temperature);
}

// Función que activa la alarma si es necesario (nivel bajo de abstracción)
void activateAlarm() {
    printf("Alarma activada: ¡La temperatura ha excedido el límite!\n");
}

```

## 3.5 Las instrucciones de tipo Switch
Las estructuras switch deben ser usadas con cuidado, ya que tienden a romper el principio de una única responsabilidad. En su lugar, es mejor utilizar polimorfismo u otras formas de delegación cuando sea posible.
Sin embargo, si se usa un switch, debe limitarse a ser lo más pequeño y manejable posible.

```cpp
#include <iostream>
#include <stdint.h>

// Enum que representa los diferentes tipos de sensores
enum class SensorType {
    ModelA,
    ModelB,
    ModelC
};

// Clase que gestiona múltiples tipos de sensores de temperatura
class TemperatureSensor {
private:
    SensorType sensorType;  // Tipo de sensor que se va a manejar

public:
    // Constructor que recibe el tipo de sensor
    TemperatureSensor(SensorType type) : sensorType(type) {}

    // Método para inicializar el sensor dependiendo del modelo
    void initialize() {
        switch (sensorType) {
            case SensorType::ModelA:
                std::cout << "Inicializando sensor Modelo A...\n";
                // Simulación de la inicialización del modelo A
                break;
            case SensorType::ModelB:
                std::cout << "Inicializando sensor Modelo B...\n";
                // Simulación de la inicialización del modelo B
                break;
            case SensorType::ModelC:
                std::cout << "Inicializando sensor Modelo C...\n";
                // Simulación de la inicialización del modelo C
                break;
            default:
                std::cout << "Tipo de sensor no soportado.\n";
                break;
        }
    }

    // Método para leer la temperatura según el tipo de sensor
    void readTemperature() {
        switch (sensorType) {
            case SensorType::ModelA:
                std::cout << "Leyendo temperatura del sensor Modelo A: 25°C\n";
                // Simulación de lectura de temperatura del modelo A
                break;
            case SensorType::ModelB:
                std::cout << "Leyendo temperatura del sensor Modelo B: 30°C\n";
                // Simulación de lectura de temperatura del modelo B
                break;
            case SensorType::ModelC:
                std::cout << "Leyendo temperatura del sensor Modelo C: 28°C\n";
                // Simulación de lectura de temperatura del modelo C
                break;
            default:
                std::cout << "Tipo de sensor no soportado.\n";
                break;
        }
    }
};

// Función principal para simular el uso de la clase TemperatureSensor
int main() {
    // Creando una instancia de sensor para el Modelo A
    TemperatureSensor sensorA(SensorType::ModelA);
    sensorA.initialize();      // Inicializar el sensor Modelo A
    sensorA.readTemperature(); // Leer la temperatura del sensor Modelo A

    std::cout << "--------------------------\n";

    // Creando una instancia de sensor para el Modelo B
    TemperatureSensor sensorB(SensorType::ModelB);
    sensorB.initialize();      // Inicializar el sensor Modelo B
    sensorB.readTemperature(); // Leer la temperatura del sensor Modelo B

    std::cout << "--------------------------\n";

    // Creando una instancia de sensor para el Modelo C
    TemperatureSensor sensorC(SensorType::ModelC);
    sensorC.initialize();      // Inicializar el sensor Modelo C
    sensorC.readTemperature(); // Leer la temperatura del sensor Modelo C

    return 0;
}
```


## 3.6 La importancia del nombrado de las funciones
Los nombres de las funciones deben ser descriptivos y reflejar claramente lo que hace la función. El nombre debe comunicar la intención de la función, facilitando su comprensión sin tener que leer su implementación.  

Ejemplo: ``sendByte()`` es más claro que ``send()``.

## 3.7 Cómo plantear de forma limpia los argumentos en las funciones
Las funciones deben tener la menor cantidad de argumentos posibles, idealmente entre cero y dos. Argumentos excesivos dificultan el uso y comprensión de la función. Cuando hay más de dos argumentos, puede ser recomendable agruparlos en objetos o estructuras.

Ejemplo: en lugar de ``init_UART(uint32_t baudrate, bool flowcontrol, uin8t_t parity)``, puede usarse una estructura/Objecto ``UARTConfig``

## 3.8 La programación funcional y las formas monádicas habituales
La programación funcional favorece funciones puras (sin efectos secundarios), donde los resultados solo dependen de los argumentos que reciben. Las monadas son estructuras que permiten manejar flujos de datos (como el manejo de errores o efectos secundarios) de manera funcional y controlada.


```cpp
#include <iostream>
#include <string>
#include <algorithm>  // Para std::transform
#include <cctype>     // Para std::tolower

// Función que convierte una cadena a minúsculas modificando el parámetro
void toLowerCase(std::string &str) {
    std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
}

int main() {
    // Cadena de prueba
    std::string text = "Hello, World!";

    // Mostrar la cadena original
    std::cout << "Cadena original: " << text << std::endl;

    // Llamada a la función para convertir la cadena a minúsculas
    toLowerCase(text);

    // Mostrar la cadena después de la conversión
    std::cout << "Cadena convertida a minúsculas: " << text << std::endl;

    return 0;
}
```

```cpp
#include <iostream>
#include <string>
#include <algorithm>  // Para std::transform
#include <cctype>     // Para std::tolower

// Función que convierte una cadena a minúsculas y la devuelve
std::string toLowerCase(const std::string &str) {
    std::string result = str;  // Crear una copia de la cadena original

    // Aplicar la transformación a minúsculas
    std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) {
        return std::tolower(c);
    });

    return result;  // Devolver la cadena modificada
}

int main() {
    // Cadena de prueba
    std::string text = "Hello, World!";

    // Mostrar la cadena original
    std::cout << "Cadena original: " << text << std::endl;

    // Llamada a la función para convertir la cadena a minúsculas y obtener el resultado
    std::string lowerText = toLowerCase(text);

    // Mostrar la cadena después de la conversión
    std::cout << "Cadena convertida a minúsculas: " << lowerText << std::endl;

    return 0;
}
```

## 3.9 Los argumentos tipo "flag"
Los argumentos de tipo "flag" son aquellos que alteran el comportamiento de una función, por ejemplo, usando un argumento booleano. En general, se debe evitar este enfoque, ya que puede causar ambigüedad y mezclas de responsabilidades.  
En lugar de un argumento booleano como ``procesar(true)``, es preferible dividir la funcionalidad en dos funciones diferentes.

```C
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>  // Para definir tipos como uint32_t

// Definir la dirección de memoria del registro de temperatura
#define TEMP_SENSOR_REG_ADDR 0x4000000C

// Función que lee el valor de temperatura desde el registro
float readTemperatureFromSensor() {
    // Leer la temperatura desde el registro de memoria (simulación)
    volatile uint32_t *tempReg = (uint32_t *)TEMP_SENSOR_REG_ADDR;
    uint32_t rawTemperature = *tempReg;

    // Simulación: convertir el valor del registro en grados Celsius
    // (Dependerá de cómo esté codificada la temperatura en el hardware real)
    float temperature = (float)(rawTemperature) / 100.0f;  // Ejemplo de conversión

    return temperature;
}

// Función que lee la temperatura y lanza una alarma si el flag está activado
void readTemperature(float limit, bool alarmFlag) {
    // Leer la temperatura desde el sensor
    float temperature = readTemperatureFromSensor();
    printf("Temperatura leída: %.2f°C\n", temperature);

    if (temperature > limit) {
        printf("Advertencia: La temperatura excede el límite de %.2f°C\n", limit);
        
        // Lanzar alarma si el flag alarmFlag es true
        if (alarmFlag) {
            printf("¡Alarma activada!\n");
        }
    } else {
        printf("La temperatura está dentro del rango aceptable.\n");
    }
}

int main() {

    float temperatureLimit = 30.0;  // Límite de temperatura

    // Llamar a la función sin activar la alarma (alarmFlag = false)
    printf("Sin alarma:\n");
    readTemperature(temperatureLimit, false);

    // Llamar a la función con la alarma activada (alarmFlag = true)
    printf("\nCon alarma:\n");
    readTemperature(temperatureLimit, true);

    return 0;
}

```

## 3.10 Planteando funciones diádicas
Las funciones diádicas son aquellas que reciben dos argumentos. En general, son aceptables siempre que los dos argumentos estén claramente relacionados y no resulten confusos para el lector.

Ejemplo: una función ``sumar(a, b)`` es clara, pero una función con dos argumentos de naturaleza distinta puede ser problemática.


```cpp

void writeFile(std::ostream& outputStream, const std::vector<uint8_t>& data) {
    // Escribimos los bytes del vector en el output stream
    outputStream.write(reinterpret_cast<const char*>(data.data()), data.size());

    // Verificamos si hubo algún error durante la escritura
    if (!outputStream) {
        std::cerr << "Error: Failed to write data to the output stream." << std::endl;
    }
}
```
Esta función podría convertirse en una función de un solo argumento si el metodo writeFile perteneciera a una clase que contara con un ``std::ostream`` como miembro (que sería inicializado en el constructor).

```cpp
class FileHandler {

private:
    std::ostream& m_fileStream;  // Referencia al flujo de salida

public:
    // Constructor que inicializa el miembro m_fileStream con el std::ostream pasado
    FileHandler(std::ostream& fileStream) : m_fileStream(fileStream) {}

    void writeFile(const std::vector<uint8_t>& data)
    {
        m_fileStream.write(reinterpret_cast<const char*>(data.data()), data.size());
    }
}
```

## 3.11 Las triadas
Las funciones con tres argumentos empiezan a ser más difíciles de manejar y comprender.
Antes de crear una función con tres argumentos, piensa:  

¿Es necesario? ¿Estoy rompiendo el principio "Single Responsability"? ¿Podría reordenar mi código para tener menos parámetros?

**Nota**: La combinatoria que tiene una función de 3 argumentos es muy alta. Lo cual aumentará enormemente la tarea de hacer tests unitarios para la misma.


## 3.12 Objetos y listas de argumentos
Si una función requiere demasiados argumentos, puede ser preferible **agrupar esos valores en un objeto** o **utilizar listas de argumentos** para mejorar la claridad y mantener el código organizado.


```C
int printf(const char *restrict format, ...);
int sprintf(char *restrict str, const char *restrict format, ...);
```

## 3.13 La importancia de los verbos y las palabras clave
Elegir buenos nombres para las funciones facilita enormemente la comprensión de la tarea que desarrolla la función.

En el caso de una función "monad" la forma verbo/nombre es la más adecuada.

```C
void send(uint8_t byte); /// ¿Que hace la función? Enviar. ¿Que envia? Un byte
```

```C
void sendByte(uint8_t byte);
```

## 3.14 Los argumentos de salida de una función y sus efectos secundarios
Las funciones que alteran el estado de objetos o tienen efectos secundarios deben ser claras al respecto en su nombrado.  

En general, es preferible evitar los efectos secundarios, favoreciendo funciones puras que solo devuelvan valores.
Si una función tiene efectos secundarios, como modificar variables globales o cambiar el estado de un objeto, esto debe ser explícito. 

En cuanto a los argumentos de salida. Deben ser evitados. En OOP, es más apropiado modificar el estado de algunos de los miembros de la propia clase. Y en programación funcional, solo utilizar los valores de retorno.

```cpp
class LoRaModem {

private:

std::queue<vector<uint8_t>> m_ReceivedMessages;

    void fetchMessages()
    {
        std::vector<uint8_t> message = readMessage(UART_Type uart);

        m_ReceivedMessages.push(message);
    }
};
```

## 3.15 Separación de consultas
Una función debe hacer una cosa, o bien consultar (devolver información) o ejecutar una acción (modificar el estado), pero no ambas cosas a la vez.

```cpp
#include <iostream>
#include <string>

class LoRaModem {
private:
    bool poweredOn;
    int frequency;      // Frequency in Hz
    int power;          // Transmission power in dBm
    std::string lastMessage;

public:
    // Constructor
    LoRaModem() : poweredOn(false), frequency(0), power(0), lastMessage("") {}

    // Command: Turns the modem on or off
    void powerOn() {
        poweredOn = true;
        std::cout << "LoRa modem powered on." << std::endl;
    }

    void powerOff() {
        poweredOn = false;
        std::cout << "LoRa modem powered off." << std::endl;
    }

    // Command: Configures the operating frequency of the modem
    void setFrequency(int newFrequency) {
        if (poweredOn) {
            frequency = newFrequency;
            std::cout << "Frequency set to " << frequency << " Hz." << std::endl;
        } else {
            std::cout << "Error: The modem is powered off." << std::endl;
        }
    }

    // Command: Configures the transmission power of the modem
    void setPower(int newPower) {
        if (poweredOn) {
            power = newPower;
            std::cout << "Power set to " << power << " dBm." << std::endl;
        } else {
            std::cout << "Error: The modem is powered off." << std::endl;
        }
    }

    // Command: Sends a message via the LoRa modem
    void sendMessage(const std::string& message) {
        if (poweredOn) {
            lastMessage = message;
            std::cout << "Message sent: " << message << std::endl;
        } else {
            std::cout << "Error: The modem is powered off." << std::endl;
        }
    }

    // Query: Gets the power status of the modem (does not modify state)
    bool isPoweredOn() const {
        return poweredOn;
    }

    // Query: Gets the modem's operating frequency (does not modify state)
    int getFrequency() const {
        return frequency;
    }

    // Query: Gets the modem's transmission power (does not modify state)
    int getPower() const {
        return power;
    }

    // Query: Gets the last message sent (does not modify state)
    std::string getLastMessage() const {
        return lastMessage;
    }
};

```

## 3.16 Una excepción, siempre mejor que un código de error
En lugar de devolver códigos de error (por ejemplo, -1 o NULL), es preferible lanzar excepciones. Esto permite manejar errores de manera más clara y efectiva, sin necesidad de añadir lógica extra para evaluar códigos de error.

```cpp
#include <iostream>
#include <stdexcept>
#include <string>

// Clase de excepción personalizada para errores del módem LoRa
class LoRaModemException : public std::runtime_error {
public:
    // Constructor que toma un mensaje de error
    LoRaModemException(const std::string& message)
        : std::runtime_error(message) {}  // Pasa el mensaje a la clase base

    // Sobrescribe el método what() para proporcionar un mensaje personalizado
    const char* what() const noexcept override {
        return std::runtime_error::what();
    }
};

// Clase que simula el módem LoRa
class LoRaModem {
public:
    // Simula el envío de datos y lanza una excepción personalizada en caso de fallo
    void sendData(const std::string& data) {
        if (data.empty()) {
            throw LoRaModemException("Error: No data to send to LoRa modem.");
        }
        // Simulación de un fallo de transmisión
        throw LoRaModemException("Error: Failed to transmit data.");
    }
};

int main() {
    LoRaModem modem;

    try {
        std::string data = "Hello, LoRa!";  // Prueba con datos válidos
        modem.sendData(data);
    } catch (const LoRaModemException& e) {
        std::cerr << "LoRaModemException caught: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Standard exception caught: " << e.what() << std::endl;
    }

    return 0;
}
```

**Nota**: Las excepciones tienen un precio a pagar. 
El manejo de excepciones puede tener un impacto en el rendimiento, ya que el proceso de lanzar y capturar una excepción (incluyendo el stack unwinding) es costoso en términos de tiempo de ejecución. Aunque no hay un costo adicional significativo si no se lanza ninguna excepción, el costo es alto cuando se lanza y maneja una excepción.

En el caso de sistemas embebidos, esto puede ser especialmente crítico.

**Nota2**: Si el código C++ se mezcla con código en C (librerías 3rd, por ejemplo), no se pueden usar excepciones (C no tiene soporte para ellas).

## 3.17 La importancia de los bloques Try/Catch
El manejo adecuado de excepciones es crucial para asegurar que el código no falle de manera inesperada. Los bloques try/catch deben usarse para controlar errores y asegurar que el código fallará de manera segura y predecible.
El manejo de excepciones debe ser claro y eficiente, evitando capturar excepciones genéricas o dejarlas sin tratar.

Ver [std::exception](https://en.cppreference.com/w/cpp/error/exception)


```cpp
#include <iostream>
#include <stdexcept>

void procesarDatos(int valor) {
    if (valor < 0) {
        throw std::invalid_argument("Valor negativo no permitido.");
    } else if (valor == 0) {
        throw std::runtime_error("El valor no puede ser cero.");
    }
    std::cout << "El valor es válido: " << valor << std::endl;
}

int main() {
    try {
        procesarDatos(0); // Lanza una excepción std::runtime_error
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error de argumento: " << e.what() << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Error de ejecución: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error general: " << e.what() << std::endl;
    }

    return 0;
}
```


```cpp
#include <iostream>
#include <stdexcept>

void procesarDatos(int valor) {
    if (valor < 0) {
        throw std::invalid_argument("Valor negativo no permitido.");
    } else if (valor == 0) {
        throw std::runtime_error("El valor no puede ser cero.");
    }
    std::cout << "El valor es válido: " << valor << std::endl;
}

int main() {
    try {
        procesarDatos(0); // Lanza una excepción std::runtime_error
    } catch (...) {
        std::cerr << "Se capturó una excepción, pero no sabemos cuál." << std::endl;
    }

    return 0;
}
```

## 3.18 DRY, No te repitas
El principio DRY (Don't Repeat Yourself) establece que no se debe duplicar código innecesariamente. El código repetido es más difícil de mantener, ya que cualquier cambio debe realizarse en múltiples lugares.

```cpp
#include <iostream>
#include <string>

int main() {
    // Primer bloque de código repetido
    std::string nombre1 = "Alice";
    std::cout << "Nombre: " << nombre1 << std::endl;
    std::cout << "Longitud del nombre: " << nombre1.length() << std::endl;
    if (nombre1.length() > 5) {
        std::cout << "El nombre es largo." << std::endl;
    } else {
        std::cout << "El nombre es corto." << std::endl;
    }

    // Segundo bloque de código repetido
    std::string nombre2 = "Bob";
    std::cout << "Nombre: " << nombre2 << std::endl;
    std::cout << "Longitud del nombre: " << nombre2.length() << std::endl;
    if (nombre2.length() > 5) {
        std::cout << "El nombre es largo." << std::endl;
    } else {
        std::cout << "El nombre es corto." << std::endl;
    }

    // Tercer bloque de código repetido
    std::string nombre3 = "Catherine";
    std::cout << "Nombre: " << nombre3 << std::endl;
    std::cout << "Longitud del nombre: " << nombre3.length() << std::endl;
    if (nombre3.length() > 5) {
        std::cout << "El nombre es largo." << std::endl;
    } else {
        std::cout << "El nombre es corto." << std::endl;
    }

    return 0;
}
```

```cpp
#include <iostream>
#include <string>

// Función que encapsula la lógica repetida
void procesarNombre(const std::string& nombre) {
    std::cout << "Nombre: " << nombre << std::endl;
    std::cout << "Longitud del nombre: " << nombre.length() << std::endl;
    if (nombre.length() > 5) {
        std::cout << "El nombre es largo." << std::endl;
    } else {
        std::cout << "El nombre es corto." << std::endl;
    }
}

int main() {
    // Ahora solo llamamos a la función para cada nombre
    procesarNombre("Alice");
    procesarNombre("Bob");
    procesarNombre("Catherine");

    return 0;
}
```

## 3.19 La programación estructurada
La programación estructurada favorece el uso de estructuras claras como funciones, bucles, y condicionales bien definidos. Evita el uso de saltos arbitrarios como goto, que pueden hacer que el código sea difícil de seguir.

Tipicamente se habla de que los bloques de código tengan un punto de entrada y uno de salida. Solo un ``return`` y no usar ``break`` o ``continue``.
Y por supuesto, ``goto`` es el diablo.

**Nota**: En algunos casos, usar ```goto``` o varios ```return``` podría no ser malo...

```C
static int zynq_gpio_probe(struct platform_device *pdev)
{
	int ret, bank_num;
	struct zynq_gpio *gpio;
	struct gpio_chip *chip;
	struct gpio_irq_chip *girq;
	const struct of_device_id *match;

	gpio = devm_kzalloc(&pdev->dev, sizeof(*gpio), GFP_KERNEL);
	if (!gpio)
		return -ENOMEM;

	match = of_match_node(zynq_gpio_of_match, pdev->dev.of_node);
	if (!match) {
		dev_err(&pdev->dev, "of_match_node() failed\n");
		return -EINVAL;
	}
	gpio->p_data = match->data;
	platform_set_drvdata(pdev, gpio);

	gpio->base_addr = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(gpio->base_addr))
		return PTR_ERR(gpio->base_addr);

	gpio->irq = platform_get_irq(pdev, 0);
	if (gpio->irq < 0)
		return gpio->irq;

	/* configure the gpio chip */
	chip = &gpio->chip;
	chip->label = gpio->p_data->label;
	chip->owner = THIS_MODULE;
	chip->parent = &pdev->dev;
	chip->get = zynq_gpio_get_value;
	chip->set = zynq_gpio_set_value;
	chip->request = zynq_gpio_request;
	chip->free = zynq_gpio_free;
	chip->direction_input = zynq_gpio_dir_in;
	chip->direction_output = zynq_gpio_dir_out;
	chip->get_direction = zynq_gpio_get_direction;
	chip->base = of_alias_get_id(pdev->dev.of_node, "gpio");
	chip->ngpio = gpio->p_data->ngpio;

	/* Retrieve GPIO clock */
	gpio->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(gpio->clk))
		return dev_err_probe(&pdev->dev, PTR_ERR(gpio->clk), "input clock not found.\n");

	ret = clk_prepare_enable(gpio->clk);
	if (ret) {
		dev_err(&pdev->dev, "Unable to enable clock.\n");
		return ret;
	}

	spin_lock_init(&gpio->dirlock);

	pm_runtime_set_active(&pdev->dev);
	pm_runtime_enable(&pdev->dev);
	ret = pm_runtime_resume_and_get(&pdev->dev);
	if (ret < 0)
		goto err_pm_dis;

	/* disable interrupts for all banks */
	for (bank_num = 0; bank_num < gpio->p_data->max_bank; bank_num++) {
		writel_relaxed(ZYNQ_GPIO_IXR_DISABLE_ALL, gpio->base_addr +
			       ZYNQ_GPIO_INTDIS_OFFSET(bank_num));
		if (gpio->p_data->quirks & GPIO_QUIRK_VERSAL)
			bank_num = bank_num + VERSAL_UNUSED_BANKS;
	}

	/* Set up the GPIO irqchip */
	girq = &chip->irq;
	gpio_irq_chip_set_chip(girq, &zynq_gpio_edge_irqchip);
	girq->parent_handler = zynq_gpio_irqhandler;
	girq->num_parents = 1;
	girq->parents = devm_kcalloc(&pdev->dev, 1,
				     sizeof(*girq->parents),
				     GFP_KERNEL);
	if (!girq->parents) {
		ret = -ENOMEM;
		goto err_pm_put;
	}
	girq->parents[0] = gpio->irq;
	girq->default_type = IRQ_TYPE_NONE;
	girq->handler = handle_level_irq;

	/* report a bug if gpio chip registration fails */
	ret = gpiochip_add_data(chip, gpio);
	if (ret) {
		dev_err(&pdev->dev, "Failed to add gpio chip\n");
		goto err_pm_put;
	}

	irq_set_status_flags(gpio->irq, IRQ_DISABLE_UNLAZY);
	device_init_wakeup(&pdev->dev, 1);
	pm_runtime_put(&pdev->dev);

	return 0;

err_pm_put:
	pm_runtime_put(&pdev->dev);
err_pm_dis:
	pm_runtime_disable(&pdev->dev);
	clk_disable_unprepare(gpio->clk);

	return ret;
}
```
## 3.20 Creación de funciones limpias
La clave para crear funciones limpias es seguir estos principios de claridad, concisión, y responsabilidad única. Las funciones limpias deben ser pequeñas, bien nombradas, sin efectos secundarios inesperados y fáciles de comprender sin esfuerzo adicional.

### ¿Pero como se hace esto en la vida real?
De forma iterativa.

Comienzas con un código desestructurado, con funciones grandes y posiblemente con duplicidades.
A medida que analizas el código (y añades tests unitarios*) se van viendo las partes de código que no cumplen los principios y se van refinando.
Este proceso de análisis y mejora continua es un proceso que nunca acaba.

 \***Nota**: El mero hecho de pensar como testear una función ya nos ayuda a detectar fallos en su implementación o mejoras a realizar.

