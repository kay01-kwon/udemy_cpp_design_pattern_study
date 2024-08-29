#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>
#include <sstream>
#include <memory>
#include <cmath>

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::ostream;


enum class PointType
{
    cartesian,
    polar
};

class Point
{
    friend class PointFactory;
    public:
    Point(double x, double y): x_(x), y_(y){}


    friend ostream& operator<<(ostream& os, const Point& obj)
    {
        os << "x: " << obj.x_ << " y: " << obj.y_;
        return os;
    }

    private:

    double x_, y_;

};

struct PointFactory
{
    static Point NewCartesian(double x, double y)
    {
        return {x, y};
    }

    static Point NewPolar(double r, double theta)
    {
        return {r*cos(theta), r*sin(theta)};
    }
};


int main()
{

    auto p = PointFactory::NewPolar(5, M_PI_4);

    cout << p << endl;

    return 0;
}