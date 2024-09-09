#ifndef OBSERVABLE_HPP
#define OBSERVABLE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::find;

template <typename T>
class Observer;


template <typename T>
class Observable
{
    public:
    void notify(T& src, const string &field_name)
    {
        for(auto observer : observers_)
        {
            observer->field_changed(src, field_name);
        }
    }

    void subscribe(Observer<T> &observer)
    {
        observers_.push_back(&observer);
    }

    void unsubscribe(Observer<T> &observer)
    {
        auto it = find(observers_.begin(),
        observers_.end(), &observer);

        if(it != observers_.end())
            observers_.erase(it);
    }

    // private:
    vector<Observer<T>*> observers_;

};


#endif // OBSERVABLE_HPP