#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct Value;
struct AdditionExpression;
struct MultiplicationExpression;
struct ExpressionVisitor
{
    virtual void accept(Value &value) = 0;
    virtual void accept(AdditionExpression &e) = 0;
    virtual void accept(MultiplicationExpression &e) = 0;

};


struct Expression
{
    virtual void visit(ExpressionVisitor &visitor) = 0;
};

struct Value : Expression
{
    int value_;

    Value(int value) : value_(value) {}

    void visit(ExpressionVisitor &visitor) override
    {
        visitor.accept(*this);
    }
};

struct AdditionExpression : Expression
{
    Expression &lhs_, &rhs_;

    AdditionExpression(Expression &lhs, Expression &rhs) : lhs_(lhs), rhs_(rhs) {}

    void visit(ExpressionVisitor &visitor) override
    {
        visitor.accept(*this);
    }
};

struct MultiplicationExpression : Expression
{
    Expression &lhs_, &rhs_;

    MultiplicationExpression(Expression &lhs, Expression &rhs) : lhs_(lhs), rhs_(rhs) {}

    void visit(ExpressionVisitor &visitor) override
    {
        visitor.accept(*this);
    }

};

struct ExpressionPrinter : ExpressionVisitor
{
    ostringstream oss;

    void accept(Value &value) override;

    void accept(AdditionExpression &e) override;

    void accept(MultiplicationExpression &e) override;

    string str() const
    {
        return oss.str();
    }

};


void ExpressionPrinter::accept(Value &value)
{
    oss << value.value_;
}

void ExpressionPrinter::accept(AdditionExpression &e)
{
    oss << "(";
    e.lhs_.visit(*this);
    oss << "+";
    e.rhs_.visit(*this);
    oss << ")";
}

void ExpressionPrinter::accept(MultiplicationExpression &e)
{
    e.lhs_.visit(*this);
    oss << "*";
    e.rhs_.visit(*this);
}


int main()
{
    Value v1(2);
    Value v2(3);
    
    AdditionExpression sum(v1, v2);

    ExpressionPrinter ep;

    sum.visit(ep);

    cout << ep.str() << endl;

    return 0;
}