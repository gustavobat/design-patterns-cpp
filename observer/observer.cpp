//
// Created by Gustavo on 2/22/22.
//

#include "observer.h"
#include "subject.h"

Subject *Observer::get_subject() const {
    return subject;
}

void Observer::set_subject(Subject *new_subject) {
    subject = new_subject;
}

void Observer::unsubscribe() {
    subject->remove_observer(shared_from_this());
    subject = nullptr;
}
