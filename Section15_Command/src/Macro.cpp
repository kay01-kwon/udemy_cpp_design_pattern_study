#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;
using std::ostream;
using std::initializer_list;

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

struct CompositBankAccountCommand 
: vector<BankAccountCommand>, Command
{
    CompositBankAccountCommand(const initializer_list<BankAccountCommand>& items)
    : vector(items) {}

    void call() override
    {
        for(auto& cmd : *this)
            cmd.call();
    }

    void undo() override
    {
        for(auto it = rbegin(); it != rend(); ++it)
            it->undo();
    }
};

struct DependentCompositeCommand : CompositBankAccountCommand
{
    DependentCompositeCommand(const initializer_list<BankAccountCommand>& items)
    : CompositBankAccountCommand(items) {}

    void call() override
    {
        bool ok = true;
        for(auto& cmd : *this)
        {
            if(ok)
            {
                cmd.call();
                ok = cmd.succeeded;
            }
            else
            {
                cmd.succeeded = false;
            }
        }

    }
};


struct MoneyTransferCommand : DependentCompositeCommand
{
    MoneyTransferCommand(BankAccount& from, BankAccount& to, int amount)
    : DependentCompositeCommand(
        {
            BankAccountCommand{from, Action::withdraw, amount},
            BankAccountCommand{to, Action::deposit, amount}
        }
    ) {}
};  

// struct MoneyTransferCommand : CompositBankAccountCommand
// {
//     MoneyTransferCommand(BankAccount& from, BankAccount& to, int amount)
//     : CompositBankAccountCommand(
//         {
//             BankAccountCommand{from, Action::withdraw, amount},
//             BankAccountCommand{to, Action::deposit, amount}
//         }
//     ) {}
// };

int main()
{
    BankAccount ba1, ba2;

    ba1.deposit(100);

    MoneyTransferCommand cmd{ba1, ba2, 5000};
    cmd.call();

    cout << ba1 << endl << ba2 << endl;

    cmd.undo();

    cout << ba1 << endl << ba2 << endl;

    return 0;
}