#include "fileData/loadData.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>



// Load data from a file
void loadData::dataLoader(map<int, user>& users, const string& data_file) {
    // Use the DATA_DIR definition to construct the file path
    string filePath = string(DATA_DIR) + "/" + data_file;

    // Check if the file exists
    if (!filesystem::exists(filePath)) {
        return;
    }

    // Open the file and read data
    ifstream inFile(filePath);
    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        int user_id, movie_id;
        ss >> user_id;
        if (users.find(user_id) == users.end()) {
            users[user_id] = user(user_id);
        }
        while (ss >> movie_id) {
            users[user_id].addMovie(movie_id);
        }
    }
}