#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <boost/lexical_cast.hpp>
#include <memory>

using std::cout;
using std::endl;
using std::ostream;
using std::ostringstream;
using std::string;
using std::vector;
using std::make_shared;
using std::shared_ptr;

enum class TokenType
{
    integer,
    plus,
    minus,
    lparen,
    rparen
};

struct Token
{
    TokenType type_;
    string text_;

    Token(TokenType type, const string &text)
    : type_(type), text_(text) {}

    friend ostream& operator<<(ostream& os, const Token &obj)
    {
        os << "'" << obj.text_
        << "'";
        return os;
    }
};


vector<Token> lex(const string &input)
{
    vector<Token> result;

    for( int i = 0; i < input.size(); i++)
    {
        switch(input[i])
        {
            case '+':
                result.push_back(Token{TokenType::plus, "+"});
                break;
            case '-':
                result.push_back(Token{TokenType::minus, "-"});
                break;
            case '(':
                result.push_back(Token{TokenType::lparen, "("});
                break;
            case ')':
                result.push_back(Token{TokenType::rparen, ")"});
                break;
            default:
                ostringstream buffer;
                buffer << input[i];
                for(int j = i+1; j < input.size(); j++)
                {
                    if(isdigit(input[j]))
                    {
                        buffer << input[j];
                        i++;
                    }
                    else
                    {
                        result.push_back(Token{TokenType::integer, buffer.str()});
                        break;
                    }
                }
        }
    }
    return result;
}

struct Element
{
    virtual int eval() const = 0;
};

struct Integer: Element
{
    int value_;

    Integer(int value): value_(value) {}

    int eval() const override
    {
        return value_;
    }
};

enum class BinaryOperationType
{
    addition,
    subtraction
};

struct BinaryOperation : Element
{
    BinaryOperationType type_;
    shared_ptr<Element> lhs_, rhs_;

    int eval() const override
    {
        if(type_ == BinaryOperationType::addition)
        {
            return lhs_->eval() + rhs_->eval();
        }
        else if(type_ == BinaryOperationType::subtraction)
        {
            return lhs_->eval() - rhs_->eval();
        }
        else
        {
            return 0;
        }
    }
};

shared_ptr<Element> parse(const vector<Token>& tokens)
{
    auto result = std::make_shared<BinaryOperation>();
    bool have_lhs{false};

    for(int i = 0; i < tokens.size(); i++)
    {
        auto token = tokens[i];
        switch(token.type_)
        {
            case TokenType::integer:
            {
                int value = boost::lexical_cast<int>(token.text_);
                auto integer = make_shared<Integer>(value);
                if(!have_lhs)
                {
                    result->lhs_ = integer;
                    have_lhs = true;
                }
                else
                {
                    result->rhs_ = integer;
                }
                break;
            }
            case TokenType::plus:
                result->type_ = BinaryOperationType::addition;
                break;
            case TokenType::minus:
                result->type_ = BinaryOperationType::subtraction;
                break;
            case TokenType::lparen:
            {
                int j = i;
                for(j = i; j < tokens.size(); j++)
                {
                    if(tokens[j].type_ == TokenType::rparen)
                        break;
                }

                vector<Token> subexpression(&tokens[i+1], &tokens[j]);
                auto element = parse(subexpression);
                if(!have_lhs)
                {
                    result->lhs_ = element;
                    have_lhs = true;
                }
                else
                {
                    result->rhs_ = element;
                }
                i = j;
                break;

            }
        }
    }

    return result;
}

int main()
{
    string input{"(13-4)-(12+1)"};
    auto tokens = lex(input);

    for(auto &t: tokens)
    {
        cout << t << " ";
    }
    cout << endl;

    try{
        auto parsed = parse(tokens);
        cout << input << " = " << parsed->eval() << endl;
    }
    catch(const std::exception &e)
    {
        cout << e.what() << endl;
    }

    return 0;
}