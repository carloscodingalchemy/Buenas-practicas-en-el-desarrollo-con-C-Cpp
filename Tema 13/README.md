# TEMA 13 - CONCURRENCIA


## 13.1 Desmitificando la concurrencia
La concurrencia es el concepto que permite que múltiples tareas se ejecuten de manera simultánea o entrelazada, dando la impresión de que se están realizando al mismo tiempo. Esto no siempre significa que las tareas se ejecuten en paralelo (como en sistemas de multiprocesamiento), sino que el sistema distribuye los recursos de manera eficiente para que múltiples procesos o hilos progresen de forma cooperativa.

**Mitos comunes**
- *La concurrencia siempre mejora el rendimiento*
- *El diseño no cambia cuand se escriben programas cocurrentes*

**Algunas afirmaciones más exactas**

- *Conseguir concurrencia es difícil, incluso para problemas sencillos*
- *Los bugs normalmente no son reproducibles y suelen considerarse como incidentes puntuales*
- *La concurrencia produce "overhead"*


## 13.2 Entendiendo correctamente qué es la concurrencia
La concurrencia es la capacidad de un programa para manejar múltiples tareas al mismo tiempo, aunque no necesariamente significa que estas tareas se ejecuten simultáneamente. A menudo, se confunde con el paralelismo, pero son conceptos relacionados, no equivalentes.

Concurrencia implica que múltiples tareas están en progreso, y el sistema puede cambiar rápidamente entre ellas. No es obligatorio que se ejecuten al mismo tiempo; lo importante es que el programa gestiona varios flujos de trabajo de manera intercalada, optimizando el uso de recursos.

Paralelismo, por otro lado, es una forma específica de concurrencia en la que múltiples tareas se ejecutan simultáneamente en diferentes procesadores o núcleos de la CPU.

En un programa concurrente, los hilos o procesos pueden compartir recursos y alternar el uso de los mismos, mientras que en el paralelismo, las tareas se distribuyen en núcleos diferentes para correr de manera simultánea.

Un diseño concurrente bien hecho implica **manejar la sincronización**, **evitar conflictos en el acceso a recursos compartidos** y **garantizar la correcta ejecución de tareas**, independientemente de si están ejecutándose en paralelo o no. La concurrencia, bien aplicada, mejora la eficiencia y la capacidad de respuesta de las aplicaciones, pero requiere una buena planificación para evitar errores como condiciones de carrera o deadlocks.

## 13.3 Principios sobre la concurrencia
Existen una serie de principios que se deben seguir para diseñar sistemas concurrente. Estos principios son:

### 13.3.1 El Principio de Responsabilidad Única aplicado a la concurrencia
El principio SRP dice: "un método/clase/componente debe tener una única razón para cambiar". 
La concurrencia es suficientemente compleja para tratarla de forma independiente.

RECOMENDACON: Mantener el código relacionado con la concurrencia separado del resto del código.

```cpp
#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <chrono>

int main() {
    std::queue<std::string> data_queue;
    std::mutex mtx;
    std::condition_variable cv;
    bool stop_flag = false;

    // Hilo que lee los datos de los sensores
    std::thread sensor_thread([&]() {
        while (!stop_flag) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));  // Simula tiempo de lectura
            std::string data = "sensor_data";  // Simulación de los datos obtenidos

            // Protección de la cola compartida
            std::lock_guard<std::mutex> lock(mtx);
            data_queue.push(data);  // Inserta los datos en la cola
            std::cout << "Datos del sensor leídos: " << data << std::endl;

            cv.notify_one();  // Notifica al hilo de transmisión que hay datos disponibles
        }
    });

    // Hilo que envía los datos al gateway LoRaWAN
    std::thread transmit_thread([&]() {
        while (!stop_flag) {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [&]() { return !data_queue.empty() || stop_flag; });  // Espera hasta que haya datos o se detenga el hilo

            if (!data_queue.empty()) {
                std::string data_to_send = data_queue.front();
                data_queue.pop();
                lock.unlock();  // Liberar el bloqueo mientras se realiza la transmisión

                // Simulación del envío de datos
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));  // Simula tiempo de envío
                std::cout << "Datos enviados al gateway: " << data_to_send << std::endl;
            }
        }
    });

    // Simulación de ejecución por un tiempo determinado (5 segundos)
    std::this_thread::sleep_for(std::chrono::seconds(5));

    // Detener los hilos
    {
        std::lock_guard<std::mutex> lock(mtx);
        stop_flag = true;  // Señal para detener las tareas
    }
    cv.notify_all();  // Notificar a los hilos de transmisión para que terminen

    sensor_thread.join();
    transmit_thread.join();

    std::cout << "Sistema embebido detenido." << std::endl;

    return 0;
}

```

