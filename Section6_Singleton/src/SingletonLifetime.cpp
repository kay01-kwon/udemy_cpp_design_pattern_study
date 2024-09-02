#include "di.hpp"
#include <string>
#include <iostream>
#include <memory>
#include <boost/lexical_cast.hpp>

using namespace boost;

using std::string;
using std::cout;
using std::endl;

using std::make_unique;
using std::make_shared;

using std::ostream;


struct Engine
{
    float volume = 5;
    int horse_power = 400;

    friend ostream& operator<<(ostream& os, const Engine& obj)
    {
        os << "volume: " << obj.volume
        << " horse_power: " << obj.horse_power
        << endl;
        return os;
    }

};

struct ILogger
{
    virtual ~ILogger(){}

    virtual void Log(const string &s) = 0;
};

struct ConsoleLogger : ILogger
{
    ConsoleLogger() {}

    void Log(const string &s) override
    {
        cout << "LOG: " << s << endl;
    }
};

struct Car
{
    std::unique_ptr<Engine> engine_;
    std::shared_ptr<ILogger> logger_;

    Car(std::unique_ptr<Engine> engine,
    const std::shared_ptr<ILogger> &logger)
    : engine_(std::move(engine)), logger_(logger)
    {
        logger_->Log("Making a car");
    }

    friend ostream& operator<<(ostream& os, const Car& obj)
    {
        os << "Car with engine: " << *obj.engine_;
        return os;
    }
};

int main()
{
    auto logger = make_shared<ConsoleLogger>();
    auto c = make_shared<Car>(make_unique<Engine>(Engine{5, 400}), logger);

    auto injector = di::make_injector(
    di::bind<ILogger>.to<ConsoleLogger>()
    );

    auto car = injector.create<std::shared_ptr<Car>>();

    cout << *car << endl;

    return 0;
}