#include <iostream>
#include <vector>
#include "Observer.hpp"
#include "Observable.hpp"
using std::cout;
using std::endl;
using std::vector;

class Person : public Observable<Person>  // Observable
{
    public:

    Person() = delete;

    Person(int age): age_(age){}

    int get_age() const
    {
        return age_;
    }

    void set_age(int age)
    {
        if(age_ == age)
            return;
        
        age_ = age;
        notify(*this, "age");
    }

    private:
    int age_;
};

// Observer and observable
struct ConsolePersonObserver : public Observer<Person>
{
    void field_changed(Person &src, const string &field_name) override
    {
        cout << "Person's " << field_name << " has changed to ";
        if( field_name == "age")
        {
            cout << src.get_age();
        }
        cout << endl;
    }
};

int main()
{
    Person person(10);
    ConsolePersonObserver cpo;
    person.subscribe(cpo);

    person.set_age(11);
    person.set_age(12);

    person.unsubscribe(cpo);

    // No longer monitoring
    person.set_age(13);

    return 0;
}