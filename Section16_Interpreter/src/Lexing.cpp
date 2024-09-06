#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::ostream;
using std::ostringstream;
using std::string;
using std::vector;

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

                break;
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
    return 0;
}