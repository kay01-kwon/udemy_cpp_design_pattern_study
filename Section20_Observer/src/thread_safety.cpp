#include <iostream>
#include <string>
#include <vector>
#include "SaferObservable.hpp"
#include "Observer.hpp"

using std::cout;
using std::endl;
using std::string;
using std::vector;



class Person : public SaferObservable<Person>
{
    public:
    
    Person() : age_(0) {}
    Person(int age) : age_(age) {}

    int get_age() const
    {
        return age_;
    }

    void set_age(int age)
    {
        if (age_ == age)
            return;
        
        auto old_can_vote = get_can_vote();
        age_ = age;
        notify(*this, "age");

        if(old_can_vote != get_can_vote())
            notify(*this, "can_vote");
    }

    bool get_can_vote() const
    {
        return age_ >= 16;
    }

    private:
    int age_;
};

struct ConsolePersonObserver : public Observer<Person>
{
    void field_changed(Person &src, const string &field_name) override
    {
        cout << "Person's " << field_name << " has changed to ";
        if(field_name == "age")
            cout << src.get_age();
        else if(field_name == "can_vote")
            cout << std::boolalpha << src.get_can_vote();
        cout << endl;
    }
};

struct TrafficAdministration : Observer<Person>
{
    void field_changed(Person &src, const string &field_name) override
    {
        if(field_name == "age")
        {
            if(src.get_age() < 17)
                cout << "Whoa there, you're not old enough to drive!" << endl;
            else
            {
                cout << "You can drive now!" << endl;
                src.unsubscribe(*this);
            }
        }
    }


};

int main()
{
    // Person p;
    // ConsolePersonObserver cpo;
    // p.subscribe(cpo);

    // p.set_age(10);
    // p.set_age(20);

    Person p;
    TrafficAdministration ta;
    p.subscribe(ta);

    p.set_age(15);
    p.set_age(16);
    try{
        p.set_age(17);
    }
    catch(const std::exception &e)
    {
        cout << "Ooops, " << e.what() << endl;
    }


    

    return 0;
}