const Movie = require('../models/movie');

// Check if the user is registered by given userName and password
const checkIfUserRegistered = async (userName, password, res) => {
    // const bodyJson = req.body;
    // const { userName, password } = bodyJson;
    // Fetch the user by userName and password 
    const user = await tokenService.getUserByUserNameAndPassword(userName, password);
    
         // If the userName and password belong to registered user
         if (user) {
            return res.json({ id: user.id });
        // If the userName and password do not belong to a registered user
         } else {
                return res.status(404).json({ errors: ['User name or password are not associated with registered user'] });
         }

}; // It will change in the next exercise

// Get a user by userName and password
const getUserByUserNameAndPassword = async (userName, password) => {
    return await users.findOne({ userName, password }); // Find user by userName and password
};

module.exports = { checkIfUserRegistered, getUserByUserNameAndPassword };
