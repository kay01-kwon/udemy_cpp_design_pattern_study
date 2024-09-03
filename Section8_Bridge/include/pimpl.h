#ifndef PIMPL_H
#define PIMPL_H

#include <iostream>
#include <string>
#include <memory>


template <typename T>
class Pimpl
{
    public:

    Pimpl();

    ~Pimpl();

    template <typename ... Args> Pimpl(Args&& ...args);

    T* operator->();
    T& operator*();


    private:

    std::unique_ptr<T> impl_;

};

#endif

template <typename T>
inline Pimpl<T>::Pimpl()
:impl_(nedw T())
{
    
}

template <typename T>
inline Pimpl<T>::~Pimpl()
{

}

template <typename T>
inline T *Pimpl<T>::operator->()
{
    return impl.get();
}

template <typename T>
inline T &Pimpl<T>::operator*()
{
    // TODO: insert return statement here
    return *impl_.get();
}

template <typename T>
template <typename... Args>
inline Pimpl<T>::Pimpl(Args &&...args)
: impl_(new T(std::forward<Args>(args)...))
{

}
