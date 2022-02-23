//
// Created by Gustavo on 2/22/22.
//

#include "subject.h"

void Subject::add_observer(const std::shared_ptr<Observer>& observer) {
    if (observer->get_subject() != this) {
        observer->set_subject(this);
    }
    observers.push_back(observer);
}

void Subject::remove_observer(const std::shared_ptr<Observer>& observer) {
    observers.remove(observer);
}

void Subject::notify_observers() {
    for (const auto &observer : observers) {
        observer->update();
    }
}
