const Category = require('../models/category');
const Movie = require('../models/movie');
const User = require('../models/user');
const axios = require('axios');
const UserService = require('../services/user');
const net = require('net');

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
const deleteMovie = async (movieId) => {
    const movie = await Movie.findById(movieId);
    //const movie = await Movie.findByIdAndDelete(movieId);
    if (movie) {
        //console.log(movie);
        // Remove the movie ID from the associated categories
        await Category.updateMany(
            { movieIds: movieId },
            { $pull: { movieIds: movieId } }
        );
        const users = await User.find({ watch_list: movieId });
        const movieIdNumber = await getMovieIdNumber(movieId);

        // Iterate over the users and perform your action
        for (const user of users) {
            const userIdNumber = await getUserIdNumber(user._id);
            
            const command = `DELETE ${userIdNumber} ${movieIdNumber}`;
            // Call the function to send the command via net
            const response = await sendCommand(command, 'localhost', 8080);
            //console.log(response);
            await user.watch_list.pull(movieId.toString());
            await user.save();
        }
        await Movie.findByIdAndDelete(movieId);
    }
    return movie;
};

const getMoviesByIdNumbers = async (idNumbers) => {
    return Movie.find({ idNumber: { $in: idNumbers } }); // Fetch movies with matching idNumbers
};

// Define a method that returns movie recommendations for a specific user and movie
const getRecommendations = async (userId, movieId) => {
    const userIdNumber = await getUserIdNumber(userId);
    const movieIdNumber = await getMovieIdNumber(movieId);
    const user = await UserService.getUserById(userId);
    
    const command = `GET ${userIdNumber} ${movieIdNumber}`;
    // Call the function to send the command via net
    const response = await sendCommand(command, 'localhost', 8080);
    //console.log(response);
    if (response.trim().startsWith('200 Ok')) {
        // Extract data after the first two lines (200 Ok and the blank line)
        const responseLines = response.split('\n').map(line => line.trim());
        const idLine = responseLines[2] || ''; // Third line contains IDs (if present)
        
        // Split the line into individual numbers and parse them
        const idNumbers = idLine.split(' ').filter(id => id).map(id => {
            const num = Number(id);
            if (isNaN(num)) {
                throw new Error(`Invalid ID received: ${id}`);
            }
            return num;
        });
        const movieIds = await getMoviesByIdNumbers(idNumbers);

        // Convert the data to numbers (or leave as strings if needed)
        // const numericIdNumbers = idNumbers.filter(line => line).map(Number);

        // // Fetch MongoDB IDs for the movies using `idNumber`
        // const movieIds = await getMoviesByIdNumbers(numericIdNumbers);

        // Map and return MongoDB _id values
        const mongoIds = movieIds.map(movie => movie._id.toString());
        return mongoIds;
    }
    return [];
};

// Get a specific IDNumber movie by id object
const getMovieIdNumber = async (id) => {
    const movie = await Movie.findById(id);
    if (!movie) {
        //return res.status(404).json({ errors: ['Movie not found'] });
    }
    //console.log(movie.idNumber);
    return movie.idNumber;
};

const createRecommendation = async (userId, movieId) => {
    const userIdNumber = await getUserIdNumber(userId);
    const movieIdNumber = await getMovieIdNumber(movieId);
    const user = await UserService.getUserById(userId);
    // If the user has no watch_list, create a new recommendation
    if (user.watch_list.length === 0) {
        const command = `POST ${userIdNumber} ${movieIdNumber}`;

        // Call the function to send the command via net
        const response = await sendCommand(command, 'localhost', 8080);
        console.log(response);
        if (response.trim() === '201 Created') {
            UserService.updateUser(user, movieId);
        }
    }
    // If the user has a watch_list, update the recommendation
    else {
        const command = `PATCH ${userIdNumber} ${movieIdNumber}`;

        // Call the function to send the command via net
        const response = await sendCommand(command, 'localhost', 8080);
        console.log(response);
        if (response.trim() === '204 No Content') {
            UserService.updateUser(user, movieId);
        }
    }

};

const sendCommand = (command, host, port) => {
    return new Promise((resolve, reject) => {
        const client = new net.Socket();

        client.connect(port, host, () => {
            client.write(`${command}\n`);
        });

        client.on('data', (data) => {
            resolve(data.toString()); // Resolve the promise with server response
            client.destroy(); // Close the connection after receiving response
        });

        client.on('close', () => {
        });

        client.on('error', (err) => {
            reject(new Error(`Connection error: ${err.message}`)); // Reject the promise on error
        });
    });
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
    const watchedMoviesList = user.watch_list || [];
    const watchedMovies = watchedMoviesList.slice(-20);

    moviesByCategories.push({
        category: 'Watched Movies',
        movies: watchedMovies
    });

    return moviesByCategories;
};

// Get a specific IDNumber user by id object
const getUserIdNumber = async (id) => {
    const user = await UserService.getUserById(id);
    if (!user) {
        return res.status(404).json({ errors: ['User not found'] });
    }
    return user.idNumber;
};

module.exports = { createMovie, getMovies, getMovieById, updateMovie, deleteMovie, getRecommendations, createRecommendation, searchMovie, getMoviesByCategories, getMovieIdNumber, getUserIdNumber };
