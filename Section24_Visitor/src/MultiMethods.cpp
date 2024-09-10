#include <iostream>
#include <typeindex>
#include <map>
#include <functional>

using namespace std;

struct GameObject;
void collide(GameObject &first, GameObject &second);

struct GameObject
{
    virtual type_index type() const = 0;
    virtual void collide(GameObject &other)
    {
        ::collide(*this, other);
    }
};

// CRTP
template <typename T>
struct GameObjectImpl : GameObject
{
    type_index type() const override
    {
        return typeid(T);
    }
};


struct Planet : GameObjectImpl<Planet>
{

};

struct Asteroid : GameObjectImpl<Asteroid>
{

};

struct Spaceship : GameObjectImpl<Spaceship>
{

};

void spaceship_planet()
{
    cout << "Spaceship lands on planet" << endl;
}

void asteroid_planet()
{
    cout << "Asteroid burns up in atmosphere" << endl;
}

void asteroid_spaceship()
{
    cout << "Asteroid hits and destroys spaceship" << endl;
}

map<pair<type_index, type_index>, void(*)(void)> outcomes
{
    {{typeid(Spaceship), typeid(Planet)}, spaceship_planet},
    {{typeid(Asteroid), typeid(Planet)}, asteroid_planet},
    {{typeid(Asteroid), typeid(Spaceship)}, asteroid_spaceship}
};

void collide(GameObject &first, GameObject &second)
{
    auto it = outcomes.find({first.type(), second.type()});
    if(it == outcomes.end())
    {
        it = outcomes.find({second.type(), first.type()});
        if(it == outcomes.end())
        {
            cout << "Nothing happens" << endl;
            return;
        }
    }
    it->second();
}


int main()
{
    Spaceship spaceship;
    Planet planet;
    Asteroid asteroid;

    collide(spaceship, planet);
    collide(asteroid, planet);
    collide(asteroid, spaceship);
    collide(planet, spaceship);
    collide(planet, asteroid);
    collide(spaceship, asteroid);

    return 0;

}