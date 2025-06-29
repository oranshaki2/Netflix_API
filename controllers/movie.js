const Movie = require('../models/movie');
const movieService = require('../services/movie');
const userService = require('../services/user');
const mongoose = require('mongoose');

async function generateIdNumber() {
    const allMovies = await movieService.getMovies();
    let highestId = 0;
    for (const movie of allMovies) {
        if (movie.idNumber > highestId) {
            highestId = movie.idNumber;
        }
    }
    // The first user will have an id of 1
    return highestId + 1;
}

// Create a new movie
const createMovie = async (req, res) => {
    const userId = req.headers['x-user-id'];
    if (!userId) {
        return res.status(400).json({ errors: ['User ID is required'] });
    }
    const { name, categoryIds } = req.body;
    const existingMovie = await Movie.findOne({ name });
    if (existingMovie) {
        return res.status(404).json({ errors: ['Movie already exists'] });
    }
    const idNumber = await generateIdNumber();
    const movie = await movieService.createMovie(name, categoryIds, idNumber);
    res.status(201).send();
};

// Get all movies
const getMovies = async (req, res) => {
    const userId = req.headers['x-user-id'];
    if (!userId) {
        return res.status(400).json({ errors: ['User ID is required'] });
    }
    try {
        const moviesByCategories = await movieService.getMoviesByCategories(userId);
        res.json(moviesByCategories);
    } catch (error) {
        res.status(400).json({ errors: [error.message] });
    }
};

// Get a specific movie by ID
const getMovie = async (req, res) => {
    const movie = await movieService.getMovieById(req.params.id);
    if (!movie) {
        return res.status(404).json({ errors: ['Movie not found'] });
    }
    res.json(movie);
};

// Update a specific movie by ID
const changeMovie = async (req, res) => {
    const userId = req.headers['x-user-id'];
    if (!userId) {
        return res.status(400).json({ errors: ['User ID is required'] });
    }
    const { name, categoryIds } = req.body;
    // Check if all parameters are provided
    if (!name || !categoryIds) return res.status(400).json({ errors: ['Name and category IDs are required'] });

    const updatedMovie = await movieService.updateMovie(req.params.id, { name, categoryIds });
    if (!updatedMovie) {
        return res.status(404).json({ errors: ['Movie not found'] });
    }

    res.status(204).send();
};

// Delete a specific movie by ID
const deleteMovie = async (req, res) => {
    const userId = req.headers['x-user-id'];
    if (!userId) {
        return res.status(400).json({ errors: ['User ID is required'] });
    }
    const movie = await movieService.deleteMovie(req.params.id);
    if (!movie) {
        return res.status(404).json({ errors: ['Movie not found'] });
    }

    res.status(204).send();
};

const getRecommendations = async (req, res) => {
    const userId = req.headers['x-user-id'];
    const movieId = req.params.id;
    if (!userId) {
        return res.status(400).json({ errors: ['User ID is required'] });
    }
    const existingUser = await userService.getUserById(userId);
    if (!existingUser) {
        return res.status(404).json({ errors: ['User ID not exsit'] });
    }
    const recommendations = await movieService.getRecommendations(userId, movieId);
    res.status(200).json(recommendations);
};

const createRecommendation = async (req, res) => {
    const userId = req.headers['x-user-id'];
    const movieId = req.params.id;

    if (!userId) {
        return res.status(400).json({ errors: ['User ID is required'] });
    }
    const userExists = await userService.getUserById(userId);
    if (!userExists) {
        return res.status(404).json({ errors: ['User not found'] });
    }

        const recommendation = await movieService.createRecommendation(userId, movieId);
        const statusCode = parseInt(recommendation.split(' ')[0], 10);
        res.status(statusCode).json();
};

// Search movies by query
const searchMovie = async (req, res) => {
    const query = req.params.query;

    try {
        const movies = await movieService.searchMovie(query);
        res.json(movies);
    } catch (error) {
        res.status(400).json({ errors: [error.message] });
    }
};

module.exports = { createMovie, getMovies, getMovie, changeMovie, deleteMovie, getRecommendations, createRecommendation, searchMovie };