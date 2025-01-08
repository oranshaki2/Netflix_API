#ifndef ADD_H
#define ADD_H

#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "dataUser/movie.h"
#include "commands/Icommands.h"

using namespace std;

// The add class creates a new user and adds movies to the user
class add : public Icommands 
{

    int user_id;
    vector<int> movie_ids;

    private:

    public:
        static const int post = 1;
        static const int patch = 0;

        // Constructor
        add(int user, const vector<int>& movies);
        add();
        
        void execute(map<int, user>& users);
        string execute();
        string execute(map<int, user> &users, int flag);

        static bool userExists(map<int, user>& users, int user_id);
        int isVaildInput(const string& input);
        int isVaildInput(const string& input,map<int, user>& users, int flag);
};

#endif // ADD_H