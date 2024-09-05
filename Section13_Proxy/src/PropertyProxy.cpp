#include <iostream>
#include <string>
#include <memory>

using std::cout;
using std::endl;

using std::string;

template <typename T>
struct Property
{
    T value_;

    Property(T value)
    : value_(value)
    {
        value_ = value;
    }

    operator T()
    {
        return value_;
    }

    T operator=(T new_value)
    {
        cout << " Assignment " << endl;
        return value_ = new_value;
    }
};


struct Creature
{
    // void setStrength(int value)
    // {
    //     strength = value;
    // }

    // void setAgility(int value)
    // {
    //     agility = value;
    // }

    // int getStrength() const
    // {
    //     return strength;
    // }

    // int getAgility() const
    // {
    //     return agility;
    // }

    Property<int> strength{10};
    Property<int> agility{10};
};


int main()
{
    Creature creature;
    creature.strength = 5;
    creature.agility  = 15;

    int creature_strength = creature.strength;
    int creature_agility = creature.agility;

    cout << creature_strength << endl;
    cout << creature_agility << endl;

    return 0;
}