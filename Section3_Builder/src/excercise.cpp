#include <string>
#include <ostream>
#include <iostream>
#include <vector>

using std::string;
using std::cout;
using std::endl;
using std::vector;

using std::ostream;

class CodeElement
{
    public:

    friend class CodeBuilder;

    CodeElement(const string& class_name)
    : class_name_(class_name) {}

    CodeElement(const string& name, const string& type):
    name_(name), type_(type)
    {

    }

    string class_name_;
    string name_, type_;
    vector<CodeElement> elements_;

};

class CodeBuilder
{
public:


  CodeBuilder(const string& class_name)
  : code_element_(class_name)
  {
    // todo
  }

  CodeBuilder& add_field(const string& name, const string& type)
  {
    // todo
    CodeElement added_code_element_(name, type);
    code_element_.elements_.emplace_back(added_code_element_);
    return *this;
  }

  friend ostream& operator<<(ostream& os, const CodeBuilder& obj)
  {
    // todo
    os << "class " << obj.code_element_.class_name_
    << "\n{\n";

    for(const auto& e: obj.code_element_.elements_)
    {
        os << "  " << e.type_ << " " << e.name_ << ";\n";
    }

    os << "};\n";

    return os;

  }


  CodeElement code_element_;

};


int main()
{

    auto cb = CodeBuilder{"Person"}.add_field("name", "string").add_field("age", "int");
    cout << cb;

    return 0;
}