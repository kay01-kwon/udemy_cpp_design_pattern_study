#include <iostream>
#include <string>
#include <functional>

using std::cout;
using std::endl;
using std::function;
using std::string;

struct Logger
{
    public:

    Logger(const function<void()> &func, const string &name)
    : func_(func), name_(name){}

    void operator()() const
    {
        cout << " Entering " << name_ << endl;
        func_();
        cout << " Exiting " << name_ << endl;
    }

    private:
    function<void()> func_;
    string name_;

};


template <typename Func>
struct Logger2
{
    public:

    Logger2(Func func, const string &name)
    : func_(func), name_(name){}

    void operator()() const
    {
        cout << " Entering " << name_ << endl;
        func_();
        cout << " Exiting " << name_ << endl;
    }


    private:
    Func func_;
    string name_;
};

template <typename Func>
auto make_logger2(Func func, const string &name)
{
    return Logger2<Func>(func, name);
}

double add(double a, double b)
{
    cout << a << 
    " + " << b
    << " = " 
    << (a + b) << endl;
    return a + b;
}

template <typename> struct Logger3;

template <typename R, typename... Args>
struct Logger3<R(Args...)>
{
    public:

    Logger3(function<R(Args...)> func, const string &name)
    : func_(func), name_(name){}

    R operator() (Args ...args)
    {
        cout << " Entering " << name_ << endl;
        R result = func_(args...);
        cout << " Exiting " << name_ << endl;
        return result;
    }
    
    private:
    function<R(Args...)> func_;
    string name_;
};

template <typename R, typename... Args>
auto make_logger3(R (*func)(Args...), const string &name)
{
    return Logger3<R(Args...)>(function<R(Args...)>(func), name);
}

int main()
{
    Logger(
        []()
        {
            cout << " Hello" << endl;
        }
        , "HelloFunction"
    )();

    auto log2 = make_logger2(
        []()
        {
            cout << " Hello" << endl;
        }, "HelloFunction2"
    );

    log2();

    auto log3 = make_logger3(add, "AddFunction");
    auto result = log3(2,3);

    cout << "Result: " << result << endl;

    return 0;
}