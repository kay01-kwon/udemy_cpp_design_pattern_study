#include "Person.hpp"

using std::cout;
using std::endl;

class Person::PersonImpl
{
    public:
    void greet(Person *p);

    private:

    void stuff()
    {
        cout << "stuff" << endl;
    }
};

void Person::PersonImpl::greet(Person *p)
{
    cout << "Hello, my name is " << p->name_ << endl;
}

Person::Person()
: impl(new PersonImpl)
{

}

Person::Person(const string &name)
: name_(name), impl(new PersonImpl)
{
    
}

Person::~Person()
{
    delete impl;
}

void Person::greet()
{
    impl->greet(this);

}