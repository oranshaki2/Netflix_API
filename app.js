// const express = require('express');
// const bodyParser = require('body-parser');
// const cors = require('cors');
// const mongoose = require('mongoose');
// const articles = require('./routes/article');
// require('custom-env').env(process.env.NODE_ENV, './config');
// // mongoose.connect(process.env.CONNECTION_STRING,
// //     {
// //         useNewUrlParser: true,
// //         useUnifiedTopology: true
// //     });
// mongoose.connect(process.env.CONNECTION_STRING);
// var app = express();
// app.use(cors());
// app.use(bodyParser.urlencoded({ extended: true }));
// app.use(express.json());
// app.use('/articles', articles);
// app.listen(process.env.PORT);

// require('dotenv').config({ path: './config/.env.local' });

const express = require('express');
const bodyParser = require('body-parser');
const cors = require('cors');
const mongoose = require('mongoose');
const categories = require('./routes/category'); // Import the category routes.


require('dotenv').config({ path: './config/.env.local' });

mongoose.connect(process.env.CONNECTION_STRING);

mongoose.connection.once('open', () => {
    console.log('Connected to MongoDB');
}).on('error', (error) => {
    console.error('Connection error:', error);
});

const app = express();

app.use(cors());
app.use(express.json());
app.use(bodyParser.urlencoded({ extended: true }));


// app.use('/categories', categories); 
// app.use('/articles', articles); 
app.use('/api/categories', categories);



// Start the server
const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
    console.log(`Server is running on port ${PORT}`);
});
