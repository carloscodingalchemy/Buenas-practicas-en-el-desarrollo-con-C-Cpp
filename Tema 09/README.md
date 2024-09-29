# TEMA 9 - INTRODUCCION A LOS PRINCIPIOS SOLID


## 9.1 Principios de la arquitectura limpia y las siglas SOLID
Arquitectura limpia es un enfoque de diseño de software que tiene como objetivo crear aplicaciones modulares, independientes del marco de trabajo, la infraestructura y la interfaz de usuario. La arquitectura limpia promueve la separación de preocupaciones y facilita el mantenimiento, las pruebas y la evolución del software.
SOLID es un conjunto de cinco principios fundamentales que guían la escritura de software orientado a objetos bien estructurado. Estos principios fueron popularizados por Robert C. Martin (Uncle Bob) y se centran en crear código que sea más fácil de entender, modificar y extender.

**S**: Single Responsibility Principle (SRP) o Principio de Responsabilidad Única.
**O**: Open/Closed Principle (OCP) o Principio de Abierto/Cerrado.
**L**: Liskov Substitution Principle (LSP) o Principio de Sustitución de Liskov.
**I**: Interface Segregation Principle (ISP) o Principio de Segregación de la Interfaz.
**D**: Dependency Inversion Principle (DIP) o Principio de Inversión de la Dependencia.


## 9.2 Principio de responsabilidad única (S)
El Principio de Responsabilidad Única (SRP) establece que una clase debe tener una sola razón para cambiar, es decir, una clase debe tener una única responsabilidad o propósito.
Este principio promueve la separación de preocupaciones al asegurarse de que cada clase cumpla con una función específica en lugar de mezclar múltiples responsabilidades. Esto hace que el código sea más fácil de mantener y de entender.

```Cpp
#include <iostream>
#include <string>

// Clase que incumple el SRP al manejar tanto la UART como la lógica del módem LoRa
class LoRaModem {
public:
    // Método para enviar datos a través de la UART
    void sendToUart(const std::string& data) {
        // Simulación del envío de datos a través de la UART
        std::cout << "[UART] Enviando: " << data << std::endl;
    }

    // Método para recibir datos de la UART
    std::string receiveFromUart() {
        // Simulación de la recepción de datos de la UART
        std::string receivedData = "OK";
        std::cout << "[UART] Recibiendo: " << receivedData << std::endl;
        return receivedData;
    }

    // Método para inicializar el módem LoRa
    void initialize() {
        std::string atCommand = "AT+INIT";
        std::cout << "[LoRaModem] Inicializando módem con comando: " << atCommand << std::endl;
        sendToUart(atCommand);
        std::string response = receiveFromUart();
        if (response == "OK") {
            std::cout << "[LoRaModem] Módem inicializado correctamente." << std::endl;
        } else {
            std::cout << "[LoRaModem] Error en la inicialización del módem." << std::endl;
        }
    }

    // Método para configurar la frecuencia del módem LoRa
    void setFrequency(const std::string& frequency) {
        std::string atCommand = "AT+FREQ=" + frequency;
        std::cout << "[LoRaModem] Configurando frecuencia con comando: " << atCommand << std::endl;
        sendToUart(atCommand);
        std::string response = receiveFromUart();
        if (response == "OK") {
            std::cout << "[LoRaModem] Frecuencia configurada correctamente." << std::endl;
        } else {
            std::cout << "[LoRaModem] Error al configurar la frecuencia." << std::endl;
        }
    }

    // Otros métodos que mezclan la lógica del módem con la gestión UART...
};

int main() {
    // Crear una instancia del módem LoRa
    LoRaModem loraModem;

    // Inicializar el módem LoRa
    loraModem.initialize();

    // Configurar una frecuencia en el módem LoRa
    loraModem.setFrequency("868.1");

    return 0;
}
```


## 9.3 Principio de abierto-cerrado (O)
El Principio de Abierto/Cerrado (OCP) dicta que el código debe estar abierto para extensión, pero cerrado para modificación. Esto significa que las clases deben poder extenderse sin necesidad de modificarse.
La idea es que deberíamos poder agregar nueva funcionalidad sin alterar el código existente, lo que reduce el riesgo de introducir errores en el software ya probado. Este principio se suele implementar utilizando la herencia o los patrones de diseño como el patrón de estrategia.

