#ifndef ICOMMANDS_H
#define ICOMMANDS_H

#include <map>
#include <sstream>
#include <string>
#include "dataUser/user.h"

using namespace std;

/*
 * The Icommands class serves as an abstract interface for defining command execution
 * behaviors in a system. It is designed to be inherited by concrete classes that implement
 * specific command functionalities.
 */

class Icommands 
{
    public:
        static const int INVALID_INPUT = 0;
        static const int INVALID_LOGIC_INPUT = -1;
        static const int VALID_INPUT = 1;

        // Implicitly declares a constexpr constructor
        Icommands() = default; 
        // Implicitly declares a destructor 
        ~Icommands() = default; 
        virtual void execute(map<int, user>& users) = 0;
        // Used by help
        virtual string execute() = 0; 
        // Used by recommend
        virtual string execute(map<int, user>& users, int flag) = 0; 
        virtual int isVaildInput(const string& input) = 0;
        virtual int isVaildInput(const string& input,map<int, user>& users, int flag) = 0;

};

#endif // ICOMMANDS