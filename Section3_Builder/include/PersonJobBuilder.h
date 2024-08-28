#ifndef PERSON_JOB_BUILDER_H
#define PERSON_JOB_BUILDER_H

#include <string>
#include "PersonBuilder.h"

using std::string;

class PersonJobBuilder: public PersonBuilderBase
{
    typedef PersonJobBuilder Self;

    public:
    explicit PersonJobBuilder(Person &person): PersonBuilderBase(person){}

    Self& at(string company_name)
    {
        person_.company_name = company_name;
        return *this;
    }

    Self& as_a(string position)
    {
        person_.position = position;
        return *this;
    }

    Self& earning(int annual_income)
    {
        person_.annual_income = annual_income;
        return *this;
    }

};

#endif