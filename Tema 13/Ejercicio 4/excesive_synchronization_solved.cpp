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

    // Método que procesa los datos, reduciendo la sincronización
    void processData() {
        std::vector<int> localData(data.size());  // Procesamiento en una copia local

        // Simula un procesamiento lento de datos
        for (int i = 0; i < localData.size(); ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));  // Simula trabajo pesado
            localData[i] = i * 2;
        }

        // Bloqueo reducido solo para la actualización del recurso compartido
        {
            std::lock_guard<std::mutex> lock(mtx);
            data = localData;  // Actualización crítica
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
