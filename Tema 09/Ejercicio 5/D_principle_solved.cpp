#include <iostream>
#include <string>

// Interfaz abstracta para cualquier tipo de red
class INetwork {
public:
    virtual void connect() = 0;
    virtual void sendData(const std::string& data) = 0;
    virtual void receiveData() = 0;

    virtual ~INetwork() = default;
};

// Clase de bajo nivel que maneja la red WiFi, implementa la interfaz INetwork
class WiFiNetwork : public INetwork {
private:
    std::string ssid;
    std::string password;

public:
    // Constructor que inicializa ssid y password
    WiFiNetwork(const std::string& ssid, const std::string& password)
        : ssid(ssid), password(password) {}

    // Implementación de la función connect
    void connect() override {
        std::cout << "Connecting to WiFi network: " << ssid << " with password: " << password << std::endl;
        // Lógica de conexión...
    }

    // Implementación de la función sendData
    void sendData(const std::string& data) override {
        std::cout << "Sending data: " << data << std::endl;
        // Lógica para enviar datos...
    }

    // Implementación de la función receiveData
    void receiveData() override {
        std::cout << "Receiving data..." << std::endl;
        // Lógica para recibir datos...
    }
};

// Clase de alto nivel que maneja la red, ahora usa una referencia a INetwork
class NetworkManager {
private:
    INetwork& network; // Referencia a INetwork

public:
    // El constructor acepta cualquier clase que implemente INetwork
    NetworkManager(INetwork& net) : network(net) {}

    // Delegación de la función connect a través de la referencia
    void connectToNetwork() {
        network.connect();
    }

    // Delegación de la función sendData a través de la referencia
    void sendData(const std::string& data) {
        network.sendData(data);
    }

    // Delegación de la función receiveData a través de la referencia
    void receiveData() {
        network.receiveData();
    }
};

int main() {
    // Creamos una instancia de WiFiNetwork con ssid y password
    WiFiNetwork wifi("MyNetwork", "password123");

    // Inyectamos la instancia de WiFiNetwork en el NetworkManager usando una referencia
    NetworkManager networkManager(wifi);

    // Ahora NetworkManager trabaja a través de la referencia a INetwork
    networkManager.connectToNetwork();
    networkManager.sendData("Hello, World!");
    networkManager.receiveData();

    return 0;
}
