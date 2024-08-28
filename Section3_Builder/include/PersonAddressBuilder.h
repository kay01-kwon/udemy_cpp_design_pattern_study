#ifndef PERSON_ADDRESS_BUILDER_H
#define PERSON_ADDRESS_BUILDER_H

#include "PersonBuilder.h"
#include <string>

using std::string;

class PersonAddressBuilder: public PersonBuilderBase
{
    typedef PersonAddressBuilder Self;
    public:

    PersonAddressBuilder(Person &person)
    : PersonBuilderBase(person){}

    Self& at(string street_address)
    {
        person_.street_address = street_address;
        return *this;
    }

    Self& with_postcode(string post_code)
    {
        person_.post_code = post_code;
        return *this;
    }

    Self& in(string city)
    {
        person_.city = city;
        return *this;
    }
};



#endif