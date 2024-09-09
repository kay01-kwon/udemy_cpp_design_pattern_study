#ifndef SAFEROBSERVABLE_HPP
#define SAFEROBSERVABLE_HPP

#include <string>
#include <vector>
#include <algorithm>
#include <mutex>

using std::string;
using std::vector;
using std::find;

template <typename T>
class Observer;

template <typename T>
class SaferObservable{

    typedef std::recursive_mutex mutex_t;

    public:

    void notify(T& src, const string &field_name)
    {
        std::scoped_lock<mutex_t> lock{mtx_};
        for(auto observer : observers_)
            observer->field_changed(src, field_name);
    }


    void subscribe(Observer<T> &observer)
    {
        std::scoped_lock<mutex_t> lock{mtx_};
        observers_.push_back(&observer);
    }

    void unsubscribe(Observer<T> &observer)
    {
        auto it = find(observers_.begin(), 
                    observers_.end(),
                    &observer);
        if(it != observers_.end())
            *it = nullptr;
    }

    private:

    vector<Observer<T>*> observers_;
    mutex_t mtx_;
};


#endif // SAFEROBSERVABLE_HPP