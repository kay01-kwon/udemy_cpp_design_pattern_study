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

struct Document;

struct IMachine
{
    virtual void print(Document& doc) = 0;
    virtual void scan(Document& doc) = 0;
    virtual void fax(Document& doc) = 0;
};

struct MFP : IMachine
{
    void print(Document& doc) override
    {
        // Ok
    }

    void scan(Document& doc) override
    {
        // Not supported
    }

    void fax(Document& doc) override
    {
    }
};

struct Scanner : IMachine
{
    void print(Document& doc) override
    {
        // Not supported
    }

    void scan(Document& doc) override
    {
        // Ok
    }

    void fax(Document& doc) override
    {
        // Not supported
    }
};

struct IPrinter
{
    virtual void print(Document& doc) = 0;
};

struct IScanner
{
    virtual void scan(Document& doc) = 0;
};

struct IFax
{
    virtual void fax(Document& doc) = 0;
};


struct Printer : IPrinter
{
    void print(Document& doc) override
    {
        // Ok
    }
};

int main()
{
    return 0;
}