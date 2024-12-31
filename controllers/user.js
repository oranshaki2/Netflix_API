const userService = require('../services/user');
const mongoose = require('mongoose');
const fs = require('fs');
const path = require('path');

// Get the path to the directory containing the profile pictures
const pictureDirectory = path.join(__dirname, '../profilePics');

// Load the list of picture files once
const pictureFiles = fs.readdirSync(pictureDirectory).filter(file => file.endsWith('.jpg'));

const createUser = async (req, res) => {
    const { username, password, email, watch_list } = req.body;
    const existingUser = await userService.getUserByUsername(username);

    if (existingUser) {
        return res.status(201).json(existingUser);
    }

    // Select a random picture from the available files-
    // Math.random() generates a random number between 0 (inclusive) and 1 (exclusive)
    // The floor function Rounds the result down to the nearest whole number,
    // ensuring an index within the bounds of the array.
    const randomPicture = pictureFiles[Math.floor(Math.random() * pictureFiles.length)];
    // Construct the full path to the selected picture
    const picture = path.join(pictureDirectory, randomPicture);

    const user = await userService.createUser(username, password, email, watch_list, picture);
    res.status(201).json(user);
}

const getUserById = async (req, res) => {
    try {
        const user = await userService.getUserById(req.params.id);
        if (!user) {
            return res.status(404).json({ errors: ['User not found'] });
        }
        res.json(user);
    } catch (error) {
        res.status(404).json({ errors: ['User not found'] });
    }
}

module.exports = {
    createUser,
    getUserById
};