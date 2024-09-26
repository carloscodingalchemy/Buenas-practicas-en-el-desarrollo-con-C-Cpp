# TEMA 8 - LOS LIMITES DE NUESTRO CÓDIGO

## 8.1 ¿Qué ocurre cuando hacemos uso de código de terceras partes?
Utilizar código de terceras partes, como **bibliotecas, frameworks o servicios de terceros**, es una práctica común en el desarrollo moderno. Sin embargo, esta práctica implica ciertos riesgos y desafíos:

**Dependencias externas**: Al utilizar código de terceros, nuestra aplicación se vuelve dependiente de ese código, lo que puede influir en su estabilidad, seguridad y rendimiento.

**Problemas de compatibilidad**: Las bibliotecas o frameworks de terceros pueden tener incompatibilidades con otras partes de nuestro código o con versiones futuras de nuestras herramientas.

**Actualizaciones y mantenimiento**: Las dependencias de terceros pueden cambiar con el tiempo. Esto incluye nuevas versiones, parches de seguridad o incluso la discontinuación del soporte, lo que puede afectar el funcionamiento de nuestro código.

**Riesgos de seguridad**: Los componentes de terceros pueden introducir vulnerabilidades si no se mantienen actualizados o si contienen fallos de seguridad no descubiertos. Esto fue notorio en incidentes como el de la vulnerabilidad de Log4j.
Es importante elegir cuidadosamente las dependencias externas, investigar su estabilidad y mantenerlas actualizadas, además de evaluar regularmente su seguridad y desempeño.

```C
/*! *********************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
********************************************************************************** */
/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_MemoryAllocate
 * Description   : Reserves the requested amount of memory in bytes.
 *
 *END**************************************************************************/
void *OSA_MemoryAllocate(uint32_t memLength)
{
#if defined(configSUPPORT_DYNAMIC_ALLOCATION) && (configSUPPORT_DYNAMIC_ALLOCATION > 0)

    void *p = (void *)pvPortMalloc(memLength);

    if (NULL != p)
    {
        (void)memset(p, 0, memLength);
    }

    return p;
#else
    return NULL;
#endif
}
```

Código extraido de: [fsl_os_abstraction_free_rtos.c](https://github.com/nxp-mcuxpresso/mcux-sdk/blob/main/components/osa/fsl_os_abstraction_free_rtos.c)

## 8.2 Debemos conocer los límites
Conocer los límites de nuestro código implica entender cómo interactúa con los elementos externos, y cómo esas dependencias afectan la funcionalidad, el rendimiento y la seguridad de nuestro sistema. Esto incluye:

**Límites tecnológicos**: Es crucial saber hasta qué punto una biblioteca o componente externo puede manejar la carga, las restricciones de memoria o el número de solicitudes simultáneas antes de que falle.

**Límites de integración**: Comprender cómo el código de terceros se integra con nuestro propio código, así como los posibles conflictos o dependencias indirectas que puedan surgir.

**Responsabilidad del código**: Incluso si un componente es externo, somos responsables de su comportamiento dentro de nuestro sistema. Si una dependencia tiene un límite de rendimiento o fiabilidad, debemos ser conscientes de ello y manejarlo adecuadamente.

## 8.3 Haciendo uso Log4cxx
Log4cxx es una biblioteca de logging utilizada en C++ (Porting de log4j a C++). Estas herramientas son fundamentales para el registro y la depuración de eventos durante la ejecución del código.
Log4cxx (para C++): Proporciona una estructura flexible para registrar información sobre la ejecución del programa (como errores, advertencias, información de depuración, etc.). Es configurable a través de archivos y permite manejar distintos niveles de severidad (como DEBUG, INFO, WARN, ERROR).

Utilizar bibliotecas de logging como estas es esencial para monitorear el comportamiento del software en entornos de desarrollo, prueba y producción. 


## 8.4 Haciendo uso de código que todavía no está listo
En algunos casos, es posible que tengamos que utilizar código incompleto o en desarrollo, ya sea propio o de terceros. Este escenario puede darse en proyectos donde las dependencias no están completamente implementadas o en bibliotecas que están en versiones beta.

**Riesgos**: El uso de código que no está listo puede introducir inestabilidad y errores difíciles de predecir. También puede ocasionar comportamientos inesperados, como fallos de compatibilidad o falta de funcionalidad crítica.

Estrategias:
* Utilizar patrones de diseño como feature toggles o mocking para aislar el código que aún no está listo.
* Asegurarse de que el código en desarrollo esté debidamente probado mediante pruebas unitarias y de integración.

```Cpp
struct SensorData {
    float temperature;
    float humidity;
    float wind_speed;
};

class Sensor {
public:
    virtual ~Sensor() = default;
    virtual void init() = 0;
    virtual SensorData read() = 0;
};

class SensorFake : public Sensor {
public:
    void init() override {
        std::srand((unsigned) std::time(nullptr));
    }

    SensorData read() override {
        SensorData data;
        data.temperature = (std::rand() % 3000) / 100.0f;  // 0.0 a 30.0 grados
        data.humidity = (std::rand() % 10000) / 100.0f;    // 0.0 a 100.0%
        data.wind_speed = (std::rand() % 5000) / 100.0f;   // 0.0 a 50.0 km/h
        return data;
    }
};


class SensorManager
{
    private:
    Sensor &m_sensor;
    
    public:
    
    SensorManager(Sensor& sensorImpl) : m_sensor(sensorImpl) {
        m_sensor.init();
    }

    // Método que delega la lectura de datos al sensor
    SensorData getSensorData() {
        return m_sensor.read();
    }
};

int main()
{
    SensorFake sensor;
    
    SensorManager manager(sensor);
    
    SensorData data =  manager.getSensorData();
    
    std::cout << "temperature: " << data.temperature << std::endl;
    std::cout << "humidity: " << data.humidity << std::endl;
    std::cout << "wind_speed:  "<< data.wind_speed << std::endl;

    return 0;
}
```


## 8.5 ¿Qué entendemos por límites limpios?
Límites limpios se refiere a la práctica de mantener una separación clara y organizada entre nuestro código y las dependencias externas.  
Esto implica diseñar el código de manera que las interacciones con componentes de terceros estén bien definidas y encapsuladas.

**Encapsulación de dependencias**: Minimizar la dispersión del uso de dependencias externas en todo el sistema. Las dependencias deben ser utilizadas en puntos claramente definidos (como adaptadores o capas de servicio) en lugar de estar presentes en múltiples partes del código.

**Interfaces claras**: Definir interfaces que encapsulen la interacción con bibliotecas de terceros, de modo que si una dependencia cambia o se reemplaza, solo las implementaciones específicas deben modificarse, no todo el código que las utiliza.

**Pruebas aisladas**: Asegurarse de que las partes del código que interactúan con componentes externos sean fácilmente testeables de manera independiente, por ejemplo, utilizando stubs o mocks.

*Nota: 

**Control de errores^**: Manejar adecuadamente los errores y excepciones que provienen de componentes externos, asegurando que no afecten el flujo normal de nuestra aplicación y que sean correctamente registrados y notificados.


