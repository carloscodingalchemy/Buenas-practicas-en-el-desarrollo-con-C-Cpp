# TEMA 4- DOCUMENTANDO ATRAVES DE COMENTARIOS


## 4.41 La importancia de los comentarios
Los comentarios son esenciales para transmitir información que no es inmediatamente obvia a partir del código.

Ayudan a otros desarrolladores a entender las **intenciones, el contexto y la lógica** detrás del código.

Deben aclarar **por qué se tomó una decisión en particular** o proporcionar detalles sobre la funcionalidad que no son evidentes solo con leer el código.

## 4.2 Los comentarios no pueden excusar un código incorrecto
Un comentario no debe justificar un código mal escrito o incorrecto. El código siempre debe ser correcto, y los comentarios deben usarse para complementar, no para justificar fallos o atajos.
Un código malo no se convierte en bueno solo porque está acompañado de una explicación.
 ```C
 #include <stdio.h>
#include <string.h>

// Simulaciones para los sensores y las comunicaciones
int read_temperature_sensor() { return 25; }    // Simula un sensor de temperatura
int read_humidity_sensor() { return 50; }       // Simula un sensor de humedad
int send_data_to_server(char *data) { 
    printf("Enviando datos al servidor: %s\n", data);
    return 1; // Simula éxito en el envío
}

// Función principal de un sistema IoT
int main() {
    // Inicialización de variables y buffers
    int temp = 0, humidity = 0;     // Variables para los sensores
    char message[100];              // Buffer para el mensaje a enviar
    int cloud_response = 0;         // Variable para almacenar la respuesta del servidor

    // Inicializamos las comunicaciones UART o I2C (simulado)
    // En un código real, aquí irían las configuraciones de hardware para UART/I2C
    printf("Inicializando interfaces de comunicación...\n");

    // Lectura de los sensores (temperatura y humedad)
    // Aquí el código podría estar mejor estructurado, pero por alguna razón
    // se optó por mezclar varias responsabilidades en lugar de modularizar.
    temp = read_temperature_sensor();   // Leer sensor de temperatura
    if (temp >= 0) {
        humidity = read_humidity_sensor();  // Solo leemos humedad si temperatura es válida

        // Si los valores de los sensores son razonables, los procesamos
        if (humidity >= 0) {
            // Llenamos el buffer del mensaje con los datos leídos de los sensores
            // Esto podría estar mejor gestionado pero, por simplicidad, asumimos
            // que siempre caben los datos en el buffer.
            sprintf(message, "Temp:%dC, Humidity:%d%%", temp, humidity);
        } else {
            // En caso de error con la humedad, ponemos un mensaje por defecto
            sprintf(message, "Temp:%dC, Humidity:ERROR", temp);
        }
    } else {
        // Si el sensor de temperatura falla, mostramos un mensaje de error
        sprintf(message, "Sensor de temperatura fallido");
    }

    // Simulamos un retraso en la toma de decisiones
    // Mientras podríamos enviar el mensaje directamente al servidor, decidimos
    // verificar el estado de la batería (que no tenemos, pero lo simulamos).
    if (temp > 30) {
        // Si la temperatura es alta, asumimos que el dispositivo se está calentando
        // y hacemos que el dispositivo entre en un estado de ahorro de energía
        printf("Alerta: Temperatura alta, activando modo de ahorro de energía...\n");
        // Aquí podríamos apagar algunos sensores, pero por ahora, solo imprimimos.
    }

    // Comunicación con la nube
    // Aquí se llama una función que "envía" los datos a la nube (simulado)
    cloud_response = send_data_to_server(message); 

    // Si la comunicación con el servidor falla, intentamos reenviar
    if (cloud_response == 0) {
        printf("Error al enviar datos. Reintentando...\n");
        cloud_response = send_data_to_server(message);
        if (cloud_response == 0) {
            // Si aún falla, dejamos de intentar y mostramos un mensaje de error
            printf("Fallo permanente en la comunicación con la nube\n");
        } else {
            // Si la segunda vez fue exitosa
            printf("Reenvío exitoso\n");
        }
    } else {
        // El envío fue exitoso a la primera
        printf("Datos enviados con éxito\n");
    }

    // Aquí podríamos realizar otras operaciones como logging local o procesamiento adicional
    // pero en este ejemplo simplemente termina el programa.

    return 0;  // Fin del programa
}
```

