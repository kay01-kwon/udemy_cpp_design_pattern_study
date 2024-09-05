#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;


struct Image
{
    virtual void draw() = 0;
};

struct Bitmap : Image
{
    Bitmap(const string &filename)
    {
        cout << "Loading bitmap from " << filename << endl;
    }

    void draw() override
    {
        cout << "Drawing bitmap" << endl;
    }
};

struct LazyBitmap : Image
{
    LazyBitmap(const string &filename)
    : filename_(filename) {}

    void draw() override
    {
        if(!bmp_)
            bmp_ = new Bitmap(filename_);
        bmp_->draw();
    }

    private:
        string filename_;
        Bitmap *bmp_{nullptr};
};

int main()
{
    LazyBitmap bmp{"pokemon.png"};
    bmp.draw();


    return 0;
}