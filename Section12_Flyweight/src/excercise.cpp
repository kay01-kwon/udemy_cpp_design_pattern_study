#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include <map>
#include <algorithm>


using std::cout;
using std::endl;
using std::ostringstream;
using std::string;
using std::vector;
using std::map;


struct Sentence
{
    struct WordToken
    {
        bool capitalize;
    };

    Sentence(const string &text)
    {
        std::istringstream iss(text);
        string word;
        int index = 0;
        while(iss >> word)
        {
            words_.push_back(word);
        }
    }

    WordToken& operator[](size_t index)
    {
        tokens_[index] = WordToken{true};
        return tokens_[index];
    }

    string str() const
    {
        vector<string> ws;
        for(size_t i = 0; i < words_.size(); i++)
        {
            string w = words_[i];
            auto it = tokens_.find(i);
            if(it != tokens_.end() && it->second.capitalize)
            {
                std::transform(w.begin(), w.end(), w.begin(), ::toupper);
            }
            ws.push_back(w);
        }

        ostringstream oss;
        for(size_t i = 0; i < ws.size(); i++)
        {
            oss << ws[i];
            if(i < ws.size() - 1)
                oss << " ";
        }
        return oss.str();
    }


    private:
    vector<string> words_;
    map<int, WordToken> tokens_;


};

int main()
{
    Sentence sentence("hello world");
    sentence[1].capitalize = true;
    cout << sentence.str() << endl;

    return 0;
}