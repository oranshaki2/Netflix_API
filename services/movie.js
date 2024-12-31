const Movie = require('../models/movie');
const axios = require('axios');

// // Create a new category and associate it with an array of user IDs (userIds is an array of strings)
// const createCategory = async (name, promoted, userIds) => {
//     const category = new Category({
//         name,
//         promoted,
//         userIds  // userIds is an array of strings
//     });

//     await category.save();
//     return category;
// };

// // Fetch categories that are associated with a specific user (check if userId exists in the userIds array)
// const getCategories = async (userId) => {
//     return await Category.find({ userIds: userId });  // Check if userId exists in the userIds array
// };

// // Get a category by name
// const getCategoryByName = async (name) => {
//     return await Category.findOne({ name });  // Find category by name
// };

// // Fetch a specific category by ID and ensure it belongs to the user (check if userId exists in the userIds array)
// const getCategoryById = async (id, userId) => {
//     return await Category.findOne({ _id: id, userIds: userId });  // Check if userId exists in the userIds array
// };

// // Update a category and ensure it belongs to the user (adding/removing userId from the userIds array)
// const updateCategory = async (id, { name, promoted, userId }) => {
// //     return await Category.findOneAndUpdate(
// //         { _id: id, userIds: { $in: userIds } },  // Ensure the userIds array contains the userIds
// //         { name, promoted },
// //         { new: true }
// //     );
// // };
//     const updatedCategory = await Category.findOneAndUpdate(
//     { _id: id, userIds: userId },    // Find by category ID and user ID
//     { name, promoted },      // Fields to update
//     { new: true }            // Return the updated category
//     );

// return updatedCategory;  // Return the updated category
// };

// // Delete a category and ensure it belongs to the user (check if userId exists in the userIds array)
// const deleteCategory = async (id, userId) => {
//     return await Category.findOneAndDelete({ _id: id, userIds: userId });  // Check if userId exists in the userIds array
// };

// Define a method that returns movie recommendations for a specific user and movie
const getRecommendations = async (userId, movieId) => {
    try {
        const command = `GET ${userId} ${movieId}`;
        const response = await axios.post(
            'https://localhost:8080', // Server URL
            {command} // Send the formatted string in the request body
        );
        console.log(response.data); // Return the response from the server
    } catch (error) {
        //console.error('Error sending data:', error.message);
    }
};

// Define a method that add a movie for a specific user and send it to the recommendation
//  system
const createRecommendation = async (userId, movieId) => {
    try {
        const command = `POST ${userId} ${movieId}`;
        const response = await axios.post(
            'https://localhost:8080', // Server URL
            {command} // Send the formatted string in the request body
        );
        console.log(response.data); // Return the response from the server
        if (response.data.includes('200 Ok')){
            // להוסיף את החלק של הוספה של הסרט לסרטים שהיוזר צפה בהם
        }
    } catch (error) {
        //console.error('Error sending data:', error.message);
    }
};

// module.exports = { createCategory, getCategories, getCategoryById, updateCategory, deleteCategory , getCategoryByName};
module.exports = { getRecommendations, createRecommendation };
