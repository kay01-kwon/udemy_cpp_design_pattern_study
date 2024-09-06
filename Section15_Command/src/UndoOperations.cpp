#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;
using std::ostream;

struct BankAccount{

    int balance{0};
    int overdraft_limit{-500};

    void deposit(int amount)
    {
        balance += amount;
        cout << "Deposited " << amount
        << ", balance is now " << balance << endl;
    }

    bool withdraw(int amount)
    {
        if(balance - amount >= overdraft_limit)
        {
            balance -= amount;
            cout << "Withdrew " << amount
            << ", balance is now " << balance << endl;
            return true;
        }
        return false;
    }
    
    friend ostream& operator<<(ostream& os, const BankAccount& account)
    {
        os << "balance: " << account.balance;
        return os;
    }
};

struct Command
{
    bool succeeded;
    virtual void call() = 0;
    virtual void undo() = 0;
};

enum class Action {deposit, withdraw};

struct BankAccountCommand : Command
{
    BankAccountCommand(BankAccount& account, Action action, int amount)
    : account_(account), action_(action), amount_(amount) 
    {
        succeeded = false;
    }

    void call() override
    {
        switch(action_)
        {
            case Action::deposit :
                account_.deposit(amount_);
                succeeded = true;
                break;
            case Action::withdraw :
                succeeded = account_.withdraw(amount_);
                break;
            default:
                break;
        }
    }

    void undo() override
    {
        if(!succeeded)
            return;
        switch(action_)
        {
            case Action::deposit :
                account_.withdraw(amount_);
                break;
            case Action::withdraw :
                account_.deposit(amount_);
                break;
            default:
                break;
        }

    }

    private:
    BankAccount& account_;
    Action action_;
    int amount_;

};

int main()
{
    BankAccount ba;

    vector<BankAccountCommand> commands(
        {
            BankAccountCommand{ba, Action::deposit, 100},
            BankAccountCommand{ba, Action::withdraw, 200}
        }
    );

    cout << ba << endl;

    for(auto &cmd :commands)
        cmd.call();

    for(auto it = commands.rbegin(); it != commands.rend(); ++it)
        it->undo();
    
    cout << ba << endl;

    return 0;
}