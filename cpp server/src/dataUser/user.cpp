#include <set>
#include <iostream>
#include "dataUser/movie.h"
#include "dataUser/user.h"
#include <regex>
#include <string>
#include <vector>
#include <sstream>

using namespace std;
int userId;
user::user()
{
    this->user_id = userId;
}
// Consructor of user class
user::user(int id)
{
    this->user_id = id;
    userId = id;
}


// Disconstructor of user class
user::~user()

{
    // Delete all dynamically allocated movie objects
    for (movie* m : this->movies) {
        delete m;
    }
    // Clear the set to remove dangling pointers
    movies.clear(); 
}

// A method that get specific movie id, define new movie with this id and
// add it to the movies set of the user 
void user::addMovie(int movie_id) 
{
    movie* new_movie = new movie(movie_id);
    movies.insert(new_movie);
}
// A method that get specific movie id and remove it from the movies set of the user
void user::removeMovie(int movie_id) {
       for (auto it = movies.begin(); it != movies.end(); ++it) {
        if ((*it)->Get_ID() == movie_id) {
            delete *it;
            movies.erase(it);
            break;
        }
    }
}
// A method that get a user and return a set of all the movies ids that he watched
set<int> user::Get_movies_ids()
{
    // Declare on empty set of int
    set<int> set_of_movies_id;

    // Iterate over the movies set of the user
    for (const movie* m : this->movies)
    {
        set_of_movies_id.insert(m->Get_ID());
    }  
    return set_of_movies_id;
}

int user::getUserId() const 
{
    int userID = this->user_id;
    return user_id;
}

void user::print_movie()
{
    for (const movie* m : this->movies)
    {
        cout << m->Get_ID() << endl;
    }
    cout << endl;
}

// A static method that checks if the string is an integer
bool user::isInteger(const std::string &str)
{
    // Check if the string matches the integer format
    std::regex intRegex("^-?\\d+$");
    std::istringstream iss(str);
    std::string token;

    while (iss >> token) {
        if (!std::regex_match(token, intRegex)) {
            return false;
        }
    }
    return true;
}

// A static method that converts a string to an integer of the first word
int user::stringToUser(const string &str) {
    if(!isInteger(str)){
        return 0;
    }
    // Create a string stream from the input
    istringstream iss(str);
    int userId;
    // Get the first integer
    iss >> userId;
    return userId;
}

// A static method that converts a string to a vector of integers from the second word
vector<int> user::stringToMovies(const string &str) {
    vector<int> movieIds = {};
    // if the movie id is not an integer return an empty vector
    if(!isInteger(str)){
        return movieIds;
    }
    // Create a string stream from the input
    istringstream iss(str);
    int userId;
    // Skip the first integer
    iss >> userId; 
    int movieId;
    // Get the rest of the integers
    while (iss >> movieId) {
        if(movieId <= 0){
            return movieIds = {};
        }
        movieIds.push_back(movieId);
    }
    return movieIds;
}

// A static method that converts a string to an integer of the second word
int user::stringToMovie(const string &str) {
    if(!isInteger(str)){
        return 0;
    }
    // Create a string stream from the input
    istringstream iss(str);
    int firstId, secondId;
    // Skip the first integer
    iss >> firstId >> secondId;
    return secondId;
}