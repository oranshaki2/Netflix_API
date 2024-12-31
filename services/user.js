const User = require('../models/user');

// Create a new user
const createUser = async (username, password, email, watch_list, picture) => {
    const user = new User({
        username,
        password,
        email,
        watch_list,
        picture
    });

    await user.save();
    return user;
};

// Get user's details by id
const getUserById = async (id) => {
    return await User.findById // WE WILL CHANGE THIS LATER
};

// Get user's details by username
const getUserByUsername = async (username) => {
    return await User.findOne({ username });
};
