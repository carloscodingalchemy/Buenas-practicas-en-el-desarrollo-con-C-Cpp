#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <chrono>

// Simulador de la lectura de sensores
class SensorReader {
public:
    // Método que simula la recogida de datos de los sensores
    std::string read_sensor_data() {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));  // Simula tiempo de lectura
        return "sensor_data";  // Simulación de los datos obtenidos
    }
};

// Simulador de la comunicación LoRaWAN
class LoRaWANTransmitter {
public:
    // Método que simula el envío de datos al gateway
    void send_data(const std::string& data) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));  // Simula tiempo de envío
        std::cout << "Datos enviados al gateway: " << data << std::endl;
    }
};

// Clase que maneja la concurrencia y sincronización entre la lectura y el envío de datos
class DataManager {
public:
    DataManager(SensorReader& reader, LoRaWANTransmitter& transmitter) 
        : sensor_reader(reader), lorawan_transmitter(transmitter), stop_flag(false) {}

    // Método para iniciar los hilos
    void start() {
        sensor_thread = std::thread(&DataManager::sensor_task, this);
        transmit_thread = std::thread(&DataManager::transmit_task, this);
    }

    // Método para detener los hilos y limpiar los recursos
    void stop() {
        {
            std::lock_guard<std::mutex> lock(mtx);
            stop_flag = true;  // Señal para detener las tareas
        }
        cv.notify_all();  // Despertar el hilo de transmisión si está esperando
        sensor_thread.join();
        transmit_thread.join();
    }

private:
    SensorReader& sensor_reader;
    LoRaWANTransmitter& lorawan_transmitter;
    std::queue<std::string> data_queue;  // Cola para almacenar los datos leídos
    std::mutex mtx;  // Mutex para proteger la cola compartida
    std::condition_variable cv;  // Variable de condición para sincronizar los hilos
    std::thread sensor_thread;
    std::thread transmit_thread;
    bool stop_flag;

    // Tarea del hilo que lee datos de los sensores
    void sensor_task() {
        while (!stop_flag) {
            std::string data = sensor_reader.read_sensor_data();
            {
                std::lock_guard<std::mutex> lock(mtx);
                data_queue.push(data);  // Insertar datos en la cola protegida
                std::cout << "Datos del sensor leídos: " << data << std::endl;
            }
            cv.notify_one();  // Notificar al hilo de transmisión que hay datos disponibles
        }
    }

    // Tarea del hilo que envía los datos al gateway LoRaWAN
    void transmit_task() {
        while (!stop_flag) {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this] { return !data_queue.empty() || stop_flag; });  // Espera hasta que haya datos o se detenga el hilo

            if (!data_queue.empty()) {
                std::string data_to_send = data_queue.front();
                data_queue.pop();
                lock.unlock();  // Liberar el bloqueo mientras se realiza la transmisión
                lorawan_transmitter.send_data(data_to_send);  // Enviar los datos
            }
        }
    }
};

// Función principal que ejecuta la lógica del sistema embebido
int main() {
    SensorReader sensor_reader;
    LoRaWANTransmitter lorawan_transmitter;

    DataManager data_manager(sensor_reader, lorawan_transmitter);
    data_manager.start();

    // Simulación de ejecución por un tiempo determinado (5 segundos)
    std::this_thread::sleep_for(std::chrono::seconds(5));

    // Detener los hilos
    data_manager.stop();

    std::cout << "Sistema embebido detenido." << std::endl;
    return 0;
}