//
// Created by Gustavo on 2/22/22.
//

#ifndef SUBJECT_H
#define SUBJECT_H

#include <list>
#include <memory>
#include "observer.h"

class Subject : public std::enable_shared_from_this<Subject> {
private:
    std::list<std::shared_ptr<Observer>> observers;

public:
    Subject() = default;

    void add_observer(const std::shared_ptr<Observer>& observer);

    void remove_observer(const std::shared_ptr<Observer>& observer);

    void notify_observers();

    virtual ~Subject() = default;
};

#endif // SUBJECT_H
