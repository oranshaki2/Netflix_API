// const categoryService = require('../services/category'); 


// const createCategory = async (req, res) => {
//     // Handle the creation of a new category.
//     const { name, promoted } = req.body; 
//     const category = await categoryService.createCategory(name, promoted); 
//     res.status(201).json(category); 
// };

// const getCategories = async (req, res) => {
//     // Handle retrieval of all categories.
//     const categories = await categoryService.getCategories(); // Call the service to get all categories.
//     res.json(categories); // Send the list of categories as the response.
// };

// const getCategory = async (req, res) => {
//     // Handle retrieval of a specific category by ID.
//     const category = await categoryService.getCategoryById(req.params.id); // Get the category using its ID from the URL.
//     if (!category) { // If the category doesn't exist, return a 404 error.
//         return res.status(404).json({ errors: ['Category not found'] });
//     }
//     res.json(category); // Send the category as the response.
// };

// // const updateCategory = async (req, res) => {
// //     // Handle updating an existing category.
// //     const { name, promoted } = req.body; // Extract updated name and description from the request body.
// //     const category = await categoryService.updateCategory(req.params.id, name, promoted); // Update the category by ID.
// //     if (!category) { // If the category doesn't exist, return a 404 error.
// //         return res.status(404).json({ errors: ['Category not found'] });
// //     }
// //     res.status(204).send(); // Send the updated category as the response.
// // };

// const updateCategory = async (req, res) => {
//     try {
//         const { name, promoted } = req.body; // Extract updated fields from the request body

//         // Attempt to update the category by ID
//         const category = await categoryService.updateCategory(req.params.id, { name, promoted });

//         // Check if the category exists
//         if (!category) {
//             return res.status(404).json({ errors: ['Category not found'] }); // Return 404 if no category is found
//         }

//         // Respond with 204 No Content if the update was successful
//         res.status(204).send();
//     } catch (error) {
//         // Handle unexpected errors
//         res.status(500).json({ errors: [error.message] });
//     }
// };

// const deleteCategory = async (req, res) => {
//     // Handle deletion of a category by ID.
//     const category = await categoryService.deleteCategory(req.params.id); // Delete the category by ID.
//     if (!category) { // If the category doesn't exist, return a 404 error.
//         return res.status(404).json({ errors: ['Category not found'] });
//     }
//     res.status(204).send();// Confirm successful deletion.
// };

// // Export the controller functions to use them in the routes.
// module.exports = { createCategory, getCategories, getCategory, updateCategory, deleteCategory };


const categoryService = require('../services/category');
const mongoose = require('mongoose');

const createCategory = async (req, res) => {
    const { name, promoted } = req.body;
    // const userId = req.userId;  // Get userId from the request object
    const userId = req.headers['x-user-id'];
    // const userObjectId = new mongoose.Types.ObjectId(userId);

    const existingCategory = await categoryService.getCategoryByName(name); 

    // if (existingCategory) {
    //     return res.status(201).json(existingCategory); exists
    // }
    if (existingCategory) {
        // // If the category exists, check if the user is already associated with it
        // if (existingCategory.users.includes(userId)) {
        //     return res.status(201).json(existingCategory); 
        // }

        // If the user is not associated, add the userId to the category
        existingCategory.userIds.push(userId);  // Assuming you have a `users` field in the category model

        // Save the updated category
        await existingCategory.save();

        return res.status(201).json(existingCategory);   // Return the updated category
    }

    const category = await categoryService.createCategory(name, promoted, userId);  // Pass userId to the service
    res.status(201).json(category);
};

const getCategories = async (req, res) => {
    // const userId = req.userId;  // Get userId from the request object
    const userId = req.headers['x-user-id'];
    // try {
        const categories = await categoryService.getCategories(userId);  // Pass userId to the service
        res.json(categories);
    // } catch (error) {
    //     res.status(500).json({ errors: [error.message] });
    // }
};

const getCategory = async (req, res) => {
    // const userId = req.userId;  // Get userId from the request object
    const userId = req.headers['x-user-id'];
    try {
        const category = await categoryService.getCategoryById(req.params.id, userId);  // Pass userId to the service
        if (!category) {
            return res.status(404).json({ errors: ['Category not found'] });
        }
        res.json(category);
    } catch (error) {
        res.status(404).json({ errors: ['Category not found'] });
    }
};

const updateCategory = async (req, res) => {
    const { name, promoted } = req.body;
    // const userId = req.userId;  // Get userId from the request object
    const userId = req.headers['x-user-id'];

     // Fetch the category by ID and userId
     const category = await categoryService.getCategoryById(req.params.id, userId);

     // Check if the category exists and belongs to the user
     if (!category) {
         return res.status(404).json({ errors: ['Category not found or not associated with the user'] });
     }

     // Update the category with new data
     const updatedCategory = await categoryService.updateCategory(req.params.id, { name, promoted, userId });
 

     res.status(204).send();

    // const existingCategory = await categoryService.getCategoryByName(name); 
    // if (!existingCategory) {
    //     return res.status(404).json({ errors: ['Category not found'] });
    // }
    // // try {
    //     const category = await categoryService.updateCategory(req.params.id, { name, promoted, userId });  // Pass userId to the service
    //     if (!existingCategory) {
    //         return res.status(404).json({ errors: ['Category not found'] });
    //     }
    //     await category.save();
    //     res.status(204).send();
    // } catch (error) {
    //     res.status(500).json({ errors: [error.message] });
    // }
};

const deleteCategory = async (req, res) => {
    // const userId = req.userId;  // Get userId from the request object
    const userId = req.headers['x-user-id'];
    // try {
        const category = await categoryService.deleteCategory(req.params.id, userId);  // Pass userId to the service
        if (!category) {
            return res.status(404).json({ errors: ['Category not found'] });
        }
        
        res.status(204).send();
    // } catch (error) {
    //     res.status(500).json({ errors: [error.message] });
    // }
};

module.exports = { createCategory, getCategories, getCategory, updateCategory, deleteCategory };
