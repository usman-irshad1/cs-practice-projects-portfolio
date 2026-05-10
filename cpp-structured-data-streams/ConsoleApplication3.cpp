#include <iostream>
#include <string>

// ===================================
// ===== Engine Class (Composition Part) =====
// ===================================
class Engine {
private:
    int engine_id;
    int horsepower;

public:
    // Constructor to initialize the engine
    Engine(int id, int hp) : engine_id(id), horsepower(hp) {
        std::cout << "Engine " << engine_id << " has been built." << std::endl;
    }

    // Destructor to show when the engine is destroyed
    ~Engine() {
        std::cout << "-> Engine " << engine_id << " has been destroyed." << std::endl;
    }

    void display() const {
        std::cout << "  Engine ID: " << engine_id << ", Horsepower: " << horsepower << " HP" << std::endl;
    }
};

// =====================================
// ===== Driver Class (Aggregation Part) =====
// =====================================
class Driver {
private:
    std::string name;
    int license_number;

public:
    // Constructor to initialize the driver
    Driver(std::string n, int lic) : name(n), license_number(lic) {
        std::cout << "Driver " << name << " is ready to drive." << std::endl;
    }

    // Destructor to show the driver's independent lifetime
    ~Driver() {
        std::cout << "-> Driver " << name << " is going home." << std::endl;
    }

    void display() const {
        std::cout << "  Driver: " << name << ", License #: " << license_number << std::endl;
    }
};

// =====================================
// ===== Car Class (The Whole Object) ======
// =====================================
class Car {
private:
    std::string make;
    std::string model;
    Engine engine; // COMPOSITION: Engine is a direct member object
    Driver* current_driver; // AGGREGATION: Car has a pointer to a Driver

public:
    // Constructor initializes the Car and its Engine member
    Car(std::string mk, std::string mdl, int engine_id, int hp, Driver* driver)
        : make(mk), model(mdl), engine(engine_id, hp), current_driver(driver) {
        std::cout << "Car " << make << " " << model << " has been assembled." << std::endl;
    }

    // Destructor shows the car is being destroyed. The 'engine' member's destructor will be called automatically after this.
    ~Car() {
        std::cout << "-> Car " << make << " " << model << " has been sent to the junkyard." << std::endl;
    }

    void display() const {
        std::cout << "\n--- Car Details ---" << std::endl;
        std::cout << "Make & Model: " << make << " " << model << std::endl;
        engine.display();
        if (current_driver) {
            (*current_driver).display();
        }
        std::cout << "-------------------" << std::endl;
    }
};

// =====================================
// ===== Main Function Demonstration =====
// =====================================
int main() {
    // 1. Create a Driver object. It exists independently.
    Driver driver1("Alice", 12345);

    std::cout << "\n--- Creating the Car and associating the Driver ---" << std::endl;
    {
        // 2. Create a Car object in a limited scope.
        // It is COMPOSED of an Engine and has an AGGREGATION relationship with the Driver.
        Car myCar("Toyota", "Camry", 9876, 203, &driver1);
        myCar.display();

        std::cout << "\n--- The Car object is about to go out of scope ---" << std::endl;
    } // The 'myCar' object is destroyed here.

    std::cout << "\n--- The Car has been destroyed, but the Driver still exists ---" << std::endl;

    // The program ends, and now the 'driver1' object is destroyed.
    return 0;
}