```Cpp
// Clase concreta para un sensor de temperatura
class TemperatureSensor {
public:
    float readValue() const {
        // Simulación de la lectura de un valor de temperatura
        return 23.5;  // Temperatura simulada en grados Celsius
    }

    std::string getName() const {
        return "Temperature Sensor";
    }
};

// Clase concreta para un sensor de humedad
class HumiditySensor {
public:
    float readValue() const {
        // Simulación de la lectura de un valor de humedad
        return 60.2;  // Humedad simulada en porcentaje
    }

    std::string getName() const {
        return "Humidity Sensor";
    }
};

// Clase concreta para un sensor de presión
class PressureSensor {
public:
    float readValue() const {
        // Simulación de la lectura de un valor de presión
        return 1012.8;  // Presión simulada en hPa
    }

    std::string getName() const {
        return "Pressure Sensor";
    }
};

// Clase concreta para un sensor de luz
class LightSensor {
public:
    float readValue() const {
        // Simulación de la lectura de un valor de luz
        return 300.5;  // Luz simulada en lux
    }

    std::string getName() const {
        return "Light Sensor";
    }
};

// Clase que maneja múltiples sensores
class SensorManager {
private:
    TemperatureSensor tempSensor;
    HumiditySensor humiditySensor;
    PressureSensor pressureSensor;
    LightSensor lightSensor;

public:
    // Método para leer y mostrar todos los valores de los sensores
    void readAllSensors() const {
        // Lectura de cada sensor de forma individual
        std::cout << tempSensor.getName() << ": " << tempSensor.readValue() << " C" << std::endl;
        std::cout << humiditySensor.getName() << ": " << humiditySensor.readValue() << " %" << std::endl;
        std::cout << pressureSensor.getName() << ": " << pressureSensor.readValue() << " hPa" << std::endl;
        std::cout << lightSensor.getName() << ": " << lightSensor.readValue() << " lux" << std::endl;
    }
};
```

## 9.4 Principio de sustitución de Liskov (L)
El Principio de Sustitución de Liskov (LSP) establece que los objetos de una clase derivada deben poder sustituir a los objetos de su clase base sin alterar el comportamiento esperado del programa.
Esto significa que las clases derivadas deben ser completamente intercambiables con sus clases base, respetando los contratos establecidos por estas últimas. Las subclases no deben alterar las expectativas ni violar las suposiciones hechas en la clase base.
Ejemplo: Si tienes una clase base Ave con un método volar(), cualquier subclase como Gorrión debería poder volar. Sin embargo, una subclase como Pingüino, que no puede volar, violaría este principio, ya que no cumpliría con las expectativas establecidas en la clase base Ave.

```Cpp	
// Clase base Sensor
class Sensor {
public:
    virtual float readValue() const {
        return 0.0f;  // Valor predeterminado
    }

    virtual std::string getType() const {
        return "Generic Sensor";
    }

    virtual ~Sensor() = default;  // Destructor virtual
};

// Subclase para un sensor de temperatura
class TemperatureSensor : public Sensor {
public:
    float readValue() const override {
        return 25.0f;  // Simulación de lectura de temperatura
    }

    std::string getType() const override {
        return "Temperature Sensor";
    }
};

// Subclase que representa un sensor que siempre falla
class ErrorSensor : public Sensor {
public:
    float readValue() const override {
        // Simulación de un error en la lectura
        throw std::runtime_error("Error reading sensor value");
    }

    std::string getType() const override {
        return "Error Sensor";
    }
};
```

## 9.5 Principio de segregación de la interfaz (I)
El Principio de Segregación de la Interfaz (ISP) establece que los clientes no deben verse obligados a depender de interfaces que no usan. En otras palabras, es preferible crear interfaces específicas y pequeñas en lugar de interfaces grandes y monolíticas.
Este principio promueve la creación de interfaces altamente especializadas y enfocadas en propósitos específicos, evitando la implementación de métodos que no son relevantes para ciertos clientes.
Ejemplo: En lugar de tener una única interfaz Vehículo con métodos como acelerar(), frenar(), y navegar(), es mejor crear interfaces más especializadas como Terrestre (con métodos acelerar() y frenar()) y Marítimo (con métodos navegar()), de manera que las clases que implementen estas interfaces solo tengan que cumplir con los métodos relevantes.

