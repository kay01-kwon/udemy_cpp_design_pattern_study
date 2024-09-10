#include <iostream>
#include <vector>
#include <complex>
#include <tuple>
#include <limits>

using std::cout;
using std::endl;
using std::vector;
using std::complex;
using std::tuple;

struct DiscriminantStrategy
{
    virtual double calculate_discriminant(double a, double b, double c) = 0;
};

struct OrdinaryDiscriminantStrategy : DiscriminantStrategy
{
    double calculate_discriminant(double a, double b, double c) override
    {
        return b * b - 4 * a * c;
    }
};

struct RealDiscriminantStrategy : DiscriminantStrategy
{
    double calculate_discriminant(double a, double b, double c) override
    {
        double result = b * b - 4 * a * c;
        return result < 0 ? std::numeric_limits<double>::quiet_NaN() : result;
    }
};

class QuadraticEquationSolver
{
    public:
    QuadraticEquationSolver(DiscriminantStrategy &strategy)
    : strategy_(strategy)
    {}

    tuple<complex<double>, complex<double>> solve(double a, double b, double c)
    {
        complex<double> disc{strategy_.calculate_discriminant(a, b, c), 0};
        auto root_disc = sqrt(disc);
        return{
            (-b + root_disc) / (2 * a),
            (-b - root_disc) / (2 * a)
        };
    }

    private:
    DiscriminantStrategy &strategy_;

};

int main()
{
    {
        OrdinaryDiscriminantStrategy ordinary_strategy;
        QuadraticEquationSolver solver1(ordinary_strategy);
        auto result1 = solver1.solve(1, 10, 16);
        cout << "Ordinary Strategy "
        << "Root 1: " << std::get<0>(result1)
        << " Root 2: " << std::get<1>(result1);
        cout << endl;
    }


    cout << "**************************************" << endl;

    {
        RealDiscriminantStrategy real_strategy;
        QuadraticEquationSolver solver2(real_strategy);
        auto result2 = solver2.solve(1, 10, 16);
        cout << "Real Strategy "
        << "Root 1: " << std::get<0>(result2)
        << " Root 2: " << std::get<1>(result2);
        cout << endl;
    }



    cout << "**************************************" << endl;


    {
        OrdinaryDiscriminantStrategy ordinary_strategy;
        QuadraticEquationSolver solver1(ordinary_strategy);
        auto result1 = solver1.solve(1, 4, 5);
        cout << "Ordinary Strategy "
        << "Root 1: " << std::get<0>(result1)
        << " Root 2: " << std::get<1>(result1);
        cout << endl;
    }


    cout << "**************************************" << endl;

    {
        RealDiscriminantStrategy real_strategy;
        QuadraticEquationSolver solver2(real_strategy);
        auto result2 = solver2.solve(1, 4, 5);
        cout << "Real Strategy "
        << "Root 1: " << std::get<0>(result2)
        << " Root 2: " << std::get<1>(result2);
        cout << endl;
    }


    cout << "**************************************" << endl;

    return 0;
}