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

using boost::lexical_cast;

enum class Color {red, green, blue};
enum class Size {small, medium, large};


struct Product
{
    string name;
    Color color;
    Size size;
};

struct ProductFilter
{
    vector<Product*> by_color(vector<Product*> items, Color color)
    {
        vector<Product*> result;
        for(auto& i : items)
        {
            if(i->color == color)
            {
                result.push_back(i);
            }
        }
        return result;
    }

    vector<Product*> by_size(vector<Product*> items, Size size)
    {
        vector<Product*> result;
        for(auto& i : items)
        {
            if(i->size == size)
            {
                result.push_back(i);
            }
        }
        return result;
    }

    vector<Product*> by_size_and_color(vector<Product*> items, Size size, Color color)
    {
        vector<Product*> result;
        for(auto& i : items)
        {
            if(i->size == size && i->color == color)
            {
                result.push_back(i);
            }
        }
        return result;
    }
};

template <typename T>
struct AndSpecification;

template <typename T>
struct Specification
{
    virtual bool is_satisfied(T* item) = 0;

    AndSpecification<T> operator&&(Specification<T>& other)
    {
        return AndSpecification<T>(*this, other);
    }
};

template <typename T>
struct Filter
{
    virtual vector<T*> filter(vector<T*> items, 
    Specification<T>& spec) = 0;
};

struct BetterFilter : Filter<Product>
{
    virtual vector<Product*> filter(vector<Product*> items, Specification<Product> &spec) 
    {
        vector<Product*> result;
        for(auto &item: items)
        {
            if(spec.is_satisfied(item))
            {
                result.push_back(item);
            }
        }
        return result;
    }
};

struct ColorSpecification: Specification<Product>
{
    Color color_;
    ColorSpecification(Color color): color_(color){}

    virtual bool is_satisfied(Product* item)
    {
        return item->color == color_;
    }
};

struct SizeSpecification: Specification<Product>
{
    Size size_;
    SizeSpecification(Size size): size_(size){}

    virtual bool is_satisfied(Product* item)
    {
        return item->size == size_;
    }
};

template <typename T>
struct AndSpecification: Specification<T>
{
    Specification<T>& first_;
    Specification<T>& second_;

    AndSpecification(Specification<T>& first,
    Specification<T>& second): first_(first), second_(second)
    {}

    virtual bool is_satisfied(T* item)
    {
        return first_.is_satisfied(item) && second_.is_satisfied(item);
    }
};


int main()
{
    Product apple{"Apple", Color::green, Size::small};
    Product tree{"Tree", Color::green, Size::large};
    Product house{"House", Color::blue, Size::large};

    vector<Product*> items{&apple, &tree, &house};

    // ProductFilter pf;

    // auto green_things = pf.by_color(items, Color::green);

    // for(auto& item: green_things)
    // {
    //     cout << item->name << " is green" << endl;
    // }

    BetterFilter bf;

    ColorSpecification green(Color::green);

    for(auto &item: bf.filter(items, green))
    {
        cout << item->name << " is green " << endl;
    }

    SizeSpecification large(Size::large);
    AndSpecification<Product> green_and_large(green, large);
    
    auto spec = green && large;
    

    for(auto &item: bf.filter(items, spec))
    {
        cout << item->name << " is green and large " << endl;
    }

    



    return 0;
}