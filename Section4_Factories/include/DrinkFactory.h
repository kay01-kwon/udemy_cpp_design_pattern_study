#ifndef DRINK_FACTORY_H
#define DRINK_FACTORY_H

#include "HotDrink.h"
#include "HotDrinkFactory.h"
#include <string>
#include <map>
#include <functional>

using std::map;
using std::string;
using std::function;

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

class DrinkWithVolumeFactory
{
    public:

    DrinkWithVolumeFactory()
    {
        factories["tea"] = [] {
            auto tea = make_unique<Tea>();
            tea->prepare(200);
            return tea;
        };

        factories["coffee"] = []{
            auto coffee = make_unique<Coffee>();
            coffee->prepare(50);
            return coffee;
        };
    }

    unique_ptr<HotDrink> make_drink(const string& name)
    {
        return factories[name]();
    }


    private:

    map<string, function<unique_ptr<HotDrink>()>> factories;

};



#endif