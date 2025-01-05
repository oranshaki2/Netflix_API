const userService = require('../services/user');
const mongoose = require('mongoose');
const fs = require('fs');
const path = require('path');

// Get the path to the directory containing the profile pictures
const pictureDirectory = path.join(__dirname, '../profilePics');

// Load the list of picture files once
const pictureFiles = fs.readdirSync(pictureDirectory).filter(file => file.endsWith('.jpg'));

async function generateIdNumber() {
    const allUsers = await userService.getAllUsers();
    let highestId = 0;
    for (const user of allUsers) {
        if (user.idNumber > highestId) {
            highestId = user.idNumber;
        }
    }
    // The first user will have an id of 1
    return highestId + 1;
}

const createUser = async (req, res) => {
    const { username, password, email, watch_list } = req.body;
    const existingUser = await userService.getUserByUsername(username);
    // Check if a user with the same username already exists
    if (existingUser) {
        return res.status(404).json({ errors: ['This username already exists.'] });
    }
    const existingEmail = await userService.getUserByEmail(email);
    // Check if a user with the same email already exists
    if (existingEmail) {
        return res.status(404).json({ errors: ['This email already exists.'] });
    }
    const validPassword = password.length >= 7;
    // Check if the password meets the minimum length requirement
    if (!validPassword) {
        return res.status(400).json({ errors: ['Password must be at least 7 characters long.'] });
    }
    const validEmail = email.includes('@') && email.includes('.') && email.length >= 5;
    // Check if the email is valid
    if (!validEmail) {
        return res.status(400).json({ errors: ['Please enter a valid email address.'] });
    }

    // Select a random picture from the available files-
    // Math.random() generates a random number between 0 (inclusive) and 1 (exclusive)
    // The floor function Rounds the result down to the nearest whole number,
    // ensuring an index within the bounds of the array.
    const randomPicture = pictureFiles[Math.floor(Math.random() * pictureFiles.length)];
    // Construct the full path to the selected picture
    const picture = path.join(pictureDirectory, randomPicture);
    const idNumber = await generateIdNumber();
    const user = await userService.createUser(username, password, idNumber, email, watch_list, picture);
    res.status(201).send();
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