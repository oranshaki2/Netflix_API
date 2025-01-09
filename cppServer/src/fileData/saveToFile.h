#ifndef SAVETOFILE_H
#define SAVETOFILE_H

#include <map>
#include <set>
#include <fstream>
#include <string>
#include "dataUser/user.h"

using namespace std;



/**
 * This class provides static methods to write and manage movie data files.
 * Each line in the output file contains a user ID followed by their movie IDs.
 */
class saveToFile {
public:
    saveToFile(); 
    static bool clearFile(const string& filename = "data.txt");
    static bool writeToFile(map<int, user>& users, const string& filename = "data.txt");
};

#endif // SAVETOFILE_H