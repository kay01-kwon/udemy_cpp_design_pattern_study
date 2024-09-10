#include <iostream>
#include <string>
#include <sstream>

using namespace std;

template <typename Visitable>
struct Visitor
{
    virtual void visit(Visitable &obj) = 0;
};

struct VisitorBase
{
    virtual ~VisitorBase() = default;
};

struct Expression
{
    virtual ~Expression() = default;

    //                               vvv  visitor<T>
    virtual void accept(VisitorBase &obj)
    {
        using EV = Visitor<Expression>;
        if(auto ev = dynamic_cast<EV*>(&obj))
        {
            ev->visit(*this);
        }
    }
};

struct DoubleExpression : Expression
{
    double value_;

    DoubleExpression(double value) : value_(value) {}

    virtual void accept(VisitorBase &obj)
    {
        using DEV = Visitor<DoubleExpression>;
        if(auto ev = dynamic_cast<DEV*>(&obj))
        {
            ev->visit(*this);
        }
    }
};

struct AdditionExpression : Expression
{
    Expression *left_, *right_;

    AdditionExpression(Expression *left, Expression *right)
    : left_(left), right_(right) {}

    ~AdditionExpression()
    {
        delete left_;
        delete right_;
    }

    virtual void accept(VisitorBase &obj)
    {
        using AEV = Visitor<AdditionExpression>;
        if(auto ev = dynamic_cast<AEV*>(&obj))
        {
            ev->visit(*this);
        }
    }
};

struct ExpressionPrinter :  VisitorBase,
                            Visitor<DoubleExpression>,
                            Visitor<AdditionExpression>
{
    void visit(DoubleExpression &obj) override
    {
        oss << obj.value_;
    }

    void visit(AdditionExpression &obj) override
    {
        oss << "(";
        obj.left_->accept(*this);
        oss << "+";
        obj.right_->accept(*this);
        oss << ")";
    }

    string str() const { return oss.str(); }
    private:
    ostringstream oss;

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

    ExpressionPrinter ep;
    ep.visit(*e);
    cout << ep.str() << endl;

    return 0;
}