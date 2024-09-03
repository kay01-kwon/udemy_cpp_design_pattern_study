#include "excercise.h"

int main()
{
    SingleValue single_value{5};
    MultiValues multivalues;
    multivalues.add(4);
    multivalues.add(3);
    multivalues.add(2);


    cout << "The summation of single and multi values is " << endl;
    cout << sum({&single_value, &multivalues}) << endl;

    cout << "The product of single and multi values is " << endl;
    cout << product({&single_value, &multivalues}) << endl;


    return 0;
}