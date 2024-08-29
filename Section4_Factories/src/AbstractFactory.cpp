#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>
#include <sstream>
#include <memory>
#include <cmath>

#include "HotDrinkFactory.h"
#include "DrinkFactory.h"

unique_ptr<HotDrink> make_drink(string type)
{
    unique_ptr<HotDrink> drink;
    if (type == "tea")
    {
        drink = make_unique<Tea>();
        drink->prepare(200);
    }
    else
    {
        drink = make_unique<Coffee>();
        drink->prepare(50);
    }
    return drink;
}

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::ostream;



int main()
{
    // auto d = make_drink("tea");

    DrinkFactory df;

    auto c = df.make_drink("coffee");
    

    return 0;
}