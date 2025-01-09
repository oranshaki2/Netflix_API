#ifndef DELETECOMMAND_H
#define DELETECOMMAND_H

#include <vector>
#include <map>
#include <iostream>
#include <string>
#include "commands/Icommands.h"
#include "dataUser/user.h"

using namespace std;

// The deleteCommand class removes specific movies from a user
class deleteCommand : public Icommands 
{
    int user_id;
    vector<int> moviesToDelete;

    public:
        // Constructor
        deleteCommand(int user, const vector<int>& movies);
        deleteCommand();

        void execute(map<int, user>& users) override;
        string execute();
        string execute(map<int, user> &users, int flag);

        static bool userExists(const map<int, user>& users, int user_id);
        bool userHasAllMovies(map<int, user>& users);
        bool userHasAllMovies(map<int, user>& users,int userId ,vector<int> moviesDelete);
        int isVaildInput(const string& input);
        int isVaildInput(const string& input,map<int, user>& users, int flag=VALID_INPUT);
        
};

#endif // DELETECOMMAND_H