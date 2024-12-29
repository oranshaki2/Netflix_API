// const Category = require('../models/category'); // Import the Category model.

// const createCategory = async (name, promoted) => {
//     // Create a new category document with the provided name and promoted.
//     const category = new Category({ name, promoted }); // Create a new category instance.
//     await category.save(); // Save the category to the database and return it.
// };

// const getCategories = async () => {
//     // Retrieve all categories from the database.
//     return await Category.find({});
// };

// const getCategoryById = async (id) => {
//     // Find a specific category by its unique ID.
//     return await Category.findById(id);
// };

// // const updateCategory = async (id, name, promoted) => {
// //     // Update an existing category with the provided name and description.
// //     const category = await getCategoryById(id); // Find the category by ID.
// //     if (!category) return null; // If not found, return null.
// //     category.name = name || category.name; // Update the name if provided, otherwise keep the existing name.
// //     category.promoted = promoted || category.promoted; // Update the promoted if provided.
// //     await category.save(); // Save the changes to the database.
// //     // return category; // Return the updated category.
// // };

// const updateCategory = async (id, updates) => {
//     return Category.findByIdAndUpdate(id, updates, {
//         new: true, // Ensure the function returns the updated document
//         runValidators: true, // Validate the updates against the schema
//     });
// }; 

// // const deleteCategory = async (id) => {
// //     // Delete a category by its unique ID.
// //     const category = await getCategoryById(id); // Find the category by ID.
// //     if (!category) return null; // If not found, return null.
// //     await Category.deleteOne({ _id: id }); // Delete the category from the database.
// //     // return category; // Return the deleted category for confirmation.
// // };
// const deleteCategory = async (id) => {
//     // Delete category by ID and return the deleted document (or null if not found)
//     return Category.findByIdAndDelete(id);
// };

// // Export the service functions to use them in the controller.
// module.exports = { createCategory, getCategories, getCategoryById, updateCategory, deleteCategory };

// const Category = require('../models/category');

// const createCategory = async (name, promoted, userId) => {
//     const category = new Category({
//         name,
//         promoted,
//         users: [userId],  // Associate the category with the user
//     });

//     await category.save();
//     return category;
// };

// // Get a category by name
// const getCategoryByName = async (name) => {
//     return await Category.findOne({ name });  // Find category by name
// };


// const getCategories = async (userId) => {
//     // Fetch categories that are associated with the logged-in user
//     return await Category.find({ userId });
// };

// const getCategoryById = async (id, userId) => {
//     // Fetch a specific category by ID and make sure it belongs to the user
//     return await Category.findOne({ _id: id, userId });
// };

// const updateCategory = async (id, { name, promoted, userId }) => {
//     // Update the category and ensure it belongs to the user
//     return await Category.findOneAndUpdate(
//         { _id: id, userId },
//         { name, promoted },
//         { new: true }
//     );
// };

// const deleteCategory = async (id, userId) => {
//     // Delete the category and ensure it belongs to the user
//     return await Category.findOneAndDelete({ _id: id, userId });
// };

// module.exports = { createCategory, getCategories, getCategoryById, updateCategory, deleteCategory, getCategoryByName };


const Category = require('../models/category');

// Create a new category and associate it with an array of user IDs (userIds is an array of strings)
const createCategory = async (name, promoted, userIds) => {
    const category = new Category({
        name,
        promoted,
        userIds  // userIds is an array of strings
    });

    await category.save();
    return category;
};

// Fetch categories that are associated with a specific user (check if userId exists in the userIds array)
const getCategories = async (userId) => {
    return await Category.find({ userIds: userId });  // Check if userId exists in the userIds array
};

// Get a category by name
const getCategoryByName = async (name) => {
    return await Category.findOne({ name });  // Find category by name
};

// Fetch a specific category by ID and ensure it belongs to the user (check if userId exists in the userIds array)
const getCategoryById = async (id, userId) => {
    return await Category.findOne({ _id: id, userIds: userId });  // Check if userId exists in the userIds array
};

// Update a category and ensure it belongs to the user (adding/removing userId from the userIds array)
const updateCategory = async (id, { name, promoted, userId }) => {
//     return await Category.findOneAndUpdate(
//         { _id: id, userIds: { $in: userIds } },  // Ensure the userIds array contains the userIds
//         { name, promoted },
//         { new: true }
//     );
// };
    const updatedCategory = await Category.findOneAndUpdate(
    { _id: id, userIds: userId },    // Find by category ID and user ID
    { name, promoted },      // Fields to update
    { new: true }            // Return the updated category
    );

return updatedCategory;  // Return the updated category
};

// Delete a category and ensure it belongs to the user (check if userId exists in the userIds array)
const deleteCategory = async (id, userId) => {
    return await Category.findOneAndDelete({ _id: id, userIds: userId });  // Check if userId exists in the userIds array
};

module.exports = { createCategory, getCategories, getCategoryById, updateCategory, deleteCategory , getCategoryByName};
