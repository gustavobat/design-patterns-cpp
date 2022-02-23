//
// Created by Gustavo on 2/22/22.
//

#ifndef OBSERVER_H
#define OBSERVER_H

#include <memory>

class Subject;

class Observer : public std::enable_shared_from_this<Observer> {
    friend class Subject;

private:
    Subject *subject{nullptr};

public:
    Observer() = default;

    [[nodiscard]] Subject *get_subject() const;

    virtual void update() = 0;

    void unsubscribe();

    virtual ~Observer() = default;
};

#endif // OBSERVER_H
