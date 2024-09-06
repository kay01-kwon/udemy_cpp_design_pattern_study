#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <regex>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::map;

vector<string> split(const string &stringToSplit)
{
    vector<string> result;
    size_t pos(0), lastPos(0);

    while((pos = stringToSplit.find_first_of("+-", lastPos)) != string::npos)
    {
        result.push_back(stringToSplit.substr(lastPos, pos - lastPos + 1));
        lastPos = pos + 1;
    }
    result.push_back(stringToSplit.substr(lastPos));
    return result;
}

enum class NextOp
{
    nothing,
    plus,
    minus
};

struct ExpressionProcessor
{
    map<char, int> variables;

    int calculate(const string& expression)
    {
        int current;
        auto nextOp = NextOp::nothing;

        auto parts = split(expression);

        cout << "parts (" << parts.size() << "): ";
        for(const auto& part: parts)
        {
            cout << "'" << part << "'";
        }
        cout << endl;

        for(const auto& part: parts)
        {
            auto noOp = split(part);
            auto first = noOp[0];
            int value, z;


            try{
                value = stoi(first);
            }
            catch(std::invalid_argument&)
            {
                if(first.length() == 1 && variables.find(first[0]) != variables.end())
                {
                    value = variables[first[0]];
                }
                else
                {
                    return 0;
                }
            }

            switch(nextOp)
            {
                case NextOp::nothing:
                    current = value;
                    break;
                case NextOp::plus:
                    current += value;
                    break;
                case NextOp::minus:
                    current -= value;
                    break;
                default:
                    break;
            }

            if(part.back() == '+')
            {
                nextOp = NextOp::plus;
            }
            else if(part.back() == '-')
            {
                nextOp = NextOp::minus;
            }
            else
            {
                nextOp = NextOp::nothing;
            }
        }

        return current;
    }

};


int main()
{
    ExpressionProcessor ep;
    ep.variables['x'] = 3;

    int result[5];

    result[0] = ep.calculate("1");
    result[1] = ep.calculate("1+2");
    result[2] = ep.calculate("1+x");
    result[3] = ep.calculate("1+xy");
    result[4] = ep.calculate("1-3+x");

    for(int i = 0; i < 5; i++)
    {
        cout << result[i] << endl;
    }


    return 0;
}
