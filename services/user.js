const User = require('../models/user');

// Create a new user
const createUser = async (username, password, email, watch_list, picture) => {
    const user = new User({
        username,
        password,
        idNumber,
        email,
        watch_list,
        picture
    });

    await user.save();
    return user;
};

// Get user's details by id
const getUserById = async (id) => {
    return await User.findById(id);
};

// Get user's details by username
const getUserByUsername = async (username) => {
    return await User.findOne({ username });
};

const getAllUsers = async () => {
    return await User.find({});
};

module.exports = { createUser, getUserById, getUserByUsername, getAllUsers };
