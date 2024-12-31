#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <thread>
#include <map>
#include <cstring>
#include <pthread.h>
#include "commands/Icommands.h"
#include "commands/help.h"
#include "dataUser/user.h"
#include "fileData/saveToFile.h"
#include "fileData/loadData.h"
#include "commands/deleteCommand.h"
#include "commands/add.h"
#include "commands/recommend.h"
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <atomic>

#define PORT 8080

using namespace std;
map<string, Icommands *> commands;
map<int, user> users;
std::string dataFile = "data.txt";
string filePath = "../data/" + dataFile;
// Mutex for thread safety
pthread_mutex_t mutex_lock;
std::mutex queue_mutex;
std::condition_variable condition;
std::queue<int> client_queue;
std::atomic<bool> stop_pool(false);

std::string getFirstWord(const std::string &str)
{
    std::istringstream stream(str);
    std::string word;
    // Extract the first word
    stream >> word; 
    return word;
}

std::string removeFirstWord(const std::string &str)
{
    // Find the first space
    size_t pos = str.find(' '); 
    if (pos != std::string::npos)
    {
        // Return substring after the first space
        return str.substr(pos + 1); 
    }
    // If no space, return an empty string
    return ""; 
}

void handleClient(int client_sock)
{
    while (true)
    {
        char buffer[4096];
        int expected_data_len = sizeof(buffer);
        int read_bytes = recv(client_sock, buffer, expected_data_len, 0);
        // Save the content of the bufffer in string
        string task = buffer;

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
                pthread_mutex_lock(&mutex_lock);
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
                    bool success = saveTo.writeToFile(users, filePath);
                    // Write the corresponding response to the buffer
                    strncpy(buffer, "201 Created", sizeof(buffer));
                }
                // If the user already exists, the flag is -1
                else if (flag == -1)
                {
                    // Write the corresponding response to the buffer
                    strncpy(buffer, "404 Not Found", sizeof(buffer));
                }
                // If the input is invalid, the flag is 0
                else
                {
                    // Write the corresponding response to the buffer
                    strncpy(buffer, "400 Bad Request", sizeof(buffer));
                }
                pthread_mutex_unlock(&mutex_lock);
                delete (postCommand);
            }
            else if (first_word == "PATCH")
            {
                pthread_mutex_lock(&mutex_lock);
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
                    bool success = saveTo.writeToFile(users, filePath);
                    // Write the corresponding response to the buffer
                    strncpy(buffer, "204 No Content", sizeof(buffer));
                }
                // If the user does not exist, the flag is -1
                else if (flag == -1)
                {
                    // Write the corresponding response to the buffer
                    strncpy(buffer, "404 Not Found", sizeof(buffer));
                }
                // If the input is invalid, the flag is 0
                else
                {
                    // Write the corresponding response to the buffer
                    strncpy(buffer, "400 Bad Request", sizeof(buffer));
                }
                pthread_mutex_unlock(&mutex_lock);
                delete (patchCommand);
            }
            else if (first_word == "DELETE")
            {
                pthread_mutex_lock(&mutex_lock);
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
                    bool success = saveTo.writeToFile(users, filePath);
                    // Write the corresponding response to the buffer
                    strncpy(buffer, "204 No Content", sizeof(buffer));
                }
                // If the user does not exist, the flag is -1
                else if (flag == -1)
                {
                    // Write the corresponding response to the buffer
                    strncpy(buffer, "404 Not Found", sizeof(buffer));
                }
                // If the input is invalid, the flag is 0
                else
                {
                    // Write the corresponding response to the buffer
                    strncpy(buffer, "400 Bad Request", sizeof(buffer));
                }
                pthread_mutex_unlock(&mutex_lock);
                // avoid memory leak
                delete (deleteCom);
            }
            else if (first_word == "GET")
            {
                pthread_mutex_lock(&mutex_lock);
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
                    if (concat_str.size() < sizeof(buffer))
                    {
                        // Include null terminator
                        memcpy(buffer, concat_str.c_str(), concat_str.size() + 1); 
                    }
                }
                // If the user does not exist, the flag is -1
                else if (flag == -1)
                {
                    // Write the corresponding response to the buffer
                    strncpy(buffer, "404 Not Found", sizeof(buffer));
                }
                // If the input is invalid, the flag is 0
                else
                {
                    // write the corresponding response to the buffer
                    strncpy(buffer, "400 Bad Request", sizeof(buffer));
                }
                pthread_mutex_unlock(&mutex_lock);
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
                    if (concat_str.size() < sizeof(buffer))
                    {
                        // Include null terminator
                        memcpy(buffer, concat_str.c_str(), concat_str.size() + 1); 
                    }
                }
                // If the input is invalid, the flag is 0
                else
                {
                    // Write the corresponding response to the buffer
                    strncpy(buffer, "400 Bad Request", sizeof(buffer));
                }
                delete (helpCommand);
            }
            else
            {
                // Write the corresponding response to the buffer
                strncpy(buffer, "400 Bad Request", sizeof(buffer));
            }
        }

        // Send to the client the content of the buffer
        int sent_bytes = send(client_sock, buffer, strlen(buffer), 0);
        memset(buffer, 0, sizeof(buffer)); // Clear the buffer

        if (sent_bytes < 0)
        {
            return;
        }
    }

        // Close the client and server sockets
        close(client_sock);
}

// Worker function for thread pool
void worker()
{
    while (true)
    {
        int client_sock;
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            condition.wait(lock, [] { return !client_queue.empty() || stop_pool.load(); });

            if (stop_pool.load() && client_queue.empty())
            {
                break;
            }

            client_sock = client_queue.front();
            client_queue.pop();
        }

        handleClient(client_sock);
    }
}

#ifdef BUILD_SERVER_MAIN
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        return -1;
    }
    // Define the server port
    int server_port = std::atoi(argv[1]);

    // Create a TCP server socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        return -1;
    }

    // Sin is the address structure for the server, define and initialize it
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));

    // Define the server ip listen all the potential clients and save the server port in
    // the struct
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(server_port);

    // Bind the server to the IP and port
    if (bind(sock, (struct sockaddr *)&sin, sizeof(sin)) < 0)
    {
        return -1;
    }

    // Listen to potential clients, SOMAXCONN allows the maximum number of clients that can wait
    if (listen(sock, SOMAXCONN) < 0)
    {
        return -1;
    }

    // Load existing data
    loadData loader;
    loader.dataLoader(users, filePath);
    // Initialize the mutex
    if (pthread_mutex_init(&mutex_lock, NULL) != 0) {
        return 1;
    }

    // Create thread pool
    const size_t num_threads = std::thread::hardware_concurrency();
    std::vector<std::thread> thread_pool;
    for (size_t i = 0; i < num_threads; ++i)
    {
        thread_pool.emplace_back(worker);
    }

    // Main server loop
    while (true)
    {
        int client_sock = accept(sock, nullptr, nullptr);
        if (client_sock >= 0)
        {
            {
                std::lock_guard<std::mutex> lock(queue_mutex);
                client_queue.push(client_sock);
            }
            condition.notify_one();
        }
        else
        {
            perror("Error accepting client");
        }
    }

// Clean up and stop thread pool (if server needs to be shut down)
    stop_pool.store(true);
    condition.notify_all();
    for (auto &t : thread_pool)
    {
        if (t.joinable())
        {
            t.join();
        }
    }

    pthread_mutex_destroy(&mutex_lock);
    close(sock);

    return 0;
}
#endif