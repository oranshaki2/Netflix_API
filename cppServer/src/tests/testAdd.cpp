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

using namespace std;

static const int INVALID_INPUT = 0;
static const int INVALID_LOGIC_INPUT = -1;
static const int VALID_INPUT = 1;

// Test to verify the add command with POST for a new user
TEST(AddTest, AddMoviesToNewUserWithPost)
{
    map<int, user> users;
    string dataFile = "data.txt";
    string filePath = "../../data/" + dataFile;
    add addValid;
    // Test adding movies for a new user with POST
    string method = "POST";
    if (addValid.isVaildInput({100, 101, 102}, users, 1) == 1){
        add addCommand(1, {100, 101, 102});
        addCommand.execute(users);

        // Verify the user was added
        ASSERT_TRUE(users.find(1) != users.end());
        ASSERT_EQ(users[1].Get_movies_ids().size(), 3);
        ASSERT_EQ(users[1].Get_movies_ids().count(100), 1);
        ASSERT_EQ(users[1].Get_movies_ids().count(101), 1);
        ASSERT_EQ(users[1].Get_movies_ids().count(102), 1);

        // Verify the data was saved to the file
        saveToFile saveTo;
        bool success = saveTo.writeToFile(users, dataFile);
        ASSERT_TRUE(success);

        // Verify the data was saved to the file
        ifstream file(filePath);
        stringstream buffer;
        buffer << file.rdbuf();
        file.close();
        std::string content = buffer.str();
        ASSERT_NE(content.find("1 100 101 102"), std::string::npos);
    }
}

// Test to verify the add command with PATCH for an existing user
TEST(AddTest, AddMoviesToExistingUserWithPatch)
{
    map<int, user> users;
    string dataFile = "data.txt";
    string filePath = "../../data/" + dataFile;
    add addValid;
    // Load existing data
    loadData loader;
    loader.dataLoader(users, dataFile);

    // Test adding more movies with PATCH
    string method = "PATCH";
    if (addValid.isVaildInput({101, 103, 105}, users, 0) == 1){
        add addCommand(1, {101, 103, 105});
        addCommand.execute(users);

        // Verify the user's movies
        ASSERT_TRUE(users.find(1) != users.end());
        ASSERT_EQ(users[1].Get_movies_ids().count(101), 1);
        ASSERT_EQ(users[1].Get_movies_ids().count(103), 1);
        ASSERT_EQ(users[1].Get_movies_ids().count(105), 1);

        // Verify the data was saved to the file
        saveToFile saveTo;
        bool success = saveTo.writeToFile(users, dataFile);
        ASSERT_TRUE(success);

        // Verify the data was saved to the file
        ifstream file(filePath);
        stringstream buffer;
        buffer << file.rdbuf();
        file.close();
        string content = buffer.str();
        ASSERT_NE(content.find("1 100 101 102 103 105"), string::npos);
    }
}

// Test to verify the add command with invalid movie IDs
TEST(AddTest, InvalidMovieIds)
{
    map<int, user> users;
    string dataFile = "data.txt";
    string filePath = "../../data/" + dataFile;
    add addValid;
    // Load existing data
    loadData loader;
    loader.dataLoader(users, dataFile);

    users[1].print_movie();

    if(addValid.isVaildInput({101, -1, 105}, users, 1) == 0){
    // Attempt to add invalid movie IDs (negative values)
    add addCommand(1, {101, -1, 105}); // Assuming -1 is invalid
    addCommand.execute(users);
    // Verify the user's movies were not affected by invalid input
    ASSERT_EQ(users[1].Get_movies_ids().count(-1), 0);
    ASSERT_EQ(users[1].Get_movies_ids().count(101), 1);
    ASSERT_EQ(users[1].Get_movies_ids().count(105), 1);
    }
    

    // Simulate invalid movie ID (string value) by catching the error at the input
    // parsing stage
    string invalidMovieId = "invalid";
    try
    {
        int movieId = std::stoi(invalidMovieId);
        add addCommandString(1, {100, movieId, 102});
        addCommandString.execute(users);
    }
    catch (const std::invalid_argument &e)
    {
        cout << "Caught expected invalid_argument exception for movie ID: " << e.what() << endl;
    }
    catch (...)
    {
        // Should not catch other exceptions
        ASSERT_TRUE(false); 
    }

    // Verify the data was saved to the file
    saveToFile saveTo;
    bool success = saveTo.writeToFile(users, dataFile);
    ASSERT_TRUE(success);

    // Verify the data was saved to the file
    ifstream file(filePath);
    stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    std::string content = buffer.str();
    ASSERT_EQ(content.find("-1"), std::string::npos);
    ASSERT_EQ(content.find("invalid"), std::string::npos);
}

