# TEMA 5 - FORMATO DEL CÓDIGO


## 5.1 ¿Qué es el formato y qué funcionalidad tiene?
Formato del código se refiere a la manera en que el código se organiza visualmente en un archivo. Esto incluye cómo se distribuyen las líneas de código, el espaciado, la indentación, y la alineación de elementos en el código.
El formato no influye en el funcionamiento del código, pero afecta directamente su legibilidad, mantenibilidad y la capacidad de trabajo en equipo, permitiendo una colaboración más eficiente.

## 5.2 Los dos tipos de formato: Vertical y Horizontal
El formato del código puede ser vertical o horizontal:
Formato Vertical: se refiere a cómo el código se organiza en la dimensión vertical (de arriba hacia abajo). Esto incluye la disposición de líneas, funciones, y bloques de código.


Formato Horizontal: se refiere a la disposición de elementos en una misma línea de código (de izquierda a derecha). Esto incluye el espaciado entre operadores, parámetros, y la longitud de las líneas.

```C
int send_message(uint8_t *message, uint16_t length) {
    int bytes_sent = 0;
    if (length > MAX_MESSAGE_LENGTH) {
        return -1;  // Error, el mensaje es demasiado largo
    }
    for (uint16_t i = 0; i < length; i++) {
        // Enviar el byte por UART
        if (UARTSendByte(message[i]) != 0) {
            return -1;  // Error en el envío, devolver -1 inmediatamente
        }
        // Si no hay error, incrementar el contador de bytes enviados
        bytes_sent++;
    }
    return bytes_sent;
}
```

```C
// Función para enviar un mensaje byte a byte por UART
int send_message(uint8_t *message, uint16_t length) {
int bytes_sent = 0;

// Comprobar si el mensaje excede la longitud máxima permitida
if (length > MAX_MESSAGE_LENGTH) {
return -1;  // Error, el mensaje es demasiado largo
}
 
// Bucle para enviar el mensaje byte a byte
for (uint16_t i = 0; i < length; i++) {
// Enviar el byte por UART
if (UARTSendByte(message[i]) != 0) {
return -1;  // Error en el envío, devolver -1 inmediatamente
}
// Si no hay error, incrementar el contador de bytes enviados
bytes_sent++;
}

// Devolver el número de bytes enviados
return bytes_sent;
}
```

## 5.3 Introducción al formato vertical
El formato vertical tiene que ver con la organización del código en la dimensión vertical. La idea es distribuir el código de manera que sea fácil de leer, facilitando la comprensión de la estructura lógica del programa.
El objetivo es minimizar la distancia entre conceptos relacionados y mejorar la claridad del código.

