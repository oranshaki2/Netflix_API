const tokenService = require('../services/token');
const mongoose = require('mongoose');

// const getRecommendations = async (req, res) => {
//     const userId = req.headers['x-user-id'];
//     const movieId = req.params.id;

//     try {
//         const recommendations = await movieService.getRecommendations(userId, movieId);
//         //res.json(recommendations);
//         //res.status(204).send();
//         } catch (error) {
//         //res.status(500).json({ errors: [error.message] });
//     }
// };

// const createRecommendation = async (req, res) => {
//     const userId = req.headers['x-user-id'];
//     const movieId = req.params.id;

//     try {
//         const recommendation = await movieService.createRecommendation(userId, movieId);
//         //res.status(201).json(recommendation);
//     } catch (error) {
//         //res.status(500).json({ errors: [error.message] });
//     }

// };

const checkIfUserRegistered = async (req, res) => {
    const bodyJson = req.body;
    const { userName, password } = bodyJson;

    try{
        // Fetch the user by userName and password 
        //const user = await tokenService.getUserByUserNameAndPassword(userName, password);
        const user = await tokenService.checkIfUserRegistered(userName, password);
    } catch (error) {
        //res.status(500).json({ errors: [error.message] });
    }
};

// module.exports = { createCategory, getCategories, getCategory, updateCategory, deleteCategory };
module.exports = { checkIfUserRegistered };