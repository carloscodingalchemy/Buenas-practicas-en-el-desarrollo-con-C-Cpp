# TEMA 6 - LOS OBJETOS Y OTRAS ESTRUCTURAS DE DATOS


## 6.1 La abstracción de los datos
Abstracción de datos es un **principio fundamental** de la programación orientada a objetos. 

Consiste en **ocultar los detalles** internos de una implementación y exponer solo lo necesario para que los usuarios puedan interactuar con un objeto o estructura de datos.  

El objetivo es simplificar la interacción con los datos, haciendo que los objetos presenten una interfaz clara y sencilla, mientras que los detalles complejos quedan ocultos.  
Esta separación permite una mejor mantenibilidad, ya que los cambios internos no afectan al código que utiliza el objeto.

**Ejemplo**: Una clase UART puede tener atributos internos como baudrate, parity o flowcontrol, pero los usuarios de la clase solo interactúan con métodos como enviar() o recibir(), sin necesidad de conocer cómo se realizan esas operaciones.

```cpp
#include <iostream>
#include <string>
using namespace std;

// LoRaModem class to abstract LoRa modem behavior
class LoRaModem {
private:
    // Private data members - hidden from outside the class
    string deviceID;
    double frequency; // Frequency in MHz
    int powerLevel;   // Power level in dBm
    bool isConnected; // Modem connection status

    // Simulated method for internal communication (not exposed publicly)
    void connectToNetwork() {
        if (!isConnected) {
            // Simulate network connection
            isConnected = true;
            cout << "LoRa Modem (" << deviceID << ") connected to network on " << frequency << " MHz.\n";
        }
    }

public:
    // Constructor to initialize modem with device ID, frequency, and power level
    LoRaModem(string id, double freq, int power)
        : deviceID(id), frequency(freq), powerLevel(power), isConnected(false) {
    }

    // Public method to configure modem settings (frequency and power level)
    void configureModem(double freq, int power) {
        if (freq > 0 && power >= 0) {
            frequency = freq;
            powerLevel = power;
            cout << "LoRa Modem configured to " << frequency << " MHz and power level " << powerLevel << " dBm.\n";
        } else {
            cout << "Invalid frequency or power level.\n";
        }
    }

    // Public method to send data through the modem
    void sendData(string data) {
        if (!isConnected) {
            connectToNetwork(); // Ensure modem is connected before sending data
        }
        cout << "Sending data: \"" << data << "\" from LoRa Modem (" << deviceID << ")...\n";
    }

    // Public method to receive data from the modem
    void receiveData() {
        if (isConnected) {
            cout << "Receiving data from LoRa Modem (" << deviceID << ")...\n";
            // Simulated received data
            cout << "Data received: \"Hello from LoRa Network!\"\n";
        } else {
            cout << "Modem is not connected to the network.\n";
        }
    }

    // Public method to check the connection status
    bool checkConnectionStatus() const {
        return isConnected;
    }

    // Public method to display modem information
    void displayModemInfo() const {
        cout << "Device ID: " << deviceID << "\n";
        cout << "Frequency: " << frequency << " MHz\n";
        cout << "Power Level: " << powerLevel << " dBm\n";
        cout << "Connection Status: " << (isConnected ? "Connected" : "Not Connected") << "\n";
    }
};

int main() {
    // Creating an object of LoRaModem class
    LoRaModem myModem("LoRa1234", 915.0, 14);

    // Accessing public methods, not private members directly
    myModem.displayModemInfo();

    // Configure the modem
    myModem.configureModem(868.0, 20);

    // Send and receive data
    myModem.sendData("Temperature: 25°C");
    myModem.receiveData();

    // Check the connection status
    if (myModem.checkConnectionStatus()) {
        cout << "Modem is connected to the network.\n";
    } else {
        cout << "Modem is not connected to the network.\n";
    }

    return 0;
}
```



## 6.2 Qué es la asimetría de objetos y datos
La asimetría entre objetos y estructuras de datos se refiere a las diferencias fundamentales entre cómo los objetos y las estructuras de datos se utilizan y gestionan en la programación.

**Objetos**: Los objetos combinan tanto datos como comportamientos, es decir, tienen atributos y métodos que manipulan esos atributos. En la POO, los objetos representan entidades con estado y comportamientos. Se pueden ocultar detalles internos usando encapsulación, proporcionando métodos específicos para interactuar con el estado de los datos.

**Estructuras de datos**: Las estructuras de datos, en cambio, son más transparentes. Se centran exclusivamente en almacenar datos, sin asociar comportamientos a estos. Las operaciones que manipulan estas estructuras suelen estar separadas de las propias estructuras, lo que permite acceso directo a los datos.

