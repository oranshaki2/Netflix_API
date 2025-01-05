const User = require('../models/user');

// Create a new user
const createUser = async (username, password, idNumber, email, watch_list, picture) => {
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

const getUserByEmail = async (email) => {
    return await User.findOne({ email });
}

const getAllUsers = async () => {
    return await User.find({});
};

// Get a specific IDNumber user by id object
const getUserIdNumber = async (id) => {
    const user = await userService.getUserById(id);
    if (!user) {
        return res.status(404).json({ errors: ['User not found'] });
    }
    return user.idNumber;
};

module.exports = { createUser, getUserById, getUserByUsername, getUserByEmail, getAllUsers, getUserIdNumber };
