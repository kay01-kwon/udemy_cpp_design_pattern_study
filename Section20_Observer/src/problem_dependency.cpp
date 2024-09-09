#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include "Observable.hpp"

using std::cout;
using std::endl;
using std::string;
using std::vector;

template <typename T>
class Observer
{
    public:
    virtual void field_changed(T& src, const string &field_name) = 0;
    virtual ~Observer() = default;
};

class Person : public Observable<Person>
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
        if(age_ == age)
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
        if( field_name == "age")
        {
            cout << src.get_age() << endl;
        }
        if(field_name == "can_vote")
        {
            cout << std::boolalpha << src.get_can_vote() << endl;
        }
        
    }
};

int main()
{
    Person p;
    ConsolePersonObserver cpo;
    p.subscribe(cpo);

    p.set_age(15);
    p.set_age(16);

    return 0;
}