### 13.3.2 La limitación del ámbito de los datos
Limitar el ámbito de los datos significa reducir la cantidad de datos compartidos entre procesos o hilos concurrentes. Cuantos más datos se compartan, mayor será el riesgo de condiciones de carrera, bloqueos y otros problemas de sincronización.
Soluciones:
Usar variables locales siempre que sea posible.
Encapsular los datos compartidos dentro de estructuras que gestionen correctamente la concurrencia (como las clases thread-safe o los monitores).

```cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

// Variable global que representa los datos compartidos
int shared_value = 0;
std::mutex mtx;  // Mutex global para protección (pero no se usará adecuadamente)

// Función que incrementa el valor compartido (sin protección adecuada)
void increment_data() {
    for (int i = 0; i < 5; ++i) {
        // Acceso directo a la variable global
        shared_value++;
        std::cout << "Valor incrementado a: " << shared_value << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simula trabajo
    }
}

// Función que lee el valor compartido (sin protección adecuada)
void read_data() {
    for (int i = 0; i < 5; ++i) {
        // Acceso directo a la variable global
        int value = shared_value;
        std::cout << "Valor leído: " << value << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(150)); // Simula trabajo
    }
}

int main() {
    // Crear hilos para incrementar y leer el valor
    std::thread increment_thread(increment_data);
    std::thread read_thread(read_data);

    // Esperar a que ambos hilos terminen
    increment_thread.join();
    read_thread.join();

    std::cout << "Proceso finalizado." << std::endl;
    return 0;
}
```

### 13.3.3 Las copias de los datos
Hacer copias de los datos es una estrategia para evitar los problemas que surgen del acceso concurrente a datos compartidos. En lugar de compartir la misma instancia de un objeto o estructura de datos entre múltiples hilos o procesos, cada uno tiene su propia copia.

**Ventajas**:
Evita la necesidad de sincronización, ya que cada hilo o proceso opera sobre su propia copia de los datos.
Reduce la posibilidad de errores por acceso concurrente a datos modificables.
**Desventajas**:
Aumenta el uso de memoria y puede requerir un mayor procesamiento para mantener las copias actualizadas en sistemas complejos.

### 13.3.4 La importancia de la independencia de procesos
La independencia de procesos se refiere a la capacidad de cada proceso o hilo para ejecutarse sin depender de los estados o resultados de otros procesos. Esto minimiza la necesidad de sincronización y permite que cada proceso progrese de manera autónoma.
Diseñar procesos independientes mejora el rendimiento general del sistema, ya que reduce el tiempo de espera y la probabilidad de bloqueos.

```cpp
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

// Función que simula un proceso independiente
void independent_task(int id, int start, int end) {
    long long local_sum = 0;
    
    // Realiza cálculos en un rango de números
    for (int i = start; i < end; ++i) {
        local_sum += i;
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Simula trabajo
    }

    // Imprime el resultado de la tarea independiente
    std::cout << "Hilo " << id << " suma de " << start << " a " << end << " es: " << local_sum << std::endl;
}

int main() {
    // Número de hilos
    const int num_threads = 4;
    std::vector<std::thread> threads;

    // Rango de datos a procesar (0-100)
    int range = 100;
    int chunk_size = range / num_threads;

    // Crear y lanzar hilos, cada uno con su propio rango de trabajo
    for (int i = 0; i < num_threads; ++i) {
        int start = i * chunk_size;
        int end = (i + 1) * chunk_size;

        // Lanzar cada hilo con su rango independiente
        threads.emplace_back(independent_task, i, start, end);
    }

    // Esperar a que todos los hilos terminen
    for (auto& thread : threads) {
        thread.join();
    }

    std::cout << "Todas las tareas han finalizado." << std::endl;
    return 0;
}
```

