#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <tuple>
#include <sstream>
#include <memory>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::pair;
using std::ostream;
using std::initializer_list;

struct Tag
{
    string name_, text_;
    vector<Tag> children_;
    vector<pair<string, string>> attributes;

    friend ostream &operator<<(ostream &os, const Tag &tag)
    {
        os << "<" << tag.name_;

        for (const auto &att: tag.attributes)
            os << " " << att.first << "=\"" << att.second << "\"";
        
        if(tag.children_.size() == 0 && tag.text_.length() == 0)
        {
            os << "/>" << endl;
        }
        else
        {
            os << ">" << endl;

            if(tag.text_.length())
                os << tag.text_ << endl;
            
            for(const auto &child: tag.children_)
                os << child;

            os << "</" << tag.name_ << ">" << endl;
        }

        return os;
    }
    protected:

    Tag(const string &name, const string &text): name_(name), text_(text){}

    Tag(const string &name, const vector<Tag> &children):
    name_(name), children_(children){}
};

struct P: Tag
{
    P(const string &text): Tag{"p", text}{}
    P(initializer_list<Tag> children): Tag{"p", children}{}
};

struct IMG : Tag
{
    explicit IMG(const string &url): Tag{"img",""}
    {
        attributes.emplace_back(make_pair("src", url));
    }
};

int main()
{
    cout << P{IMG{"http://a.com/a.png"}} << endl;

    return 0;
}