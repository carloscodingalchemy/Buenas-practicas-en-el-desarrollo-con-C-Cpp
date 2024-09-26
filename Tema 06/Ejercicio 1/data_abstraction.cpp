#include <iostream>
#include <string>
using namespace std;

// Ejercicio: Añadir el código necesario para que la clase LoRaModem almacene estadisticas de fallos en transmision y recepción
//            y las muestre cuando se llama al metodo displayModemInfo()

// LoRaModem class to abstract LoRa modem behavior
class LoRaModem {
private:
    // Private data members - hidden from outside the class
    string deviceID;
    double frequency; // Frequency in MHz
    int powerLevel;   // Power level in dBm
    bool isConnected; // Modem connection status

    // Simulated method for internal communication (not exposed publicly)
    void connectToNetwork() {
        if (!isConnected) {
            // Simulate network connection
            isConnected = true;
            cout << "LoRa Modem (" << deviceID << ") connected to network on " << frequency << " MHz.\n";
        }
    }

public:
    // Constructor to initialize modem with device ID, frequency, and power level
    LoRaModem(string id, double freq, int power)
        : deviceID(id), frequency(freq), powerLevel(power), isConnected(false) {
    }

    // Public method to configure modem settings (frequency and power level)
    void configureModem(double freq, int power) {
        if (freq > 0 && power >= 0) {
            frequency = freq;
            powerLevel = power;
            cout << "LoRa Modem configured to " << frequency << " MHz and power level " << powerLevel << " dBm.\n";
        } else {
            cout << "Invalid frequency or power level.\n";
        }
    }

    // Public method to send data through the modem
    void sendData(string data) {
        if (!isConnected) {
            connectToNetwork(); // Ensure modem is connected before sending data
        }
        cout << "Sending data: \"" << data << "\" from LoRa Modem (" << deviceID << ")...\n";
    }

    // Public method to receive data from the modem
    void receiveData() {
        if (isConnected) {
            cout << "Receiving data from LoRa Modem (" << deviceID << ")...\n";
            // Simulated received data
            cout << "Data received: \"Hello from LoRa Network!\"\n";
        } else {
            cout << "Modem is not connected to the network.\n";
        }
    }

    // Public method to check the connection status
    bool checkConnectionStatus() const {
        return isConnected;
    }

    // Public method to display modem information
    void displayModemInfo() const {
        cout << "Device ID: " << deviceID << "\n";
        cout << "Frequency: " << frequency << " MHz\n";
        cout << "Power Level: " << powerLevel << " dBm\n";
        cout << "Connection Status: " << (isConnected ? "Connected" : "Not Connected") << "\n";
    }
};

int main() {
    // Creating an object of LoRaModem class
    LoRaModem myModem("LoRa1234", 915.0, 14);

    // Accessing public methods, not private members directly
    myModem.displayModemInfo();

    // Configure the modem
    myModem.configureModem(868.0, 20);

    // Send and receive data
    myModem.sendData("Temperature: 25°C");
    myModem.receiveData();

    // Check the connection status
    if (myModem.checkConnectionStatus()) {
        cout << "Modem is connected to the network.\n";
    } else {
        cout << "Modem is not connected to the network.\n";
    }

    return 0;
}
