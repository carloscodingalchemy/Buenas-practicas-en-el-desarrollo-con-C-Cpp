class IUART {
public:
    virtual void send(const std::string& data) = 0;
    virtual std::string receive() = 0;
    virtual ~IUART() = default;
};


class UART : public IUART {
public:
    UART(int baudrate) : baudrate(baudrate) {}

    void send(const std::string& data) override {
        // Implementation to send data over UART
    }

    std::string receive() override {
        // Implementation to receive data from UART
        return "some data";
    }

private:
    int baudrate;
};


class IModem {
public:
    virtual void sendATCommand(const std::string& command) = 0;
    virtual std::string readATResponse() = 0;
    virtual ~IModem() = default;
};


class LoRaModem : public IModem {
public:
    LoRaModem(IUART& uart) : uart(uart) {}

    void sendATCommand(const std::string& command) override {
        uart.send(command);
    }

    std::string readATResponse() override {
        return uart.receive();
    }

private:
    IUART& uart;  // Dependency on the IUART interface
};


class LoRaWANManager {
public:
    LoRaWANManager(IModem& modem) : modem(modem) {}

    void joinNetwork(const std::string& appEui, const std::string& appKey) {
        std::string command = "AT+JOIN=" + appEui + "," + appKey;
        modem.sendATCommand(command);
        std::string response = modem.readATResponse();
        // Handle the response from the network join attempt
    }

    void sendMessage(const std::string& message) {
        std::string command = "AT+SEND=" + message;
        modem.sendATCommand(command);
        std::string response = modem.readATResponse();
        // Handle the response to the send command
    }

    void receiveMessage() {
        modem.sendATCommand("AT+RECV");
        std::string message = modem.readATResponse();
        // Handle the received message
    }

private:
    IModem& modem;  // Dependency on the IModem interface
};
