#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

struct IParticipant
{
    virtual void notify(IParticipant* sender, int value) = 0;
};

struct Mediator
{
    vector<IParticipant*> participants;

    void say(IParticipant* sender, int value)
    {
        for( auto p : participants)
            p->notify(sender, value);
    }

};

struct Participant : IParticipant
{
    int value_{0};
    Mediator& mediator_;
    
    Participant(Mediator &mediator)
    : mediator_(mediator)
    {
        mediator_.participants.push_back(this);
    }

    void say(int value)
    {
        mediator_.say(this, value);

    }

    void notify(IParticipant* sender, int value)
    {
        if(sender != this)
            value_ += value;
    }
};

int main()
{
    Mediator mediator;
    Participant p1(mediator), p2(mediator);

    p1.say(2);

    cout << p1.value_ << endl;
    cout << p2.value_ << endl;

    p2.say(4);

    cout << p1.value_ << endl;
    cout << p2.value_ << endl;



    return 0;
}