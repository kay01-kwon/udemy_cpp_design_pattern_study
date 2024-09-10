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

struct TextProcessor
{

    void clear()
    {
        oss_.str("");
        oss_.clear();
    }

    void append_list(const vector<string> &items)
    {
        list_strategy_->start(oss_);
        for(auto &item : items)
            list_strategy_->add_list_item(oss_, item);
        list_strategy_->end(oss_);
    }

    void set_output_format(const OutputFormat &format)
    {
        switch( format )
        {
            case OutputFormat::Markdown :
                list_strategy_ = make_unique<MarkdownListStrategy>();
                break;
            case OutputFormat::Html :
                list_strategy_ = make_unique<HtmlListStrategy>();
                break;
            default:
                break;
        }
    }

    string str() const { return oss_.str();}

    private:
        ostringstream oss_;
        unique_ptr<ListStrategy> list_strategy_;

};

int main()
{
    vector<string> items{"foo", "bar", "baz"};

    TextProcessor tp;

    tp.set_output_format(OutputFormat::Markdown);
    tp.append_list(items);
    cout << tp.str() << endl;
    
    tp.clear();
    tp.set_output_format(OutputFormat::Html);
    tp.append_list(items);
    cout << tp.str() << endl;


    return 0;
}