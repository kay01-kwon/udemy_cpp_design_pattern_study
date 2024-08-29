#ifndef DRINK_FACTORY_H
#define DRINK_FACTORY_H

#include "HotDrink.h"
#include "HotDrinkFactory.h"
#include <string>
#include <map>

using std::map;
using std::string;

class DrinkFactory
{
    public:

    DrinkFactory()
    {
        hot_factories["coffee"] = make_unique<CoffeeFactory>();
        hot_factories["tea"] = make_unique<TeaFactory>();
    }

    unique_ptr<HotDrink> make_drink(const string& name)
    {
        auto drink = hot_factories[name]->make();
        drink->prepare(200);

        return drink;
    }

    private:
    map<string, unique_ptr<HotDrinkFactory>> hot_factories;

};



#endif