#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
#include <vector>
#include "ChatRoom.h"

using std::cout;
using std::endl;

using std::string;
using std::vector;

class ChatRoom;

class Person
{

    public:

    friend class ChatRoom;

    Person(const string& name);

    void say(const string &message) const;

    void pm(const string &who, 
    const string &message) const;

    void receive(const string &origin,
    const string &message);

    bool operator==(const Person& rhs) const;

    bool operator!=(const Person& rhs) const;


    private:

    string name_;
    ChatRoom* room_{nullptr};
    vector<string> chat_log_;
};


#endif