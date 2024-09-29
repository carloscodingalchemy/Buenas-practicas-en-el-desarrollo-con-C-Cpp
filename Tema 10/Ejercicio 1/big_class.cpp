class LoRaWANManager {
public:
    void joinNetwork(const std::string& appEui, const std::string& appKey);
    void sendMessage(const std::string& message);
    void receiveMessage();
    void sendATCommand(const std::string& command);
    std::string readATResponse();
    void initializeUART(int baudrate);
    void sendUART(const std::string& data);
    std::string receiveUART();

private:
    std::string uartBuffer;
    int baudrate;
    std::string appEui;
    std::string appKey;
};
