//
// Created by Gustavo on 2/23/22.
//

#include <string>
#include <iostream>
#include <vector>

class Beverage {
public:
    virtual std::string description() = 0;

    virtual double cost() = 0;

    virtual ~Beverage() = default;
};

class Espresso : public Beverage {
public:
    std::string description() override { return "Espresso"; }

    double cost() override { return 1.5; }

    ~Espresso() override = default;
};

class DarkRoast : public Beverage {
public:
    std::string description() override { return "Dark Roast"; }

    double cost() override { return 2.0; }

    ~DarkRoast() override = default;
};

class HouseBlend : public Beverage {
public:
    std::string description() override { return "House Blend"; }

    double cost() override { return 2.5; }

    ~HouseBlend() override = default;
};

class Decorator : public Beverage {
private:
    Beverage *beverage;
public:
    explicit Decorator(Beverage *new_beverage) : beverage{new_beverage} {}

    Beverage *get_beverage() { return beverage; };

    ~Decorator() override = default;
};

class Mocha : public Decorator {
public:
    explicit Mocha(Beverage *new_beverage) : Decorator(new_beverage) {}

    std::string description() override { return get_beverage()->description() + ", Mocha"; }

    double cost() override { return get_beverage()->cost() + 0.3; }

    ~Mocha() override = default;
};

class Soy : public Decorator {
public:
    explicit Soy(Beverage *new_beverage) : Decorator(new_beverage) {}

    std::string description() override { return get_beverage()->description() + ", Soy"; }

    double cost() override { return get_beverage()->cost() + 0.5; }

    ~Soy() override = default;
};

class Whip : public Decorator {
public:
    explicit Whip(Beverage *new_beverage) : Decorator(new_beverage) {}

    std::string description() override { return get_beverage()->description() + ", Whip"; }

    double cost() override { return get_beverage()->cost() + 0.3; }

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