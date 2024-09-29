# TEMA 10 - LA ORGANIZACION DE LAS CLASES

## 10.1 La importancia de la encapsulación de nuestras clases
Encapsulación es un principio fundamental en la programación orientada a objetos que consiste en ocultar los detalles internos de una clase y exponer solo lo que es necesario a través de una interfaz pública bien definida.
La encapsulación mejora la modularidad del código, ya que permite cambiar la implementación interna de una clase sin afectar a las otras partes del sistema que dependen de ella.
Al encapsular correctamente, protegemos el estado interno de la clase, previniendo que los datos sean manipulados directamente desde el exterior, lo que garantiza una mayor consistencia y seguridad del sistema.


## 10.2 El tamaño de las clases también importa
Al igual que con las funciones, el tamaño de las clases es importante. Las clases demasiado grandes tienden a ser difíciles de entender, mantener y probar, y suelen violar el Principio de Responsabilidad Única (SRP).
Las clases deben ser lo más pequeñas posible, cada una cumpliendo con una sola responsabilidad o propósito claro. Si una clase empieza a manejar múltiples responsabilidades, es una señal de que necesita ser refactorizada.
Beneficios de las clases pequeñas:
Son más fáciles de mantener.
Promueven la reutilización de código.
Facilitan la prueba unitaria y la depuración.
Favorecen la cohesión dentro de la clase.

**Truco**: Deberias poder describir que hace tu clase en menos de 25 palabras **sin** usar las palabras, "si, "y", "o" o "pero".


```Cpp
class LoRaWANManager {
public:
    void joinNetwork(const std::string& appEui, const std::string& appKey);
    void sendMessage(const std::string& message);
    void receiveMessage();
    void sendATCommand(const std::string& command);
    std::string readATResponse();
    void initializeUART(int baudrate);
    void sendUART(const std::string& data);
    std::string receiveUART();

private:
    std::string uartBuffer;
    int baudrate;
    std::string appEui;
    std::string appKey;
};
```

## 10.3 El Principio de Responsabilidad Única aplicado a la organización de clases
El Principio de Responsabilidad Única (SRP) se aplica también a las clases. Este principio sostiene que una clase debe tener una única razón para cambiar, es decir, debe tener una única responsabilidad dentro del sistema.
Aplicar SRP a las clases significa que cada clase debe cumplir con un solo propósito bien definido. Esto evita que una clase se convierta en una especie de "clase dios" que maneja demasiadas cosas y se vuelve imposible de mantener.

```cpp
#include <iostream>
#include <string>

#define FPGA_MEMORY_ADDRESS 0x40000000  // Dirección base del dispositivo FPGA

class SensorSystem {
public:
    // Constructor que simula la conexión al dispositivo mapeado en memoria
    SensorSystem() : baseAddress((volatile uint32_t*)FPGA_MEMORY_ADDRESS) {}

    // Leer valores desde la FPGA (memoria mapeada)
    void readValues() {
        current = baseAddress[0];        // Corriente
        voltage = baseAddress[1];        // Voltaje
        activePower = baseAddress[2];    // Potencia activa
        reactivePower = baseAddress[3];  // Potencia reactiva
    }

    // Calcular potencia aparente
    double calculateApparentPower() {
        return sqrt(activePower * activePower + reactivePower * reactivePower);
    }

    // Mostrar los valores en consola
    void displayValues() {
        std::cout << "Current: " << current << " A\n";
        std::cout << "Voltage: " << voltage << " V\n";
        std::cout << "Active Power: " << activePower << " W\n";
        std::cout << "Reactive Power: " << reactivePower << " VAR\n";
        std::cout << "Apparent Power: " << calculateApparentPower() << " VA\n";
    }

    // Guardar los valores en algún almacenamiento (simulación)
    void saveToDatabase() {
        std::cout << "Saving values to database...\n";
        // Simulación de almacenamiento de datos
    }

private:
    volatile uint32_t* baseAddress;  // Puntero al dispositivo FPGA mapeado en memoria
    double current;
    double voltage;
    double activePower;
    double reactivePower;
};
```


