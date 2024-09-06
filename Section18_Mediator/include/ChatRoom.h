#ifndef CHATROOM_H
#define CHATROOM_H
#include "Person.h"

using std::vector;
using std::string;

class Person;

class ChatRoom
{
    public:

    void broadcast(const string &origin,
    const string &message);

    void join(Person* p);

    void message(const string &origin,
    const string &who, const string &message);

    private:

    vector<Person*> people_;

};



#endif