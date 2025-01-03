const mongoose = require('mongoose');
const category = require('./movie');

const Schema = mongoose.Schema; 

// Define the schema for a category.
const Movie = new Schema({
    name: { // Name of the movie
        type: String, 
        required: true, 
        unique: true
    },
    // userIds: { 
    //     type: [String], 
    //     required: true
    //  },
     categoryIds: {  // Array of category IDs associated with the category.
        type: [String], 
     },
    createdAt: { // Timestamp for when the category was created.
        type: Date, 
        default: Date.now, 
    },
}, {versionKey: false}); // Disable the version key from the schema.

// Export the Mongoose model for categories to use it elsewhere in the application.
module.exports = mongoose.model('Movie', Movie);