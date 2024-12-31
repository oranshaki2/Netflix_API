#ifndef RECOMMENND_H
#define RECOMMENND_H

#include <map>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <utility>
#include "dataUser/user.h"
#include "commands/Icommands.h"

using namespace std;

/*
 * The recommend class is a specialized command class that extends the Icommands interface.
 * It is designed to handle the functionality of providing at most 10 movie recommendations
 *  for a specific user.
 */

class recommend : public Icommands 
{
    int user_id;
    int movie_id;

    public:
        // Constructor
        recommend(int user, int movie);
        recommend();

        void execute(map<int, user>& users);
        string execute();
        string execute(map<int, user>& users, int flag);

        int isVaildInput(const string& input);
        int isVaildInput(const string& input,map<int, user>& users, int flag = VALID_INPUT);

};

#endif // RECOMMENND_H