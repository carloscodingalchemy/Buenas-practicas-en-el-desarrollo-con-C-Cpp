# TEMA 11 - SISTEMAS

## 11.1 Patrón factoría e inyección de dependencias
Patrón Factoría:
El Patrón Factoría es un patrón de diseño creacional que permite crear objetos sin especificar la clase exacta del objeto que se va a crear. Se encapsula el proceso de instanciación, lo que facilita el desacoplamiento y la escalabilidad del código.
Este patrón es útil cuando el sistema necesita manejar múltiples tipos de objetos relacionados o complejos, pero no quiere depender directamente de las clases concretas.

```cpp
#include <iostream>
#include <memory>  // Para std::unique_ptr
#include <string>

// Interfaz base para los sensores
class Sensor {
public:
    virtual void leer() const = 0;  // Método abstracto que debe implementar cada sensor
    virtual ~Sensor() = default;    // Destructor virtual
};

// Clase concreta para un Sensor de Temperatura
class SensorTemperatura : public Sensor {
public:
    void leer() const override {
        std::cout << "Leyendo datos del Sensor de Temperatura...\n";
    }
};

// Clase concreta para un Sensor de Humedad
class SensorHumedad : public Sensor {
public:
    void leer() const override {
        std::cout << "Leyendo datos del Sensor de Humedad...\n";
    }
};

// Clase Factory que crea los sensores según el tipo
class SensorFactory {
public:
    // Método estático para crear un sensor
    static std::unique_ptr<Sensor> crearSensor(const std::string& tipo) {
        if (tipo == "temperatura") {
            return std::make_unique<SensorTemperatura>();
        } else if (tipo == "humedad") {
            return std::make_unique<SensorHumedad>();
        } else {
            return nullptr;
        }
    }
};

// Función principal para demostrar el patrón Factory
int main() {
    // Crear un sensor de temperatura
    std::unique_ptr<Sensor> sensorTemp = SensorFactory::crearSensor("temperatura");
    if (sensorTemp) {
        sensorTemp->leer();
    }

    // Crear un sensor de humedad
    std::unique_ptr<Sensor> sensorHum = SensorFactory::crearSensor("humedad");
    if (sensorHum) {
        sensorHum->leer();
    }

    // Intentar crear un sensor no válido
    std::unique_ptr<Sensor> sensorInvalido = SensorFactory::crearSensor("invalido");
    if (sensorInvalido == nullptr) {
        std::cout << "Tipo de sensor no válido.\n";
    }

    return 0;
}
```

**Inyección de Dependencias (Dependency Injection - DI)**:
La Inyección de Dependencias es un principio de diseño en el que los objetos reciben (o se les inyectan) las dependencias que necesitan desde el exterior, en lugar de crearlas ellos mismos. Este enfoque mejora el desacoplamiento y facilita las pruebas y la mantenibilidad.
DI se utiliza en muchos frameworks y herramientas modernas de desarrollo, y permite a las clases solicitar las dependencias que necesitan (generalmente a través del constructor o métodos) en lugar de crearlas dentro de sí mismas.

```cpp
#include <vector>

// Clase Sensor que crea y maneja su propia instancia de I2CBus
class Sensor {
public:
    // El constructor ahora solo recibe la dirección I2C del sensor
    Sensor(uint8_t address) 
        : i2cAddress(address) {
        i2cBus = new I2CBus();  // Crea una nueva instancia de I2CBus
    }

    // Destructor para liberar la instancia de I2CBus
    ~Sensor() {
        delete i2cBus;
    }

    // Método para leer datos desde el sensor
    void readSensorData() {
        // Lee 4 bytes del sensor a través del bus I2C
        std::vector<uint8_t> data = i2cBus->read(i2cAddress, 4);
        // Simula procesamiento de los datos leídos
        std::cout << "Sensor data read: ";
        for (auto byte : data) {
            std::cout << "0x" << std::hex << static_cast<int>(byte) << " ";
        }
        std::cout << std::endl;
    }

    // Método para escribir datos al sensor
    void writeSensorData(const std::vector<uint8_t>& data) {
        // Escribe datos al sensor a través del bus I2C
        i2cBus->write(i2cAddress, data);
    }

private:
    I2CBus* i2cBus;  // Puntero a una instancia de I2CBus
    uint8_t i2cAddress;  // Dirección I2C del sensor
};
```

