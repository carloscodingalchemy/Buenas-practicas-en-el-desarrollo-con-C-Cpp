# TEMA 7 - EL PROCESAMIENTO CORRECTO DE LOS ERRORES

## 7.1 La importancia de hacer uso de las excepciones
Las excepciones son mecanismos que permiten manejar errores de forma estructurada y controlada. Utilizarlas correctamente es fundamental para separar el flujo normal del código de las situaciones excepcionales que podrían ocurrir.
Las excepciones facilitan el manejo de errores, permitiendo que el código en los niveles superiores decida cómo reaccionar ante fallos inesperados sin saturar las capas más bajas con lógica de control de errores. Esto mejora la legibilidad y mantenibilidad del código.


## 7.2 Try/Catch
La estructura try/catch/finally es fundamental en el manejo de excepciones en muchos lenguajes de programación:
**try**: Bloque de código que contiene las instrucciones que pueden lanzar excepciones.
**catch**: Bloque que captura y maneja las excepciones lanzadas desde el bloque try. Puede haber múltiples bloques catch para manejar diferentes tipos de excepciones.

El uso adecuado de try/catch asegura que el código se comporte de manera predecible, incluso cuando ocurren errores.

## 7.3 ¿Qué ocurre si no comprobamos las excepciones?
Ignorar excepciones puede llevar a que el sistema se comporte de forma impredecible, generando errores silenciosos que son difíciles de depurar. Esto puede resultar en fallos catastróficos, como la pérdida de datos o la corrupción de información.
Cuando las excepciones no se manejan correctamente, el código puede abortar de forma abrupta, cerrando aplicaciones o dejando recursos sin liberar. Esto compromete la estabilidad y seguridad del software.
Es crucial que todas las excepciones potenciales sean manejadas o, al menos, registradas para que se puedan rastrear y solucionar de forma efectiva.

## 7.4 Por qué ofrecer contexto junto a las excepciones
Al lanzar una excepción, es esencial proporcionar contexto adicional que describa las circunstancias del error. El simple hecho de lanzar una excepción sin información adicional puede dificultar mucho la depuración.
Proporcionar detalles como el estado de los datos en el momento del fallo, el tipo de operación que se estaba realizando, o los parámetros de entrada involucrados facilita el diagnóstico del problema y su resolución.

### 7.4.1 Mensajes descriptivos

```Cpp
#include <iostream>
#include <stdexcept>
#include <string>

class SPITransmissionError : public std::runtime_error {
public:
    // Constructor que toma un mensaje descriptivo y contexto adicional
    SPITransmissionError(const std::string& message, const std::string& context)
        : std::runtime_error(message + " | Context: " + context) {}
};

int main() {
    try {
        // Simular un error de transmisión en SPI con contexto
        throw SPITransmissionError("Data transmission failed", "Attempted to send 100 bytes to device 2");
    } catch (const SPITransmissionError& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
}
```

### 7.4.2 Excepciones anidadas

```cpp
#include <iostream>
#include <stdexcept>
#include <exception>

// Función para imprimir las excepciones anidadas
void print_nested(const std::exception& e) {
    std::cerr << "Exception: " << e.what() << std::endl;
    try {
        std::rethrow_if_nested(e);  // Vuelve a lanzar la excepción anidada
    } catch (const std::exception& nested) {
        std::cerr << "  Nested exception: ";
        print_nested(nested);
    } catch (...) {
        std::cerr << "  Unknown nested exception" << std::endl;
    }
}

class SPIDeviceError : public std::runtime_error {
public:
    explicit SPIDeviceError(const std::string& message)
        : std::runtime_error(message) {}
};

class SPITransmissionError : public std::runtime_error {
public:
    explicit SPITransmissionError(const std::string& message)
        : std::runtime_error(message) {}
};

void transmit_data() {
    try {
        // Simular un error en el dispositivo SPI
        throw SPIDeviceError("Device not responding");
    } catch (const SPIDeviceError& e) {
        // Agregar contexto mediante la excepción anidada
        throw std::nested_exception();
        throw SPITransmissionError("Failed to transmit data");
    }
}

int main() {
    try {
        transmit_data();
    } catch (const SPITransmissionError& e) {
        print_nested(e);  // Imprime la excepción principal y las anidadas
    }

    return 0;
}
```

