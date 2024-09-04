#include <iostream>
#include <sstream>
#include <string>

using std::cout;
using std::endl;
using std::ostringstream;
using std::string;



struct Flower
{
  virtual string str() = 0;
};

struct Rose : Flower
{
    Rose(){}
    
  string str() override {
    // todo
    ostringstream oss;
    oss << "A rose";
    return oss.str();
  }
};

struct RedFlower : Flower
{
    RedFlower(Flower& flower) : flower_(flower) {}
    string str() override
    {
        string s = flower_.str();
        if(s.find("red") != string::npos)
            return s;
        else if(s.find("blue") != string::npos)
            return s + " and red";
        return s + " that is red";
    }
    
    Flower& flower_;
};

struct BlueFlower : Flower
{
    BlueFlower(Flower& flower) : flower_(flower) {}
    string str() override
    {
        string s = flower_.str();
        
        if(s.find("blue") != string::npos)
            return s;
        else if(s.find("red") != string::npos)
            return s + " and blue";
        return s + " that is blue";
    }
    
    Flower& flower_;
};

int main()
{
    Rose rose;
    RedFlower red_rose(rose);
    BlueFlower blue_rose(rose);

    RedFlower red_blue_rose(blue_rose);
    BlueFlower blue_red_rose(red_rose);

    cout << red_rose.str() << endl;
    cout << blue_rose.str() << endl;
    cout << red_blue_rose.str() << endl;
    cout << blue_red_rose.str() << endl;

    return 0;
}