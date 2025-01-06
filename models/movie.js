const mongoose = require('mongoose');
// const category = require('./movie');

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
    idNumber: {
        type: Number,
        required: true,
        unique: true
    },

    categoryIds: {  // Array of category IDs associated with the category.
        type: [String], 
    },

    createdAt: { // Timestamp for when the category was created.
        type: Date, 
        default: Date.now, 
    },
}, {versionKey: false}); // Disable the version key from the schema.

// Transform the output to exclude `idNumber`
Movie.set('toJSON', {
    transform: (doc, ret) => {
        // Remove the `idNumber` field
        delete ret.idNumber; 
        // Remove sensitive data like `password`
        // delete ret.password; 
        return ret;
    }
});

// Export the Mongoose model for categories to use it elsewhere in the application.
module.exports = mongoose.model('Movie', Movie);