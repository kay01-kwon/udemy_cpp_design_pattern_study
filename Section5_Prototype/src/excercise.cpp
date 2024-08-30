#include <iostream>
#include <assert.h>

using std::cout;
using std::endl;

struct Point
{
  int x{ 0 }, y{ 0 };

  Point(){}
  
  Point(const int x, const int y) : x{x}, y{y} {}
};

struct Line
{
  Point *start, *end;
  
  Line(Point* const start, Point* const end)
    : start(start), end(end)
  {
  }

  ~Line()
  {
    delete start;
    delete end;
  }

  Line deep_copy() const
  {
    // TODO
    Line new_line(new Point(start->x, start->y), new Point(end->x, end->y));
    return new_line;
  }
};

int main()
{
    Line line1(new Point(1, 2), new Point(3, 4));
    Line line2 = line1.deep_copy();

    cout << line1.start->x << " ";
    cout << line2.start->x << endl;

        cout << line1.start->y << " ";
    cout << line2.start->y << endl;

    assert(line1.start->x == line2.start->x);

    assert(line1.start->y == line2.start->y);


    return 0;
}