# TEMA 1 - LA IMPORTANCIA DEL CÓDIGO LIMPIO

## 1.1 Introducción al concepto de código limpio y su importancia

El código limpio se refiere a un código que es fácil de entender, mantener y modificar por cualquier desarrollador, no solo por su autor. Es un código que sigue principios de simplicidad y claridad.

Importancia: Un código limpio facilita la colaboración entre equipos, reduce el tiempo de desarrollo y de corrección de errores. 

A largo plazo, **ahorra costos y tiempo**, permitiendo una evolución más eficiente del software.





## 1.2 ¿Qué se entiende como código incorrecto?

El código incorrecto o "sucio" es difícil de leer, comprender y mantener. 

**Puede** ser funcional en un momento dado, pero con el tiempo, se vuelve un obstáculo para la evolución del software.

Características:  
- Falta de comentarios o documentación.
- Funciones excesivamente largas o complejas.
- Repetición de código (código duplicado).
- Nombres de variables o funciones poco descriptivos.
- Uso de “magic numbers”  


```C
#include <stdint.h>

void initUART() {
    // Dirección base UART
    volatile uint32_t *a = (uint32_t *)(0x40000000 + 0x00);
    volatile uint32_t *b = (uint32_t *)(0x40000000 + 0x04);
    volatile uint32_t *c = (uint32_t *)(0x40000000 + 0x08);
    
    // Configurar control UART
    *a = 0x12345678; // Configuración genérica
    
    // Configurar baudrate
    *b = 115200;
    
    // Habilitar UART
    *c = 1;
}
```


## 1.3 Las consecuencias de un código incorrecto en términos económicos
Impacto en los tiempos de desarrollo: Un código sucio aumenta el tiempo de desarrollo, ya que los programadores deben dedicar más tiempo a comprenderlo antes de realizar cambios.
Mantenimiento costoso: Los errores y problemas derivados del código incorrecto pueden generar costos elevados de mantenimiento.
Ejemplo en la vida real: Casos en los que empresas han enfrentado sobrecostos o demoras debido a la deuda técnica acumulada por un código mal escrito.
En términos de rendimiento: Un código ineficiente puede llevar a problemas de rendimiento, afectando el costo operativo en el uso de servidores o dispositivos con recursos limitados.

## 1.4 La importancia de la actitud frente al cambio
Resistencia al cambio: La negativa a mejorar el código o adoptar mejores prácticas puede llevar a un estancamiento en el equipo y la calidad del software.
Actitud positiva: Promover una mentalidad abierta al aprendizaje continuo y la refactorización del código cuando sea necesario.
Refactorización constante: No esperar a que los problemas se acumulen, sino buscar siempre mejorar el código. Esto no solo mejora la calidad del software, sino también el ambiente de trabajo.
Ejemplo en C/C++: Mostrar cómo una pequeña mejora en una función mal diseñada puede tener efectos positivos en todo el código.

## 1.5 Los conceptos del código limpio
Simplicidad: El código debe ser lo más simple posible, sin redundancias innecesarias.
Modularidad: Descomponer el código en funciones o módulos pequeños y reutilizables.
Legibilidad: El código debe ser fácil de leer y comprender, tanto por ti como por otros desarrolladores.
Evitación del código duplicado: El código duplicado es enemigo del código limpio. Cada concepto o lógica debe existir una única vez.
Ejemplo en C/C++: Mostrar ejemplos de cómo aplicar modularidad usando funciones y clases (en C++) para mejorar la legibilidad y mantenibilidad.

## 1.6 Las diferencias teóricas del concepto
Código "limpio" vs. "código funcional": Explicar la diferencia entre un código que simplemente funciona y un código que es limpio y mantenible.
Calidad interna vs. calidad externa: La calidad interna del código se refiere a su estructura, legibilidad y mantenibilidad, mientras que la calidad externa es cómo el software funciona para el usuario final.
Refactorización y rediseño: Diferencia entre mejorar gradualmente un código (refactorización) y hacer cambios más profundos (rediseño), manteniendo el mismo objetivo de mejorar la calidad del software.

## 1.7 La Regla de Boy Scout y los principios del código limpio
La Regla de Boy Scout: "Deja el campamento mejor de lo que lo encontraste." Aplicado al código significa que siempre que un desarrollador trabaje en una parte del código, debe intentar dejarlo más limpio que cuando lo encontró.
Principios del código limpio:
DRY (Don't Repeat Yourself): Evitar la duplicación de código.
KISS (Keep It Simple, Stupid): Mantener las cosas simples y directas.
YAGNI (You Aren't Gonna Need It): No implementar funcionalidades adicionales que no se necesitan.
Single Responsibility Principle: Cada clase o función debe tener una única responsabilidad.
Ejemplo en C/C++: Mostrar cómo aplicar la Regla de Boy Scout refactorizando un bloque de código existente para que sea más claro y eficiente sin cambiar su funcionalidad.
