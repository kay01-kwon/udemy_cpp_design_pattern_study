#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

enum class Action {deposit, withdraw};

struct Command
{
    Action action;
    int amount;
    bool success;
};

struct Account
{
    int balance{0};

    void process(Command& cmd)
    {
        switch(cmd.action)
        {
            case Action::deposit :
                balance += cmd.amount;
                cmd.success = true;
                break;
            case Action::withdraw :
                if(balance - cmd.amount >= 0)
                {
                    balance -= cmd.amount;
                    cmd.success = true;
                }
                else
                {
                    cmd.success = false;
                }
                break;
            default:
                break;
        }
    }
};

int main()
{
    Account a;
    Command c1{Action::deposit, 100};
    a.process(c1);
    cout << " Balance : "
    << a.balance << " Success : " << c1.success << endl;

    Command c2{Action::withdraw, 50};
    a.process(c2);
    cout << " Balance : "
    << a.balance << " Success : " << c2.success << endl;

    return 0;
}