#include <iostream>
#include <vector>
#include <memory>

using std::cout;
using std::endl;
using std::vector;
using std::shared_ptr;
using std::make_shared;


struct Token
{
    Token(int value) : value_(value) {}
    int value_;
};

struct Memento
{
    vector<shared_ptr<Token>> tokens;
};

struct TokenMachine
{

    vector<shared_ptr<Token>> tokens;

    Memento add_token(int value)
    {
        return add_token(make_shared<Token>(value));
    }

    Memento add_token(const shared_ptr<Token> &token)
    {
        tokens.push_back(token);
        Memento m;
        for(auto t : tokens)
            m.tokens.push_back(make_shared<Token>(t->value_));
        return m;
    }

    void revert(const Memento &m)
    {
        tokens.clear();
        for(auto t: m.tokens)
            tokens.push_back(make_shared<Token>(t->value_));

    }

};

int main()
{
    TokenMachine tm;

    cout << "Make a token with value = 111 and kept a reference\n";
    auto token = make_shared<Token>(111);
    cout << "Added this token to the list\n";
    tm.add_token(token);
    auto m = tm.add_token(222);
    cout << "Changed this token's valueto 333: \n";
    token->value_ = 333;

    tm.revert(m);


    return 0;
}