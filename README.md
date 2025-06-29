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
## To view the MongoDB objects (such as databases, collections, and documents)  
## use the following commands:  
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

![תמונה של WhatsApp‏ 2025-01-09 בשעה 11 49 52_d45d3c1a](https://github.com/user-attachments/assets/609d07dc-29de-42d9-9c23-d25fa6ce1364)


### _User homepage_  
### Categories-  
Add a new category:  

![image](https://github.com/user-attachments/assets/3fe66847-a50c-410a-88ad-d353d2ef8e4f)


Show details of a specific category:  

![image](https://github.com/user-attachments/assets/40814820-7caf-4950-bbb3-5624442adfb6)

Notice that the category is not promoted by default.  

Update a specific category:  

![image](https://github.com/user-attachments/assets/dfd7ecb2-17ad-4105-9c12-b159a7f9a5c0)


And using GET command, see how "Horror" was changed to "Action"  

![image](https://github.com/user-attachments/assets/f3980d62-778b-4a2a-8d95-ce612317d56c)


See the list of available categories:  

![image](https://github.com/user-attachments/assets/bea096db-ef00-457b-91db-bc3a4b18f9a2)


Delete a specific category:  

![image](https://github.com/user-attachments/assets/5b99b4b6-7d99-418f-8a25-1bf96bbe48e5)

And using GET command, see how "Disney" is no longer available:  

![image](https://github.com/user-attachments/assets/8fb0fb10-c180-4edd-95c2-594bb0588b8e)


### Movies-  

Get a list of 20 available movies arranged by promoted categories,  
and also the last (at most) 20 movies the user watched:  
In the first example, we created 24 movies, and the user watched 3 of them.  

![תמונה של WhatsApp‏ 2025-01-09 בשעה 13 00 21_09619726](https://github.com/user-attachments/assets/cdb05682-9566-461a-b0b4-5db6f389a856)
![תמונה של WhatsApp‏ 2025-01-09 בשעה 13 01 00_8a824c28](https://github.com/user-attachments/assets/416175b3-4c05-44eb-9fed-c76de0c8ae26)
![תמונה של WhatsApp‏ 2025-01-09 בשעה 13 01 16_8b0ef9b2](https://github.com/user-attachments/assets/a674beab-4a8e-4a51-bb77-f300ab6d79b3)
![תמונה של WhatsApp‏ 2025-01-09 בשעה 13 02 00_43e4041d](https://github.com/user-attachments/assets/1c9648d0-8675-44b4-b83f-b0c19be7359b)
![תמונה של WhatsApp‏ 2025-01-09 בשעה 13 02 21_e3b9bdb7](https://github.com/user-attachments/assets/504e82aa-a266-443e-b241-42ef707f90f0)
![תמונה של WhatsApp‏ 2025-01-09 בשעה 13 02 41_015f0f37](https://github.com/user-attachments/assets/d62763e2-4525-4eeb-85f4-6494b0595d41)
![תמונה של WhatsApp‏ 2025-01-09 בשעה 13 03 00_f613914c](https://github.com/user-attachments/assets/c5f112b8-b9ee-4151-b7df-5d22ec72e494)
![תמונה של WhatsApp‏ 2025-01-09 בשעה 13 03 17_fb0248a4](https://github.com/user-attachments/assets/df5074de-e0cf-45d3-8364-a0f932a487e9)

In the seccond example, the user watched 21 movies and we get only 20 as reqired.  

![תמונה של WhatsApp‏ 2025-01-09 בשעה 14 41 47_b638cdca](https://github.com/user-attachments/assets/91e776cb-5ae3-48ee-8d49-08880d2ccd6c)

![תמונה של WhatsApp‏ 2025-01-09 בשעה 14 39 42_e20a0b1e](https://github.com/user-attachments/assets/9cf89780-bd02-45b8-93e6-4aa151620d58)
![תמונה של WhatsApp‏ 2025-01-09 בשעה 14 40 02_068c61c7](https://github.com/user-attachments/assets/087fd02d-b7f4-417d-9250-b694f01a4fa0)


Add a new movie:  

![תמונה של WhatsApp‏ 2025-01-09 בשעה 10 46 55_2ac71458](https://github.com/user-attachments/assets/03f5c127-2686-448c-b9dd-e4535937f177)


Trying to add the same movie again:  

![image](https://github.com/user-attachments/assets/0f398d6b-682c-49c4-a0ce-04614cc5be05)


Show details of a specific movie:  

![תמונה של WhatsApp‏ 2025-01-09 בשעה 11 12 51_5ba61fca](https://github.com/user-attachments/assets/d88fb4aa-f510-4785-8bb6-c1222034d5d2)


Change a specific movie:  

![תמונה של WhatsApp‏ 2025-01-09 בשעה 11 29 51_cf01a22a](https://github.com/user-attachments/assets/1ca9b9f4-4e4e-448d-9850-2a8dae81e0f7)


Delete a movie:  

![תמונה של WhatsApp‏ 2025-01-09 בשעה 11 50 56_828402ac](https://github.com/user-attachments/assets/e41abf67-da33-424e-b9d5-04d9f80c29cc)


Trying to delete unknown movie:  

![image](https://github.com/user-attachments/assets/9d6891b5-f3af-42d4-8d92-83d258d3f92a)


Trying to send a GET command for movies without a user id:  

![image](https://github.com/user-attachments/assets/0fe04fc1-6939-4c6f-aa83-351f9b22e7c3)


Trying to send a GET command for movies with an unknown user:  

![image](https://github.com/user-attachments/assets/009b6b74-43e4-42c5-8204-557136fd8cf2)
 

### Search-  

Search for a movie by using keywords:  

![image](https://github.com/user-attachments/assets/a81f199a-1e15-4366-90e9-358ad410ed2d)


### Recommendations-  

Update the recommendation system that the current user watched a specific movie:  

For a new user-  

![תמונה של WhatsApp‏ 2025-01-09 בשעה 18 54 17_c88089c3](https://github.com/user-attachments/assets/7f8cac6a-bf77-41ba-84b5-b32fb2d00544)

For an existing user-  

![תמונה של WhatsApp‏ 2025-01-09 בשעה 18 55 18_451784c3](https://github.com/user-attachments/assets/16f8999e-b4fc-43c1-b419-b786a5c15744)


Get movie recommendations for the current user based on a specific movie:  

![תמונה של WhatsApp‏ 2025-01-09 בשעה 18 56 00_ecd8b831](https://github.com/user-attachments/assets/0af0e7be-577a-4e09-a316-ad71c3e81096)


Indeed, movie number 3 was added to user ID 2, followed by movie number 5.  

![תמונה של WhatsApp‏ 2025-01-09 בשעה 18 56 26_099c5817](https://github.com/user-attachments/assets/25381b4e-d57a-4c24-8642-72ae5a5941e3)
