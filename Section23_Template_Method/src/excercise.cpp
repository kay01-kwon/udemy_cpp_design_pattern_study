#include <iostream>
#include <vector>
#include <complex>
#include <tuple>
#include <cassert>

using namespace std;

struct Creature{

    int attack_, health_;

    Creature(int attack, int health)
    : health_(health), attack_(attack) {}

};

struct CardGame
{
    public:

    CardGame(const vector<Creature> &creatures)
    : creatures_(creatures) {}

    int combat(int creature1, int creature2)
    {
        Creature &first = creatures_[creature1];
        Creature &second = creatures_[creature2];
        hit(first, second);
        hit(second, first);
        bool first_alive = first.health_ > 0;
        bool second_alive = second.health_ > 0;
        if (first_alive == second_alive)
            return -1;
        return first_alive ? creature1 : creature2;
    }

    virtual void hit(Creature &attacker, Creature &other) = 0;

    private:
    vector<Creature> creatures_;

};

struct TemporaryCardDamageGame : CardGame
{
    public:

    TemporaryCardDamageGame(const vector<Creature> &creatures) 
    : CardGame(creatures) {}

    void hit(Creature &attacker, Creature &other) override
    {
        if(other.health_ <= attacker.attack_)
            other.health_  -= attacker.attack_;
    }

    private:

};

struct PermanentCardDamageGame : CardGame
{
    public:

    PermanentCardDamageGame(const vector<Creature> &creatures) : CardGame(creatures) {}

    void hit(Creature &attacker, Creature &other) override
    {
        other.health_ -= attacker.attack_;
    }

    private:

};

int main()
{
    Creature c1(1, 2);
    Creature c2(1, 2);

    TemporaryCardDamageGame temp_game({c1, c2});

    // assert(temp_game.combat(0, 1) == -1);

    cout << "Temporary combat result: " 
    << temp_game.combat(0, 1) << endl;

    cout << "Temporary combat result: " 
    << temp_game.combat(0, 1) << endl;




    return 0;
}