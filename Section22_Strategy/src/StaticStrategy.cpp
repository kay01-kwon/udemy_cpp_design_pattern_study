#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <memory>

using std::cout;
using std::endl;
using std::string;
using std::ostringstream;
using std::vector;
using std::unique_ptr;
using std::make_unique;

enum class OutputFormat
{
    Markdown,
    Html
};

struct ListStrategy
{
    virtual ~ListStrategy() = default;
    virtual void start(ostringstream& oss) {}
    virtual void add_list_item(ostringstream& oss, const string& item) = 0;
    virtual void end(ostringstream& oss) {}
};

struct MarkdownListStrategy : ListStrategy
{
    void add_list_item(ostringstream& oss, const string &item) override
    {
        oss << " * " << item << endl;
    }
};

struct HtmlListStrategy : ListStrategy
{
    void start(ostringstream& oss) override
    {
        oss << "<ul>" << endl;
    }

    void add_list_item(ostringstream& oss, const string &item) override
    {
        oss << " <li> " << item << " </li> " << endl;
    }

    void end(ostringstream& oss) override
    {
        oss << "</ul>" << endl;
    }
};

template <typename LS>
struct TextProcessor
{

    void clear()
    {
        oss_.str("");
        oss_.clear();
    }

    void append_list(const vector<string> &items)
    {
        list_strategy_.start(oss_);
        for(auto &item : items)
            list_strategy_.add_list_item(oss_, item);
        list_strategy_.end(oss_);
    }

    string str() const { return oss_.str();}

    private:
        ostringstream oss_;
        LS list_strategy_;

};

int main()
{
    // Markdown
    TextProcessor<MarkdownListStrategy> tpm;
    tpm.append_list({"foo", "bar", "baz"});
    cout << tpm.str() << endl;

    // HTML
    TextProcessor<HtmlListStrategy> tph;
    tph.append_list({"foo", "bar", "baz"});
    cout << tph.str() << endl;

    return 0;
}