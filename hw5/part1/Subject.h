//
// Created by Dell on 27/06/2023.
//

#ifndef HW5_SUBJECT_H
#define HW5_SUBJECT_H

#include <vector>
#include "OOP5EventException.h"



template<typename T>
class Subject {
public:
    Subject() = default;

    void notify(const T& param){
        for (Observer<T>* observer: observers)
        {
            observer->handleEvent(param);
        }
    }

    void addObserver(Observer<T>& observer)
    {
        for (Observer<T>* existingObserver : observers) {
            if (existingObserver == &observer) {
                throw ObserverAlreadyKnownToSubject();
            }
        }
        observers.push_back(&observer);
    }

    void removeObserver(Observer<T>& observer){
        bool found = false;
        for (size_t i = 0; i < observers.size(); ++i) {
            if (observers[i] == &observer) {
                observers.erase(observers.begin() + i);
                found = true;
                break;
            }
        }
        if (!found) {
            throw ObserverUnknownToSubject();
        }
    }

    Subject<T>& operator+=(Observer<T>& observer){
        addObserver(observer);
        return *this;
    }

    Subject<T>& operator-=(Observer<T>& observer){
        removeObserver(observer);
        return *this;
    }

    Subject<T>& operator()(const T& param){
        notify(param);
        return *this;
    }

private:
    std::vector<Observer<T>*> observers;
};

#endif //HW5_SUBJECT_H
