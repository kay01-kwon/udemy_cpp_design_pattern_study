#include <iostream>
#include <string>
#include <boost/bimap.hpp>

using std::cout;
using std::endl;
using std::string;

using std::ostream;

using namespace boost;

typedef uint32_t key;


struct User
{
    User(const string &first_name, const string &last_name)
    : first_name_(add(first_name)), last_name_(add(last_name))
    {}

    const string& get_first_name() const
    {
        return names_.left.find(first_name_)->second;
    }

    const string& get_last_name() const
    {
        return names_.left.find(last_name_)->second;
    }

    friend ostream &operator<<(ostream &os, const User &obj)
    {
        os << "first name: " << obj.get_first_name()
        << " last name: " << obj.get_last_name()
        << "(" << obj.last_name_ << ")" << endl;

        return os;
    }



    protected:
    key first_name_, last_name_;

    static bimap<key, string> names_;
    static int seed;

    static key add(const string& name)
    {
        auto it = names_.right.find(name);
        if( it == names_.right.end())
        {
            key id = ++ seed;
            names_.insert(bimap<key, string>::value_type(seed, name));
            return id;
        }
        return it->second;
    }
};

int User::seed{0};
bimap<key, string> User::names_{};


int main()
{
    User user1("John", "Doe");
    User user2("Jane", "Doe");

    cout << user1 << endl;
    cout << user2 << endl;
    return 0;
}