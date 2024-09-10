#include <iostream>
#include <sstream>
#include <string>

using std::cout;
using std::endl;
using std::string;
using std::ostringstream;

struct Expression
{
    virtual ~Expression() = default;
    virtual void print(ostringstream &oss) = 0;
};

struct DoubleExpression : Expression
{
    DoubleExpression(double value) : value_(value) {}

    void print(ostringstream &oss) override
    {
        oss << value_;
    }

    private:
    double value_;
};

// 1 + 2 + 3
//   +
//  / \
// 1   +
//    / \
//   2   3

struct AdditionExpression : Expression
{
    public:
    AdditionExpression(Expression *left, Expression *right)
    : left_(left), right_(right) {}

    ~AdditionExpression()
    {
        delete left_;
        delete right_;
    }

    void print(ostringstream &oss) override
    {
        oss << "(";
        left_->print(oss);
        oss << "+";
        right_->print(oss);
        oss << ")";
    }

    private:
    Expression *left_;
    Expression *right_;

};

int main()
{
    auto e = new AdditionExpression{
        new DoubleExpression{1},
        new AdditionExpression{
            new DoubleExpression{2},
            new DoubleExpression{3}
        }
    };

    ostringstream oss;
    e->print(oss);
    cout << oss.str() << endl;


    delete e;

    return 0;
}