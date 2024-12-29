const express = require('express'); // Import Express for routing.
const router = express.Router(); // Create a new router instance.
const categoryController = require('../controllers/category'); // Import the category controller.

// Middleware to check if the user is logged in by validating the user ID in the header
router.use((req, res, next) => {
    const userId = req.headers['x-user-id']; // Extract the user ID from the header

    if (!userId) {
        return res.status(401).json({ error: 'User not authenticated' }); // Return an error if no user ID is provided
    }

    req.userId = userId;  // Store user ID in the request object for later use
    next();  // Proceed to the next middleware or route handler
});

// Define the route for getting all categories and creating a new category.
router.route('/')
    .get(categoryController.getCategories) // Map GET /categories to getCategories.
    .post(categoryController.createCategory); // Map POST /categories to createCategory.

// Define the route for specific category operations by ID.
router.route('/:id')
    .get(categoryController.getCategory) // Map GET /categories/:id to getCategory.
    .patch(categoryController.updateCategory) // Map PATCH /categories/:id to updateCategory.
    .delete(categoryController.deleteCategory); // Map DELETE /categories/:id to deleteCategory.

// Export the router to use it in the app.
module.exports = router;
