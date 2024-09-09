#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::ostream;

class Memento
{
    public:

    Memento(int balance) : balance_(balance) {}

    friend class BankAccount;

    private:
    int balance_;

};


class BankAccount
{
    public:

    BankAccount(int balance)
    : balance_(balance) {}

    Memento deposit(int amount)
    {
        balance_ += amount;
        return {balance_};
    }

    void restore(const Memento& m)
    {
        balance_ = m.balance_;
    }

    friend ostream &operator<<(ostream &os, const BankAccount &account)
    {
        os << "balance: " << account.balance_;
        return os;
    }

    private:
    int balance_{0};

};

int main()
{
    BankAccount ba(100);
    auto m1 = ba.deposit(50);
    auto m2 = ba.deposit(25);

    cout << ba << endl;

    ba.restore(m1);

    cout << "Back to m1: " << ba << endl;

    ba.restore(m2);

    cout << "Back to m2: " << ba << endl;
    return 0;
}