// Test to verify the add command with invalid user IDs
TEST(AddTest, InvalidUserIds)
{
    map<int, user> users;
    string dataFile = "data.txt";
    string filePath = "../../data/" + dataFile;

    // Load existing data
    loadData loader;
    loader.dataLoader(users, dataFile);

    add addValid;
    if(addValid.isVaildInput({-1, 100, 101}, users, 1) == 1){
    // Attempt to add movies with invalid user IDs (negative values)
    add addCommandNegative(-1, {100, 101, 102});
    addCommandNegative.execute(users);
    }
    // Verify the user was not added
    ASSERT_TRUE(users.find(-1) == users.end());

    // Simulate invalid user ID (string value) by catching the error at the input parsing stage
    string invalidUserId = "invalid";
    try
    {
        int userId = stoi(invalidUserId);
        add addCommandString(userId, {100, 101, 102});
        addCommandString.execute(users);
    }
    catch (const invalid_argument &e)
    {
        cout << "Caught expected invalid_argument exception for user ID: " << e.what() << endl;
    }
    catch (...)
    {
        // Should not catch other exceptions
        ASSERT_TRUE(false); 
    }

    // Verify the data was saved to the file
    saveToFile saveTo;
    bool success = saveTo.writeToFile(users, dataFile);
    ASSERT_TRUE(success);

    // Verify the data was saved to the file
    ifstream file(filePath);
    stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    string content = buffer.str();
    ASSERT_EQ(content.find("-1"), string::npos);
    ASSERT_EQ(content.find("invalid"), string::npos);
}

// Test to verify the add command with no movie IDs
TEST(AddTest, AddUserWithoutMovies)
{
    map<int, user> users;
    string dataFile = "data.txt";
    string filePath = "../../data/" + dataFile;

    // Load existing data
    loadData loader;
    loader.dataLoader(users, dataFile);

    // Attempt to add a user without movies
    add addCommand(8, {});
    addCommand.execute(users);

    // Verify the user was not added
    ASSERT_TRUE(users.find(8) == users.end());

    // Verify the data was saved to the file
    saveToFile saveTo;
    bool success = saveTo.writeToFile(users, dataFile);
    ASSERT_TRUE(success);

    // Verify the data was saved to the file
    ifstream file(filePath);
    stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    string content = buffer.str();
    // Ensure no user ID 8 is saved
    ASSERT_EQ(content.find("8"), string::npos); 
}

// Test to verify the isVaildInput function
TEST(AddTest, IsValidInput) {
    map<int, user> users;
    users[1] = user(1);
    users[2] = user(2);

    add addValid;

    // Valid input for POST
    EXPECT_EQ(addValid.isVaildInput("3 100 101", users, 1), VALID_INPUT);

    // Valid input for PATCH
    EXPECT_EQ(addValid.isVaildInput("1 102 103", users, 0), VALID_INPUT);

    // Invalid input: non-integer user ID
    EXPECT_EQ(addValid.isVaildInput("abc 100 101", users, 1), INVALID_INPUT);

    // Invalid input: non-integer movie ID
    EXPECT_EQ(addValid.isVaildInput("1 abc 101", users, 1), INVALID_INPUT);

    // Invalid input: negative user ID
    EXPECT_EQ(addValid.isVaildInput("-1 100 101", users, 1), INVALID_INPUT);

    // Invalid input: negative movie ID
    EXPECT_EQ(addValid.isVaildInput("1 -100 101", users, 1), INVALID_INPUT);

    // Invalid input: user does not exist for PATCH
    EXPECT_EQ(addValid.isVaildInput("3 100 101", users, 0), INVALID_LOGIC_INPUT);

    // Invalid input: user already exists for POST
    EXPECT_EQ(addValid.isVaildInput("1 100 101", users, 1), INVALID_LOGIC_INPUT);

    // Invalid input: no movie IDs
    EXPECT_EQ(addValid.isVaildInput("1", users, 1), INVALID_INPUT);
}