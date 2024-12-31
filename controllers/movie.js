const movieService = require('../services/movie');
const mongoose = require('mongoose');

// const createCategory = async (req, res) => {
//     const { name, promoted } = req.body;
//     // const userId = req.userId;  // Get userId from the request object
//     const userId = req.headers['x-user-id'];
//     // const userObjectId = new mongoose.Types.ObjectId(userId);

//     const existingCategory = await categoryService.getCategoryByName(name); 

//     // if (existingCategory) {
//     //     return res.status(201).json(existingCategory); exists
//     // }
//     if (existingCategory) {
//         // // If the category exists, check if the user is already associated with it
//         // if (existingCategory.users.includes(userId)) {
//         //     return res.status(201).json(existingCategory); 
//         // }

//         // If the user is not associated, add the userId to the category
//         existingCategory.userIds.push(userId);  // Assuming you have a `users` field in the category model

//         // Save the updated category
//         await existingCategory.save();

//         return res.status(201).json(existingCategory);   // Return the updated category
//     }

//     const category = await categoryService.createCategory(name, promoted, userId);  // Pass userId to the service
//     res.status(201).json(category);
// };

// const getCategories = async (req, res) => {
//     // const userId = req.userId;  // Get userId from the request object
//     const userId = req.headers['x-user-id'];
//     // try {
//         const categories = await categoryService.getCategories(userId);  // Pass userId to the service
//         res.json(categories);
//     // } catch (error) {
//     //     res.status(500).json({ errors: [error.message] });
//     // }
// };

// const getCategory = async (req, res) => {
//     // const userId = req.userId;  // Get userId from the request object
//     const userId = req.headers['x-user-id'];
//     try {
//         const category = await categoryService.getCategoryById(req.params.id, userId);  // Pass userId to the service
//         if (!category) {
//             return res.status(404).json({ errors: ['Category not found'] });
//         }
//         res.json(category);
//     } catch (error) {
//         res.status(404).json({ errors: ['Category not found'] });
//     }
// };

// const updateCategory = async (req, res) => {
//     const { name, promoted } = req.body;
//     // const userId = req.userId;  // Get userId from the request object
//     const userId = req.headers['x-user-id'];

//      // Fetch the category by ID and userId
//      const category = await categoryService.getCategoryById(req.params.id, userId);

//      // Check if the category exists and belongs to the user
//      if (!category) {
//          return res.status(404).json({ errors: ['Category not found or not associated with the user'] });
//      }

//      // Update the category with new data
//      const updatedCategory = await categoryService.updateCategory(req.params.id, { name, promoted, userId });
 

//      res.status(204).send();

//     // const existingCategory = await categoryService.getCategoryByName(name); 
//     // if (!existingCategory) {
//     //     return res.status(404).json({ errors: ['Category not found'] });
//     // }
//     // // try {
//     //     const category = await categoryService.updateCategory(req.params.id, { name, promoted, userId });  // Pass userId to the service
//     //     if (!existingCategory) {
//     //         return res.status(404).json({ errors: ['Category not found'] });
//     //     }
//     //     await category.save();
//     //     res.status(204).send();
//     // } catch (error) {
//     //     res.status(500).json({ errors: [error.message] });
//     // }
// };

// const deleteCategory = async (req, res) => {
//     // const userId = req.userId;  // Get userId from the request object
//     const userId = req.headers['x-user-id'];
//     // try {
//         const category = await categoryService.deleteCategory(req.params.id, userId);  // Pass userId to the service
//         if (!category) {
//             return res.status(404).json({ errors: ['Category not found'] });
//         }
        
//         res.status(204).send();
//     // } catch (error) {
//     //     res.status(500).json({ errors: [error.message] });
//     // }
// };

const getRecommendations = async (req, res) => {
    const userId = req.headers['x-user-id'];
    const movieId = req.params.id;

    try {
        const recommendations = await movieService.getRecommendations(userId, movieId);
        //res.json(recommendations);
        //res.status(204).send();
        } catch (error) {
        //res.status(500).json({ errors: [error.message] });
    }
};

const createRecommendation = async (req, res) => {
    const userId = req.headers['x-user-id'];
    const movieId = req.params.id;

    try {
        const recommendation = await movieService.createRecommendation(userId, movieId);
        //res.status(201).json(recommendation);
    } catch (error) {
        //res.status(500).json({ errors: [error.message] });
    }

};

// module.exports = { createCategory, getCategories, getCategory, updateCategory, deleteCategory };
module.exports = { getRecommendations, createRecommendation };