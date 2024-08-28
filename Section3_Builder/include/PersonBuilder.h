#ifndef PERSON_BUILDER_H
#define PERSON_BUILDER_H
#include "Person.h"

using std::move;

class PersonJobBuilder;
class PersonAddressBuilder;

class PersonBuilderBase
{
    public:

    PersonBuilderBase(Person &person);

    operator Person() const
    {
        return std::move(person_);
    }

    PersonAddressBuilder lives() const;
    PersonJobBuilder works() const;

    protected:
    Person &person_;



};

class PersonBuilder: public PersonBuilderBase
{
    public:
    PersonBuilder();


    private:

    Person p;

};

#endif