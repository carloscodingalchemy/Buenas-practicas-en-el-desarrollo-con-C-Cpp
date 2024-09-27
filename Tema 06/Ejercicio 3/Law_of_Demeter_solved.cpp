#include <iostream>
#include <string>

class Engine {
public:
    void start() const {
        std::cout << "Engine started" << std::endl;
    }
};

class Car {
private:
    Engine engine;  // La clase Car tiene un motor (Engine)
public:
    void start() {
        // Ahora el coche se encarga de arrancar el motor
        engine.start();
    }
};

class Driver {
public:
    void startCar(Car& car) {
        // Ahora el conductor solo interactúa con el coche, no con el motor
        car.start();
    }
};

int main() {
    Car car;
    Driver driver;
    driver.startCar(car);
    return 0;
}