```Cpp
#include <iostream>
#include <string>

// Interfaz monolítica IDevice para dispositivos que combina sensores y actuadores
class IDevice {
public:
    virtual float readValue() const = 0;   // Método para leer valores (solo para sensores)
    virtual void activate() = 0;            // Método para activar (solo para actuadores)
    virtual void deactivate() = 0;          // Método para desactivar (solo para actuadores)
    virtual std::string getType() const = 0; // Obtener el tipo de dispositivo
    virtual ~IDevice() = default;           // Destructor virtual
};

// Clase que implementa IDevice (sensor de temperatura)
class TemperatureSensor : public IDevice {
public:
    float readValue() const override {
        return 25.0f;  // Simulación de lectura de temperatura
    }

    void activate() override {
        // Implementación innecesaria para un sensor
        throw std::runtime_error("TemperatureSensor cannot be activated.");
    }

    void deactivate() override {
        // Implementación innecesaria para un sensor
        throw std::runtime_error("TemperatureSensor cannot be deactivated.");
    }

    std::string getType() const override {
        return "Temperature Sensor";
    }
};

// Clase que implementa IDevice (ventilador)
class Fan : public IDevice {
public:
    float readValue() const override {
        // Implementación innecesaria para un actuador
        throw std::runtime_error("Fan does not have a value to read.");
    }

    void activate() override {
        std::cout << "Fan activated." << std::endl;
    }

    void deactivate() override {
        std::cout << "Fan deactivated." << std::endl;
    }

    std::string getType() const override {
        return "Fan";
    }
};

// Función para mostrar la lectura de un dispositivo
void displayDeviceValue(IDevice& device) {
    try {
        std::cout << device.getType() << ": " << device.readValue() << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;  // Manejo del error
    }
}

// Función para activar y desactivar un actuador
void controlActuator(IDevice& actuator, bool activate) {
    if (activate) {
        actuator.activate();
    } else {
        actuator.deactivate();
    }
}

int main() {
    // Crear instancias de sensores y actuadores
    TemperatureSensor tempSensor;
    Fan fan;

    // Mostrar valores de los dispositivos
    displayDeviceValue(tempSensor);   // "TemperatureSensor cannot be activated."
    controlActuator(fan, true);       // "Fan activated."
    displayDeviceValue(fan);           // "Fan does not have a value to read."

    return 0;
}
```

## 9.6 Principio de inversión de la dependencia (D)
El Principio de Inversión de la Dependencia (DIP) establece que los módulos de alto nivel no deben depender de los módulos de bajo nivel; ambos deben depender de abstracciones. Asimismo, las abstracciones no deben depender de detalles; los detalles deben depender de abstracciones.
Este principio promueve la idea de que el código debe depender de interfaces o clases abstractas en lugar de implementaciones concretas. Esto facilita el desacoplamiento y permite reemplazar fácilmente las implementaciones de bajo nivel sin afectar a las capas superiores.

```Cpp
// Clase de bajo nivel que maneja la red
class WiFiNetwork {
public:
    void connect(const std::string& ssid, const std::string& password) {
        std::cout << "Connecting to WiFi network: " << ssid << std::endl;
        // Lógica de conexión...
    }

    void sendData(const std::string& data) {
        std::cout << "Sending data: " << data << std::endl;
        // Lógica para enviar datos...
    }

    void receiveData() {
        std::cout << "Receiving data..." << std::endl;
        // Lógica para recibir datos...
    }
};

// Clase de alto nivel que maneja la red
class NetworkManager {
private:
    WiFiNetwork wifi; // Dependencia directa de la clase de bajo nivel

public:
    void connectToNetwork(const std::string& ssid, const std::string& password) {
        wifi.connect(ssid, password);
    }

    void sendData(const std::string& data) {
        wifi.sendData(data);
    }

    void receiveData() {
        wifi.receiveData();
    }
};
```
