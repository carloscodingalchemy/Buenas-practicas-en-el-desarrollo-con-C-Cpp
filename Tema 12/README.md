# TEMA 12 - DISEÑOS EMERGENTES

## 12.1 ¿Qué es un diseño emergente?
Un diseño emergente es aquel que **surge y mejora de manera progresiva** a lo largo del ciclo de vida del desarrollo del software, **en lugar de ser planificado por completo al inicio**. 

En lugar de intentar prever todos los detalles de un sistema complejo desde el principio, se construye el software de manera incremental y se ajusta el diseño a medida que se entienden mejor los requisitos y el comportamiento del sistema.

Este concepto **está alineado con prácticas ágiles y enfoques iterativos de desarrollo**, donde se priorizan soluciones simples y de fácil cambio. El diseño emergente permite que el sistema se ajuste de manera dinámica a los nuevos requisitos y cambios inesperados.

Beneficios:
**Adaptabilidad**: Permite que el software responda a los cambios en los requisitos del negocio de manera ágil y flexible.
**Simplicidad**: Se evita la sobreingeniería, lo que permite que el diseño crezca orgánicamente en lugar de forzar estructuras innecesarias desde el principio.
**Mantener la calidad del código**: Un diseño emergente bien gestionado mejora la calidad del código mediante la refactorización constante y la eliminación de complejidad innecesaria.

## 12.2 Refactorización
Refactorización es el proceso de mejorar el diseño interno del código sin cambiar su comportamiento externo. Consiste en ajustar y mejorar el código existente para hacerlo más legible, mantenible y eficiente, sin introducir nuevas características.

La refactorización es un aspecto clave de un diseño emergente, ya que a medida que el software crece, las partes del código que inicialmente eran adecuadas pueden volverse ineficaces o difíciles de entender. 

La refactorización permite a los desarrolladores ajustar continuamente el código para alinearse con las mejores prácticas y el nuevo conocimiento adquirido durante el desarrollo.

Ejemplos comunes de refactorización:
- Renombrar variables o métodos para que sus nombres sean más descriptivos.
- Simplificar lógica compleja o reducir anidaciones profundas.
- Extraer métodos o clases para reducir el tamaño y mejorar la modularidad.
- Eliminar dependencias innecesarias o duplicadas.

Ventajas:
Mejora la legibilidad del código.
Facilita la localización y corrección de errores.
Mejora la modularidad y la capacidad de prueba del código.

## 12.3 Eliminación de código duplicado
Eliminar código duplicado es una de las prácticas fundamentales en la mejora continua del diseño del software. El código duplicado no solo aumenta el tamaño del código y lo hace más difícil de mantener, sino que también introduce riesgo de inconsistencias y errores.  

**Estrategias para eliminar código duplicado:**

- **Refactorización de métodos comunes**: Identificar patrones o funcionalidades repetidas en diferentes partes del código y extraerlas en métodos o clases reutilizables.
- **Uso de herencia o composición**: Aplicar principios de diseño orientado a objetos para reutilizar código entre clases que comparten comportamientos similares.
- **Uso de funciones o utilidades compartidas**: Centralizar el código reutilizable en bibliotecas o módulos comunes para evitar la duplicación a nivel del proyecto.

**Beneficios:**
- **Mantenibilidad**: Cuando una lógica necesita cambiar, solo hay que actualizar un lugar en el código, en lugar de modificar varias instancias.
- **Reducción de errores**: Se reduce la posibilidad de errores relacionados con inconsistencias en implementaciones duplicadas.
- **Legibilidad**: El código es más compacto y fácil de seguir cuando no hay duplicación.

```cpp
// Serializa la estructura a un archivo binario
void serialize(const SensorData& data, const std::string& filename) {
    std::ofstream ofs(filename, std::ios::binary);
    if (!ofs) {
        std::cerr << "Error al abrir el archivo para escritura." << std::endl;
        return;
    }

    // Serializar cada miembro individualmente
    ofs.write(reinterpret_cast<const char*>(&data.temperature), sizeof(data.temperature));
    ofs.write(reinterpret_cast<const char*>(&data.pressure), sizeof(data.pressure));
    ofs.write(reinterpret_cast<const char*>(&data.humidity), sizeof(data.humidity));
    ofs.write(reinterpret_cast<const char*>(&data.timestamp), sizeof(data.timestamp));

    ofs.close();
}

// Deserializa la estructura desde un archivo binario
void deserialize(SensorData& data, const std::string& filename) {
    std::ifstream ifs(filename, std::ios::binary);
    if (!ifs) {
        std::cerr << "Error al abrir el archivo para lectura." << std::endl;
        return;
    }

    // Deserializar cada miembro individualmente
    ifs.read(reinterpret_cast<char*>(&data.temperature), sizeof(data.temperature));
    ifs.read(reinterpret_cast<char*>(&data.pressure), sizeof(data.pressure));
    ifs.read(reinterpret_cast<char*>(&data.humidity), sizeof(data.humidity));
    ifs.read(reinterpret_cast<char*>(&data.timestamp), sizeof(data.timestamp));

    ifs.close();
}
```

## 12.4 Minificación de clases y métodos
Los conceptos de "eliminacion de duplicados", "codigo legible" y la "responsabilidad unica" pueden ser llevados al extremo. Esto nos puede llevar a crear una gran cantidad de clases y funciones diminutas.

Por lo que una regla a seguir también es "intentar mantener el conteo de clases y funciones lo mas bajo posible".

**TRADUCCIÓN**: *No permitas que el dogmatismo estropee tu código*
