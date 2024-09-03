#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;


struct GraphicObject
{
    virtual void draw() = 0;
};

struct Circle : GraphicObject
{
    void draw() override
    {
        cout << "Circle" << endl;
    }
};

struct Group : GraphicObject
{
    public:

    explicit Group(const string &name) : name_(name) {}

    void draw() override
    {
        cout << "Group " << name_.c_str() << " contains: " << endl;

        for(auto &o: objects_)
            o->draw();
    }

    vector<GraphicObject*> objects_;

    private:

    string name_;

};


int main()
{
    Group root("root");

    Circle c1, c2;

    root.objects_.push_back(&c1);

    Group subgroup("sub");

    subgroup.objects_.push_back(&c2);

    root.objects_.push_back(&subgroup);

    root.draw();


    return 0;
}