### 7.4.3 Uso de std::system_error para errores de Sistema

```cpp
#include <iostream>
#include <system_error>

int main() {
    try {
        // Simula un error del sistema (código de error 5, que es "Access Denied" en muchos sistemas)
        throw std::system_error(std::make_error_code(std::errc::permission_denied), "SPI communication failed");
    } catch (const std::system_error& e) {
        std::cerr << "System error: " << e.what() << " (Error code: " << e.code() << ")" << std::endl;
    }

    return 0;
}
```

### 7.4.4 Excepciones personalizadas con datos adicionales
```cpp
#include <iostream>
#include <stdexcept>
#include <string>

class SPIError : public std::runtime_error {
private:
    int device_id;  // Contexto adicional: ID del dispositivo SPI

public:
    SPIError(const std::string& message, int device_id)
        : std::runtime_error(message), device_id(device_id) {}

    // Método para acceder al ID del dispositivo
    int get_device_id() const { return device_id; }
};

int main() {
    try {
        // Lanzar una excepción con información adicional
        throw SPIError("Failed to communicate with device", 2);
    } catch (const SPIError& e) {
        std::cerr << "Exception caught: " << e.what() << " (Device ID: " << e.get_device_id() << ")" << std::endl;
    }

    return 0;
}
```


## 7.5 Definiendo clases de excepciones
Definir clases personalizadas de excepciones permite categorizar y manejar los errores de manera más específica. En lugar de utilizar solo excepciones genéricas, se pueden crear excepciones adaptadas a las necesidades del sistema.
Por ejemplo, en una aplicación bancaria, podríamos definir excepciones como SaldoInsuficienteException, CuentaNoEncontradaException, etc. Esto ayuda a los desarrolladores a distinguir entre los distintos tipos de errores y reaccionar de manera más adecuada.
Crear jerarquías de clases de excepciones (herencia) también permite capturar diferentes tipos de excepciones en distintos niveles de abstracción.

## 7.6 La definición del flujo "normal" del código
El flujo "normal" del código debe estar libre de controles de errores innecesarios. El manejo de excepciones debe reservarse para situaciones excepcionales y no para controlar el flujo normal de la lógica del programa.

Errores comunes: Utilizar excepciones para manejar casos que deberían formar parte del flujo regular del código, como validar datos de entrada. Los flujos de control no deben depender de excepciones.
Mantener el flujo normal separado del manejo de excepciones mejora la claridad del código, haciéndolo más fácil de seguir y comprender.

