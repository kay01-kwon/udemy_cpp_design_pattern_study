#include "Person.h"


Person::Person(const string& name)
: name_(name)
{

}

void Person::say(const string &message) const
{
    room_->broadcast(name_, message);

}

void Person::pm(const string &who,
const string &message) const
{
    room_->message(name_, who, message);
}

void Person::receive(const string &origin,
const string &message)
{
    string s{origin + ": \" " + message + "\" "};
    cout << "[" << name_ << "'s chat session] " 
    << s << endl;
    chat_log_.push_back(s);
}

bool Person::operator==(const Person &rhs) const
{
    return name_ == rhs.name_;
}

bool Person::operator!=(const Person &rhs) const
{
    return name_ != rhs.name_;
}