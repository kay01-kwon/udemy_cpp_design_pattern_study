#include <iostream>

using std::cout;
using std::endl;

struct Square
{
  int side{ 0 };


  explicit Square(const int side)
    : side(side)
  {
  }
};

struct Rectangle
{
  virtual int width() const = 0;
  virtual int height() const = 0;

  int area() const
  {
    return width() * height();
  }
};

struct SquareToRectangleAdapter : Rectangle
{
  SquareToRectangleAdapter(const Square& square)
  : square_(square)
  {
      // todo
    //   square_ = square;
  }
  
  int width() const override
  {
      return square_.side;
  }
  int height() const override
  {
      return square_.side;
  }
  
  const Square& square_;
};

int main()
{
    Square sq{11};
    SquareToRectangleAdapter adapter{sq};
    cout << adapter.area() << endl;
    
    return 0;
}