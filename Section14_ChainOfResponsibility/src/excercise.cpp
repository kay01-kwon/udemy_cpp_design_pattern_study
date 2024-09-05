#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

struct Creature;
struct Game
{
  vector<Creature*> creatures;
};

struct StatQuery
{
  enum Statistic { attack, defense };
  Statistic statistic;
  int result;
};

struct Creature
{
protected:
  Game& game;
  int base_attack, base_defense;

public:
  Creature(Game &game, int base_attack, int base_defense) : game(game), base_attack(base_attack),
                                                            base_defense(base_defense) {}
  virtual int get_attack() = 0;
  virtual int get_defense() = 0;
  virtual void query(void *source, StatQuery &sq) = 0;
};

class Goblin : public Creature
{
public:
    Goblin(Game &game, int base_attack, int base_defense) : Creature(game, base_attack, base_defense) {}
    
    Goblin(Game &game) : Creature(game, 1, 1) {}

    int get_attack() override {
        // todo
        return get_statistic(StatQuery::attack);
    }

    int get_defense() override {
        // todo
        return get_statistic(StatQuery::defense);
    }

    int get_statistic(StatQuery::Statistic stat)
    {
        StatQuery q{stat, 0};
        for (auto c : game.creatures)
            c->query(this, q);
        return q.result;
    }

    void query(void *source, StatQuery &sq) override
    {
        if(source == this)
        {
            switch(sq.statistic)
            {
                case StatQuery::attack:
                    sq.result += base_attack;
                    break;
                case StatQuery::defense:
                    sq.result += base_defense;
                    break;
                default:
                    break;
            }
        }
        else
        {
            if(sq.statistic == StatQuery::defense)
                sq.result++;
        }
    }

};

class GoblinKing : public Goblin
{
public:
  GoblinKing(Game &game) : Goblin(game, 3, 3) {}

  // todo
    void query(void *source, StatQuery &sq) override
    {
        if(source != this && sq.statistic == StatQuery::attack)
        {
            sq.result++;
        }
        else
        {
            Goblin::query(source, sq);
        }
    }
};

int main()
{
    Game game;
    Goblin goblin(game);
    game.creatures.push_back(&goblin);

    cout <<" Checking that a baseline goblin is a 1/1..." 
    << endl;

    cout << " Goblin1: " << goblin.get_attack() << " / "
    << goblin.get_defense() << endl;


    cout << " Adding a second goblin, "
    << "now they should be 1/2 ..." << endl;

    Goblin goblin2(game);
    game.creatures.push_back(&goblin2);

    cout << " Goblin1: " << goblin.get_attack() << " / "
    << goblin.get_defense() << endl;

    cout << " Goblin2: " << goblin2.get_attack() << " / "
    << goblin2.get_defense() << endl;
    

    cout << " Adding a goblin king, "
    << "now an ordinary goblin should be 2/3" << endl;

    GoblinKing goblin3(game);
    game.creatures.push_back(&goblin3);

    cout << " Goblin1: " << goblin.get_attack() << " / "
    << goblin.get_defense() << endl;

    cout << " Goblin2: " << goblin2.get_attack() << " / "
    << goblin2.get_defense() << endl;

    cout << " Goblinking: " << goblin3.get_attack() << " / "
    << goblin3.get_defense() << endl;

    cout << " Adding a second goblin king, "
    << "now an ordinary goblin should be 3/4" << endl;

    GoblinKing goblin4(game);
    game.creatures.push_back(&goblin4);

    cout << " Goblin1: " << goblin.get_attack() << " / "
    << goblin.get_defense() << endl;

    cout << " Goblin2: " << goblin2.get_attack() << " / "
    << goblin2.get_defense() << endl;

    cout << " Goblinking1: " << goblin3.get_attack() << " / "
    << goblin3.get_defense() << endl;

    cout << " Goblinking2: " << goblin4.get_attack() << " / "
    << goblin4.get_defense() << endl;


    return 0;
}