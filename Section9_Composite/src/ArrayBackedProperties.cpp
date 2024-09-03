#include <iostream>
#include <array>
#include <algorithm>
#include <numeric>
#include <string>

using std::cout;
using std::endl;
using std::string;

// class Creature
// {   
//     public:

//     int get_strength() const
//     {
//         return strength_;
//     }

//     int get_agility() const
//     {
//         return agility_;
//     }

//     int get_intelligence() const
//     {
//         return intelligence_;
//     }

//     void set_strenth(int strength)
//     {
//         strength_ = strength;
//     }

//     void set_agility(int agility)
//     {
//         agility_ = agility;
//     }

//     void set_intelligence(int intelligence)
//     {
//         intelligence_ = intelligence;
//     }


//     // These member functions are not a good idea
//     // because when we add a new property, 
//     // we have to add a new member function

//     double sum() const
//     {
//         return strength_ + agility_ + intelligence_;
//     }

//     double average() const
//     {
//         return sum()/3.0;
//     }

//     double max() const
//     {
//         return std::max(strength_, std::max(agility_, intelligence_));
//     }

//     private:

//     int strength_, agility_, intelligence_;

// };


class Creature
{
    public:

    int get_strength() const
    {
        return abilities[str];
    }

    int get_agility() const
    {
        return abilities[agl];
    }

    int get_intelligence() const
    {
        return abilities[intl];
    }

    void set_strength(int value)
    {
        abilities[str] = value;
    }

    void set_agility(int value)
    {
        abilities[agl] = value;
    }

    void set_intelligence(int value)
    {
        abilities[intl] = value;
    }


    double sum() const
    {
        return std::accumulate(abilities.begin(), abilities.end(), 0);
    }

    double average() const
    {
        return sum()/ (double) count;
    }

    int max() const
    {
        return *std::max_element(abilities.begin(), abilities.end());
    }

    private:
    enum Abilities {str, agl, intl, count};

    std::array<int, count> abilities;

};

int main(int argc, char **argv)
{
    Creature orc;
    orc.set_strength(16);
    orc.set_agility(11);
    orc.set_intelligence(9);

    cout << "The orc has an average stat of "
    << orc.average() 
    << " and a maximum stat of "
    << orc.max()
    << endl;


    return 0;
}
