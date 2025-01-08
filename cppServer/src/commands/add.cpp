#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include "commands/add.h"
#include "dataUser/movie.h"
#include "commands/Icommands.h"
#include "dataUser/user.h"
#include <stdexcept>
#include <regex>

using namespace std;

// A method that execute the add command
void add::execute(map<int, user> &users)
{
    // Check if the user ID is valid or the movie IDs vector is empty
    if (user_id <= INVALID_INPUT || movie_ids.empty())
    {
        return;
    }

    // Check if the user is need to be created
    if (users.find(user_id) == users.end())
    {
        // users.insert({user_id, user(user_id)});
        users.emplace(user_id, user(user_id)); // Insert a new user if not present
    }
    // Add the movies to the user
    for (movie movie_obj : movie_ids)
    {
        int movie_id_number = movie_obj.Get_ID();
        // Check if the movie ID is valid
        if (movie_id_number <= INVALID_INPUT)
        {
            continue;
        }

        // Find the iterator and dereference it to access the user object
        auto it = users.find(user_id);
        if (it != users.end())
        {
            it->second.addMovie(movie_id_number); // Access the user and call addMovie
        }
    }
}

// Consructor of add class
add::add(int user, const vector<int> &movies)
{
    this->user_id = user;
    // Create a movie object for each movie ID
    for (int movie_id : movies)
    {
        movie_ids.push_back(movie_id);
    }
}

// Default constructor
add::add() {}

// A static method that checks if a user already exists
bool add::userExists(map<int, user> &users, int user_id)
{
    // Check if the user exists return true if the user exists, otherwise return false
    return users.find(user_id) != users.end();
}

// not used
int add::isVaildInput(const string &input)
{
    return INVALID_INPUT;
}

int add::isVaildInput(const string &input, map<int, user> &users, int flag)
{
    int userId = user::stringToUser(input);
    vector<int> movieIds = user::stringToMovies(input);
    //check if the user ID is a positive integer
    if (userId <= INVALID_INPUT)
    {
        return INVALID_INPUT;
    }
    // Check if the movie IDs is not empty
    else if(movieIds.empty()){
        return INVALID_INPUT;
    }
    // Check if the user is exists because we need to create a new user
    else if (userExists(users, userId) && flag == post)
    {
        return INVALID_LOGIC_INPUT;
    }
    // Check if the user is not exists because we need to add movies to an existing user
    else if (!userExists(users, userId) && flag == patch)
    {
        return INVALID_LOGIC_INPUT;
    }
    else{
        return VALID_INPUT;
    }

}

string add::execute(){return "";}
string add::execute(map<int, user> &users, int flag){return "";}
