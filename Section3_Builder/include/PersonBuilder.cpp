#include "PersonBuilder.h"
#include "PersonAddressBuilder.h"
#include "PersonJobBuilder.h"

PersonBuilderBase::PersonBuilderBase(Person &person): person_(person)
{
}

PersonAddressBuilder PersonBuilderBase::lives() const
{
    return PersonAddressBuilder(person_);
}

PersonJobBuilder PersonBuilderBase::works() const
{
    return PersonJobBuilder(person_);
}

PersonBuilder::PersonBuilder() : PersonBuilderBase(p)
{
}
