const mongoose = require('mongoose');
const Schema = mongoose.Schema; 

const userSchema = new Schema({
    username: {
        type: String,
        required: true,
        unique: true
    },

    password: { 
        type: String,
        required: true,
        min: 7
    },

    idNumber: {
        type: Number,
        required: true,
        unique: true,
    },

    email: { 
        type: String,
        required: true,
        unique: true,
        min: 5,
        max: 255,
    },

    watch_list: {
        type: [String], 
        default: []
    },

    picture: {
        type: String,
        default: 'default.jpg'
    },
}, {versionKey: false}); // Disable the version key from the schema.

// Transform the output to exclude `idNumber`
userSchema.set('toJSON', {
    transform: (doc, ret) => {
        // Remove the `idNumber` field
        delete ret.idNumber; 
        // Remove sensitive data like `password`
        // delete ret.password; 
        return ret;
    }
});

module.exports = mongoose.model('User', userSchema);