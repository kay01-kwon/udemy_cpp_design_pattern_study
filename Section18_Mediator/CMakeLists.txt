cmake_minimum_required(VERSION 3.12)
project(Section18_Mediator)

# set(CMAKE_CXX_STANDARD 17)

include_directories(
    include
)

add_executable(ChatRoom
    src/main_chat_room.cpp
    include/Person.cpp
    include/ChatRoom.cpp
)