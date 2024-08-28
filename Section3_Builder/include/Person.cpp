#include "Person.h"
#include "PersonBuilder.h"

PersonBuilder Person::create()
{
    return PersonBuilder();
}

ostream &operator<<(ostream &os, const Person &obj)
{
    os << "street_address: " << obj.street_address <<
    " post_code: " << obj.post_code <<
    " city: " << obj.city <<
    " company_name: " << obj.company_name <<
    " position: " << obj.position <<
    " annual_income: " << obj.annual_income;

    return os;
}