## 4.3 ¿Qué es un comentario de calidad?
Un comentario de calidad es claro, conciso, y explica el por qué detrás del código en lugar de simplemente describir qué hace el código. Debe ser relevante y aportar información valiosa.
Estos comentarios ayudan a comprender la lógica, las suposiciones, las restricciones, y el propósito del código.

```C
static int board_nrf52833dongle_nrf52833_init(void)
{

	/* If the nrf52833dongle_nrf52833 board is powered from USB
	 * (high voltage mode), GPIO output voltage is set to 1.8 volts by
	 * default and that is not enough to turn the green and blue LEDs on.
	 * Increase GPIO voltage to 3.0 volts.
	 */
	if ((nrf_power_mainregstatus_get(NRF_POWER) ==
	     NRF_POWER_MAINREGSTATUS_HIGH) &&
	    ((NRF_UICR->REGOUT0 & UICR_REGOUT0_VOUT_Msk) ==
	     (UICR_REGOUT0_VOUT_DEFAULT << UICR_REGOUT0_VOUT_Pos))) {

		nrf_nvmc_mode_set(NRF_NVMC, NRF_NVMC_MODE_WRITE);
		while (!nrf_nvmc_ready_check(NRF_NVMC)) {
			;
		}

		NRF_UICR->REGOUT0 =
		    (NRF_UICR->REGOUT0 & ~((uint32_t)UICR_REGOUT0_VOUT_Msk)) |
		    (UICR_REGOUT0_VOUT_3V0 << UICR_REGOUT0_VOUT_Pos);

		nrf_nvmc_mode_set(NRF_NVMC, NRF_NVMC_MODE_READONLY);
		while (!nrf_nvmc_ready_check(NRF_NVMC)) {
			;
		}

		/* A reset is required for changes to take effect. */
		NVIC_SystemReset();
	}

	return 0;
}
```

## 4.4 Comentarios TODO
Los comentarios TODO se usan para señalar que algo necesita ser completado en el futuro. Son útiles para marcar áreas de mejora, pero no deben quedar olvidados en el código. Eventualmente deben ser resueltos o eliminados.

```C
#include <zephyr/net/net_event.h>
#include <ctrl_iface_zephyr.h>
#include <supp_events.h>
#include <utils.h>
#include <supp_main.h>
#include <zephyr/logging/log.h>
#include <zephyr/kernel.h>
LOG_MODULE_REGISTER(wpas_event, CONFIG_WFA_QT_LOG_LEVEL);

/* TODO: Handle other events */
#define WPA_SUPP_EVENTS (NET_EVENT_WPA_SUPP_READY)

static struct net_mgmt_event_callback net_wpa_supp_cb;

K_SEM_DEFINE(wpa_supp_ready_sem, 0, 1);

static void handle_wpa_supp_ready(struct net_mgmt_event_callback *cb)
{
	k_sem_give(&wpa_supp_ready_sem);
}

static void wpa_supp_event_handler(struct net_mgmt_event_callback *cb,
	uint32_t mgmt_event, struct net_if *iface)
{
	/* TODO: Handle other events */
	switch (mgmt_event) {
	case NET_EVENT_WPA_SUPP_READY:
		handle_wpa_supp_ready(cb);
		break;
	default:
		LOG_DBG("Unhandled event (%d)", mgmt_event);
		break;
	}
}
```

## 4.5 Comentarios Informativos
Estos comentarios proporcionan información adicional sobre el código, como la explicación de algoritmos complejos, referencias a documentación externa, o contexto histórico.

