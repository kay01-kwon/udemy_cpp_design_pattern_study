#include <iostream>
#include <sstream>
#include <string>

using std::cout;
using std::endl;
using std::string;
using std::ostringstream;

struct DoubleExpression;
struct AdditionExpression;
struct SubtractionExpression;

struct ExpressionVisitor
{
    virtual void visit(DoubleExpression *de) = 0;
    virtual void visit(AdditionExpression *ae) = 0;
    virtual void visit(SubtractionExpression *se) = 0;
};

struct ExpressionPrinter : ExpressionVisitor
{
    void visit(DoubleExpression *de) override;

    void visit(AdditionExpression *ae) override;

    void visit(SubtractionExpression *se) override;

    string str() const 
    {
        return oss.str();
    }

    private:

    ostringstream oss;

};

struct ExpressionEvaluator : ExpressionVisitor
{
    double result;
    void visit(DoubleExpression *de) override;
    void visit(AdditionExpression *ae) override;
    void visit(SubtractionExpression *se) override; 
};

struct Expression
{
    virtual void accept(ExpressionVisitor *visitor) = 0;
};

struct DoubleExpression : Expression
{
    friend struct ExpressionPrinter;
    friend struct ExpressionEvaluator;
    DoubleExpression(const double value) : value_(value) {}

    void accept(ExpressionVisitor* visitor) override
    {
        visitor->visit(this);
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
    friend struct ExpressionPrinter;
    friend struct ExpressionEvaluator;
    AdditionExpression(Expression *left, Expression *right)
    : left_(left), right_(right) {}

    ~AdditionExpression()
    {
        delete left_;
        delete right_;
    }

    void accept(ExpressionVisitor* visitor) override
    {
        visitor->visit(this);
    }


    private:
    Expression *left_;
    Expression *right_;

};

struct SubtractionExpression : Expression
{
    public:
    friend struct ExpressionPrinter;
    friend struct ExpressionEvaluator;
    SubtractionExpression(Expression *left, Expression *right)
    : left_(left), right_(right) {}

    ~SubtractionExpression()
    {
        delete left_;
        delete right_;
    }

    void accept(ExpressionVisitor* visitor) override
    {
        visitor->visit(this);
    }

    private:
    Expression *left_;
    Expression *right_;

};


void ExpressionPrinter::visit(DoubleExpression *de)
{
    oss << de->value_;
}

void ExpressionPrinter::visit(AdditionExpression *ae)
{
    bool need_braces = dynamic_cast<AdditionExpression*>(ae->right_);

    if(need_braces)
        oss << "(";

    ae->left_->accept(this);
    oss << "+";

    ae->right_->accept(this);
    
    if(need_braces)
        oss << ")";
}

void ExpressionPrinter::visit(SubtractionExpression *se)
{
    bool need_braces = dynamic_cast<SubtractionExpression*>(se->right_);
    if(need_braces)
        oss << "(";
    se->left_->accept(this);
    oss << "-";
    se->right_->accept(this);
    if(need_braces)
        oss << ")";
}

void ExpressionEvaluator::visit(DoubleExpression *de)
{
    result = de->value_;
}

void ExpressionEvaluator::visit(AdditionExpression *ae)
{
    ae->left_->accept(this);
    auto temp = result;
    ae->right_->accept(this);
    result += temp;
}

void ExpressionEvaluator::visit(SubtractionExpression *se)
{
    se->right_->accept(this);
    auto temp = result;
    se->left_->accept(this);
    result -= temp;
}

int main()
{
    ostringstream oss;
    // 1 + (2 - 3)
    auto e = new AdditionExpression{
        new DoubleExpression{1},
        new SubtractionExpression{
            new DoubleExpression{2},
            new DoubleExpression{3}
        }
    };

    ExpressionPrinter ep;
    ExpressionEvaluator ev;

    ep.visit(e);
    ev.visit(e);

    cout << ep.str();

    cout << " = ";

    cout << ev.result << endl;

    delete e;

    return 0;
}