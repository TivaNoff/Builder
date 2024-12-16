#include <iostream>
#include <string>
#include <memory>

// Клас, який представляє продукт - Автомобіль
class Car {
public:
    void setWheels(const std::string& wheels) { wheels_ = wheels; }
    void setEngine(const std::string& engine) { engine_ = engine; }
    void setBody(const std::string& body) { body_ = body; }

    void specifications() const {
        std::cout << "Car Specifications: " << std::endl;
        std::cout << " Body: " << body_ << std::endl;
        std::cout << " Engine: " << engine_ << std::endl;
        std::cout << " Wheels: " << wheels_ << std::endl;
    }

private:
    std::string wheels_;
    std::string engine_;
    std::string body_;
};

// Абстрактний будівельник
class CarBuilder {
public:
    virtual ~CarBuilder() = default;
    virtual void buildBody() = 0;
    virtual void buildEngine() = 0;
    virtual void buildWheels() = 0;
    virtual std::unique_ptr<Car> getCar() = 0;
};

// Конкретний будівельник для спортивного автомобіля
class SportsCarBuilder : public CarBuilder {
public:
    SportsCarBuilder() {
        car_ = std::make_unique<Car>();
    }

    void buildBody() override {
        car_->setBody("Sleek body");
    }

    void buildEngine() override {
        car_->setEngine("V8 engine");
    }

    void buildWheels() override {
        car_->setWheels("18-inch low-profile wheels");
    }

    std::unique_ptr<Car> getCar() override {
        return std::move(car_);
    }

private:
    std::unique_ptr<Car> car_;
};

// Конкретний будівельник для позашляховика (SUV)
class SUVBuilder : public CarBuilder {
public:
    SUVBuilder() {
        car_ = std::make_unique<Car>();
    }

    void buildBody() override {
        car_->setBody("Rugged SUV body");
    }

    void buildEngine() override {
        car_->setEngine("V6 engine");
    }

    void buildWheels() override {
        car_->setWheels("17-inch all-terrain wheels");
    }

    std::unique_ptr<Car> getCar() override {
        return std::move(car_);
    }

private:
    std::unique_ptr<Car> car_;
};

// Директор, який визначає порядок побудови
class Director {
public:
    void setBuilder(CarBuilder* builder) {
        builder_ = builder;
    }

    std::unique_ptr<Car> buildCar() {
        if (!builder_) {
            return nullptr;
        }
        builder_->buildBody();
        builder_->buildEngine();
        builder_->buildWheels();
        return builder_->getCar();
    }

private:
    CarBuilder* builder_ = nullptr;
};

int main() {
    Director director;

    // Створення спортивного автомобіля
    SportsCarBuilder sportsBuilder;
    director.setBuilder(&sportsBuilder);
    auto sportsCar = director.buildCar();
    sportsCar->specifications();

    // Створення позашляховика
    SUVBuilder suvBuilder;
    director.setBuilder(&suvBuilder);
    auto suvCar = director.buildCar();
    suvCar->specifications();

    return 0;
}
