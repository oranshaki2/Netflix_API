#ifndef MOVIE
#define MOVIE

/*
 * The movie class represents a movie entity with a unique identifier.
 * It provides a simple interface to manage and access movie-related data.
 */

class movie
{
private:
    int movie_id;
public:
    // Constructor
    movie(int id);

    //Disconstructor
    ~movie() = default;

    int Get_ID() const;
};

#endif // MOVIE