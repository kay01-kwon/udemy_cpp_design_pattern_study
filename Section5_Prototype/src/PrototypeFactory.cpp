#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>
#include <sstream>
#include <memory>
#include <cmath>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::ostream;
using std::unique_ptr;
using std::make_unique;


struct Address{

    Address(const string &street, const string &city, int suite)
    : street_(street), city_(city), suite_(suite) {}

    Address(const Address &other_address)
    : street_(other_address.street_),
    city_(other_address.city_),
    suite_(other_address.suite_)
    {

    }

    string street_;
    string city_;
    int suite_;

    friend ostream& operator<<(ostream &os, const Address &address)
    {
        os << " Street: " << address.street_ 
        << " City: " << address.city_
        << " Suite: " << address.suite_
        << endl;

        return os;
    }

};

struct Contact{

    Contact(const string &name, Address *address)
    : name_(name), address_(address) {}

    // Deep copy constructor 1
    // Contact(const Contact &other)
    // : name_(other.name_), address_(new Address{other.address_->street_,
    // other.address_->city_, other.address_->suite_})
    // {
    // }

    // Deep copy constructor 2
    Contact(const Contact &other)
    : name_(other.name_), address_(new Address(*other.address_)) {}

    ~Contact()
    {
        delete address_;
    }

    string name_;
    Address *address_;

    friend ostream& operator<<(ostream &os, const Contact &contact)
    {
        os << " Name: " << contact.name_
        << " Address: " << *(contact.address_);

        return os;
    }

};

struct EmployeeFactory
{
    static unique_ptr<Contact> new_main_office_employee(const string &name, int suite)
    {
        static Contact p("", new Address("123 East Dr", "London", 0));
        return new_employee(name, suite, p);
    }
    private:
    static unique_ptr<Contact> new_employee(const string &name, int suite, const Contact &prototype)
    {
        auto result = make_unique<Contact>(prototype);
        result->name_ = name;
        result->address_->suite_ = suite;
        return result;
    }
};


int main()
{
    auto john = EmployeeFactory::new_main_office_employee("John", 123);
    cout << *john << endl;
    return 0;
}