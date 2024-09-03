#ifndef FOO_HPP
#define FOO_HPP

#include "pimpl.h"

class Foo
{
    public:

    class impl;
    
    Pimpl<impl> impl_;

};


#endif