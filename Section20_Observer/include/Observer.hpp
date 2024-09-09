#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include <iostream>
#include <string>

using std::string;

template <typename T>
class Observer
{
    public:
    virtual void field_changed(T& src, const string &field_name) = 0;
    virtual ~Observer() = default;

};



#endif // OBSERVER_HPP