const express = require('express'); // Import Express for routing.
const router = express.Router(); // Create a new router instance.
const movieController = require('../controllers/movie'); // Import the movie controller.

// // Middleware to check if the user is logged in by validating the user ID in the header
// router.use((req, res, next) => {
//     const userId = req.headers['x-user-id']; // Extract the user ID from the header

//     if (!userId) {
//         return res.status(401).json({ error: 'User not authenticated' }); // Return an error if no user ID is provided
//     }

//     req.userId = userId;  // Store user ID in the request object for later use
//     next();  // Proceed to the next middleware or route handler
// });

// Define the route for getting all movies for user and creating a new movie.
router.route('/')
    .get(movieController.getMovies)  // Get movies by categories.
    .post(movieController.createMovie); // Create a new movie.

// Define the route for specific movie operations by ID.
router.route('/:id')
    .get(movieController.getMovie) // Get a specific movie by ID.
    .put(movieController.changeMovie) //change a specific movie by ID.
    .delete(movieController.deleteMovie); // Delete a specific movie by ID.

// Define the route for getting recommendations and creating a new recommendation.    
router.route('/:id/recommend')
    .get(movieController.getRecommendations)
    .post(movieController.createRecommendation);

// Define the route for searching movies by query.
router.route('/search/:query')
    .get(movieController.searchMovie);

// Export the router to use it in the app.
module.exports = router;