**Asimetría**: En un sistema orientado a objetos, los objetos son opacos y solo exponen lo necesario (a través de métodos). En cambio, las estructuras de datos tienden a ser más transparentes, exponiendo sus campos directamente. Esta asimetría puede generar diferencias en la manera de diseñar y organizar el código.

>Procedural code (code using data structures) makes it easy to add new functions without changing the existing data structures. OO code, on the other hand, makes >it easy to add new classes without changing existing functions.
> 
>Procedural code makes it hard to add new data structures because all the functions must change. OO code makes it hard to add new functions because all the classes must change.



## 6.3 La Directiva del Principio de Menor Conocimiento o LOD
El Principio de Menor Conocimiento (Law of Demeter - LoD), también conocido como la regla de *no hablar con extraños*, es un principio de diseño de software orientado a objetos que busca minimizar las dependencias entre componentes.  

Básicamente, establece que un objeto solo debería hablar con sus "amigos cercanos" y no con objetos desconocidos o lejanos.  

Esto implica que un objeto solo debería interactuar con:
- Sus propios métodos.
- Los métodos de los objetos que posee directamente (es decir, sus atributos).
- Los métodos de los objetos pasados como parámetros.
- Los métodos de cualquier objeto que crea directamente.

**Objetivo**: Reducir el acoplamiento entre los componentes, lo que facilita el mantenimiento, las pruebas, y el cambio del sistema. También mejora la modularidad del código y evita que los objetos accedan a detalles internos de otros objetos que no les corresponden.

Ejemplo: Si un objeto ``A`` posee un objeto ``B``, y ``B`` tiene un objeto ``C``, el objeto ``A`` no debería llamar directamente a métodos en ``C``. En su lugar, ``A`` debería interactuar con ``B`` y permitir que ``B`` maneje la comunicación con ``C``.

```Cpp
#include <iostream>
#include <string>

class Engine {
public:
    void start() {
        std::cout << "Motor encendido.\n";
    }
};

class Car {
private:
    Engine engine;  // El coche tiene un motor

public:
    Engine& getEngine() {
        return engine;
    }
};

class Driver {
public:
    void startCar(Car& car) {
        car.getEngine().start();  // El conductor accede al motor del coche y lo enciende
    }
};

int main() {
    Car myCar;
    Driver driver;
    driver.startCar(myCar);  // El conductor enciende el coche
    return 0;
}
```


## 6.4 Los objetos de transferencia de datos
Los Objetos de Transferencia de Datos (DTO, Data Transfer Objects) son objetos simples diseñados para transportar datos entre diferentes capas o partes de una aplicación, particularmente entre la capa de presentación, lógica de negocios y la capa de acceso a datos.

A diferencia de los objetos en programación orientada a objetos que encapsulan tanto datos como comportamientos, los DTOs solo contienen atributos y no incluyen lógica de negocio ni comportamientos. Su propósito es simplificar el transporte de datos entre sistemas o componentes de una manera eficiente y estandarizada.

**Uso:** Los DTOs son comúnmente utilizados en arquitecturas de capas (como la arquitectura MVC) y en comunicaciones entre aplicaciones (por ejemplo, en servicios REST o SOAP). Permiten estructurar la información de manera clara y eficiente, facilitando la transferencia de datos sin exponer directamente los detalles internos de las entidades.  

```Cpp
#include <iostream>
#include <vector>
#include <cstring>  // Para memcpy
#include <string>

// Definición de un DTO para los datos del sensor con serialización binaria
class SensorDataDTO {
public:
    float temperatura;
    float humedad;
    uint32_t timestamp;  // Timestamp como un entero (ej: Unix time)

    // Constructor para inicializar el DTO con los datos del sensor
    SensorDataDTO(float temp, float hum, uint32_t time)
        : temperatura(temp), humedad(hum), timestamp(time) {}

    // Método para serializar los datos en un vector de bytes (binario)
    std::vector<uint8_t> serialize() const {
        std::vector<uint8_t> buffer;

        // Serializar la temperatura (4 bytes)
        buffer.insert(buffer.end(), reinterpret_cast<const uint8_t*>(&temperatura), 
                      reinterpret_cast<const uint8_t*>(&temperatura) + sizeof(temperatura));
        
        // Serializar la humedad (4 bytes)
        buffer.insert(buffer.end(), reinterpret_cast<const uint8_t*>(&humedad), 
                      reinterpret_cast<const uint8_t*>(&humedad) + sizeof(humedad));
        
        // Serializar el timestamp (4 bytes)
        buffer.insert(buffer.end(), reinterpret_cast<const uint8_t*>(&timestamp), 
                      reinterpret_cast<const uint8_t*>(&timestamp) + sizeof(timestamp));
        
        return buffer;
    }
};
```
