#include "commands/add.h"
#include "gtest/gtest.h"
#include "fileData/saveToFile.h"
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cassert>
#include "fileData/loadData.h"
#include "dataUser/user.h"
#include <thread>
#include <chrono>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "tcp/Server.h"
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <commands/deleteCommand.h>
#include <commands/help.h>
#include <commands/recommend.h>

using namespace std;
extern std::string getFirstWord(const std::string &str);
extern std::string removeFirstWord(const std::string &str);

// Global variables
static int server_socket = -1;
static bool server_running = false;
// Mutex for thread safety
pthread_mutex_t lock_for_test;
std::string dataFile1 = "data.txt";
string filePath1 = "../data/" + dataFile1;

void handleClient1(int client_sock)
{
    char buffer_client[4096];
    int expected_data_len = sizeof(buffer_client);
    int read_bytes = recv(client_sock, buffer_client, expected_data_len, 0);
    // Save the content of the bufffer in string
    string task = buffer_client;

    // Check if the connection is closed and if it still open
    // check the content of the command
    if (read_bytes <= 0)
    {
        // connection is closed
        return;
    }

    else
    {
        // Extract the first word and the arguments from the task
        string first_word = getFirstWord(task);
        string arguments = removeFirstWord(task);
        if (first_word == "POST")
        {
            pthread_mutex_lock(&lock_for_test);
            Icommands *postCommand = new add();
            commands["POST"] = postCommand;
            int flag = postCommand->isVaildInput(arguments, users, 1);
            if (flag == 1)
            {
                int user_id = user::stringToUser(arguments);
                vector<int> movie_ids = user::stringToMovies(arguments);
                add postExec = add(user_id, movie_ids);
                postExec.execute(users);
                // save the data to the file
                saveToFile saveTo;
                bool success = saveTo.writeToFile(users, filePath1);
                // Write the corresponding response to the buffer
                strncpy(buffer_client, "201 Created", sizeof(buffer_client));
            }
            // If the user already exists, the flag is -1
            else if (flag == -1)
            {
                // Write the corresponding response to the buffer
                strncpy(buffer_client, "404 Not Found", sizeof(buffer_client));
            }
            // If the input is invalid, the flag is 0
            else
            {
                // Write the corresponding response to the buffer
                strncpy(buffer_client, "400 Bad Request", sizeof(buffer_client));
            }
            pthread_mutex_unlock(&lock_for_test);
            delete (postCommand);
        }
        else if (first_word == "PATCH")
        {
            pthread_mutex_lock(&lock_for_test);
            Icommands *patchCommand = new add();
            commands["PATCH"] = patchCommand;
            int flag = patchCommand->isVaildInput(arguments, users, 0);
            if (flag == 1)
            {
                // Extract the user id and movie ids from the arguments
                int user_id = user::stringToUser(arguments);
                vector<int> movie_ids = user::stringToMovies(arguments);
                // Create an instance of the add class and execute the command
                add patchExec = add(user_id, movie_ids);
                patchExec.execute(users);
                // save the data to the file
                saveToFile saveTo;
                bool success = saveTo.writeToFile(users, filePath1);
                // Write the corresponding response to the buffer
                strncpy(buffer_client, "204 No Content", sizeof(buffer_client));
            }
            // If the user does not exist, the flag is -1
            else if (flag == -1)
            {
                // Write the corresponding response to the buffer
                strncpy(buffer_client, "404 Not Found", sizeof(buffer_client));
            }
            // If the input is invalid, the flag is 0
            else
            {
                // Write the corresponding response to the buffer
                strncpy(buffer_client, "400 Bad Request", sizeof(buffer_client));
            }
            pthread_mutex_unlock(&lock_for_test);
            delete (patchCommand);
        }
        else if (first_word == "DELETE")
        {
            pthread_mutex_lock(&lock_for_test);
            Icommands *deleteCom = new deleteCommand();
            commands["DELETE"] = deleteCom;
            int flag = deleteCom->isVaildInput(arguments, users, 1);
            if (flag == 1)
            {
                int user_id = user::stringToUser(arguments);
                vector<int> movie_ids = user::stringToMovies(arguments);
                deleteCommand deleteExec = deleteCommand(user_id, movie_ids);
                deleteExec.execute(users);
                // save the data to the file
                saveToFile saveTo;
                bool success = saveTo.writeToFile(users, filePath1);
                // Write the corresponding response to the buffer
                strncpy(buffer_client, "204 No Content", sizeof(buffer_client));
            }
            // If the user does not exist, the flag is -1
            else if (flag == -1)
            {
                // Write the corresponding response to the buffer
                strncpy(buffer_client, "404 Not Found", sizeof(buffer_client));
            }
            // If the input is invalid, the flag is 0
            else
            {
                // Write the corresponding response to the buffer
                strncpy(buffer_client, "400 Bad Request", sizeof(buffer_client));
            }
            pthread_mutex_unlock(&lock_for_test);
            // avoid memory leak
            delete (deleteCom);
        }
        else if (first_word == "GET")
        {
            pthread_mutex_lock(&lock_for_test);
            Icommands *GetCommand = new recommend();
            commands["GET"] = GetCommand;
            int flag = GetCommand->isVaildInput(arguments, users, 1);
            if (flag == 1)
            {
                int user_id = user::stringToUser(arguments);
                int movie_id = user::stringToMovie(arguments);
                recommend GETExec = recommend(user_id, movie_id);
                task = GETExec.execute(users, 1);
                // write the corresponding response to the buffer
                string concat_str = "200 Ok\n\n" + task;
                if (concat_str.size() < sizeof(buffer_client))
                {
                    // Include null terminator
                    memcpy(buffer_client, concat_str.c_str(), concat_str.size() + 1); 
                }
            }
            // If the user does not exist, the flag is -1
            else if (flag == -1)
            {
                // Write the corresponding response to the buffer
                strncpy(buffer_client, "404 Not Found", sizeof(buffer_client));
            }
            // If the input is invalid, the flag is 0
            else
            {
                // write the corresponding response to the buffer
                strncpy(buffer_client, "400 Bad Request", sizeof(buffer_client));
            }
            pthread_mutex_unlock(&lock_for_test);
            delete (GetCommand);
        }
        else if (first_word == "help")
        {
            Icommands *helpCommand = new help();
            commands["help"] = helpCommand;
            int flag = helpCommand->isVaildInput(arguments);
            if (flag == 1)
            {
                task = helpCommand->execute();
                string concat_str = "200 Ok\n\n" + task;
                if (concat_str.size() < sizeof(buffer_client))
                {
                    // Include null terminator
                    memcpy(buffer_client, concat_str.c_str(), concat_str.size() + 1); 
                }
            }
            // If the input is invalid, the flag is 0
            else
            {
                // Write the corresponding response to the buffer
                strncpy(buffer_client, "400 Bad Request", sizeof(buffer_client));
            }
            delete (helpCommand);
        }
        else
        {
            // Write the corresponding response to the buffer
            strncpy(buffer_client, "400 Bad Request", sizeof(buffer_client));
        }
    }

    // Send to the client the content of the buffer
    int sent_bytes = send(client_sock, buffer_client, strlen(buffer_client), 0);
    if (sent_bytes < 0)
    {
        return;
    }
    // Close the client and server sockets
    close(client_sock);
}

