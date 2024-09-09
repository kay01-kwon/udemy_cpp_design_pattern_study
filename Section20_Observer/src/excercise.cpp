#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using std::cout;
using std::endl;
using std::vector;

struct IRat;
struct Rat;

struct IRat
{
    public:
    virtual void rat_enters(IRat* sender) = 0;
    virtual void rat_dies(IRat* sender) = 0;
    virtual void notify(IRat* target) = 0;
};

struct Game
{
    public:
    friend struct Rat;

    void rat_enters_at_game(IRat* sender)
    {
        for(auto rat : rats_)
            rat->rat_enters(sender);
    }

    void rat_dies_at_game(IRat* sender)
    {
        for(auto rat : rats_)
            rat->rat_dies(sender);
    }

    void notify_at_game(IRat* target)
    {
        for(auto rat : rats_)
            rat->notify(target);
    }

    private:
    vector<IRat*> rats_;

};



struct Rat : IRat
{
    public:

    Rat(Game &game): game_(game)
    {
        game_.rats_.push_back(this);
        game_.rat_enters_at_game(this);
    }

    ~Rat()
    {
        game_.rat_dies_at_game(this);
        game_.rats_.erase(std::remove(game_.rats_.begin(), game_.rats_.end(), this));
    }

    void rat_enters(IRat *sender) override
    {
        if(sender != this)
        {
            ++attack_;
            game_.notify_at_game(sender);
        }
    }

    void rat_dies(IRat *sender) override
    {
        --attack_;
    }

    void notify(IRat *target) override
    {
        if(target == this)
            ++attack_;
    }

    int attack_{1};

    private:
    Game &game_;


};

int main()
{
    Game game;
    Rat rat1(game);
    
    cout << "The attack of rat1 is: ";
    cout << rat1.attack_ << endl;

    // assert(rat1.attack_ == 1);

    cout << "******************************" << endl;

    Rat rat2(game);

    cout << "The attack of rat1 is: ";
    cout << rat1.attack_ << endl;
    cout << "The attack of rat2 is: ";
    cout << rat2.attack_ << endl;

    // assert(rat1.attack_ == 2);
    // assert(rat2.attack_ == 2);

    cout << "******************************" << endl;

    {
        Rat rat3(game);
        cout << "The attack of rat1 is: ";
        cout << rat1.attack_ << endl;
        cout << "The attack of rat2 is: ";
        cout << rat2.attack_ << endl;
        cout << "The attack of rat3 is: ";
        cout << rat3.attack_ << endl;

        // assert(rat1.attack_ == 3);
        // assert(rat2.attack_ == 3);
        // assert(rat3.attack_ == 3);
        
    }
    cout << "******************************" << endl;

    cout << "The attack of rat1 is: ";
    cout << rat1.attack_ << endl;
    cout << "The attack of rat2 is: ";
    cout << rat2.attack_ << endl;


    return 0;

}