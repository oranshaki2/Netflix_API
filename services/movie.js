const Category = require('../models/category');
const Movie = require('../models/movie');
const User = require('../models/user');
const axios = require('axios');
const UserController = require('../controllers/user');
const MovieController = require('../controllers/movie');


// Create a new movie
const createMovie = async (name, categoryIds, idNumber) => {
    const movie = new Movie({
        name,
        categoryIds,
        idNumber
    });

    await movie.save();
    return movie;
};

// Get all movies
const getMovies = async () => {
    return await Movie.find({});
};

// Get a specific movie by ID
const getMovieById = async (id) => {
    return await Movie.findById(id);
};

// Update a specific movie by ID
const updateMovie = async (id, { name, categoryIds }) => {
    const movie = await Movie.findById(id);
    if (!movie) return null;

    if (name) movie.name = name;
    if (categoryIds) {
        // Remove the first categoryId if it exists
        if (movie.categoryIds.length > 0) {
            movie.categoryIds.shift();
        }
        // Convert existing categoryIds and new categoryIds to a set to avoid duplicates
        const categoryIdsSet = new Set([categoryIds]);
        movie.categoryIds = Array.from(categoryIdsSet);

    }

    await movie.save();
    return movie;
};

// Delete a specific movie by ID
const deleteMovie = async (id) => {
    const movie = await Movie.findByIdAndDelete(id);
    if (movie) {
        // Remove the movie ID from the associated categories
        await Category.updateMany(
            { movieIds: id },
            { $pull: { movieIds: id } }
        );
    }
    return movie;
};

// Define a method that returns movie recommendations for a specific user and movie
const getRecommendations = async (userId, movieId) => {
    try {
        const command = `GET ${userId} ${movieId}`;
        const response = await axios.post(
            'https://localhost:8080', // Server URL
            { command } // Send the formatted string in the request body
        );
        console.log(response.data); // Return the response from the server
    } catch (error) {
        //console.error('Error sending data:', error.message);
    }
};

// Get a specific IDNumber movie by id object
const getMovieIdNumber = async (id) => {
    const movie = await movieService.getMovieById(id);
    if (!movie) {
        return res.status(404).json({ errors: ['Movie not found'] });
    }
    return movie.idNumber;
};

// Define a method that add a movie for a specific user and send it to the recommendation
//  system
const createRecommendation = async (userId, movieId) => {
    try {
        const userIdNumber = await UserController.getUserIdNumber(userId);
        const movieIdNumber = await MovieController.getMovieIdNumber(movieId);
        console.log({ userId, movieId });
        console.log({ userIdNumber, movieIdNumber });
        const command = `POST ${userIdNumber} ${movieIdNumber}`;
        const response = await axios.post(
            'https://localhost:8080', // Server URL
            { command } // Send the formatted string in the request body
        );
        console.log(response.data); // Return the response from the server
        if (response.data.includes('200 Ok')) {
            const user = await User.findById(userId);
            user.findByIdAndUpdate(userId, { $addToSet: { watch_list: movieId } });
        }
    } catch (error) {
        //console.error('Error sending data:', error.message);
    }
};

// Search movies by query
const searchMovie = async (query) => {
    return await Movie.find({
        $or: [
            { name: new RegExp(query, 'i') },
            { categoryIds: new RegExp(query, 'i') }
        ]
    });
};

// Get movies by categories
const getMoviesByCategories = async (userId) => {
    const user = await User.findById(userId);
    if (!user) {
        throw new Error('User not found');
    }

    const categories = await Category.find({});
    const moviesByCategories = [];

    for (const category of categories) {
        if (category.promoted.includes(userId)) {
            const movies = await Movie.find({
                _id: { $nin: user.watch_list },
                categoryIds: category._id
            }).limit(20);

            moviesByCategories.push({
                category: category.name,
                movies
            });
        }
    }

    const watchedMovies = await Movie.find({
        _id: { $in: user.watch_list }
    }).limit(20);

    moviesByCategories.push({
        category: 'Watched Movies',
        movies: watchedMovies
    });

    return moviesByCategories;
};

module.exports = { createMovie, getMovies, getMovieById, updateMovie, deleteMovie, getRecommendations, createRecommendation, searchMovie, getMoviesByCategories, getMovieIdNumber };
