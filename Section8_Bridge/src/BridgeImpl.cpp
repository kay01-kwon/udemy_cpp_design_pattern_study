#include <iostream>

using std::cout;
using std::endl;

// Shapes - circle, square
// Rendering - vector, raster

// 2x2 RasterCircleRenderer, RasterSquareRenderer, VectorCircleRenderer

struct Renderer
{
    virtual void render_circle(double x, double y, double radius) = 0;
};

struct VectorRenderer : Renderer
{
    void render_circle(double x, double y, double radius) override
    {
        cout << "Rasterizing a circle of radius " << radius << endl;
    }
};

struct RasterRenderer : Renderer
{
    void render_circle(double x, double y, double radius) override
    {
        cout << "Drawing a vector circle of radius " << radius << endl;
    }
};

struct Shape
{
    public:

    virtual void draw() = 0;
    virtual void resize(double factor) = 0;

    protected:
    Renderer &renderer_;
    Shape(Renderer &renderer): renderer_(renderer) {}

};

struct Circle : Shape
{
    public:

    Circle(Renderer &renderer, double x, 
    double y, double radius): Shape(renderer), 
    x_(x), y_(y), radius_(radius) {}

    void draw() override
    {
        renderer_.render_circle(x_, y_, radius_);
    }

    void resize(double factor) override
    {
        radius_ *= factor;
    }


    private:

    double x_, y_, radius_;
};


int main()
{
    RasterRenderer raster_renderer;
    Circle circle(raster_renderer, 3, 4, 5);

    circle.draw();
    circle.resize(2);
    circle.draw();

    return 0;
}