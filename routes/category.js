const express = require('express'); 
const router = express.Router();
const categoryController = require('../controllers/category'); 

// Middleware to check if the user is logged in by validating the user ID in the header
router.use((req, res, next) => {
     // Allow GET requests without authentication
    if (req.method === 'GET') {
        return next();
    }
     // Extract the user ID from the header
    const userId = req.headers['x-user-id'];

    // Return an error if no user ID is provided
    if (!userId) {
        return res.status(401).json({ error: 'User not authenticated' }); 
    }

    req.userId = userId;  
    next();  
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