```C
static int uart_putxmitchar(FAR uart_dev_t *dev, int ch, bool oktoblock)
{
  irqstate_t flags;
  int nexthead;
  int ret;

  /* Increment to see what the next head pointer will be.
   * We need to use the "next" head pointer to determine when the circular
   *  buffer would overrun
   */

  nexthead = dev->xmit.head + 1;
  if (nexthead >= dev->xmit.size)
    {
      nexthead = 0;
    }

  /* Loop until we are able to add the character to the TX buffer. */

  for (; ; )
    {
      /* Check if the TX buffer is full */

      if (nexthead != dev->xmit.tail)
        {
          /* No.. not full.  Add the character to the TX buffer and return. */

          dev->xmit.buffer[dev->xmit.head] = ch;
          dev->xmit.head = nexthead;
          break;
        }

      /* The TX buffer is full.  Should be block, waiting for the hardware
       * to remove some data from the TX buffer?
       */

      else if (oktoblock)
        {
          /* The following steps must be atomic with respect to serial
           * interrupt handling.
           */

          flags = enter_critical_section();

          /* Check again...  In certain race conditions an interrupt may
           * have occurred between the test at the top of the loop and
           * entering the critical section and the TX buffer may no longer
           * be full.
           *
           * NOTE: On certain devices, such as USB CDC/ACM, the entire TX
           * buffer may have been emptied in this race condition.  In that
           * case, the logic would hang below waiting for space in the TX
           * buffer without this test.
           */

          if (nexthead != dev->xmit.tail)
            {
              ret = OK;
            }

#ifdef CONFIG_SERIAL_REMOVABLE
          /* Check if the removable device is no longer connected while we
           * have interrupts off.  We do not want the transition to occur
           * as a race condition before we begin the wait.
           */

          else if (dev->disconnected)
            {
              ret = -ENOTCONN;
            }
#endif
          else
            {
              /* Wait for some characters to be sent from the buffer with
               * the TX interrupt enabled.  When the TX interrupt is enabled,
               * uart_xmitchars() should execute and remove some of the data
               * from the TX buffer.
               *
               * NOTE that interrupts will be re-enabled while we wait for
               * the semaphore.
               */

#ifdef CONFIG_SERIAL_TXDMA
              uart_dmatxavail(dev);
#endif
              uart_enabletxint(dev);
              ret = nxsem_wait(&dev->xmitsem);
              uart_disabletxint(dev);
            }

          leave_critical_section(flags);

#ifdef CONFIG_SERIAL_REMOVABLE
          /* Check if the removable device was disconnected while we were
           * waiting.
           */

          if (dev->disconnected)
            {
              return -ENOTCONN;
            }
#endif

          /* Check if we were awakened by signal. */

          if (ret < 0)
            {
              /* A signal received while waiting for the xmit buffer to
               * become non-full will abort the transfer.
               */

              return -EINTR;
            }
        }

      /* The caller has request that we not block for data.  So return the
       * EAGAIN error to signal this situation.
       */

      else
        {
          return -EAGAIN;
        }
    }

  /* We won't get here.  Some compilers may complain that this code is
   * unreachable.
   */

  return OK;
}
```

## 5.4 Leyendo código como un periódico
El código bien formateado debe poder leerse de manera similar a como se lee un periódico: las ideas importantes deben ser fáciles de encontrar y entender con una rápida ojeada.
El lector debe poder obtener una visión clara de la estructura general y los bloques lógicos con un vistazo, lo que permite identificar rápidamente las partes importantes.

## 5.5 La densidad vertical en el código
Densidad vertical se refiere a la cantidad de líneas de código sin interrupciones entre bloques lógicos. Un código con demasiada densidad puede ser difícil de leer, por lo que es importante insertar líneas en blanco estratégicamente para separar las ideas.
Separar bloques de código que cumplen funciones diferentes con líneas en blanco mejora la legibilidad y ayuda a identificar secciones lógicas.

```Cpp
#include <iostream>

// Prototipo de la función para inicializar SPI
void inicializarSPI();

void imprimirMensajeInicio() {
    std::cout << "Iniciando sistema..." << std::endl;
}

int main() {
    // Mensaje de bienvenida
    imprimirMensajeInicio();
    
    // Configurar velocidad del reloj
    std::cout << "Configurando velocidad del reloj a 8 MHz..." << std::endl;
    // Código de configuración de velocidad (imaginemos que hay registros involucrados)
    // por ejemplo: SPI_CLOCK_REGISTER = 0x01; 

    // Otro código irrelevante
    int numero = 42;
    std::cout << "Este número no tiene nada que ver: " << numero << std::endl;

    // Configuración de pines SPI (mucho después)
    std::cout << "Configurando pines para SPI..." << std::endl;
    // Código de configuración de pines (por ejemplo)
    // SPI_PIN_REGISTER = 0x00; 

    // Código irrelevante de nuevo
    int valor = 100;
    std::cout << "Otro valor irrelevante: " << valor << std::endl;

    // Inicialización de SPI, finalmente
    inicializarSPI();
}

void inicializarSPI() {
    // Configurar modo maestro
    std::cout << "Configurando SPI en modo maestro..." << std::endl;
    // Código de configuración (por ejemplo)
    // SPI_CONTROL_REGISTER = 0x40;
}
```

