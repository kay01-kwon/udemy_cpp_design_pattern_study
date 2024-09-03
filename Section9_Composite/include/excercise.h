#ifndef EXCERCISE_H
#define EXCERCISE_H

#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;

using std::vector;

struct ContainsIntegers
{
    virtual int sum() const = 0;
    virtual int product() const = 0;
};

struct SingleValue : ContainsIntegers
{
    public:

    SingleValue(): value_(0) {}

    explicit SingleValue(const int &value) 
    : value_(value) {}

    int sum() const override
    {
        return value_;
    }

    int product() const override
    {
        return value_;
    }


    private:

    int value_;

};

struct MultiValues : vector<int>, ContainsIntegers
{
    public:

    void add(const int &value)
    {
        push_back(value);
    }

    int sum() const override
    {
        return std::accumulate(begin(), end(), 0);   
    }

    int product() const override
    {
        return std::accumulate(begin(), end(), 1, std::multiplies<int>());
    }

};

int sum(const vector<ContainsIntegers*> items)
{
    int result = 0;

    for( auto item: items)
        result += item->sum();

    return result;
}

int product(const vector<ContainsIntegers*> items)
{
    int result = 1;

    for(auto item: items)
        result *= item->product();
    return result;
}

#endif