## 10.4 La importancia de la cohesión y consistencia de resultados
La cohesión se refiere a cuán estrechamente relacionadas y enfocadas están las responsabilidades dentro de una clase. Las clases con alta cohesión son aquellas en las que todos sus métodos y atributos están fuertemente conectados y trabajan juntos para cumplir con una única tarea bien definida.
La consistencia de resultados se refiere a que las clases deben siempre producir salidas coherentes y predecibles. Las clases bien diseñadas no deben presentar comportamientos inconsistentes o inesperados.
La alta cohesión facilita la mantenibilidad, entendibilidad, y reutilización de las clases. Además, reduce la cantidad de dependencias entre diferentes partes del sistema.

```cpp
#include <iostream>
#include <stdexcept>
#include <cmath>

class PowerMeasurement {
public:
    // Constructor that initializes current, voltage, and power factor
    PowerMeasurement(float current, float voltage, float powerFactor) 
        : current_(current), voltage_(voltage), powerFactor_(powerFactor) {
        if (powerFactor < 0.0 || powerFactor > 1.0) {
            throw std::invalid_argument("Power factor must be between 0 and 1");
        }
    }

    // Calculate active power (P = V * I * PF)
    float calculateActivePower() const {
        return voltage_ * current_ * powerFactor_; // P = V * I * PF
    }

    // Calculate reactive power (Q = P * sqrt(1 - PF^2))
    float calculateReactivePower() const {
        float activePower = calculateActivePower();
        return activePower * std::sqrt(1 - powerFactor_ * powerFactor_); // Q = P * sqrt(1 - PF^2)
    }

    // Calculate apparent power (S = V * I)
    float calculateApparentPower() const {
        return voltage_ * current_; // S = V * I
    }

private:
    float current_;     // Current in Amperes
    float voltage_;     // Voltage in Volts
    float powerFactor_; // Power factor (0 to 1)
};

int main() {
    try {
        // Create a PowerMeasurement object with current, voltage, and power factor
        PowerMeasurement powerMeasurement(5.0, 230.0, 0.8);  // 5A, 230V, PF = 0.8
        
        std::cout << "Active Power: " << powerMeasurement.calculateActivePower() << " W\n";
        std::cout << "Reactive Power: " << powerMeasurement.calculateReactivePower() << " VAR\n";
        std::cout << "Apparent Power: " << powerMeasurement.calculateApparentPower() << " VA\n";
        
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
    return 0;
}
```


## 10.5 ¿Cómo organizar los cambios?
Organizar los cambios de manera efectiva en el código es clave para minimizar la introducción de errores y facilitar el mantenimiento. Esto implica tener una estrategia clara para realizar modificaciones o agregar nuevas funcionalidades sin afectar el código existente de manera negativa.
Estrategias:

* **Refactorización incremental**: En lugar de realizar grandes cambios de una vez, es recomendable aplicar mejoras de manera incremental, probando cada cambio individualmente para asegurarse de que no se introducen errores.

* **Uso de patrones de diseño**: Los patrones de diseño como el Patrón de Estrategia, el Patrón Observador o Fábricas ayudan a organizar el código de manera que los cambios y nuevas funcionalidades puedan ser introducidos sin modificar el código existente.

* **Pruebas automatizadas**: Tener una buena cobertura de pruebas unitarias y de integración es crucial para poder realizar cambios con confianza, sabiendo que cualquier fallo será detectado rápidamente.

* **Control de versiones**: Utilizar herramientas de control de versiones (como Git) permite gestionar los cambios de manera controlada, habilitando la posibilidad de revertir modificaciones cuando sea necesario.

Hay muchas formas de usar un control de versiones. Pero, hay unas mejores que otras...

**Tips para un bueno uso del control de versiones**
* Commits pequeños y frecuentes
* Mensajes de commit descriptivos ([conventional commits](https://www.conventionalcommits.org/en/v1.0.0/))
* Uso de ramas.
* Revisar código antes de hacer merge (merge/pull requests)
* Eliminar ramas después de merge (y quizás usar "squash")


