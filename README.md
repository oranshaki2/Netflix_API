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

## Running the server using Dockerfile:  
### Build the Docker Images
The docker-compose allows running the web server and the recommendation system server.  
Use the command:  
  ```bash
   docker-compose build 
  ```
Start with the web server using the following command:  
  ```bash
    docker-compose run --name <server_name> web-server <choose_port>
  ```
For example:
   ```bash
    docker-compose run --name ntfx-web-server server 8080
   ```
### In a new terminal, run the recommendations system server using the following command:
   ```bash
    docker-compose run --name <rec_system_server_name> server <server_name> <choose_port>
   ```
For example:
   ```bash
    docker-compose run --name ntfx-server server ntfx-web-server 8080
   ```
### To stop a running container, use:
   ```bash
   docker stop <container_id_or_name>
   ```
### To remove a container, use:
   ```bash
   docker rm <server_or_client_image_id>
   ```
---
## Examples of how the project works in action: 
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




