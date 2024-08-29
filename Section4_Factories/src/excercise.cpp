#include <string>
#include <iostream>
#include <memory>

using namespace std;

struct Person
{
  int id;
  string name;
};

class PersonFactory
{
public:
  Person create_person(const string& name)
  {
    // todo
    static int i = 0;
    return {i++, name};

  }
};

int main()
{
    PersonFactory pf;
    auto p = pf.create_person("John");
    auto p2 = pf.create_person("Jane");
    cout << p.name << " " << p.id << endl;
    cout << p2.name << " " << p2.id << endl;
    return 0;
}