```Cpp
#include <iostream>

// Inicialización de SPI en modo maestro
void inicializarSPI() {
    std::cout << "Configurando SPI en modo maestro..." << std::endl;

    // Configurar velocidad del reloj a 8 MHz
    std::cout << "Configurando velocidad del reloj a 8 MHz..." << std::endl;
    // Código de configuración de velocidad (ejemplo)
    // SPI_CLOCK_REGISTER = 0x01;

    // Configurar pines de SPI
    std::cout << "Configurando pines para SPI..." << std::endl;
    // Código de configuración de pines (ejemplo)
    // SPI_PIN_REGISTER = 0x00;

    // Habilitar SPI en modo maestro
    std::cout << "Habilitando SPI..." << std::endl;
    // Código para habilitar SPI (ejemplo)
    // SPI_CONTROL_REGISTER = 0x40;
}

int main() {
    // Mensaje de inicio del sistema
    std::cout << "Iniciando sistema..." << std::endl;

    // Inicializar SPI en modo maestro
    inicializarSPI();
}
```

## 5.6 La distancia vertical en el código
La distancia vertical se refiere al espacio que existe entre diferentes bloques o funciones en el código. Mantener funciones o bloques relacionados cerca entre sí facilita la lectura y comprensión.
Las funciones o variables que dependen unas de otras deben colocarse lo más juntas posible para que su relación sea evidente.

