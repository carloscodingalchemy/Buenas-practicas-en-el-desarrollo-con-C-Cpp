#include <cstdint>  // For fixed-width integer types like uint8_t, uint32_t, etc.
#include <iostream>
#include <queue>
#include <stdexcept>  // For std::runtime_error
#include <string>

// Custom exception class inherited from std::runtime_error
class QueueSizeLimitExceeded : public std::runtime_error {
public:
    // Constructor that takes an error message
    QueueSizeLimitExceeded(const std::string& message)
        : std::runtime_error(message) {}
};

class UART {
private:
    uint32_t baud_rate;          // Baud rate (32-bit unsigned integer)
    std::queue<uint8_t> tx_buffer;  // Transmission buffer (8-bit unsigned integer)
    std::queue<uint8_t> rx_buffer;  // Reception buffer (8-bit unsigned integer)
    static const size_t MAX_QUEUE_SIZE = 10;  // Maximum allowed queue size

public:
    // Constructor
    UART(uint32_t baud = 9600) : baud_rate(baud) {
        std::cout << "UART initialized with baud rate: " << baud_rate << std::endl;
    }

    // Destructor
    ~UART() {
        std::cout << "UART de-initialized" << std::endl;
    }

    // Initialize the UART interface
    void init(uint32_t baud) {
        baud_rate = baud;
        std::cout << "UART re-initialized with baud rate: " << baud_rate << std::endl;
    }

    // Write data to the transmission buffer (simulates sending data)
    void write(uint8_t data) {
        if (tx_buffer.size() >= MAX_QUEUE_SIZE) {
            throw QueueSizeLimitExceeded("TX buffer size limit exceeded!");
        }
        tx_buffer.push(data);
        std::cout << "Data written to TX buffer: " << static_cast<char>(data) << std::endl;
    }

    // Read data from the reception buffer (simulates receiving data)
    uint8_t read() {
        if (!rx_buffer.empty()) {
            uint8_t data = rx_buffer.front();
            rx_buffer.pop();
            std::cout << "Data read from RX buffer: " << static_cast<char>(data) << std::endl;
            return data;
        } else {
            std::cout << "RX buffer is empty" << std::endl;
            return 0;  // No data to read
        }
    }

    // Simulate receiving data by placing it in the RX buffer
    void receive(uint8_t data) {
        if (rx_buffer.size() >= MAX_QUEUE_SIZE) {
            throw QueueSizeLimitExceeded("RX buffer size limit exceeded!");
        }
        rx_buffer.push(data);
        std::cout << "Data received into RX buffer: " << static_cast<char>(data) << std::endl;
    }
};

int main() {
    try {
        // Create a UART object with default baud rate 9600
        UART uart;

        // Initialize with a different baud rate
        uart.init(115200);

        // Write data to UART, will throw exception if buffer exceeds limit
        for (size_t i = 0; i < 12; ++i) {
            uart.write('A' + i);  // Simulate writing characters A, B, C, ...
        }

    } catch (const QueueSizeLimitExceeded& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
