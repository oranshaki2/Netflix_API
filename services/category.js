

const Category = require('../models/category');

// Create a new category and associate it with an array of user IDs (userIds is an array of strings)
const createCategory = async (name, promoted, userIds, movieIds) => {
    let category = await Category.findOne({ name });

    const movieIdsSet = new Set(movieIds);

    if (category) {
        if (promoted) {
            category.promoted.push(userIds);
        }
        if (!category.userIds.includes(userIds)) {
            category.userIds.push(userIds);
        }
        category.movieIds = Array.from(new Set([...category.movieIds, ...movieIdsSet]));
    } else {
        category = new Category({
            name,
            promoted: promoted ? [userIds] : [],
            userIds: [userIds],
            movieIds: Array.from(movieIdsSet)
        });
    }

    await category.save();
    return category;
};

// Fetch categories that are associated with a specific user (check if userId exists in the userIds array)
const getCategories = async (userId) => {
    const categories = await Category.find({});
    return categories.map(category => ({
        id: category._id,
        name: category.name,
        promoted: userId ? category.promoted.includes(userId) : false,
        movieIds: category.movieIds
    }));
};

// Get a category by name
const getCategoryByName = async (name) => {
    return await Category.findOne({ name });  
};

// Get a category by ID
const getCategoryById = async (id, userId) => {  
    const category = await Category.findOne({ _id: id });  
    if (!category) {
        return null;
    }
    return {
        id: category._id,
        name: category.name,
        promoted: userId ? category.promoted.includes(userId) : false,
        movieIds: category.movieIds
    };
};

const updateCategory = async (id, { name, promoted, movieIds, userId }) => {
    const category = await Category.findById(id);
    if (!category) return null;

    if (name) category.name = name;
    if (promoted !== undefined) {
        if (promoted) {
            if (!category.promoted.includes(userId)) {
                category.promoted.push(userId);
            }
        } else {
            category.promoted = category.promoted.filter(id => id !== userId);
        }
    }
    if (movieIds) {
        // Convert existing movieIds and new movieIds to a set to avoid duplicates
        const movieIdsSet = new Set([...category.movieIds, ...movieIds.split(' ')]);
        category.movieIds = Array.from(movieIdsSet);
    }

    await category.save();
    return category;
};

// Delete a category and ensure it belongs to the user (check if userId exists in the userIds array)
const deleteCategory = async (id, userId) => {
    return await Category.findOneAndDelete({ _id: id, userIds: userId }); 
};

module.exports = { createCategory, getCategories, getCategoryById, updateCategory, deleteCategory , getCategoryByName};
