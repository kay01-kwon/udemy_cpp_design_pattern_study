#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::tuple;

enum class Relationship
{
    parent,
    child,
    sibling
};

struct Person
{
    string name;
};

struct RelationBrowser
{
    virtual vector<Person> find_all_children_of(const string& name) = 0;
};

struct Relationships : RelationBrowser    // Low-level module 
{
    vector<tuple<Person, Relationship, Person>> relations;

    void add_parent_and_child(const Person& parent, const Person& child)
    {
        relations.push_back({parent, Relationship::parent, child});
        relations.push_back({child, Relationship::child, parent});
    }

    vector<Person> find_all_children_of(const string& name) override
    {
        vector<Person> result;
        for(auto&& [first, rel, second]: relations)
        {
            if(first.name == name && rel == Relationship::parent)
            {
                result.push_back(second);
            }
        }
        return result;
    }
};

struct Research    // High-level module
{
    // Research(Relationships& relationships)
    // {
    //     auto& relations = relationships.relations;
    //     for(auto&& [first, rel, second]: relations)
    //     {
    //         if(first.name == "John" && rel == Relationship::parent)
    //         {
    //             cout << " John has a child called" << second.name << endl;
    //         }
    //     }
    // }

    Research(RelationBrowser& browser)
    {
        for(auto& child : browser.find_all_children_of("John"))
        {
            cout << "John has a child called " << child.name << endl;
        }
    }
};

int main()
{
    Person parent{"John"};
    Person child1{"Chris"}, child2{"Matt"};

    Relationships relationships;
    relationships.add_parent_and_child(parent, child1);
    relationships.add_parent_and_child(parent, child2);

    Research _(relationships);

    return 0;
}