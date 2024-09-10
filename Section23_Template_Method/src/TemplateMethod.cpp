#include <iostream>

using std::cout;
using std::endl;

class Game
{
    public:

    Game(int number_of_players) : number_of_players_(number_of_players) {}


    void run()
    {
        start();
        while(!have_winner())
        {
            take_turn();

            cout << "Player "<< get_winner() << " wins." << endl;
        }

    }

    protected:

    virtual void start() = 0;
    virtual bool have_winner() = 0;
    virtual void take_turn() = 0;
    virtual int get_winner() = 0;
    int current_player_{0};
    int number_of_players_;

};

class Chess : public Game
{
    public:

    Chess() : Game(2) {}

    Chess(int number_of_players) : Game(2) {}

    protected:

    void start() override
    {
        cout << " Starting a game of chess with "
        << "players. " << endl;
    }

    bool have_winner() override
    {
        return turns_ == max_turns_;
    }

    void take_turn() override
    {
        cout << "Turn " << turns_ << " taken by player"
        << current_player_ << endl;
        turns_++;
        current_player_ = (current_player_ + 1) % number_of_players_;
    }

    int get_winner() override
    {
        return current_player_;
    }

    private:

    int turns_{0}, max_turns_{10};

};

int main()
{
    Chess chess;
    chess.run();


    return 0;
}