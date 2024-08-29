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
    private:

    class PointFactory
    {
        public:
        static Point NewCartesian(double x, double y)
        {
            return {x, y};
        };

        static Point NewPolar(double r, double theta)
        {
            return {r*cos(theta), r*sin(theta)};
        }
    };


    public:

    friend ostream& operator<<(ostream& os, const Point& obj)
    {
        os << "x: " << obj.x_ << " y: " << obj.y_;
        return os;
    }

    static PointFactory Factory;

    private:

    Point(double x, double y): x_(x), y_(y){}

    double x_, y_;

};



int main()
{

    auto p = Point::Factory.NewCartesian(3.0, 4.0);

    cout << p << endl;

    return 0;
}