// Helper function to simulate a client
std::string simulateClient(const std::string &message, int port)
{
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0)
    {
        perror("Failed to create socket");
        // Exit or handle the error
        exit(1); 
    }
    EXPECT_GE(client_socket, 0) << "Client socket creation failed";

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    int attempts = 5;
    while (connect(client_socket, (sockaddr *)&server_addr, sizeof(server_addr)) < 0 && attempts > 0)
    {
        perror("Failed to connect to server, retrying...");
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        attempts--;
    }
    EXPECT_GE(attempts, 0) << "Failed to connect to server after multiple attempts";

    // Send the message
    send(client_socket, message.c_str(), message.size(), 0);

    // Receive the response
    char buffer[4096] = {0};
    int bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
    EXPECT_GT(bytes_received, 0) << "Failed to receive response from server";
    return std::string(buffer);
}

void startServer(int port)
{
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
    {
        perror("Socket creation failed");
        return;
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(server_socket, (sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Bind failed");
        return;
    }

    if (listen(server_socket, 5) < 0)
    {
        perror("Listen failed");
        return;
    }

    // Initialize the mutex
    if (pthread_mutex_init(&lock_for_test, NULL) != 0)
    {
        return;
    }

    server_running = true;

    // Accept and handle clients in a loop
    while (server_running)
    {
        // Each Client has connect to the server
        int client_socket1 = accept(server_socket, nullptr, nullptr);
        int client_socket2 = accept(server_socket, nullptr, nullptr);
        int flag1 = 0;
        int flag2 = 0;
       
        if (client_socket1 >= 0)
        {
            std::thread(handleClient1, client_socket1).detach();
            flag1 = 1;
        }
        if (client_socket2 >= 0)
        {
            std::thread(handleClient1, client_socket2).detach();
            flag2 = 1;
        }
        // Ensure that both threds done and then stop the server
        if (flag1 == 1 && flag2 == 1){
            server_running = false;
        }
    }
}

TEST(UtilityFunctions, GetFirstWord)
{
    EXPECT_EQ(getFirstWord("POST 1 100"), "POST");
    EXPECT_EQ(getFirstWord("GET"), "GET");
    EXPECT_EQ(getFirstWord(""), "");
    EXPECT_EQ(getFirstWord("PATCH 2 123"), "PATCH");
}

TEST(UtilityFunctions, RemoveFirstWord)
{
    EXPECT_EQ(removeFirstWord("POST 1 100"), "1 100");
    EXPECT_EQ(removeFirstWord("GET"), "");
    EXPECT_EQ(removeFirstWord("PATCH 2 123"), "2 123");
    EXPECT_EQ(removeFirstWord(""), "");
}

// Test case: Start server and handle valid requests
TEST(ServerTest, ValidPostRequests)
{
    int port = 1111;

    // Run the server in seperte thread
    std::thread server_thread([port]()
                              { startServer(port); });
   
    // Wait for server to start
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Store the result of simulateClient in a shared variable
    std::string result1;
    std::string result2;

    // Create a thread for simulateClient
    std::thread client_thread1([&]()
                               { result1 = simulateClient("POST 4 300\n", port); });

    std::thread client_thread2([&]()
                               { result2 = simulateClient("POST 9 300 200 100\n", port); });

    // Wait for the client thread to finish
    client_thread1.join();
    client_thread2.join();
    server_thread.join();

    // Validate the result in the main thread using EXPECT_EQ
    EXPECT_EQ(result1, "201 Created");
    EXPECT_EQ(result2, "201 Created");
}
