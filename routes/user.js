// Import Express for routing
const express = require('express'); 
// Create a new router instance
const router = express.Router(); 
// Import the user controller
const userController = require('../controllers/user'); 

router.route('/')
    .post(userController.createUser);

router.route('/:id')
    .get(userController.getUserById)
    //.patch(userController.updateUser)
    //.delete(userController.deleteUser);

// Export the router to use it in the app
module.exports = router;