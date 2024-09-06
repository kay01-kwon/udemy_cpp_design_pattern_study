#include "ChatRoom.h"
#include <algorithm>

using std::find_if;


void ChatRoom::broadcast(const string &origin,
const string &message)
{
    for(auto p : people_)
    {
        if(p->name_ != origin)
        {
            p->receive(origin, message);
        }
    }
}

void ChatRoom::join(Person* p)
{
    string joint_msg = p->name_ +
    " joins the chat";
    broadcast("room", joint_msg);
    p->room_ = this;
    people_.push_back(p);
}

void ChatRoom::message(const string &origin,
const string &who, const string &message)
{
    auto target = find_if(people_.begin(), people_.end(),
    [&] (const Person* p)
    {
        return p->name_ == who;
    });

    if(target != people_.end())
    {
        (*target)->receive(origin, message);
    }
}