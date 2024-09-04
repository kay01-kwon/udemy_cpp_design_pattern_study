#include <iostream>
#include <sstream>
#include <string>
#include <vector>


using std::cout;
using std::endl;
using std::string;
using std::ostringstream;

struct Shape
{
    virtual string str() const = 0;
};


struct Circle : Shape
{

    Circle(){}

    Circle(const double &radius)
    : radius_(radius){}

    void resize(const double &factor)
    {
        radius_ *= factor;
    }

    string str() const override
    {
        ostringstream oss;
        oss << " A circle of radius " << radius_;
        return oss.str();
    }


    private:

    double radius_;
};

struct Square : Shape
{
    Square(){}

    Square(const double &side)
    : side_(side){}

    void resize(const double &factor)
    {
        side_ *= factor;
    }

    string str() const override
    {
        ostringstream oss;
        oss << " A square of side " << side_;
        return oss.str();
    }

    private:
    double side_;
};

struct ColoredShape : Shape
{
    public:

    ColoredShape(Shape &shape, const string &color)
    : shape_(shape), color_(color){}

    string str() const override
    {
        ostringstream oss;
        oss << shape_.str() << " has the color " << color_;
        return oss.str();
    }

    private:
    Shape &shape_;
    string color_;
};

struct TransparentShape : Shape
{
    public:
    
    TransparentShape(Shape &shape, const uint8_t &transparency)
    : shape_(shape), transparency_(transparency){}

    string str() const override
    {
        ostringstream oss;
        oss << shape_.str() << " has " 
        << static_cast<double>(transparency_) / 255.0 *100.0
        << "% transparency";

        return oss.str();
    }

    private:
    Shape &shape_;
    uint8_t transparency_;

};

int main()
{
    Square square(5);
    ColoredShape red_square(square, "red");

    cout << square.str() << endl;
    cout << red_square.str() << endl;

    TransparentShape my_square(red_square, 51);

    cout << my_square.str() << endl;
    return 0;
}