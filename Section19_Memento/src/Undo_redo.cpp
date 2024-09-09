#include <iostream>
#include <string>
#include <vector>
#include <memory>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::ostream;
using std::shared_ptr;
using std::make_shared;


class Memento
{
    public:

    Memento(int balance) : balance_(balance) {}

    friend class BankAccount;
    friend class BankAccount2;

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

class BankAccount2
{
    public:
    BankAccount2(int balance) : balance_(balance)
    {
        changes_.emplace_back(make_shared<Memento>(balance));
        current_ = 0;
    }

    shared_ptr<Memento> deposit(int amount)
    {
        balance_ += amount;
        auto m = make_shared<Memento>(balance_);
        changes_.push_back(m);
        ++current_;
        return m;
    }

    void restore(const shared_ptr<Memento>& m)
    {
        if(m)
        {
            balance_ = m->balance_;
            changes_.push_back(m);
            current_ = changes_.size() - 1;
        }
    }

    shared_ptr<Memento> undo()
    {
        if(current_ > 0)
        {
            --current_;
            auto m = changes_[current_];
            balance_ = m->balance_;
            return m;
        }
        return {};
    }

    shared_ptr<Memento> redo()
    {
        if(current_ + 1 < changes_.size())
        {
            ++current_;
            auto m = changes_[current_];
            balance_ = m->balance_;
            return m;
        }
        return {};
    }

    friend ostream &operator<<(ostream &os, const BankAccount2 &account)
    {
        os << "balance: " << account.balance_;
        return os;
    }


    private:

    int balance_{0};
    vector<shared_ptr<Memento>> changes_;
    int current_;

};

int main()
{
    BankAccount2 ba(100);
    ba.deposit(50);
    ba.deposit(25);
    cout << ba << endl;

    ba.undo();
    cout << " Undo 1: " << ba << endl;

    ba.undo();
    cout <<" Undo 2: " << ba << endl;

    ba.redo();
    cout << " Redo 1: " << ba << endl;

    ba.redo();
    cout << " Redo 2: " << ba << endl;

    return 0;
}