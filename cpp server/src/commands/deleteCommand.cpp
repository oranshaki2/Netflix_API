#include "commands/deleteCommand.h"
#include <vector>
#include <map>
#include <iostream>
#include <string>
#include "dataUser/user.h"

using namespace std;

// Constructor of deleteCommand class
deleteCommand::deleteCommand(int user, const vector<int>& moviesToDelete)
{
    this->user_id = user;
    this->moviesToDelete = moviesToDelete;
}

// Default constructor
deleteCommand::deleteCommand() {}

// A method that executes the delete command
void deleteCommand::execute(map<int, user>& users)
{   
    // Check if the user exists
    if (!userExists(users, user_id)) {
        return;
    }
    // Check if the user has all the specified movies
    if(!userHasAllMovies(users)){
        return;
    }
    auto it = users.find(user_id);
    // Remove the specified movies from the user
     for (int movie_id : moviesToDelete) {
        it->second.removeMovie(movie_id);
    }
}

// Static method to check if a user exists
bool deleteCommand::userExists(const map<int, user>& users, int user_id) {
    return users.find(user_id) != users.end();
}

// method to check if a user has all specified movies
bool deleteCommand::userHasAllMovies(map<int, user>& users) {
    auto it = users.find(this->user_id);
    if (it == users.end()) {
        return false;
    }
    set<int> user_movies = it->second.Get_movies_ids();
    for (int movie_id : moviesToDelete) {
        if (user_movies.find(movie_id) == user_movies.end()) {
            return false;
        }
    }
    return true;
}
bool deleteCommand::userHasAllMovies(map<int, user>& users,int userId ,vector<int> moviesDelete){
    auto it = users.find(userId);

    set<int> user_movies = users[userId].Get_movies_ids();
    for (int movie_id : moviesDelete) {
        if (user_movies.find(movie_id) == user_movies.end()) {
            return false;
        }
    }
    return true;
}

int deleteCommand::isVaildInput(const string& input) {
    return INVALID_INPUT;
}

int deleteCommand::isVaildInput(const string& input, map<int, user>& users, int flag) {
    int userId = user::stringToUser(input);
    vector<int> movieIds = user::stringToMovies(input);
    // map<int, user> usersCopy = users;
    //check if the user ID is a positive integer
    if (userId <= INVALID_INPUT)
    {
        return INVALID_INPUT;
    }
    // Check if the movie IDs is not empty
    else if(movieIds.empty()){
        return INVALID_INPUT;
    }
    // Check if the user is not exists because we delete from a user that does exist
    else if (!userExists(users, userId))
    {
        return INVALID_LOGIC_INPUT;
    }
    // Check if the user has all the specified movies
    else if(!userHasAllMovies(users,userId,movieIds)){
        return INVALID_LOGIC_INPUT;
    }
    else{
        return VALID_INPUT;
    }
}

string deleteCommand::execute(){return "";}
string deleteCommand::execute(map<int, user> &users, int flag){return "";}