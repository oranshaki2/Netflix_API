#include "fileData/saveToFile.h"
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <filesystem>

// Constructor
saveToFile::saveToFile() {}

// writeToFile() method to write the data to the file
bool saveToFile::writeToFile(map<int, user>& users, const string& filename) {

    string filePath = string(DATA_DIR) + "/" + filename;

    // Ensure the data directory exists
    filesystem::create_directories(DATA_DIR);

    // Delete the file if it exists
    saveToFile::clearFile(filename);

    // Open file in truncate mode to clear existing content
    ofstream outFile(filePath, ios::trunc);
    if (!outFile.is_open()) {
        return false;
    }

    // Write each user's data to the file
    for (auto& pair : users) {
        user& user = pair.second;
        
        // Write user ID
        outFile << user.getUserId() << " ";
        // Write all movie IDs for this user
        const set<int>& movies = user.Get_movies_ids();
        for (int movie_id : movies) {
            outFile << movie_id << " ";
        }
        outFile << "\n";
    }

    outFile.close();
    return true;
}

// clearFile() method to clear the file
bool saveToFile::clearFile(const string& filename) {
     string filePath = string(DATA_DIR) + "/" + filename;


    // Open and immediately close file in truncate mode to clear its contents
    ofstream outFile(filePath, ios::trunc);
    if (!outFile.is_open()) {
        return false;
    }
    outFile.close();
    return true;
}