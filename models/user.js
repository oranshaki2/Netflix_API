const mongoose = require('mongoose');
const Schema = mongoose.Schema; 

const userSchema = new schema({
    username: {
        type: String,
        required: true,
        unique: true
    },

    password: { 
        type: String,
        required: true,
        // min: 7
    },

    email: { 
        type: String,
        required: true,
        unique: true,
        min: 5,
        max: 255,
    },

    watch_list:{
        type: [String], 
        default: []
    },

    picture: {
        type: String,
        default: 'default.jpg'
    },
});

module.exports = mongoose.model('User', userSchema);