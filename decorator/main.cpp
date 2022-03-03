//
// Created by Gustavo on 2/23/22.
//

#include <string>
#include <iostream>
#include <vector>
#include <memory>

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
    std::unique_ptr<Beverage> beverage;
public:
    explicit Decorator(std::unique_ptr<Beverage> new_beverage) : beverage{std::move(new_beverage)} {}

    [[nodiscard]] double get_beverage_cost() const { return beverage->cost(); };

    [[nodiscard]] std::string get_beverage_description() const { return beverage->description(); };

    ~Decorator() override = default;
};

// Concrete decorators
class Mocha : public Decorator {
public:
    explicit Mocha(std::unique_ptr<Beverage> new_beverage) : Decorator(std::move(new_beverage)) {}

    [[nodiscard]] std::string description() const override { return get_beverage_description() + ", Mocha"; }

    [[nodiscard]] double cost() const override { return get_beverage_cost() + 0.3; }

    ~Mocha() override = default;
};

class Soy : public Decorator {
public:
    explicit Soy(std::unique_ptr<Beverage> new_beverage) : Decorator(std::move(new_beverage)) {}

    [[nodiscard]] std::string description() const override { return get_beverage_description() + ", Soy"; }

    [[nodiscard]] double cost() const override { return get_beverage_cost() + 0.5; }

    ~Soy() override = default;
};

class Whip : public Decorator {
public:
    explicit Whip(std::unique_ptr<Beverage> new_beverage) : Decorator(std::move(new_beverage)) {}

    [[nodiscard]] std::string description() const override { return get_beverage_description() + ", Whip"; }

    [[nodiscard]] double cost() const override { return get_beverage_cost() + 0.3; }

    ~Whip() override = default;
};

int main() {

    std::vector<std::unique_ptr<Beverage>> orders;
    orders.push_back(std::make_unique<Soy>(std::make_unique<Mocha>(std::make_unique<HouseBlend>())));
    orders.push_back(std::make_unique<Whip>(std::make_unique<Mocha>(std::make_unique<DarkRoast>())));
    orders.push_back(std::make_unique<Whip>(std::make_unique<Soy>(std::make_unique<Espresso>())));

    for (const auto &order: orders) {
        static int order_num = 1;
        std::cout << "Order #" << order_num << ": " << order->description()
                  << " - $" << order->cost() << '\n';
        ++order_num;
    }

    return 0;
}