## 11.2 Programación Orientada a Aspectos en C++ (AOP)
Programación Orientada a Aspectos (AOP):
AOP es un paradigma de programación que permite separar las preocupaciones transversales (cross-cutting concerns) del código principal. Estas preocupaciones son características que afectan a múltiples módulos del sistema, como la gestión de logs, seguridad, manejo de excepciones o transacciones.
En lugar de entrelazar estas preocupaciones en múltiples clases o métodos, AOP permite definirlas en aspectos separados que se aplican de manera automática y transparente, haciendo que el código principal se mantenga más limpio y enfocado en su lógica de negocio.
En C++, la programación orientada a aspectos se puede implementar mediante bibliotecas específicas como AspectC++, que permiten aplicar estas técnicas al lenguaje C++. Aunque AOP no es tan común en C++ como en otros lenguajes (como Java con frameworks como Spring), sigue siendo una herramienta poderosa para ciertos tipos de problemas.

```cpp
#include <iostream>

class MyClass {
public:
    void myMethod() {
        std::cout << "Executing myMethod.\n";
    }

    void anotherMethod(int value) {
        std::cout << "Executing anotherMethod with value: " << value << "\n";
    }
};

int main() {
    MyClass obj;
    obj.myMethod();
    obj.anotherMethod(42);
    return 0;
}
``` 

```cpp
// LoggingAspect.ah
#include <iostream>

// Define an aspect for logging
aspect LoggingAspect {
    // Pointcut that matches method execution in MyClass
    pointcut methodExecution() = execution("void MyClass::myMethod()") || execution("void MyClass::anotherMethod(int)");

    // Advice that runs before the matched methods
    advice methodExecution() : before() {
        std::cout << "Logging: A method is about to be executed.\n";
    }
};
```

```bash
ac++ -o MyProgram MyClass.cpp LoggingAspect.ah
```



## 11.3 ¿Cómo optimizar la toma de decisiones?
Optimizar la toma de decisiones en el desarrollo de software implica estructurar el proceso de decisión para que sea eficiente, informado y que conduzca a soluciones efectivas.

**Descomposición del problema**: Separar las decisiones en problemas más pequeños, independientes y manejables puede reducir la complejidad y mejorar la claridad.
Uso de patrones de diseño: Emplear patrones de diseño conocidos facilita tomar decisiones en torno a la estructura y el comportamiento del código. Los patrones brindan soluciones probadas que ayudan a evitar decisiones incorrectas.

**Evaluar el impacto de las decisiones**: Antes de implementar una solución, es importante considerar sus implicaciones a largo plazo, incluyendo el costo de mantenimiento, la escalabilidad y el rendimiento.

**Pruebas y experimentación**: Las pruebas y la experimentación rápida mediante prototipos o pruebas de concepto pueden ayudar a validar decisiones antes de comprometerse completamente con ellas en el sistema final.

## 11.4 El uso de estándares efectivos
Estándares efectivos son normas, convenciones y pautas que un equipo o comunidad sigue para asegurar que el código sea consistente, legible y mantenible.
Convenciones de nomenclatura: Definir y seguir convenciones claras para nombrar variables, clases, funciones y otros elementos en el código. Esto mejora la claridad y reduce la confusión.

**Estilo de código**: Seguir un estilo de código uniforme (como el uso de llaves, indentación y espaciado). Herramientas como ClangFormat o Cppcheck pueden ayudar a aplicar estos estilos de manera automática.

**Revisión de código**: Establecer prácticas sólidas de revisión de código para detectar problemas temprano, mejorar la calidad y fomentar el aprendizaje entre los miembros del equipo.

