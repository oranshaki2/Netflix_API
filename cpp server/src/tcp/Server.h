#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <map>
#include "dataUser/user.h"      
#include "commands/Icommands.h"   

/*
 * The server file that implements the server-side logic
 * of the project. The server handles incoming client connections
 * and sends responses back to the clients.
 */

// Helper functions
std::string getFirstWord(const std::string& input);
std::string removeFirstWord(const std::string& input);

// Handle a single client connection
void handleClient(int client_sock); 

// Global maps for users and commands
// Map of user IDs to user objects
extern std::map<int, user> users;
// Map of command strings to Icommands objects                       
extern std::map<std::string, Icommands*> commands;       

#endif // SERVER_H
