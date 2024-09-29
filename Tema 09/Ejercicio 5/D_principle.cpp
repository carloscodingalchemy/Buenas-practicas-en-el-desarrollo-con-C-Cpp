#include <iostream>
#include <string>

// Clase de bajo nivel que maneja la red
class WiFiNetwork {
public:
    void connect(const std::string& ssid, const std::string& password) {
        std::cout << "Connecting to WiFi network: " << ssid << std::endl;
        // Lógica de conexión...
    }

    void sendData(const std::string& data) {
        std::cout << "Sending data: " << data << std::endl;
        // Lógica para enviar datos...
    }

    void receiveData() {
        std::cout << "Receiving data..." << std::endl;
        // Lógica para recibir datos...
    }
};

// Clase de alto nivel que maneja la red
class NetworkManager {
private:
    WiFiNetwork wifi; // Dependencia directa de la clase de bajo nivel

public:
    void connectToNetwork(const std::string& ssid, const std::string& password) {
        wifi.connect(ssid, password);
    }

    void sendData(const std::string& data) {
        wifi.sendData(data);
    }

    void receiveData() {
        wifi.receiveData();
    }
};

int main() {
    NetworkManager networkManager;
    networkManager.connectToNetwork("MyNetwork", "password123");
    networkManager.sendData("Hello, World!");
    networkManager.receiveData();

    return 0;
}