[Code Review Example](https://gitlab.com/codingalchemy/codereviewtest)

**Estándares de diseño**: Adoptar estándares de diseño que favorezcan la simplicidad, reutilización y flexibilidad en el código.

## 11.5 La necesidad de los lenguajes del dominio
Lenguajes Específicos del Dominio (DSL - Domain-Specific Languages) son lenguajes de programación o scripting diseñados para un dominio específico de problemas, en lugar de ser de propósito general como C++ o Python.

**DSL internos**: Son lenguajes que se construyen sobre un lenguaje general (como funciones o bibliotecas especializadas). Por ejemplo, en C++, puedes crear un DSL interno para manipular configuraciones de bases de datos o para definir reglas de validación de datos.

```cpp
#include <iostream>
#include <string>

// Clase simple para construir consultas SQL
class SQLQuery {
public:
    SQLQuery& select(const std::string& fields) {
        query += "SELECT " + fields + " ";
        return *this;
    }

    SQLQuery& from(const std::string& table) {
        query += "FROM " + table + " ";
        return *this;
    }

    SQLQuery& where(const std::string& condition) {
        query += "WHERE " + condition + " ";
        return *this;
    }

    SQLQuery& orderBy(const std::string& field) {
        query += "ORDER BY " + field + " ";
        return *this;
    }

    void execute() const {
        std::cout << "Executing query: " << query << std::endl;
    }

private:
    std::string query;
};

// Ejemplo de uso del DSL Interno
int main() {
    SQLQuery query;
    query.select("name, age")
         .from("users")
         .where("age > 30")
         .orderBy("name")
         .execute();
    
    return 0;
}
```

**DSL externos**: Son lenguajes diseñados completamente desde cero para un dominio particular.
```
syntax = "proto3";

// Definimos un paquete opcional para organizar mejor los mensajes
package farola;

// Definición del mensaje LampPostSensors para contener los datos de los sensores
message LampPostSensors {
    // El voltaje (en voltios) medido por la farola
    float voltage = 1;        // Campo 1: voltaje
    
    // La corriente (en amperios) medida por la farola
    float current = 2;        // Campo 2: corriente

    // La luminosidad (en lux) medida por el sensor de la farola
    float luminosity = 3;     // Campo 3: luminosidad

    // Marca de tiempo opcional para saber cuándo fueron tomadas las lecturas
    int64 timestamp = 4;      // Campo 4: marca de tiempo en formato Unix
}
```

```bash
protoc --cpp_out=. lampost.proto
```

```Cpp
#include "lampost.pb.h"  // Incluir el archivo generado por protoc

int main() {
    // Crear un mensaje LampPostSensors
    farola::LampPostSensors sensorData;

    // Establecer los valores de los sensores
    sensorData.set_voltage(220.5);
    sensorData.set_current(15.2);
    sensorData.set_luminosity(300.0);
    sensorData.set_timestamp(1633036800);  // Ejemplo de timestamp

    // Serializar el mensaje a una string
    std::string serializedData;
    sensorData.SerializeToString(&serializedData);

    // Deserializar el mensaje desde la string
    farola::LampPostSensors deserializedData;
    deserializedData.ParseFromString(serializedData);

    // Imprimir los valores deserializados
    std::cout << "Voltage: " << deserializedData.voltage() << std::endl;
    std::cout << "Current: " << deserializedData.current() << std::endl;
    std::cout << "Luminosity: " << deserializedData.luminosity() << std::endl;
    std::cout << "Timestamp: " << deserializedData.timestamp() << std::endl;

    return 0;
}
```

[PROTOBUF](https://developers.google.com/protocol-buffers)

**Ventajas**: Los DSL permiten a los desarrolladores expresar soluciones de manera más natural y concisa dentro de su dominio específico. Facilitan la colaboración entre desarrolladores y expertos en el dominio, ya que estos últimos pueden interactuar con el sistema usando un lenguaje más cercano a su contexto.





