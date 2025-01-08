#include "commands/deleteCommand.h"
#include "fileData/saveToFile.h"
#include "gtest/gtest.h"
#include "dataUser/user.h"
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include "commands/add.h"

using namespace std;

static const int INVALID_INPUT = 0;
static const int INVALID_LOGIC_INPUT = -1;
static const int VALID_INPUT = 1;

// Test to verify that the saveToFile works correctly with delete
TEST(DeleteTest, RemoveMoviesAndSaveToFile)
{
    map<int, user> users;

    add addCommand(1, {100, 101, 102});
    addCommand.execute(users);

    string dataFile = "data.txt";
    string filePath = string(DATA_DIR) + "/" + dataFile;
    
    // Remove movies from the user
    deleteCommand deleteCommand1(1 , {100, 102});
    deleteCommand1.execute(users);

    // Verify the movies were not removed
    deleteCommand deleteCommand2(1 , {101,103});
    deleteCommand2.execute(users);

    // Verify the movies were removed
    ASSERT_EQ(users[1].Get_movies_ids().size(), 1);
    ASSERT_EQ(users[1].Get_movies_ids().count(100), 0);
    ASSERT_EQ(users[1].Get_movies_ids().count(102), 0);
    ASSERT_EQ(users[1].Get_movies_ids().count(101), 1);

    // Save the changes to the file
    saveToFile saveTo;
    bool success = saveTo.writeToFile(users, dataFile);
    ASSERT_TRUE(success);

    // Verify the data was saved to the file
    ifstream file(filePath);
    stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    string content = buffer.str();
    ASSERT_NE(content.find("1 101"), string::npos);
    ASSERT_EQ(content.find("100"), string::npos);
    ASSERT_EQ(content.find("102"), string::npos);
}

// Test to verify the delete command removes specific movies from a user
TEST(DeleteTest, RemoveMoviesFromUser)
{
    map<int, user> users;
    add addCommand(2, {100, 101, 103});
    addCommand.execute(users);

    deleteCommand deleteCommand(2, {100, 103});
    deleteCommand.execute(users);

    // Verify the movies were removed
    ASSERT_EQ(users[2].Get_movies_ids().size(), 1);
    ASSERT_EQ(users[2].Get_movies_ids().count(100), 0);
    ASSERT_EQ(users[2].Get_movies_ids().count(103), 0);
    ASSERT_EQ(users[2].Get_movies_ids().count(101), 1);
}

// Test to verify the userExists function
TEST(DeleteTest, UserExists)
{
    map<int, user> users;
    users.emplace(1, user(1));

    ASSERT_TRUE(deleteCommand::userExists(users, 1));
    ASSERT_FALSE(deleteCommand::userExists(users, 2));
}

// Test to verify the userHasAllMovies function
TEST(DeleteTest, UserHasAllMovies)
{
    map<int, user> users;
    add addCommand(1, {100, 101, 102});
    addCommand.execute(users);

    deleteCommand deleteCommand1(1, {100, 101});
    ASSERT_TRUE(deleteCommand1.userHasAllMovies(users));
    
    deleteCommand deleteCommand2(1, {100, 103});
    ASSERT_FALSE(deleteCommand2.userHasAllMovies(users));
    deleteCommand2.execute(users);
    
    deleteCommand deleteCommand3(2, {100, 101});
    ASSERT_FALSE(deleteCommand3.userHasAllMovies(users));
}

// Test to verify the isVaildInput function
TEST(DeleteTest, IsValidInput) {
    map<int, user> users;
    add addCommand(1, {100, 101, 102});
    addCommand.execute(users);

    deleteCommand deleteValid;

    // Valid input
    EXPECT_EQ(deleteValid.isVaildInput("1 100 101", users, 0), VALID_INPUT);

    // Invalid input: non-integer user ID
    EXPECT_EQ(deleteValid.isVaildInput("abc 100 101", users, 0), INVALID_INPUT);

    // Invalid input: non-integer movie ID
    EXPECT_EQ(deleteValid.isVaildInput("1 abc 101", users, 0), INVALID_INPUT);

    // Invalid input: negative user ID
    EXPECT_EQ(deleteValid.isVaildInput("-1 100 101", users, 0), INVALID_INPUT);

    // Invalid input: negative movie ID
    EXPECT_EQ(deleteValid.isVaildInput("1 -100 101", users, 0), INVALID_INPUT);

    // Invalid input: user does not exist
    EXPECT_EQ(deleteValid.isVaildInput("2 100 101", users, 0), INVALID_LOGIC_INPUT);

    // Invalid input: user does not have all specified movies
    EXPECT_EQ(deleteValid.isVaildInput("1 100 103", users, 0), INVALID_LOGIC_INPUT);

    // Invalid input: no movie IDs
    EXPECT_EQ(deleteValid.isVaildInput("1", users, 0), INVALID_INPUT);
}