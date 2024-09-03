#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;



struct Renderer
{
    virtual string what_to_render_as() const = 0;
};

struct VectorRenderer : Renderer
{
    string what_to_render_as() const override
    {
        return " as lines";
    }
};

struct RasterRenderer : Renderer
{
    string what_to_render_as() const override
    {
        return " as pixels";
    }
};


struct Shape
{
    string name;
};

struct Triangle : Shape
{
    
    Triangle(Renderer& renderer):renderer_(renderer) 
    {
        name_ = "Circle";
    }
    
    string str() const
    {
        return "Drawing " + name_ + renderer_.what_to_render_as();
    }
    
    private:
    Renderer &renderer_;
    string name_;
};

struct Square : Shape
{
    Square(Renderer &renderer) : renderer_(renderer)
    {
        name_ = "Square";
    }
    
    string str() const
    {
        return "Drawing " + name_ + renderer_.what_to_render_as();
    }
    
    private:
    Renderer &renderer_;
    string name_;
};


int main()
{
    RasterRenderer rr;
    VectorRenderer vr;

    Triangle rt(rr);
    Square rs(rr);

    Triangle vt(vr);
    Square vs(vr);

    cout << rt.str() << endl;
    cout << rs.str() << endl;

    cout << vt.str() << endl;
    cout << vs.str() << endl;

    return 0;
}