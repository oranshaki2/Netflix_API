# Netflix API
The project simulates the Netflix platform for watching movies and series.  
In this section, we built a web server that forms the core of the application and exposes a RESTful API,  
including saving data to a MongoDB server.  
We will implement the screens themselves in the next part, in this part we implemented the server-side functionality.  

## Installation
To set up the project and install dependencies, run the following commands:  
```bash
npm init -y  
npm install express  
npm install cors  
npm install mongoose  
npm install dotenv  
npm install axios  
```

## Running both servers using docker-compose:  
### Build the Docker Images  
Use the command:  
  ```bash
   docker-compose build 
  ```
Build the docker for the client:  
  ```bash
   docker build -f Dockerfile.client -t client . 
  ```
You can change 'client' as you wish.  

Start and run the multi-container Docker application using the following command:   
  ```bash
    docker-compose up
  ```
### In a seperate terminal, run the client:
First, check the name of the network using the following command:  
  ```bash
   docker network ls 
  ```
Then, run the client:  
  ```bash
    docker run -it --network <network_name> client
   ```
For example:  
   ```bash
    docker run -it --network netflix_api_My-network client
   ```
## Send curl commands:
If you want to see the output, use -i flag. Here is an example for POST command:  
  ```bash
   curl -i -X POST http://web-server:3000/api/users -H "Content-Type: application/json" -d '{
  "username": "oranshaki",
  "password": "securePassword123",
  "email": "oranshaki@gmail.com"
}'
   ```
## To view the MongoDB objects (such as databases, collections, and documents) use the following commands:  
List running containers-
   ```bash
    docker ps
   ```
Look for the container running MongoDB and note its CONTAINER ID or NAME.  
Access the MongoDB container:  
   ```bash
    docker exec -it <container_name_or_id> bash
   ```
Replace <container_name_or_id> with the appropriate value.  

Connect to MongoDB:  
Inside the container, use the MongoDB shell  
   ```bash
    mongosh
   ```
Once connected, you can interact with the database:  

List all databases:  
   ```bash
    show dbs;
   ```
Switch to a specific database:   
   ```bash
    use <database_name>;
   ```
List collections in the database:  
   ```bash
    show collections;
   ```
Query documents in a collection:  
   ```bash
    db.<collection_name>.find().pretty();
   ```

### To stop the running servers, use:  
   ```bash
   docker-compose down
   ```
---
## Examples of how the project works in action:  
### _Login and registration_  
Add a new user:  
![image](https://github.com/user-attachments/assets/8bc2a9c9-75d4-43e6-9ed3-eb9a3cc06ed1)  

Get user's details:  
First, check the user's id (in the _id field).  
![image](https://github.com/user-attachments/assets/92b61094-fe17-4b70-9d9d-4eb57d9565e8)  

Then, send a GET command using this id:  
![image](https://github.com/user-attachments/assets/c6c624a8-fc67-475e-9403-841213395883)  

Check if a user is registered to the system:  


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




