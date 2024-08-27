#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>

using std::string;
using std::vector;
using boost::lexical_cast;
using std::ofstream;

using std::cout;
using std::endl;


struct Journal{
    string title_;
    vector<string> entries_;
    Journal(const string &title): title_(title){}

    void add_entry(const string &entry)
    {
        static int count = 1;
        entries_.push_back(lexical_cast<string>(count++) + ": " + entry);
    }

    // void save(const string &filename)
    // {
    //     ofstream ofs(filename);
    //     for(auto& s : entries_)
    //     {
    //         ofs << s << std::endl;
    //     }

    // }

};

struct PersistenceManager{
    static void save(const Journal &j, const string &filename)
    {
        ofstream ofs(filename);
        for(auto& s: j.entries_)
        {
            ofs << s << endl;
        }
    }
};

int main()
{
    Journal journal("Dear Diary");

    journal.add_entry("I ate a bug");
    journal.add_entry("I cried today");

    // journal.save("diary.txt");

    PersistenceManager pm;
    pm.save(journal, "diary2.txt");


    getchar();



    return 0;
}