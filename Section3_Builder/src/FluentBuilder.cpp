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

using std::ostringstream;


class HtmlElement{

    friend class HtmlBuilder;

    public:

    string str(int indent = 0) const
    {
        ostringstream oss;
        string i(indent_size * indent, ' ');
        oss << i << "<" << name_ << ">" << endl;

        if(text_.size()> 0)
        {
            oss << string(indent_size * (indent + 1), ' ') << text_ << endl;
        }

        for(const auto&e: elements_)
            oss << e.str(indent + 1);

        oss << i << "</" << name_ << ">" << endl;
        return oss.str();
    }


    private:

    HtmlElement(){}

    HtmlElement(const string &name, const string &text): name_(name), text_(text){}

    string name_, text_;
    vector<HtmlElement> elements_;

    const size_t indent_size = 2;

};

struct HtmlBuilder
{
    HtmlElement root;

    HtmlBuilder(string root_name)
    {
        root.name_ = root_name;
    }

    HtmlBuilder& add_child(string child_name, string child_text)
    {
        HtmlElement e{child_name, child_text};
        root.elements_.emplace_back(e);
        return *this;
    }

    string str(int indent = 0) const { return root.str(indent);}

    operator HtmlElement() const { return root;}
};

int main()
{

    HtmlBuilder builder{"ul"};
    builder.add_child("li", "hello").add_child("li", "world");
    cout << builder.str(2) << endl;

    // HtmlElement builder = HtmlElement::build("ul").add_child("li","hello").add_child("li","world");


    return 0;
}