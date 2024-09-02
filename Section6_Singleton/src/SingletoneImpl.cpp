#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>
#include <sstream>
#include <memory>
#include <cmath>
#include <map>
#include <boost/lexical_cast.hpp>
#include <filesystem>

using std::cout;
using std::endl;

using std::string;
using std::vector;
using std::ifstream;
using std::map;


namespace fs = std::filesystem;

using namespace boost;



class SingletonDatabase
{
    SingletonDatabase()
    {
        cout << "Initializing database" << endl;

        string current_directory;
        current_directory = fs::current_path().string();

        fs::path previous_directory = fs::current_path().parent_path();
        fs::current_path(previous_directory);

        string previous_directory_path = previous_directory.string();

        previous_directory_path += "/files/capitals.txt";

        ifstream ifs(previous_directory_path);

        string s, s2;

        while(getline(ifs, s))
        {
            getline(ifs, s2);
            // int pop = std::stoi(s2);
            int pop = lexical_cast<int>(s2);
            capitals[s] = pop;
        }
    }

    map<string, int> capitals;

    public:

    SingletonDatabase(SingletonDatabase const&) = delete;
    void operator=(SingletonDatabase const&) = delete;

    static SingletonDatabase& get()
    {
        static SingletonDatabase db;
        return db;
    }

    int get_population(const string& name)
    {
        return capitals[name];
    }
  
};

int main()
{
    string city = "Seoul";
    SingletonDatabase::get().get_population(city);
    
    cout << city << " has population "
    << SingletonDatabase::get().get_population(city) 
    << endl;

    return 0;
}