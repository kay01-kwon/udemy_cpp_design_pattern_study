#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>

using std::string;
using std::ostream;


class PersonBuilder;

class Person
{
    public:

    static PersonBuilder create();

    friend ostream& operator<<(ostream& os, const Person& obj);

    friend class PersonBuilder;
    friend class PersonJobBuilder;
    friend class PersonAddressBuilder;

    private:

    // Address
    string street_address, post_code, city;

    // Employment
    string company_name, position;
    int annual_income{0};

};


#endif