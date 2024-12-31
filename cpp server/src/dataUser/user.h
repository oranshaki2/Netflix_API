#ifndef USER_H
#define USER_H

#include <set>
#include "dataUser/movie.h"
#include <iostream>
#include <vector>

using namespace std;

/*
 * The User class create a user with unique id and a set of movies that he watched.
 */

class user
{
private:
    int user_id;              
    set<movie*> movies;

public:
    // Constructor
    user(int id);
    user();

    // Destructor
    ~user();

    // Method to add a movie to the user's set of movies
    void addMovie(int movieId);
    void removeMovie(int movie_id);

    int getUserId() const;

    // Method to get a set of movies ids that the user watched
    set<int> Get_movies_ids();

    // Method to print the movies that the user watched
    void print_movie();
    static bool isInteger(const std::string &str);
    static int stringToUser(const string &str);
    static vector<int> stringToMovies(const string &str);
    static int stringToMovie(const string &str);
};

#endif // USER_H