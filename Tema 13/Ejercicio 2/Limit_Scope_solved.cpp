#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

class SharedData {
public:
    // Constructor
    SharedData() : value(0) {}

    // Función para incrementar el valor
    void increment() {
        std::lock_guard<std::mutex> lock(mtx); // Asegura la exclusión mutua
        ++value;
        std::cout << "Valor incrementado a: " << value << std::endl;
    }

    // Función para obtener el valor actual
    int get_value() {
        std::lock_guard<std::mutex> lock(mtx); // Asegura la exclusión mutua
        return value;
    }

private:
    int value;                // Dato compartido
    std::mutex mtx;          // Mutex para proteger el acceso a 'value'
};

// Función que representa un hilo que incrementa el valor
void increment_data(SharedData& data) {
    for (int i = 0; i < 5; ++i) {
        data.increment();
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simula trabajo
    }
}

// Función que representa un hilo que lee el valor
void read_data(SharedData& data) {
    for (int i = 0; i < 5; ++i) {
        int value = data.get_value();
        std::cout << "Valor leído: " << value << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(150)); // Simula trabajo
    }
}

int main() {
    SharedData shared_data;

    // Crear hilos para incrementar y leer el valor
    std::thread increment_thread(increment_data, std::ref(shared_data));
    std::thread read_thread(read_data, std::ref(shared_data));

    // Esperar a que ambos hilos terminen
    increment_thread.join();
    read_thread.join();

    std::cout << "Proceso finalizado." << std::endl;
    return 0;
}
