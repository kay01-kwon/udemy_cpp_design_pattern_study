#include "ChatRoom.h"
#include "Person.h"

int main()
{
    ChatRoom room;

    Person john{"John"};
    Person jane{"Jane"};

    room.join(&john);
    room.join(&jane);

    john.say("Hi room");
    jane.say("Oh, hey John");

    Person simon{"Simon"};
    room.join(&simon);

    simon.say("Hi everyone!");

    jane.pm("Simon", "Glad you could join us, Simon!");
    

    return 0;
}