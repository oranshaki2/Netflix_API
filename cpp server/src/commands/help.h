#ifndef HELP_H
#define HELP_H

#include <string>
#include <iostream>
#include "commands/Icommands.h" 

/*
 * The Help class is a concrete implementation of the Icommands interface.
 * Its purpose is to display the available commands and their usage instructions
 * when the user executes the `help` command.
 */
class help : public Icommands {
public:
    void execute(map<int, user>& users);
    string execute();
    string execute(map<int, user> &users, int flag);

    int isVaildInput(const string& input);
    int isVaildInput(const string& input,map<int, user>& users, int flag);
};

#endif // HELP_H
