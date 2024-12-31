const express = require('express');
const bodyParser = require('body-parser');
const cors = require('cors');
const mongoose = require('mongoose');
const categories = require('./routes/category');


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



// Start the server
const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
    console.log(`Server is running on port ${PORT}`);
});
