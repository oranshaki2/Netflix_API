#ifndef DATALOADER_H
#define DATALOADER_H

#include <map>
#include <string>
#include "dataUser/user.h"

using namespace std;

/*
    Class to load data from a file
*/ 
class loadData {
public:
    void dataLoader(std::map<int, user>& users, const std::string& data_file);
};

#endif // DATALOADER_H