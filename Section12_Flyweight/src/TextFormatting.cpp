#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::ostream;
using std::string;

using std::vector;


class FormatterText
{
    public:

    FormatterText(const string& plain_text)
    : plain_text_(plain_text)
    {
        caps_ = new bool[plain_text.length()];
    }

    ~FormatterText()
    {
        delete [] caps_;
    }

    void capitalize(int start, int end)
    {
        for(int i = start; i < end; i++)
            caps_[i] = true;
    }

    friend ostream& operator<<(ostream &os, const FormatterText &obj)
    {
        string s;
        for(int i = 0; i < obj.plain_text_.length(); i++)
        {
            char c = obj.plain_text_[i];
            s += obj.caps_[i] ? toupper(c):c;
        }
        return os << s;
    }

    private:
    string plain_text_;
    bool *caps_;


};

class BetterFormatterText
{
    public:

        BetterFormatterText(const string &plain_text)
        : plain_text_(plain_text) {}

        struct TextRange
        {
            int start, end;
            bool capitalize;

            bool covers(int position) const
            {
                return position >= start && position <= end;
            }
        };

        TextRange& get_range(int start, int end)
        {
            formatting_.push_back(TextRange{start, end});
            return *formatting_.rbegin();
        }

        friend ostream& operator<<(ostream& os, const BetterFormatterText &obj)
        {
            string s;
            for(int i = 0; i < obj.plain_text_.length(); i++)
            {
                char c = obj.plain_text_[i];
                for(const auto &range: obj.formatting_)
                {
                    if(range.covers(i) && range.capitalize)
                    {
                        c = toupper(c);
                    }
                    s += c ;
                }
            }
            return os << s;
        }

    private:

    string plain_text_;
    vector<TextRange> formatting_;

};


int main()
{
    FormatterText ft("This is a brave new world");

    ft.capitalize(10, 15);

    cout << ft << endl;

    BetterFormatterText bft("This is a brave new world");

    bft.get_range(10, 15).capitalize = true;

    cout << bft << endl;

    return 0;
}