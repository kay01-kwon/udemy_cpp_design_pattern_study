#include <iostream>

using std::cout;
using std::endl;

class LightSwitch;

struct State
{
    public:
    virtual void on(LightSwitch *ls)
    {
        cout << "Light is already on" << endl;
    }

    virtual void off(LightSwitch *ls)
    {
        cout << "Light is already off" << endl;
    }

};

struct OnState : State
{
    OnState()
    {
        cout << "Light turned on" << endl;
    }

    void off(LightSwitch *ls) override;
};

struct OffState : State
{
    OffState()
    {
        cout << "Light turned off" << endl;
    }

    void on(LightSwitch *ls) override;

};

class LightSwitch
{
    public:
    LightSwitch()
    {
        state_ = new OffState();
    }

    void set_state(State *state)
    {
        state_ = state;
    }

    void on()
    {
        state_->on(this);
    }

    void off()
    {
        state_->off(this);
    }

    private:
    State *state_;
};

void OnState::off(LightSwitch *ls)
{
    cout << "Switching light off" << endl;
    ls->set_state(new OffState());
    delete this;
}

void OffState::on(LightSwitch *ls)
{
    cout << "Switching light on" << endl;
    ls->set_state(new OnState());
    delete this;
}

int main()
{
    LightSwitch ls;
    ls.on();
    ls.off();
    ls.off();

    return 0;
}