## 13.4 Las bibliotecas y su compatibilidad con los procesos
No todas las bibliotecas están diseñadas para ser usadas en entornos concurrentes. Es crucial seleccionar bibliotecas compatibles con procesos concurrentes que sean thread-safe.
Thread-safe significa que una biblioteca puede ser usada por múltiples hilos al mismo tiempo sin riesgo de corromper los datos o causar comportamientos indeseados.

Ejemplos: En C++, bibliotecas como std::thread y std::mutex proporcionan primitivas para manejar la concurrencia de manera segura.

- **Librerías de Entrada/Salida (I/O)**
  - `<iostream>`: Operaciones de entrada/salida estándar (`std::cout`, `std::cin`, etc.).

- **Librerías de STL (Standard Template Library)**
  - Contenedores de la STL: `std::vector`, `std::list`, `std::map`, etc.

- **Librerías de Manejo de Memoria**
  - `malloc`, `free`, `new`, `delete`: Funciones de asignación y liberación de memoria.

- **Librerías de C y C++**
  - `<cstring>`, `<cstdlib>`: Funciones como `strcpy`, `strcat`, y otras operaciones de cadena.

- **Librerías de Terceros**
  - Muchas librerías gráficas y de red (consultar la documentación específica).

- **Librerías de Recursos Externos**
  - Conexiones de bases de datos y bibliotecas de red (por ejemplo, ODBC, MySQL Connector, Boost.Asio).
  
- **Clases y Objetos de C++**
  - Clases de usuario que utilizan datos compartidos sin mecanismos de sincronización.

## 13.5 Los 3 distintos modelos de ejecución

Existen tres modelos básicos de comportamiento en aplicaciones concurrentes:

**PRODUCTOR-CONSUMIDOR**  

El modelo Productor-Consumidor es un patrón clásico en programación concurrente que se utiliza para sincronizar el acceso a un recurso compartido entre dos tipos de procesos: los productores, que generan datos o tareas, y los consumidores, que procesan esos datos o tareas.

Funcionamiento
**Productores**: Generan datos y los almacenan en un buffer o cola compartida. Si el buffer está lleno, el productor debe esperar hasta que haya espacio disponible.
**Consumidores**: Toman datos del buffer. Si el buffer está vacío, el consumidor debe esperar hasta que haya datos disponibles.
Sincronización
Se utilizan mecanismos de sincronización (como semáforos o mutexes) para gestionar el acceso al buffer, garantizando que no se produzcan condiciones de carrera. Un semáforo puede indicar el número de elementos disponibles para consumir, mientras que otro puede indicar el espacio libre para producir.

```cpp
// Ejemplo simple (pseudocódigo)
while (true) {
    producir_dato();
    buffer.push(dato);
    signal(productor_semaforo); // Notifica a los consumidores
}

while (true) {
    wait(consumer_semaforo); // Espera a que haya datos
    dato = buffer.pop();
    consumir_dato(dato);
}
```

**LECTOR-ESCRITOR**  

Descripción
El modelo Lector-Escritor es otro patrón de concurrencia que se utiliza cuando múltiples hilos (o procesos) necesitan acceder a un recurso compartido, como un archivo o una base de datos. En este modelo, los hilos pueden ser de dos tipos: lectores (que solo leen el recurso) y escritores (que pueden modificarlo).