[async_client.cpp](https://github.com/eclipse/paho.mqtt.cpp/blob/master/src/async_client.cpp)  
[async_client.h](https://github.com/eclipse/paho.mqtt.cpp/blob/master/include/mqtt/async_client.h)

## 5.7 El formato a la hora de declarar variables
Las declaraciones de variables deben estar organizadas de manera que sean claras y fáciles de seguir. Las variables relacionadas deben declararse juntas y las inicializaciones deben ser inmediatas siempre que sea posible.
El formato debe hacer que las variables sean fácilmente localizables y comprensibles a primera vista.

[topic.h](https://github.com/eclipse/paho.mqtt.cpp/blob/master/include/mqtt/topic.h)  
[topic.cpp](https://github.com/eclipse/paho.mqtt.cpp/blob/master/src/topic.cpp)

## 5.8 El formato cuando instanciamos variables
Cuando se instancian variables (se les asigna un valor), el formato debe ser claro y consistente. Mantener un patrón uniforme para las instancias permite que otros desarrolladores comprendan rápidamente las variables que están siendo creadas y utilizadas.

Ver (topic.h y topic.cpp)

## 5.9 Cómo aplicar la verticalidad entre funciones dependientes
Las funciones que dependen unas de otras deben colocarse lo más cercanas posible en el archivo de código, de manera que su relación sea evidente.
Esto hace que la lectura del código sea más fluida y que las dependencias entre funciones sean claras.

Ver (topic.h y topic.cpp)

## 5.10 La verticalidad bajo términos de afinidad conceptual
La afinidad conceptual se refiere a la agrupación de bloques de código que están conceptualmente relacionados. Estos bloques deben colocarse juntos para que reflejen su relación conceptual y su propósito compartido dentro del código.
Esto incluye agrupar funciones relacionadas, clases, y declaraciones de variables para mejorar la coherencia lógica del código.

```Cpp
#ifndef SPI_H
#define SPI_H

#include <stdint.h>  // Para los tipos de datos uint8_t
#include <stddef.h>  // Para el tipo size_t

class SPI {
private:
    uint8_t m_pinNumber;
    uint8_t m_pinPort;

    void configurarRegistrosSPI();

public:
    SPI(uint8_t pinNumber, uint8_t pinPort);

    void inicializar();

    void assertCS();
    void deassertCS();

    uint8_t sendByte(uint8_t data);
    void sendMessage(uint8_t* data, size_t len);

    uint8_t receiveByte(void);
    void receiveMessage(uint8_t* buffer, size_t len);
};

#endif  // SPI_H
```

## 5.11 La importancia del orden vertical
El orden vertical es crucial para la legibilidad del código. Las funciones y bloques deben organizarse de manera lógica, desde las dependencias más generales hasta las más específicas.
El código debe seguir un flujo descendente que facilite el seguimiento del pensamiento del desarrollador, mejorando la comprensión general.

## 5.12 Introducción al formato horizontal
El formato horizontal se refiere a la forma en que se distribuyen los elementos en una sola línea de código. Un formato horizontal claro evita que el código sea denso y difícil de leer, mejorando la organización visual de las expresiones.

```Cpp
#include<iostream> using namespace std; int suma(int a,int b){int resultado=a+b;return resultado;}int main(){int x=5;int y=10;int z=suma(x,y);if(z>10){cout<<"La suma es mayor que 10";}else {cout<<"La suma es menor o igual que 10";}for(int i=0;i<5;i++){cout<<"Iteración "<<i<<" valor z: "<<z<<" ";}cout<<endl;return 0;}
```

```Cpp	
#include <iostream>

using namespace std;

int suma(int a, int b) {
    int resultado = a + b;
    return resultado;
}

int main() {
    int x = 5;
    int y = 10;
    int z = suma(x, y);

    if (z > 10) {
        cout << "La suma es mayor que 10" << endl;
    } else {
        cout << "La suma es menor o igual que 10" << endl;
    }

    for (int i = 0; i < 5; i++) {
        cout << "Iteración " << i << ", valor de z: " << z << endl;
    }

    return 0;
}
```


## 5.13 La densidad horizontal en el código
Densidad horizontal se refiere al número de elementos presentes en una sola línea de código. 
Un exceso de elementos en una línea puede hacer que el código sea difícil de leer, por lo que se recomienda usar espacios estratégicos y evitar largas líneas que abarcan demasiada lógica.
Mantener las líneas cortas (generalmente menos de 130 caracteres) mejora la legibilidad.


```Cpp
	else {
		persist_.reset(new MQTTClient_persistence {persistence,	&iclient_persistence::persistence_open,	&iclient_persistence::persistence_close,
			&iclient_persistence::persistence_put, &iclient_persistence::persistence_get, &iclient_persistence::persistence_remove,
			&iclient_persistence::persistence_keys,	&iclient_persistence::persistence_clear, &iclient_persistence::persistence_containskey});
```

```Cpp
	else {
		persist_.reset(new MQTTClient_persistence {
			persistence,
			&iclient_persistence::persistence_open,
			&iclient_persistence::persistence_close,
			&iclient_persistence::persistence_put,
			&iclient_persistence::persistence_get,
			&iclient_persistence::persistence_remove,
			&iclient_persistence::persistence_keys,
			&iclient_persistence::persistence_clear,
			&iclient_persistence::persistence_containskey
		});
```

## 5.14 La alineación horizontal
La alineación horizontal busca organizar los elementos dentro de una línea de manera clara y consistente. Sin embargo, tiene algunos inconvenientes.

- Al alinear todas las variables, se tiende a no prestar atención a los tipos de cada una de ellas
- Si en algún momento se añade una nueva variable, cuyo tipo es más largo, puede obligar a realinear a todas las variables.


```C
/**@brief SPIS control block - driver instance local data. */
typedef struct
{
    volatile uint32_t          tx_buffer_size;  //!< SPI slave TX buffer size in bytes.
    volatile uint32_t          rx_buffer_size;  //!< SPI slave RX buffer size in bytes.
    nrfx_spis_event_handler_t  handler;         //!< SPI event handler.
    volatile const uint8_t *   tx_buffer;       //!< SPI slave TX buffer.
    volatile uint8_t *         rx_buffer;       //!< SPI slave RX buffer.
    nrfx_drv_state_t           state;           //!< driver initialization state.
    volatile nrfx_spis_state_t spi_state;       //!< SPI slave state.
    void *                     p_context;       //!< Context set on initialization.
} spis_cb_t;
```

```C
/**@brief SPIS control block - driver instance local data. */
typedef struct
{
    volatile uint32_t tx_buffer_size;  //!< SPI slave TX buffer size in bytes.
    volatile uint32_t rx_buffer_size;  //!< SPI slave RX buffer size in bytes.
    nrfx_spis_event_handler_t handler; //!< SPI event handler.
    volatile const uint8_t * tx_buffer; //!< SPI slave TX buffer.
    volatile uint8_t * rx_buffer; //!< SPI slave RX buffer.
    nrfx_drv_state_t   state; //!< driver initialization state.
    volatile nrfx_spis_state_t spi_state; //!< SPI slave state.
    void * p_context; //!< Context set on initialization.
} spis_cb_t;
```

## 5.15 La indentación o sangrado horizontal
La indentación es el uso de espacios o tabulaciones para estructurar los bloques de código dentro de funciones, bucles, y condicionales. Una buena indentación permite visualizar rápidamente la jerarquía y estructura lógica del código.
El uso de una política coherente de indentación es clave para evitar confusión y errores en la estructura del código.

```C
/**@brief Function for executing the state entry action. */
static void spis_state_entry_action_execute(NRF_SPIS_Type * p_spis,
                                            spis_cb_t     * p_cb)
{
    nrfx_spis_evt_t event;

    switch (p_cb->spi_state)
    {
        case SPIS_BUFFER_RESOURCE_REQUESTED:
            nrf_spis_task_trigger(p_spis, NRF_SPIS_TASK_ACQUIRE);
            break;

        case SPIS_BUFFER_RESOURCE_CONFIGURED:
            event.evt_type  = NRFX_SPIS_BUFFERS_SET_DONE;
            event.rx_amount = 0;
            event.tx_amount = 0;

            NRFX_ASSERT(p_cb->handler != NULL);
            p_cb->handler(&event, p_cb->p_context);
            break;

        case SPIS_XFER_COMPLETED:
            event.evt_type  = NRFX_SPIS_XFER_DONE;
            event.rx_amount = nrf_spis_rx_amount_get(p_spis);
            event.tx_amount = nrf_spis_tx_amount_get(p_spis);
            NRFX_LOG_INFO("Transfer rx_len:%d.", event.rx_amount);
            NRFX_LOG_DEBUG("Rx data:");
            NRFX_LOG_HEXDUMP_DEBUG((uint8_t const *)p_cb->rx_buffer,
                                   event.rx_amount * sizeof(p_cb->rx_buffer[0]));
            NRFX_ASSERT(p_cb->handler != NULL);
            p_cb->handler(&event, p_cb->p_context);
            break;

        default:
            // No implementation required.
            break;
    }
}
```

[Indentation](https://en.wikipedia.org/wiki/Indentation_style)

### ESPACIOS VS TABS

Esta lucha aparentemente sin solución aparente durante decadas, gracias a los IDEs modernos, puede solucionarse de forma sencillisima.

Configura tu IDE para que cada pulsación de TAB se convierta en un número concreto de espacios (3 o 4 son los valores habituales).


## 5.16 ¿Qué son los ámbitos ficticios?
Los ámbitos ficticios son bloques de código delimitados por llaves ({}) que no crean un ámbito real, pero ayudan a organizar el código visualmente. Pueden ser útiles para separar diferentes secciones de código dentro de una misma función.
Aunque no cambian el comportamiento del código, ayudan a organizar la lógica interna de manera más clara.

```C
  while((HAL_GetTick() - tickstart) < wait);
```

```C
  while((HAL_GetTick() - tickstart) < wait)
  {
  }
```

## 5.17 Reglas de equipo y formato imprescindibles
Es fundamental que todos los miembros de un equipo de desarrollo sigan las mismas reglas de formato para mantener la consistencia en todo el código base. Estas reglas pueden incluir convenciones sobre indentación, longitud de líneas, espaciado, y más.
Establecer normas claras permite que el código sea uniforme, fácil de revisar y mantener a lo largo del tiempo.

[Google C++ style guide](https://google.github.io/styleguide/cppguide.html)  
[Paho C++ Style guide](https://github.com/eclipse/paho.mqtt.cpp/blob/master/CODING_STYLE.md)  
[Linux Kernel Coding Style](https://www.kernel.org/doc/html/v4.10/process/coding-style.html)

