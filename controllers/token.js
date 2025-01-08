const tokenService = require('../services/token');

const checkIfUserRegistered = async (req, res) => {
    const { username, password } = req.body;

    // Fetch the user by userName and password 
    const user = await tokenService.getUserByUserNameAndPassword(username, password);
    if (user) {
        return res.status(200).json({ id: user.id });
        // If the userName and password do not belong to a registered user
    } else {
        return res.status(404).json({ errors: ['Username or password are not associated with registered user'] });
    }
};

module.exports = { checkIfUserRegistered };