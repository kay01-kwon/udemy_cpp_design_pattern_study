#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

using std::ostream;


struct Creature
{
    public:

    Creature(const string &name, const int attack, const int defense)
    : name_(name), attack_(attack), defense_(defense) {}

    friend ostream &operator<<(ostream &os, const Creature &creature)
    {
        os << "Name: " << creature.name_
        << " Attack: " << creature.attack_
        << " Defense: " << creature.defense_;
        return os;
    }

    // private:
    string name_;
    int attack_, defense_;

};

class CreatureModifier
{
    public:
    CreatureModifier(Creature &creature):
    creature_(creature) {}

    void add(CreatureModifier *cm)
    {
        if(next_) next_->add(cm);
        else next_ = cm;
    }

    virtual void handle()
    {
        if(next_) next_->handle();
    }


    protected:
    Creature &creature_;

    private:

    CreatureModifier *next_{nullptr};

};

class DoubleAttackModifier : public CreatureModifier
{
    public:


    DoubleAttackModifier(Creature &creature)
    : CreatureModifier(creature) {}

    void handle() override
    {
        creature_.attack_ *= 2;
        CreatureModifier::handle();
    }

};

class IncreaseDefenseModifier : public CreatureModifier
{
    public:

    IncreaseDefenseModifier(Creature &creature)
    : CreatureModifier(creature){}

    void handle() override
    {
        if(creature_.attack_ <= 2)
        {
            creature_.defense_++;
        }
        CreatureModifier::handle();
    }

};

class NoBonusModifier : public CreatureModifier
{
    public:

    NoBonusModifier(Creature &creature)
    : CreatureModifier(creature) {}

    void handle() override
    {
        // Do nothing
    }

};

int main()
{
    Creature goblin("Goblin", 1, 1);
    CreatureModifier root(goblin);
    
    DoubleAttackModifier r1(goblin);
    DoubleAttackModifier r1_2(goblin);
    
    IncreaseDefenseModifier r2(goblin);

    root.add(&r1);
    root.add(&r1_2);
    root.add(&r2);

    root.handle();

    cout << goblin << endl;

    return 0;
}
