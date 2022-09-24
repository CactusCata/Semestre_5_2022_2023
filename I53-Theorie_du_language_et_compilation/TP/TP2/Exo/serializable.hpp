#ifndef SERIALIZABLE_HPP
#define SERIALIZABLE_HPP

#include <iostream>

class Serializable {

    public:

        virtual std::string serialize() = 0;

};

#endif