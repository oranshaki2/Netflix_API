const categoryService = require('../services/category');
const mongoose = require('mongoose');

// A function to create a new category
const createCategory = async (req, res) => {
    const { name, promoted, movieIds } = req.body;
    const userId = req.headers['x-user-id'];
    const movieIdsArray = movieIds.split(' ');
    const category = await categoryService.createCategory(name, promoted, userId, movieIdsArray);
    res.status(201).send();
};

// A function to get all categories
const getCategories = async (req, res) => {
    //get userId from the request object or set it to null
    // so that all categories are returned even if the user is not authenticated
    const userId = req.headers['x-user-id'] || null;
    const categories = await categoryService.getCategories(userId);
    res.json(categories);
};

// A function to get a specific category by ID
const getCategory = async (req, res) => {
    // Get userId from the request object or set it to null
    const userId = req.headers['x-user-id'] || null;
    try {
        const category = await categoryService.getCategoryById(req.params.id, userId); 
        if (!category) {
            return res.status(404).json({ errors: ['Category not found'] });
        }
        res.json(category);
    } catch (error) {
        res.status(404).json({ errors: ['Category not found'] });
    }
};

// A function to update a category
const updateCategory = async (req, res) => {
    const { name, promoted , movieIds} = req.body;
     // Get userId from the request object
    const userId = req.headers['x-user-id'];

     // Fetch the category by ID and userId
     const category = await categoryService.getCategoryById(req.params.id, userId);

     // Check if the category exists and belongs to the user
     if (!category) {
         return res.status(404).json({ errors: ['Category not found or not associated with the user'] });
     }
       // Check if the new name already exists
    if (name) {
        const existingCategory = await categoryService.getCategoryByName(name);
        if (existingCategory && existingCategory._id.toString() !== req.params.id) {
            return res.status(404).json({ errors: ['Category name already used'] });
        }
    }

     // Update the category with new data
     const updatedCategory = await categoryService.updateCategory(req.params.id, { name, promoted, movieIds, userId });
     res.status(204).send();
};

// A function to delete a category
const deleteCategory = async (req, res) => {
     // Get userId from the request object
    const userId = req.headers['x-user-id'];
        const category = await categoryService.deleteCategory(req.params.id, userId);  
        if (!category) {
            return res.status(404).json({ errors: ['Category not found'] });
        }
        
        res.status(204).send();
};

module.exports = { createCategory, getCategories, getCategory, updateCategory, deleteCategory };
