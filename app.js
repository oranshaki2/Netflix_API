const express = require('express');
const bodyParser = require('body-parser');
const cors = require('cors');
const mongoose = require('mongoose');
const categories = require('./routes/category'); // Import the category routes.

const movies = require('./routes/movie'); // Import the movie routes.
const tokens = require('./routes/token');
const users = require('./routes/user');// Import the token routes.



require('dotenv').config({ path: './config/.env.local' });

mongoose.connect(process.env.CONNECTION_STRING);

// Check if the connection is successful
mongoose.connection.once('open', () => {
    console.log('Connected to MongoDB');
}).on('error', (error) => {
    console.error('Connection error:', error);
});
// Create a new Express application
const app = express();

app.use(cors());
app.use(express.json());
app.use(bodyParser.urlencoded({ extended: true }));


app.use('/api/categories', categories);

app.use('/api/movies', movies);
app.use('/api/tokens', tokens)

app.use('/api/users', users);



// Start the server
const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
    console.log(`Server is running on port ${PORT}`);
});
