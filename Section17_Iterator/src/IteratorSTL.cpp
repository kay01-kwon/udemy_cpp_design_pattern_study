#include <iostream>
#include <vector>
#include <string>

using std::cout;
using std::endl;
using std::vector;
using std::string;

int main()
{
    vector<string> names{"John", "Jane", "Julie", "Jack"};

    vector<string>::iterator it = names.begin();

    cout << "First name: " << *it << endl;

    ++it;

    it->append(" Goodall");

    cout << "Second name: " << *it << endl;

    while(++it != names.end())
    {
        cout << "Another name: " << *it << endl;
    }

    for(auto ri = rbegin(names); ri != rend(names); ++ri)
    {
        cout << *ri;

        if(ri + 1 != rend(names))
        {
            cout << ", ";
        }
    }
    cout << endl;

    vector<string>::const_reverse_iterator jack = crbegin(names);

    for(const auto& name: names)
    {
        cout << "name = " << name << endl;
    }


    return 0;
}