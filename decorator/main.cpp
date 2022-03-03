//
// Created by Gustavo on 2/23/22.
//

#include <string>
#include <iostream>
#include <vector>

// Base beverage class
class Beverage {
public:
    [[nodiscard]] virtual std::string description() const = 0;

    [[nodiscard]] virtual double cost() const = 0;

    virtual ~Beverage() = default;
};

// Concrete beverages
class Espresso : public Beverage {
public:
    [[nodiscard]] std::string description() const override { return "Espresso"; }

    [[nodiscard]] double cost() const override { return 1.5; }

    ~Espresso() override = default;
};

class DarkRoast : public Beverage {
public:
    [[nodiscard]] std::string description() const override { return "Dark Roast"; }

    [[nodiscard]] double cost() const override { return 2.0; }

    ~DarkRoast() override = default;
};

class HouseBlend : public Beverage {
public:
    [[nodiscard]] std::string description() const override { return "House Blend"; }

    [[nodiscard]] double cost() const override { return 2.5; }

    ~HouseBlend() override = default;
};

// Base decorator class
class Decorator : public Beverage {
private:
    Beverage *beverage;
public:
    explicit Decorator(Beverage *new_beverage) : beverage{new_beverage} {}

    [[nodiscard]] Beverage *get_beverage() const { return beverage; };

    ~Decorator() override = default;
};

// Concrete decorators
class Mocha : public Decorator {
public:
    explicit Mocha(Beverage *new_beverage) : Decorator(new_beverage) {}

    [[nodiscard]] std::string description() const override { return get_beverage()->description() + ", Mocha"; }

    [[nodiscard]] double cost() const override { return get_beverage()->cost() + 0.3; }

    ~Mocha() override = default;
};

class Soy : public Decorator {
public:
    explicit Soy(Beverage *new_beverage) : Decorator(new_beverage) {}

    [[nodiscard]] std::string description() const override { return get_beverage()->description() + ", Soy"; }

    [[nodiscard]] double cost() const override { return get_beverage()->cost() + 0.5; }

    ~Soy() override = default;
};

class Whip : public Decorator {
public:
    explicit Whip(Beverage *new_beverage) : Decorator(new_beverage) {}

    [[nodiscard]] std::string description() const override { return get_beverage()->description() + ", Whip"; }

    [[nodiscard]] double cost() const override { return get_beverage()->cost() + 0.3; }

    ~Whip() override = default;
};

int main() {

    std::vector<Beverage *> orders;
    orders.push_back(new Soy(new Mocha(new Espresso())));
    orders.push_back(new Whip(new Mocha(new DarkRoast())));
    orders.push_back(new Whip(new Soy(new HouseBlend())));

    for (auto order : orders) {
        static int order_num = 1;
        std::cout << "Order #" << order_num << ": " << order->description()
                  << " - $" << order->cost() << '\n';
        ++order_num;
        delete order;
    }

    return 0;
}