```Cpp
#include <iostream>
#include <exception>
#include <unordered_map>

using namespace std;

// Excepción personalizada para errores de GPIO
class GPIOException : public exception {
private:
    string message;
public:
    GPIOException(const string& msg) : message(msg) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

// Clase para manejar los GPIO
class GPIO {
private:
    unordered_map<int, bool> pins;  // Diccionario para el estado de los pines (true: activo, false: inactivo)
    unordered_map<int, string> modes;  // Diccionario para el modo del pin (input/output)

public:
    // Método para configurar un pin como entrada o salida
    void configurePin(int pin, const string& mode) {
        if (modes.find(pin) != modes.end()) {
            // En lugar de una advertencia, lanzamos una excepción innecesariamente
            throw GPIOException("Error: El pin ya está configurado.");
        }
        if (mode != "input" && mode != "output") {
            // Lanzamos excepción en lugar de manejarlo con condicionales
            throw GPIOException("Error: Modo de pin inválido. Debe ser 'input' o 'output'.");
        }

        modes[pin] = mode;
        pins[pin] = false;  // Inicializamos el pin como inactivo
        cout << "Pin " << pin << " configurado como " << mode << "." << endl;
    }

    // Método para activar un pin (solo si es de salida)
    void setPin(int pin) {
        if (modes.find(pin) == modes.end()) {
            // Lanzamos una excepción en lugar de simplemente manejar el error con condicional
            throw GPIOException("Error: El pin no está configurado.");
        }
        if (modes[pin] != "output") {
            // Excepción innecesaria para flujo normal
            throw GPIOException("Error: No se puede activar un pin que no es de salida.");
        }

        pins[pin] = true;  // Activamos el pin
        cout << "Pin " << pin << " activado." << endl;
    }

    // Método para leer un pin (solo si es de entrada)
    bool readPin(int pin) {
        if (modes.find(pin) == modes.end()) {
            // Excepción innecesaria para un flujo que podría ser controlado
            throw GPIOException("Error: El pin no está configurado.");
        }
        if (modes[pin] != "input") {
            // Excepción innecesaria para flujo normal
            throw GPIOException("Error: No se puede leer un pin que no es de entrada.");
        }

        // Simulación de lectura del pin (por simplicidad siempre devuelve false)
        return pins[pin];
    }

    // Método para desactivar un pin (solo si es de salida)
    void resetPin(int pin) {
        if (modes.find(pin) == modes.end()) {
            // Excepción innecesaria en lugar de manejar la situación con condicionales
            throw GPIOException("Error: El pin no está configurado.");
        }
        if (modes[pin] != "output") {
            // Excepción innecesaria en lugar de manejar con condicional
            throw GPIOException("Error: No se puede desactivar un pin que no es de salida.");
        }

        pins[pin] = false;  // Desactivamos el pin
        cout << "Pin " << pin << " desactivado." << endl;
    }
};

int main() {
    GPIO gpio;

    try {
        // Flujo normal con manejo de excepciones innecesarias
        gpio.configurePin(7, "output");  // Configuramos el pin 7 como salida
        gpio.setPin(7);                  // Activamos el pin 7
        gpio.configurePin(8, "input");   // Configuramos el pin 8 como entrada
        
        // Intento de reconfigurar el mismo pin, esto lanzará una excepción innecesaria
        gpio.configurePin(7, "output");  // Esto lanzará una excepción innecesariamente

    } catch (const GPIOException& e) {
        cout << "Excepción atrapada: " << e.what() << endl;
    }

```

## 7.7 Null. La importancia de no devolverlo o pasarlo
Null es una fuente frecuente de errores en el código, principalmente debido a que manejar valores nulos requiere verificaciones constantes que aumentan la complejidad.
Devolver o pasar null como argumento puede llevar a excepciones de tipo NullPointerException si no se realiza la validación adecuada en todas partes. Estas excepciones suelen ser difíciles de rastrear y depurar.
Alternativas a null:
Objetos vacíos (Null Objects): En lugar de devolver null, se puede devolver un objeto especial que represente una instancia vacía, pero funcional.

Special Case Pattern: En lugar de devolver null, se puede devolver un objeto especial que represente una instancia vacía, pero funcional.

```cpp
#include <iostream>
#include <memory>
#include <string>

using namespace std;

// Clase para representar un sensor
class Sensor {
private:
    string name;
public:
    Sensor(const string& name) : name(name) {}

    void readData() {
        cout << "Leyendo datos del sensor: " << name << endl;
    }

    string getName() const {
        return name;
    }
};

// Clase para gestionar múltiples sensores
class SensorManager {
public:
    // Método para obtener un sensor. Si no existe, devuelve nullptr.
    shared_ptr<Sensor> getSensor(const string& sensorName) {
        // Simulamos que solo hay un sensor disponible llamado "Temperatura"
        if (sensorName == "Temperatura") {
            return make_shared<Sensor>("Temperatura");
        } else {
            // Si el sensor no existe, devolvemos nullptr
            return nullptr;
        }
    }
};

int main() {
    SensorManager manager;

    // Intentamos obtener un sensor que existe
    shared_ptr<Sensor> sensor1 = manager.getSensor("Temperatura");
    
    if (sensor1) {  // Verificamos si es nullptr
        cout << "Sensor encontrado: " << sensor1->getName() << endl;
        sensor1->readData();
    } else {
        cout << "Error: El sensor 'Temperatura' no está disponible." << endl;
    }

    // Intentamos obtener un sensor que no existe
    shared_ptr<Sensor> sensor2 = manager.getSensor("Presion");

    if (sensor2) {  // Verificamos si es nullptr
        cout << "Sensor encontrado: " << sensor2->getName() << endl;
        sensor2->readData();
    } else {
        cout << "Error: El sensor 'Presion' no está disponible." << endl;
    }

    return 0;
}
```