#include <iostream>
#include <string>
#include <vector>
#include <memory>

using std::cout;
using std::endl;

using std::string;
using std::ostream;

using std::make_shared;

struct BankAccount
{
    virtual ~BankAccount() = default;
    virtual void deposit(int amount) = 0;
    virtual void withdraw(int amount) = 0;
};

struct CurrentAccount : BankAccount
{
    public:
    explicit CurrentAccount(int balance)
    : balance_(balance){}

    void deposit(int amount) override
    {
        balance_ += amount;
    }

    void withdraw(int amount) override
    {
        if(balance_ >= amount)
            balance_ -= amount;
    }

    
    friend ostream& operator<<(ostream& os, const CurrentAccount& obj)
    {
        os << "balance: " << obj.balance_;
        return os;
    }

    private:
    int balance_;

};

int main()
{
    BankAccount* a = new CurrentAccount(123);
    a->deposit(321);

    auto b = make_shared<CurrentAccount>(123);
    // b->deposit(321);
    BankAccount *actual = b.get();
    actual->deposit(321);

    cout << *b << endl;

    delete a;
    return 0;
}