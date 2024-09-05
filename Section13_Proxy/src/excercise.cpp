#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;


class Person
{
  friend class ResponsiblePerson;
  int age;
public:
  Person(int age) : age(age) {}

  int get_age() const { return age; }
  void set_age(int age) { this->age=age; }

  string drink() const { return "drinking"; }
  string drive() const { return "driving"; }
  string drink_and_drive() const { return "driving while drunk"; }
};

class ResponsiblePerson
{
  public:
    ResponsiblePerson(const Person &person) : person_(person) {}
    // todo

    void set_age(int age)
    {
      person_.set_age(age);
    }
  
    string drink() const
    {
      if(person_.get_age() < 18)
        return "too young";
      return person_.drink();
    }

    string drive() const
    {
      if(person_.get_age() < 16)
        return "too young";
      return person_.drive();
    }

    string drink_and_drive() const
    {
      return "dead";
    }

private:
    Person person_;
};


int main()
{
  Person p(10);
  ResponsiblePerson rp(p);

  cout << rp.drink() << endl;
  cout << rp.drive() << endl;
  cout << rp.drink_and_drive() << endl;

  rp.set_age(20);

  cout << rp.drink() << endl;
  cout << rp.drive() << endl;
  cout << rp.drink_and_drive() << endl;



  return 0;
}