Funcionamiento
**Lectores**: Pueden acceder al recurso simultáneamente siempre que no haya escritores activos.
**Escritores**: Tienen acceso exclusivo al recurso. Mientras un escritor esté escribiendo, ningún lector o otro escritor puede acceder al recurso.
Sincronización
Se requieren mecanismos de sincronización para gestionar el acceso a los recursos. Por lo general, se utilizan mutexes y contadores para llevar la cuenta de los lectores activos y controlar el acceso de los escritores.

```cpp
// Ejemplo simple (pseudocódigo)
mutex lock; // Mutex para acceso exclusivo
int reader_count = 0;

void read() {
    lock.lock();
    reader_count++;
    if (reader_count == 1) {
        // Bloquear escritores
        writer_lock.lock();
    }
    lock.unlock();
    
    // Lectura del recurso
    realizar_lectura();
    
    lock.lock();
    reader_count--;
    if (reader_count == 0) {
        // Permitir que los escritores accedan
        writer_lock.unlock();
    }
    lock.unlock();
}

void write() {
    writer_lock.lock(); // Acceso exclusivo para escribir
    realizar_escritura();
    writer_lock.unlock();
}
```

**CENA DE LOS FILOSOFOS**  

Descripción
El problema de la Cena de los Filósofos es un famoso problema de concurrencia que ilustra los problemas de sincronización y la gestión de recursos compartidos. En este modelo, un número de filósofos están sentados alrededor de una mesa y deben alternar entre pensar y comer.

Funcionamiento
Cada filósofo necesita dos tenedores (recursos) para comer.
Si un filósofo quiere comer, debe tomar ambos tenedores de su izquierda y derecha.
Después de comer, debe devolver los tenedores.
Problemas
Este modelo puede conducir a problemas como:

Deadlock: Si todos los filósofos toman el tenedor de la izquierda al mismo tiempo, ninguno podrá comer porque todos estarán esperando al tenedor de la derecha.
Starvation: Un filósofo podría no obtener ambos tenedores si otros filósofos están comiendo constantemente.
Soluciones
Utilizar un mutex para cada tenedor y un sistema de espera, de modo que se asegure que no se produzca un deadlock.
Implementar un algoritmo que permita a los filósofos esperar de manera que se evite el deadlock y se garantice que todos tengan la oportunidad de comer.

```cpp
// Ejemplo simple (pseudocódigo)
mutex tenedores[NUM_FILOSOFOS];

void philosopher(int id) {
    while (true) {
        pensar();
        
        // Intentar tomar los tenedores
        tenedores[id].lock(); // Tenedor izquierdo
        tenedores[(id + 1) % NUM_FILOSOFOS].lock(); // Tenedor derecho
        
        comer();
        
        // Devolver los tenedores
        tenedores[(id + 1) % NUM_FILOSOFOS].unlock();
        tenedores[id].unlock();
    }
}
```



| Concepto             | Descripción                                                                                                 |
|----------------------|-------------------------------------------------------------------------------------------------------------|
| **Bounded Resources**| Se refiere a la limitación de recursos disponibles en un sistema. Los recursos son finitos, lo que significa que hay un límite en cuántos procesos o hilos pueden acceder a ellos simultáneamente. Esto requiere una gestión cuidadosa para evitar problemas de acceso. |
| **Mutual Exclusion** | Es un principio de sincronización que asegura que solo un hilo o proceso puede acceder a un recurso compartido en un momento dado. Esto es crucial para prevenir condiciones de carrera y garantizar la integridad de los datos. |
| **Starvation**       | Ocurre cuando un hilo o proceso no puede acceder a los recursos que necesita para continuar su ejecución, debido a que otros hilos están siempre ocupando esos recursos. Esto puede suceder si los algoritmos de programación no permiten el acceso equitativo a los recursos. |
| **Deadlock**         | Es una situación en la que dos o más hilos o procesos están bloqueados mutuamente, esperando que el otro libere un recurso que necesitan. Esto resulta en una situación en la que ninguno de los procesos puede continuar su ejecución. |
| **Livelock**         | Es similar a un deadlock, pero en lugar de estar bloqueados, los procesos continúan cambiando de estado sin hacer progresos. Por ejemplo, dos hilos pueden estar tratando de evitar un deadlock, pero en su esfuerzo, terminan alterando su comportamiento sin que ninguno avance. |



