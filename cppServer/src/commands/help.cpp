#include "commands/help.h"
#include <iostream>

using namespace std;
string answer = 
    "DELETE, arguments: [userid] [movieid1] [movieid2] ...\n"
    "GET, arguments: [userid] [movieid]\n"
    "PATCH, arguments: [userid] [movieid1] [movieid2] ...\n"
    "POST, arguments: [userid] [movieid1] [movieid2] ...\n"
    "help\n";


// Executes the command and prints the help message
string help::execute(){
     return answer;
}

void help::execute(map<int, user>& users){}
string help::execute(map<int, user> &users, int flag){return "";}

// Check if the input is valid
int help::isVaildInput(const string& input) {
    // if the input is not empty it means that the input is not "help"
    if (!input.empty()){
        return INVALID_INPUT;
    }
    // if the input is empty it means that the input is "help"
    else{
        return VALID_INPUT;
    }
}
// not used
int help::isVaildInput(const string& input,map<int, user>& users, int flag) {
    return INVALID_INPUT;
}