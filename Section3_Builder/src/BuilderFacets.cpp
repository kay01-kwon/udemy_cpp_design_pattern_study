#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>
#include <sstream>
#include <memory>

#include "Person.h"
#include "PersonBuilder.h"
#include "PersonJobBuilder.h"
#include "PersonAddressBuilder.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;



int main()
{
    Person p = Person::create()
    .lives().at("123 London Road").with_postcode("SW1 1GB").in("London")
    .works().at("PragmaSoft").as_a("Consultant").earning(10e6);

    cout << p << endl;

    return 0;
}