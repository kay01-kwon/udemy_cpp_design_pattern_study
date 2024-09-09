#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <functional>

#include <boost/signals2.hpp>

using std::cout;
using std::endl;
using std::string;
using std::vector;

using namespace boost;
using namespace boost::signals2;

template <typename T>
class Observer
{
    public:
    virtual void field_changed(T& src, const string &field_name) = 0;
    virtual ~Observer() = default;
};

template <typename T>
class Observable
{
    public:
    signal<void(T&, const string &)> field_changed;
};

class Person : public Observable<Person>
{
    public:
    Person(): age_(0){}

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
        field_changed(*this, "age");
    }


    private:
    int age_;

};


int main()
{
    Person person(10);
    auto conn = person.field_changed.connect(
        [] (Person &p, const string &field_name)
        {
            cout << "Person's " << field_name << " has changed to ";
            if (field_name == "age")
            {
                cout << p.get_age();
            }
            cout << endl;
        }
    );

    person.set_age(20);
    conn.disconnect();

    return 0;
}