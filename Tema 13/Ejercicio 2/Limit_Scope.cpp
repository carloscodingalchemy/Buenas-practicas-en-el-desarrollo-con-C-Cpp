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
