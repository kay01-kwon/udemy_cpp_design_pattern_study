#ifndef HOTDRINK_H
#define HOTDRINK_H

#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::unique_ptr;
using std::make_unique;


struct HotDrink
{
    virtual ~HotDrink() = default;
    virtual void prepare(int volume) = 0;
};

struct Tea: HotDrink
{
    void prepare(int volume) override
    {
        cout << "Take tea bag, boil water, pour "
        << " " << volume << "ml, add some lemon" << endl;
    }

};

struct Coffee: HotDrink
{
    void prepare(int volume) override
    {
        cout << "Grind some beans, boil water, pour "
        << " " << volume << "ml, add cream and sugar" << endl;
    }
};

#endif