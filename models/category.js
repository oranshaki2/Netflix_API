const mongoose = require('mongoose');

const Schema = mongoose.Schema; 

// Define the schema for a category.
const Category = new Schema({
    name: { // Name of the category (e.g., Action, Drama, Thriller).
        type: String, 
        required: true, 
        unique: true
    },
    promoted: { // Indicates whether the category is promoted or not.
        type: Boolean,
        default: false, 
    },
    // description: { // Optional description for the category.
    //     type: String,
    // },
    userIds: { 
        type: [String], 
        required: true
     },
    createdAt: { // Timestamp for when the category was created.
        type: Date, 
        default: Date.now, 
    },
}, {versionKey: false}); // Disable the version key from the schema.

// Export the Mongoose model for categories to use it elsewhere in the application.
module.exports = mongoose.model('Category', Category);
