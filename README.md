# Netflix API
The project simulates the Netflix platform for watching movies and series.  
In this section, we built a web server that forms the core of the application and exposes a RESTful API,  
including saving data to a MongoDB server.  
We will implement the screens themselves in the next part, in this part we implemented the server-side functionality.  

## Running the server using Dockerfile:  
The docker-compose allows running the web server and the recommendation system server.  
Use the command:  

## All possible commands:  
### _Login and registration_  
Add a new user:  

Get user's details:  

Check if the user exists in the system:  

### _User homepage_  
### Categories-  

If you want to see the list of available categories:  

Add a new category:  

Show details of a specific category:  

Update a specific category:  

Delete a specific category:  

### Movies-  

If you want to see the list of available movies arranged by promoted categories, and also the last 20 movies the user watched:  

Add a new movie:  

Show details of a specific movie:  

Change a specific movie:  

Delete a movie:  

### Recommendations-  

Displays movie recommendations for the current user based on a specific movie:  

Update the recommendation system that the current user watched a specific movie:  

### Search-  

Search for a movie by using keywords:  