## 13.6 La dependencia entre métodos sincronizados
La dependencia entre métodos sincronizados ocurre cuando varios métodos requieren sincronización para acceder a los mismos recursos compartidos. Este tipo de dependencia puede causar problemas como bloqueos o retardos si no se gestionan correctamente.
Para minimizar estas dependencias, se debe reducir la cantidad de código que necesita sincronización, usar técnicas como el bloqueo de granularidad fina y aplicar un diseño que favorezca la independencia entre las partes del sistema.

```cpp
#include <iostream>
#include <thread>
#include <mutex>

class BankAccount {
private:
    double balance;
    std::mutex mtx;  // Mutex para proteger el acceso al balance

public:
    BankAccount(double initial_balance) : balance(initial_balance) {}

    // Método para depositar dinero
    void deposit(double amount) {
        std::lock_guard<std::mutex> lock(mtx);  // Sincronización
        std::cout << "Depositando " << amount << "...\n";
        balance += amount;
        std::cout << "Nuevo balance tras el deposito: " << balance << "\n";
    }

    // Método para retirar dinero
    void withdraw(double amount) {
        std::lock_guard<std::mutex> lock(mtx);  // Sincronización
        if (balance >= amount) {
            std::cout << "Retirando " << amount << "...\n";
            balance -= amount;
            std::cout << "Nuevo balance tras la retirada: " << balance << "\n";
        } else {
            std::cout << "Fondos insuficientes para retirar " << amount << "!\n";
        }
    }

    // Método para transferir dinero entre dos cuentas
    void transfer(BankAccount& to, double amount) {
        // Sincronización manual usando dos mutexes (potencial para interbloqueo)
        std::scoped_lock lock(mtx, to.mtx);  // Se bloquean ambos mutexes simultáneamente
        if (balance >= amount) {
            std::cout << "Transferencia de " << amount << " de esta cuenta a otra cuenta...\n";
            balance -= amount;
            to.balance += amount;
            std::cout << "Transferencia completada. Nuevo balance: " << balance << "\n";
        } else {
            std::cout << "Fondos insuficientes para transferir " << amount << "!\n";
        }
    }
};

void threadFunction1(BankAccount& account) {
    account.deposit(100);  // Hilo 1: realiza un depósito
}

void threadFunction2(BankAccount& account1, BankAccount& account2) {
    account1.transfer(account2, 50);  // Hilo 2: realiza una transferencia
}

int main() {
    BankAccount account1(200);  // Primera cuenta con $200
    BankAccount account2(100);  // Segunda cuenta con $100

    std::thread t1(threadFunction1, std::ref(account1));  // Hilo para hacer un depósito
    std::thread t2(threadFunction2, std::ref(account1), std::ref(account2));  // Hilo para transferir dinero

    t1.join();
    t2.join();

    return 0;
}
```

## 13.7 La importancia de reducir las partes sincronizadas
La sincronización es necesaria para evitar conflictos entre procesos concurrentes que acceden a recursos compartidos, pero también introduce sobrecarga y puede causar problemas de rendimiento.
Reducir las partes sincronizadas implica diseñar el sistema de manera que el código que requiere sincronización sea lo más pequeño y rápido posible, minimizando el impacto en el rendimiento.

