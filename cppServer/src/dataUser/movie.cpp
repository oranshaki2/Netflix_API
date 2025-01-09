#include "dataUser/movie.h"

using namespace std;

// Constuctor of movie
movie::movie(int id)
{
    this->movie_id = id;
}

int movie::Get_ID() const
{
    return this->movie_id; 
}