```C
/*
 * This mysterious table is just the CRC of each possible byte. It can be
 * computed using the standard bit-at-a-time methods. The polynomial can
 * be seen in entry 128, 0x8408. This corresponds to x^0 + x^5 + x^12.
 * Add the implicit x^16, and you have the standard CRC-CCITT.
 */
u16 const crc_ccitt_table[256] = {
	0x0000, 0x1189, 0x2312, 0x329b, 0x4624, 0x57ad, 0x6536, 0x74bf,
	0x8c48, 0x9dc1, 0xaf5a, 0xbed3, 0xca6c, 0xdbe5, 0xe97e, 0xf8f7,
	0x1081, 0x0108, 0x3393, 0x221a, 0x56a5, 0x472c, 0x75b7, 0x643e,
	0x9cc9, 0x8d40, 0xbfdb, 0xae52, 0xdaed, 0xcb64, 0xf9ff, 0xe876,
	0x2102, 0x308b, 0x0210, 0x1399, 0x6726, 0x76af, 0x4434, 0x55bd,
	0xad4a, 0xbcc3, 0x8e58, 0x9fd1, 0xeb6e, 0xfae7, 0xc87c, 0xd9f5,
	0x3183, 0x200a, 0x1291, 0x0318, 0x77a7, 0x662e, 0x54b5, 0x453c,
	0xbdcb, 0xac42, 0x9ed9, 0x8f50, 0xfbef, 0xea66, 0xd8fd, 0xc974,
	0x4204, 0x538d, 0x6116, 0x709f, 0x0420, 0x15a9, 0x2732, 0x36bb,
	0xce4c, 0xdfc5, 0xed5e, 0xfcd7, 0x8868, 0x99e1, 0xab7a, 0xbaf3,
	0x5285, 0x430c, 0x7197, 0x601e, 0x14a1, 0x0528, 0x37b3, 0x263a,
	0xdecd, 0xcf44, 0xfddf, 0xec56, 0x98e9, 0x8960, 0xbbfb, 0xaa72,
	0x6306, 0x728f, 0x4014, 0x519d, 0x2522, 0x34ab, 0x0630, 0x17b9,
	0xef4e, 0xfec7, 0xcc5c, 0xddd5, 0xa96a, 0xb8e3, 0x8a78, 0x9bf1,
	0x7387, 0x620e, 0x5095, 0x411c, 0x35a3, 0x242a, 0x16b1, 0x0738,
	0xffcf, 0xee46, 0xdcdd, 0xcd54, 0xb9eb, 0xa862, 0x9af9, 0x8b70,
	0x8408, 0x9581, 0xa71a, 0xb693, 0xc22c, 0xd3a5, 0xe13e, 0xf0b7,
	0x0840, 0x19c9, 0x2b52, 0x3adb, 0x4e64, 0x5fed, 0x6d76, 0x7cff,
	0x9489, 0x8500, 0xb79b, 0xa612, 0xd2ad, 0xc324, 0xf1bf, 0xe036,
	0x18c1, 0x0948, 0x3bd3, 0x2a5a, 0x5ee5, 0x4f6c, 0x7df7, 0x6c7e,
	0xa50a, 0xb483, 0x8618, 0x9791, 0xe32e, 0xf2a7, 0xc03c, 0xd1b5,
	0x2942, 0x38cb, 0x0a50, 0x1bd9, 0x6f66, 0x7eef, 0x4c74, 0x5dfd,
	0xb58b, 0xa402, 0x9699, 0x8710, 0xf3af, 0xe226, 0xd0bd, 0xc134,
	0x39c3, 0x284a, 0x1ad1, 0x0b58, 0x7fe7, 0x6e6e, 0x5cf5, 0x4d7c,
	0xc60c, 0xd785, 0xe51e, 0xf497, 0x8028, 0x91a1, 0xa33a, 0xb2b3,
	0x4a44, 0x5bcd, 0x6956, 0x78df, 0x0c60, 0x1de9, 0x2f72, 0x3efb,
	0xd68d, 0xc704, 0xf59f, 0xe416, 0x90a9, 0x8120, 0xb3bb, 0xa232,
	0x5ac5, 0x4b4c, 0x79d7, 0x685e, 0x1ce1, 0x0d68, 0x3ff3, 0x2e7a,
	0xe70e, 0xf687, 0xc41c, 0xd595, 0xa12a, 0xb0a3, 0x8238, 0x93b1,
	0x6b46, 0x7acf, 0x4854, 0x59dd, 0x2d62, 0x3ceb, 0x0e70, 0x1ff9,
	0xf78f, 0xe606, 0xd49d, 0xc514, 0xb1ab, 0xa022, 0x92b9, 0x8330,
	0x7bc7, 0x6a4e, 0x58d5, 0x495c, 0x3de3, 0x2c6a, 0x1ef1, 0x0f78
};
EXPORT_SYMBOL(crc_ccitt_table);
```