```cpp	
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>

class DataProcessor {
private:
    std::vector<int> data;
    std::mutex mtx;

public:
    // Constructor que inicializa los datos
    DataProcessor(int size) {
        data.resize(size, 0);
    }

    // Método que procesa todos los datos (sincronización excesiva)
    void processData() {
        std::lock_guard<std::mutex> lock(mtx);  // Bloquea todo el método

        // Simula un procesamiento lento de datos
        for (int i = 0; i < data.size(); ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));  // Simula trabajo pesado
            data[i] = i * 2;
        }

        std::cout << "Datos procesados.\n";
    }

    // Método para leer los datos de forma segura
    int getData(int index) {
        std::lock_guard<std::mutex> lock(mtx);  // Sincronización para lectura
        if (index >= 0 && index < data.size()) {
            return data[index];
        }
        return -1;
    }
};

void threadFunction(DataProcessor& processor) {
    processor.processData();  // Cada hilo intentará procesar los datos
}

int main() {
    DataProcessor processor(10);  // Crear un DataProcessor con 10 elementos

    std::thread t1(threadFunction, std::ref(processor));  // Hilo 1
    std::thread t2(threadFunction, std::ref(processor));  // Hilo 2

    t1.join();
    t2.join();

    return 0;
}
```

## 13.8 ¿Cómo probar adecuadamente un código con procesos?
Probar código concurrente es considerablemente más difícil que probar código secuencial, debido a la naturaleza impredecible de la concurrencia. Las pruebas deben cubrir una amplia variedad de escenarios para detectar problemas como condiciones de carrera, bloqueos y desincronización de datos.

Recomendacion: "Escribir tests que tengan el potencial de exponer problemas y ejecutarlos frecuentemente, con diferentes configuraciones programaticas, de sistema y de carga. Si un test falla alguna vez, busca la causa. No ignores el fallo porque al ejecutar el test de nuevo pase".

Concretando esta recomendación un poco más tenemos estos consejos:

- Trata fallos espurios como candidatos a fallos en los hilos
- Consigue primero tener tu código no concurrente operativo
- Haz que tu código concurrente pueda acoplarse y desacoplarse de forma sencilla
- Haz tu codigo concurrente "tuneable"
- Corre tu código concurrente con mas hilos que cores
- Corre tu código concurrente en diferentes plataformas
- Instrumenta tu código para tratar de forzar errores

```cpp
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <cassert>

// Clase BankAccount sin sincronización
class BankAccount {
private:
    double balance;

public:
    BankAccount() : balance(0) {}

    // Método para depositar dinero
    void deposit(double amount) {
        balance += amount;
    }

    // Método para retirar dinero
    bool withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            return true;
        }
        return false;
    }

    // Obtener el balance actual
    double getBalance() const {
        return balance;
    }
};

// Clase que envuelve a BankAccount para manejar concurrencia
class ConcurrentBankAccount {
private:
    BankAccount account;
    std::mutex mtx;

public:
    // Método concurrente para depositar
    void deposit(double amount) {
        std::lock_guard<std::mutex> lock(mtx);  // Sincronización en este nivel
        account.deposit(amount);
    }

    // Método concurrente para retirar
    bool withdraw(double amount) {
        std::lock_guard<std::mutex> lock(mtx);  // Sincronización en este nivel
        return account.withdraw(amount);
    }

    // Método concurrente para obtener el balance
    double getBalance() const {
        std::lock_guard<std::mutex> lock(mtx);  // Sincronización en este nivel
        return account.getBalance();
    }
};

// Función para simular operaciones concurrentes de depósito y retiro
void simulateTransactions(ConcurrentBankAccount& account, int numIterations) {
    for (int i = 0; i < numIterations; ++i) {
        account.deposit(100);  // Deposita 100
        account.withdraw(50);  // Retira 50
    }
}

int main() {
    ConcurrentBankAccount account;  // Usamos la clase envuelta en concurrencia

    const int numThreads = 10;
    const int numIterations = 1000;

    std::vector<std::thread> threads;

    // Ejecuta varias operaciones concurrentes desde múltiples hilos
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(simulateTransactions, std::ref(account), numIterations);
    }

    // Espera a que todos los hilos terminen
    for (auto& t : threads) {
        t.join();
    }

    // Verifica el balance final esperado
    double expectedBalance = numThreads * numIterations * 50;
    std::cout << "Balance final: " << account.getBalance() << std::endl;
    std::cout << "Balance esperado: " << expectedBalance << std::endl;

    assert(account.getBalance() == expectedBalance);
    return 0;
}
```