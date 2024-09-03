#ifndef PERSON_HPP
#define PERSON_HPP
#include <iostream>
#include <string>

using std::string;

class Person
{
    public:

    class PersonImpl;
    
    friend class PersonImpl;

    PersonImpl *impl;

    Person();

    Person(const string &name);
    ~Person();

    void greet();

    private:

    string name_;

    void secret() {}

};


#endif