## 4.6 Comentarios Legales
Son comentarios que incluyen avisos legales o de derechos de autor. Normalmente se colocan en la cabecera de archivos y describen la licencia bajo la cual se distribuye el código.

```C
// SPDX-License-Identifier: GPL-2.0-only
/*
 *	linux/lib/crc-ccitt.c
 */
```

```C
/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */
```

## 4.7 Se debe explicar la intencionalidad del código
Un buen comentario debe explicar por qué se está haciendo algo, no simplemente qué está haciendo el código. Este tipo de comentarios aclaran las decisiones del desarrollador.


```C
  /* Wait for the FLASH operation to complete by polling on BUSY flag to be reset.
     Even if the FLASH operation fails, the BUSY flag will be reset and an error
     flag will be set */
  /* Get tick */
  tickstart = HAL_GetTick();

  while (__HAL_FLASH_GET_FLAG(FLASH_FLAG_BSY) != RESET)
  {
    if (Timeout != HAL_MAX_DELAY)
    {
      if ((Timeout == 0U) || ((HAL_GetTick() - tickstart) > Timeout))
      {
        return HAL_TIMEOUT;
      }
    }
  }
```
Snippet extraido del fichero [stm32f4xx_hal_flash.c](https://github.com/STMicroelectronics/stm32f4xx_hal_driver/blob/d232197f12c592d87944f0f462b2d5297750f762/Src/stm32f4xx_hal_flash.c)


## 4.8 Incluir explicaciones de consecuencias
Cuando una acción en el código tiene efectos secundarios significativos o consecuencias importantes, debe explicarse en los comentarios para que los desarrolladores lo tengan en cuenta al modificar el código.

```c
//! As a side effect of this function, the Ethernet MAC is reset so any
//! previous MAC configuration is lost.
//!
//! \return None.
//
//*****************************************************************************
void
EMACPHYConfigSet(uint32_t ui32Base, uint32_t ui32Config)
{
    //
    // Write the Ethernet PHY configuration to the peripheral configuration
    // register.
    //
    HWREG(ui32Base + EMAC_O_PC) = ui32Config;

    //
    // If using the internal PHY, reset it to ensure that new configuration is
    // latched there.
    //
```

## 4.9 Clarificación de comentarios
A veces los comentarios requieren clarificación adicional si el tema es complejo. En lugar de ser vagos, los comentarios deben ser precisos y explicar bien el contexto.

```C
/**@brief Function for sending sample key presses to the peer.
 *
 * @param[in]   key_pattern_len   Pattern length.
 * @param[in]   p_key_pattern     Pattern to be sent.
 */
static void keys_send(uint8_t key_pattern_len, uint8_t * p_key_pattern)
{
    ret_code_t err_code;
    uint16_t actual_len;

    err_code = send_key_scan_press_release(&m_hids,
                                           p_key_pattern,
                                           key_pattern_len,
                                           0,
                                           &actual_len);
    // An additional notification is needed for release of all keys, therefore check
    // is for actual_len <= key_pattern_len and not actual_len < key_pattern_len.
    if ((err_code == NRF_ERROR_RESOURCES) && (actual_len <= key_pattern_len))
    {
        // Buffer enqueue routine return value is not intentionally checked.
        // Rationale: Its better to have a a few keys missing than have a system
        // reset. Recommendation is to work out most optimal value for
        // MAX_BUFFER_ENTRIES to minimize chances of buffer queue full condition
        UNUSED_VARIABLE(buffer_enqueue(&m_hids, p_key_pattern, key_pattern_len, actual_len));
    }
```

## 4.10. ¿Qué es un comentario de mala calidad?
Un comentario de **mala calidad** es aquel que es *confuso*, *impreciso*, *innecesario* o *engañoso*. No aporta valor al código y puede incluso distraer o inducir a error a los desarrolladores.

```C
// Asignar 10 a la variable a
int a = 10;
```

```C
// Restar 1 a la variable count
count--;
```

```C
// Esto podría estar mal, pero funciona
int resultado = calcular_valor(x, y);
```

```C
#ifdef HEADER_SSL_H
/* hack: if we included OpenSSL's ssl.h, we know about SSL_CTX
 * this will of course break if we're included before OpenSSL headers...
 */
```
Comentario visto en: [sdk-nrf/ext/curl/include/curl/typecheck-gcc.h](https://github.com/nrfconnect/sdk-nrf/blob/bf37ded3e439428ff84537ba0464093c2748b3ee/ext/curl/include/curl/typecheck-gcc.h#L664)

## 4.11 Comentarios confusos
Estos comentarios pueden ser ambiguos o contradictorios con el código. Son difíciles de entender y pueden dar lugar a malas interpretaciones.

```C
/**
 * struct fw_rsc_vdev - virtio device header
 * @id: virtio device id (as in virtio_ids.h)
 * @notifyid is a unique rproc-wide notify index for this vdev. This notify
 * index is used when kicking a remote processor, to let it know that the
 * status/features of this vdev have changes.
 * @dfeatures specifies the virtio device features supported by the firmware
 * @gfeatures is a place holder used by the host to write back the
 * negotiated features that are supported by both sides.
 * @config_len is the size of the virtio config space of this vdev. The config
 * space lies in the resource table immediate after this vdev header.
 * @status is a place holder where the host will indicate its virtio progress.
 * @num_of_vrings indicates how many vrings are described in this vdev header
 * @reserved: reserved (must be zero)
 * @vring is an array of @num_of_vrings entries of 'struct fw_rsc_vdev_vring'.
 *
 * This resource is a virtio device header: it provides information about
 * the vdev, and is then used by the host and its peer remote processors
 * to negotiate and share certain virtio properties.
 *
 * By providing this resource entry, the firmware essentially asks remoteproc
 * to statically allocate a vdev upon registration of the rproc (dynamic vdev
 * allocation is not yet supported).
 *
 * Note: unlike virtualization systems, the term 'host' here means
 * the Linux side which is running remoteproc to control the remote
 * processors. We use the name 'gfeatures' to comply with virtio's terms,
 * though there isn't really any virtualized guest OS here: it's the host
 * which is responsible for negotiating the final features.
 * Yeah, it's a bit confusing.
 *
 * Note: immediately following this structure is the virtio config space for
 * this vdev (which is specific to the vdev; for more info, read the virtio
 * spec). the size of the config space is specified by @config_len.
 */
struct fw_rsc_vdev {
	u32 id;
	u32 notifyid;
	u32 dfeatures;
	u32 gfeatures;
	u32 config_len;
	u8 status;
	u8 num_of_vrings;
	u8 reserved[2];
	struct fw_rsc_vdev_vring vring[0];
};
```

## 4.12 Comentarios redundantes
Los comentarios que simplemente repiten lo que ya dice el código son innecesarios. Si el código es claro por sí mismo, no hace falta un comentario que diga lo mismo.

```C
/* Free up and clear all certificates and chains */

void ssl_cert_clear_certs(CERT *c)
{
```

## 4.13 Comentarios mal descritos
Son comentarios que describen incorrectamente lo que hace el código. Esto puede llevar a errores, ya que los desarrolladores pueden confiar en la información incorrecta.

```C
/*
 * PKCS#12 decoder.  It operates by decoding all of the blob content,
 * extracting all the interesting data from it and storing them internally,
 * then serving them one piece at a time.
 */
static OSSL_STORE_INFO *try_decode_PKCS12(const char *pem_name,
                                          const char *pem_header,
                                          const unsigned char *blob,
                                          size_t len, void **pctx,
                                          int *matchcount,
                                          const UI_METHOD *ui_method,
                                          void *ui_data, const char *uri,
                                          OSSL_LIB_CTX *libctx,
                                          const char *propq)
```                                          

## 4.14 Comentarios sobrantes
Son comentarios que ya no tienen relevancia porque el código ha sido modificado o porque simplemente no aportan nada útil al contexto actual.
Deben eliminarse para mantener el código limpio.

```C
// Se requiere esta pequeña pausa para evitar que GCC 4.8 optimice incorrectamente el acceso a los registros UART
// Esto causaba un fallo de transmisión en algunos microcontroladores
for (volatile int i = 0; i < 1000; i++);  // Pausa para "arreglar" fallo en GCC 4.8

// Enviar dato por UART
UART0->DR = dato;
 ```

## 4.15 Comentarios periódicos
Algunos desarrolladores insertan comentarios a intervalos regulares en el código, incluso si no son necesarios. Esto puede ser una distracción, especialmente cuando el código es lo suficientemente claro por sí mismo.

```C
/*-----------------------------------------------------------*/

/* pxDelayedTaskList and pxOverflowDelayedTaskList are switched when the tick
 * count overflows. */
#define taskSWITCH_DELAYED_LISTS()                                                \
    do {                                                                          \
        List_t * pxTemp;                                                          \
                                                                                  \
        /* The delayed tasks list should be empty when the lists are switched. */ \
        configASSERT( ( listLIST_IS_EMPTY( pxDelayedTaskList ) ) );               \
                                                                                  \
        pxTemp = pxDelayedTaskList;                                               \
        pxDelayedTaskList = pxOverflowDelayedTaskList;                            \
        pxOverflowDelayedTaskList = pxTemp;                                       \
        xNumOfOverflows = ( BaseType_t ) ( xNumOfOverflows + 1 );                 \
        prvResetNextTaskUnblockTime();                                            \
    } while( 0 )

/*-----------------------------------------------------------*/

/*
 * Place the task represented by pxTCB into the appropriate ready list for
 * the task.  It is inserted at the end of the list.
 */
#define prvAddTaskToReadyList( pxTCB )                                                                     \
    do {                                                                                                   \
        traceMOVED_TASK_TO_READY_STATE( pxTCB );                                                           \
        taskRECORD_READY_PRIORITY( ( pxTCB )->uxPriority );                                                \
        listINSERT_END( &( pxReadyTasksLists[ ( pxTCB )->uxPriority ] ), &( ( pxTCB )->xStateListItem ) ); \
        tracePOST_MOVED_TASK_TO_READY_STATE( pxTCB );                                                      \
    } while( 0 )
/*-----------------------------------------------------------*/
```

## 4.16 Comentarios obligatorios
En algunas organizaciones o proyectos, se exigen comentarios en lugares específicos, como las cabeceras de funciones o archivos, incluso si no añaden valor. Este tipo de comentarios pueden volverse una carga innecesaria.

**NOTA**: Si vamos a generar documentacion con Doxygen será necesario poner esos "comentarios obligatorios" en la interface publica de nuestro código.

## 4.17 Marcadores de posición
Estos comentarios sirven para marcar una serie de sentencias que realizan una determinada tarea. En general no suelen ser necesarias.

```C
//////////////////////////////////////////Deprecated Functions//////////////////////////////////////////////////////////
/////////////////////////////The following functions are only used by the legacy driver/////////////////////////////////
/////////////////////////////They might be removed in the next major release (ESP-IDF 6.0)//////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void i2c_hal_master_handle_tx_event(i2c_hal_context_t *hal, i2c_intr_event_t *event)
{
    uint32_t intr_status = 0;
    i2c_ll_get_intr_mask(hal->dev, &intr_status);
    if (intr_status != 0) {
        // If intr status is 0, no need to handle it.
        i2c_ll_master_get_event(hal->dev, event);
        if ((*event < I2C_INTR_EVENT_END_DET) ||
            (*event == I2C_INTR_EVENT_TRANS_DONE)) {
            i2c_ll_master_disable_tx_it(hal->dev);
            i2c_ll_clear_intr_mask(hal->dev, intr_status);
        } else if (*event == I2C_INTR_EVENT_END_DET) {
            i2c_ll_clear_intr_mask(hal->dev, intr_status);
        }
    }
}
```



## 4.18 Uso de funciones o variables sin comentarios
A veces, se crean funciones o variables sin agregar comentarios en los casos en que serían necesarios. Los nombres no siempre son suficientes, y los comentarios pueden aclarar el propósito o el comportamiento esperado.
Ejemplo: una función llamada procesar() que no tiene explicación de lo que realmente procesa.

## 4.19 Comentarios de llave de cierre
Los comentarios de llave de cierre se usan para indicar el final de bloques de código, especialmente cuando son largos o están anidados. Pueden ser útiles en bloques complejos, pero innecesarios en bloques simples o cortos.


```Cpp
namespace
{

constexpr chip::EndpointId mTemperatureMeasurementEndpointId = 1;
constexpr int16_t startingMockedValue = 1600;

constexpr uint16_t kSimulatedReadingFrequency = (60000 / kSensorTimerPeriodMs); /*Change simulated number every minute*/

#if CONFIG_THERMOSTAT_TEMPERATURE_STEP == 0
constexpr int16_t sMockTemp[] = { 2000, 2731, 1600, 2100, 1937, 3011, 1500, 1899 };
#endif

} // namespace
```

## 4.20 Comentarios que incluyen información no local
Estos comentarios contienen información que no está directamente relacionada con el código en el lugar donde se encuentran. Pueden generar confusión al tratar de entender el contexto.

```Cpp
#include <iostream>
#include <mqtt/async_client.h>  // Incluir la biblioteca paho.mqtt.cpp

int main() {
    const std::string SERVER_ADDRESS("tcp://test.mosquitto.org:1883");  // Puerto 1883
    const std::string CLIENT_ID("cliente_prueba");

    // Crear un cliente MQTT asincrónico
    mqtt::async_client client(SERVER_ADDRESS, CLIENT_ID);

    try {
        // Conectar al broker MQTT
        std::cout << "Conectando al broker en " << SERVER_ADDRESS << "..." << std::endl;
        auto connOpts = mqtt::connect_options_builder().clean_session(true).finalize();
        client.connect(connOpts)->wait();  // Esperar a que se realice la conexión
        std::cout << "Conectado exitosamente." << std::endl;

        // Aquí se pueden agregar más funcionalidades como publicar o suscribirse a temas.

        // Desconectar
        std::cout << "Desconectando..." << std::endl;
        client.disconnect()->wait();
        std::cout << "Desconectado." << std::endl;
    }
    catch (const mqtt::exception& exc) {
        std::cerr << "Error: " << exc.what() << std::endl;
        return 1;
    }

    return 0;
}

```

## 4.21 Menciones y asignaciones en los comentarios
A veces los comentarios contienen menciones de personas o asignaciones de tareas, como ```// Asignado a Juan para arreglar```. Estos comentarios no deberían estar en el código.

Para asignar tareas existen otras herramientas (como JIRA o Gitlab Issues) que permiten asociar tareas con código.

## 4.22 Comentarios con demasiada información
Los comentarios no deben ser demasiado extensos ni contener detalles irrelevantes. Un exceso de información puede ser tan malo como la falta de ella, ya que hace difícil discernir qué es importante.

```C
/*
 * Copies xCount bytes from the pxStreamBuffer's data storage area to pucData.
 * This function does not update the buffer's xTail pointer, so multiple reads
 * may be chained together "atomically". This is useful for Message Buffers where
 * the length and data bytes are read in two separate chunks, and we don't want
 * the writer to see the buffer as having more free space until after all data is
 * copied over, especially if we have to abort the read due to insufficient receiving space.
 * This function takes a custom xTail value to indicate where to read from (necessary
 * for chaining) and returns the the resulting xTail position.
 * To mark the read as complete, manually set the buffer's xTail field with the
 * returned xTail from this function.
 */
static size_t prvReadBytesFromBuffer( StreamBuffer_t * pxStreamBuffer,
                                      uint8_t * pucData,
                                      size_t xCount,
                                      size_t xTail ) PRIVILEGED_FUNCTION;
```                                      

## 4.23 Comentarios como encabezados de funciones
Los comentarios en la cabecera de las funciones deben explicar claramente el propósito de la función, sus parámetros y el valor de retorno. Ayudan a otros desarrolladores a entender la función sin tener que leer todo su contenido.

```C
/** @brief Initialize console device.
 *
 *  This function should be called once to initialize pull-style
 *  access to console via console_getchar() function and buffered
 *  output using console_putchar() function. This function supersedes,
 *  and incompatible with, callback (push-style) console handling
 *  (via console_input_fn callback, etc.).
 *
 * @return 0 on success, error code (<0) otherwise
 */
int console_init(void);
```
Visto en: [zephyr/include/zephyr/console/console.h](https://github.com/zephyrproject-rtos/zephyr/blob/main/include/zephyr/console/console.h)

## 4.24 Documentando código público y privado
El código público (métodos y clases accesibles fuera de un módulo) generalmente requiere comentarios más detallados, ya que será usado por otros desarrolladores. El código privado puede necesitar menos documentación, pero sigue siendo útil explicar decisiones clave.
Es importante mantener un equilibrio entre la documentación excesiva y la que proporciona la información adecuada según la visibilidad del código.

[async_client class (MQTT Pharao lib)](https://github.com/eclipse/paho.mqtt.cpp/blob/master/include/mqtt/async_client.h)

