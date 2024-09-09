#include <iostream>
#include <vector>
#include <string>

using std::cout;
using std::endl;
using std::vector;
using std::string;

class CombinationLock
{
    public:

    string status;

    CombinationLock(const vector<int> &combination) : combination_(combination)
    {
        status = "LOCKED";
    }

    void enter_digit(int digit)
    {
        if (status == "LOCKED")
        {
            status = "";
        }

        status += std::to_string(digit);
        if (digit != combination_[status.size() - 1])
        {
            status = "ERROR";
        }
        else if (status.size() == combination_.size())
        {
            status = "OPEN";
        }
    }

    private:
    vector<int> combination_;

};


int main()
{
    CombinationLock cl({1, 2, 3});

    cout << cl.status << endl;
    cl.enter_digit(1);
    cout << cl.status << endl;
    cl.enter_digit(2);
    cout << cl.status << endl;
    cl.enter_digit(3);
    cout << cl.status << endl;
    cl.enter_digit(4);
    cout << cl.status << endl;
    cl.enter_digit(5);
    cout << cl.status << endl;
    return 0;
}