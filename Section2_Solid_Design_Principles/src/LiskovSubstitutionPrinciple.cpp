#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>

using std::cout;
using std::endl;
using std::vector;
using std::string;


class Rectangle{
    
    public:
        Rectangle(int width, int height):
        width_(width), height_(height)
        {}
        
        int get_width() const { return width_; }

        int get_height() const { return height_; }

        virtual void setWidth(const int width)
        {
            width_ = width;
        }

        virtual void setHeight(const int height)
        {
            height_ = height;
        }

        int area() const
        {
            return width_ * height_;
        }


    protected:
        int width_, height_;
    
};

class Square: public Rectangle{
    public:
        Square(int size): Rectangle(size, size) {}

        virtual void setHeight(const int height)
        {
            this->width_ = height;
            this->height_ = height;
        }

        virtual void setWidth(const int width)
        {
            this->width_ = width;
            this->height_ = width;
        }
};

void process(Rectangle& r)
{
    int w = r.get_width();
    r.setHeight(10);

    cout << "expected aera = " << (w*10)
        << ", got " << r.area() << endl;
}

struct RectangleFactory
{
    static Rectangle create_rectangle(int w, int h);
    static Rectangle create_square(int sizde);
};

int main()
{

    Rectangle r(3, 4);
    process(r);

    Square sq(5);
    // Problem occurs here
    process(sq);

    return 0;
}