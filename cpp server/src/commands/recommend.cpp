#include "commands/recommend.h"
#include "dataUser/user.h"
#include "dataUser/movie.h"
#include "commands/Icommands.h"
#include <map>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <utility>
#include <sstream>

using namespace std;

// Implementation of the execute method
string recommend::execute(map<int, user> &users, int flag)
{
    // Check if the user ID is valid
    if (this->user_id <= INVALID_INPUT)
    {
        return "";
    }

    // Check if the movie ID is valid
    if (this->movie_id <= INVALID_INPUT)
    {
        return "";
    }

    // If the user doesn't exist, do nothing
    if (users.find(this->user_id) == users.end())
    {
        return "";
    }

    map<int, int> movie_scores;

    for (pair<const int, user> &user_pair : users)
    {
        int other_user_id = user_pair.first;
        user &other_user = user_pair.second;

        set<int> list_other_user = other_user.Get_movies_ids();

        // Skip the current user
        if (other_user_id == this->user_id)
            continue;

        // Calculate the number of common movies
        int common_movies = 0;

        auto it = users.find(this->user_id);
        if (it != users.end())
        {
            // Check if the user exists
            const std::set<int> &current_movies = it->second.Get_movies_ids();
            for (int movie : current_movies)
            {
                if (other_user.Get_movies_ids().count(movie))
                {
                    ++common_movies;
                }
            }
        }

        // Check if the conditions for recommendations are met
        if (common_movies > INVALID_INPUT && other_user.Get_movies_ids().count(this->movie_id))
        {
            // Iterate over other movies and compute scores
            for (int other_movie : other_user.Get_movies_ids())
            {
                if (other_movie != this->movie_id)
                {
                    if (users[this->user_id].Get_movies_ids().count(other_movie) == 0)
                    {
                        movie_scores[other_movie] += common_movies;
                    }
                }
            }
        }
    }

    // Sort movies by scores
    vector<pair<int, int>> sorted_movies(movie_scores.begin(), movie_scores.end());
    sort(sorted_movies.begin(), sorted_movies.end(),
         [](const pair<int, int> &a, const pair<int, int> &b)
         {
             // Sort by descending relevance, then ascending movie ID for ties
             if (a.second == b.second)
             {
                 return a.first < b.first;
             }
             return a.second > b.second;
         });

    int count = 0;
    // Output at most 10 recommendations
    string output = "";
    for (const pair<int, int> &movie_score : sorted_movies)
    {
        if (count == 10)
            break;
        output += to_string(movie_score.first) + " ";
        ++count;
    }
    return output;
}

// Constructor
recommend::recommend(int input_user, int input_movie)
{
    this->user_id = input_user;
    this->movie_id = input_movie;
}
recommend::recommend() {}

// not used
int recommend::isVaildInput(const string &input)
{
    return INVALID_INPUT;
}

int recommend::isVaildInput(const string &input, map<int, user> &users, int flag)
{
    int userId = user::stringToUser(input);
    int movieId = user::stringToMovie(input);
    vector<int> movieIds = user::stringToMovies(input);

     if (userId <= INVALID_INPUT || movieId <= INVALID_INPUT)
    {
        return INVALID_INPUT;
    }
    // Check if their is only one movie ID
    else if (movieIds.size() != VALID_INPUT)
    {
        return INVALID_INPUT;
    }
    // Check if the user exists
    else if(users.find(userId) == users.end())
    {
        return INVALID_LOGIC_INPUT;
    }
    else
    {
        return VALID_INPUT;
    }
}

string recommend::execute(){return "";}
void recommend::execute(map<int, user> &users){}
