#ifndef HOT_DRINK_FACTORY_H
#define HOT_DRINK_FACTORY_H

#include "HotDrink.h"

struct HotDrinkFactory  // Abstract Factory
{
    virtual unique_ptr<HotDrink> make() const = 0;

};

struct TeaFactory: HotDrinkFactory
{
    unique_ptr<HotDrink> make() const override
    {
        return make_unique<Tea>();
    }
};

struct CoffeeFactory: HotDrinkFactory
{
    unique_ptr<HotDrink> make() const override
    {
        return make_unique<Coffee>();
    }
};

#endif  // HOT_DRINK_FACTORY_H