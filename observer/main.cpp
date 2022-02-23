//
// Created by Gustavo on 2/22/22.
//

#include <iostream>
#include "observer.h"
#include "subject.h"

class WeatherData : public Subject {
private:
    double temperature{0.0};
    double humidity{0.0};
    double pressure{0.0};

public:
    [[nodiscard]] double get_temperature() const {
        return temperature;
    }

    [[nodiscard]] double get_humidity() const {
        return humidity;
    }

    [[nodiscard]] double get_pressure() const {
        return pressure;
    }

    void update_data(double new_temperature, double new_humidity, double new_pressure) {
        temperature = new_temperature;
        humidity = new_humidity;
        pressure = new_pressure;
        notify_observers();
    }

    ~WeatherData() override = default;
};

class Display {
public:
    virtual void display() = 0;

    virtual ~Display() = default;
};

class TemperatureDisplay : public Observer, public Display {
    double temperature{0.0};
public:
    void update() override {
        const auto *weather_data = dynamic_cast<WeatherData *>(get_subject());
        if (!weather_data) std::cerr << "The subject is not of type 'WeatherData'\n";
        temperature = weather_data->get_temperature();
        display();
    }

    void display() override {
        std::cout << "The temperature is " << temperature << " degrees\n";
    }

    ~TemperatureDisplay() override = default;
};

class HumidityDisplay : public Observer, public Display {
    double humidity{0.0};
public:
    void update() override {
        const auto *weather_data = dynamic_cast<WeatherData *>(get_subject());
        if (!weather_data) std::cerr << "The subject is not of type 'WeatherData'\n";
        humidity = weather_data->get_humidity();
        display();
    }

    void display() override {
        std::cout << "The humidity is " << humidity << " %\n";
    }

    ~HumidityDisplay() override = default;
};

class PressureDisplay : public Observer, public Display {
    double pressure{0.0};
public:
    void update() override {
        const auto *weather_data = dynamic_cast<WeatherData *>(get_subject());
        if (!weather_data) std::cerr << "The subject is not of type 'WeatherData'\n";
        pressure = weather_data->get_pressure();
        display();
    }

    void display() override {
        std::cout << "The pressure is " << pressure << " hPa\n";
    }

    ~PressureDisplay() override = default;
};

int main() {
    WeatherData weather_data;

    std::shared_ptr<Observer> t_disp = std::make_shared<TemperatureDisplay>(TemperatureDisplay());
    std::shared_ptr<Observer> h_disp = std::make_shared<HumidityDisplay>(HumidityDisplay());
    std::shared_ptr<Observer> p_disp = std::make_shared<PressureDisplay>(PressureDisplay());

    weather_data.add_observer(t_disp);
    weather_data.add_observer(h_disp);
    weather_data.add_observer(p_disp);

    weather_data.update_data(1, 1, 1);
    weather_data.update_data(2, 2, 2);

    p_disp->unsubscribe();

    weather_data.update_data(3, 3, 3);

    weather_data.add_observer(p_disp);

    weather_data.update_data(4, 4, 4);

    return 0;
}
