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


int main()
{
    auto text = "hello";
    string output;
    output += "<p>";
    output += text;
    output += "</p>";

    cout << output << endl;


    string words[] = { "hello", "world" };
    ostringstream oss;
    oss << "<ul>";
    for(auto w: words)
    {
        oss << "  <li>" << w << "</li>";
    }
    oss << "</ul>";

    cout << oss.str() << endl;


    return 0;
}