//
// Created by Dell on 27/06/2023.
//

#ifndef HW5_OBSERVER_H
#define HW5_OBSERVER_H

template<typename T>
class Observer {
public:
    Observer() = default;
    virtual void handleEvent(const T&) = 0;
};

#endif //HW5_OBSERVER_H
