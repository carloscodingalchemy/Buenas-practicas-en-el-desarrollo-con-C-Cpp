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
