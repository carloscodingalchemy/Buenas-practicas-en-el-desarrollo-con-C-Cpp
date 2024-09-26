#include <iostream>
#include <string>

// EJERCICIO: Modificar la clase para que cumple con la "law of Demeter".

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
    Engine& getEngine() {
        return engine;
    }
};

class Driver {
public:
    void startCar(Car& car) {
        // Aquí se está violando la Ley de Demeter, porque el conductor
        // está accediendo al motor a través del coche.
        car.getEngine().start();
    }
};

int main() {
    Car car;
    Driver driver;
    driver.startCar(car);
    return 0;
}
