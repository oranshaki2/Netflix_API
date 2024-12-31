#include "commands/recommend.h"
#include "gtest/gtest.h"
#include "dataUser/user.h"
#include <map>
#include <set>
#include <vector>
#include "commands/add.h"
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

static const int INVALID_INPUT = 0;
static const int INVALID_LOGIC_INPUT = -1;
static const int VALID_INPUT = 1;

using namespace std;

// Helper function to capture stdout
string captureStdout(function<void()> func) {
    stringstream buffer;
    streambuf* old = cout.rdbuf(buffer.rdbuf());
    func();
    cout.rdbuf(old);
    return buffer.str();
}

TEST(RecommendTest, ValidRecommendations) {
    // Create users and their movie lists
    map<int, user> users;
    users[1] = user(1);
    vector<int> set_of_movies_id = {100, 101};
    add obj1 = add(1, set_of_movies_id);
    obj1.execute(users);

    users[2] = user(2);
    vector<int> set_of_movies_id2 = {101, 102};
    add obj2 = add(2, set_of_movies_id2);
    obj2.execute(users);

    users[3] = user(3);
    vector<int> set_of_movies_id3 = {100, 101, 103};
    add obj3 = add(3, set_of_movies_id3);
    obj3.execute(users);

    // Create recommend object
    recommend rec(1, 101);

    //Capture output
    string output = rec.execute(users, 0);

    //Check that movie 102 and 103 are recommended
    EXPECT_NE(output.find("102"), string::npos);
    EXPECT_NE(output.find("103"), string::npos);
}

// A case that the output has to be empty because user1 is the onlt that watched in movie 100
TEST(RecommendTest, NoRecommendations) {
    map<int, user> users;

    // User with no common movies
    users[1] = user(1);
    users[1].addMovie(100);

    users[2] = user(2);
    users[2].addMovie(200);

    // Create recommend object
    recommend rec(1, 100);

    // Capture output
    string output = rec.execute(users, 0);

    // Check that output is empty
    EXPECT_TRUE(output.empty());
}

// Check a case with more than 10 recommendations and ensore that the output has
// 10 recommendations
TEST(RecommendTest, MaxTenRecommendations) {
    map<int, user> users;

    // Add 12 users with unique movies
    for (int i = 2; i <= 13; ++i) {
        users[i] = user(i);
        users[i].addMovie(200 + i);
        users[i].addMovie(100); // Common movie with user 1
    }

    // User 1
    users[1] = user(1);
    users[1].addMovie(100);

    // Create recommend object
    recommend rec(1, 100);

    // Save output
    string output = rec.execute(users, 0);

    // Split the output into individual movie IDs
    istringstream iss(output);
    vector<int> recommendations((istream_iterator<int>(iss)),
                                      istream_iterator<int>());

    // Check that the number of recommendations is at most 10
    EXPECT_LE(recommendations.size(), 10);
}

// Check of invalid user ID
TEST(RecommendTest, InvalidUserID) {
    map<int, user> users;

    // Create recommend object with invalid user ID
    recommend rec(-1, 100);

    // Save output
    string output = rec.execute(users, 0);

    // Check that output is empty
    EXPECT_TRUE(output.empty());
}  

// An example from our exercise
TEST(RecommendTest, ExampleFromExercise) {
    map<int, user> users;

    users[1] = user(1);
    vector<int> set_of_movies_id = {100, 101, 102, 103};
    add obj1 = add(1, set_of_movies_id);
    obj1.execute(users);

    users[2] = user(2);
    vector<int> set_of_movies_id2 = {101, 102, 104, 105, 106};
    add obj2 = add(2, set_of_movies_id2);
    obj2.execute(users);

    users[3] = user(3);
    vector<int> set_of_movies_id3 = {100, 104, 105, 107, 108};
    add obj3 = add(3, set_of_movies_id3);
    obj3.execute(users);

    users[4] = user(4);
    vector<int> set_of_movies_id4 = {101, 105, 106, 107, 109, 110};
    add obj4 = add(4, set_of_movies_id4);
    obj4.execute(users);

     users[5] = user(5);
    vector<int> set_of_movies_id5 = {100, 102, 103, 105, 108, 111};
    add obj5 = add(5, set_of_movies_id5);
    obj5.execute(users);

     users[6] = user(6);
    vector<int> set_of_movies_id6 = {100, 103, 104, 110, 111, 112, 113};
    add obj6 = add(6, set_of_movies_id6);
    obj6.execute(users);

     users[7] = user(7);
    vector<int> set_of_movies_id7 = {102, 105, 106, 107, 108, 109, 110};
    add obj7 = add(7, set_of_movies_id7);
    obj7.execute(users);

     users[8] = user(8);
    vector<int> set_of_movies_id8 = {101, 104, 105, 106, 109, 111, 114};
    add obj8 = add(8, set_of_movies_id8);
    obj8.execute(users);

     users[9] = user(9);
    vector<int> set_of_movies_id9 = {100, 103, 105, 107, 112, 113, 115};
    add obj9 = add(9, set_of_movies_id9);
    obj9.execute(users);

     users[10] = user(10);
    vector<int> set_of_movies_id10 = {100, 102, 105, 106, 107, 109, 110, 116};
    add obj10 = add(10, set_of_movies_id10);
    obj10.execute(users);

    recommend recommend_of_user1_movie104 = recommend(1, 104);

    string output = recommend_of_user1_movie104.execute(users, 0);
    
    string expected_output = "105 106 111 110 112 113 107 108 109 114 ";

    // Check that output is as we expect
    EXPECT_EQ(output, expected_output);
} 
// Tests for isVaildInput function
TEST(RecommendTest, IsValidInput) {
    map<int, user> users;
    users[1] = user(1);
    users[2] = user(2);

    recommend rec;

    // Valid input
    EXPECT_EQ(rec.isVaildInput("1 100", users), VALID_INPUT);

    // Invalid input: non-integer user ID
    EXPECT_EQ(rec.isVaildInput("abc 100", users), INVALID_INPUT);

    // Invalid input: non-integer movie ID
    EXPECT_EQ(rec.isVaildInput("1 abc", users), INVALID_INPUT);

    // Invalid input: negative user ID
    EXPECT_EQ(rec.isVaildInput("-1 100", users), INVALID_INPUT);

    // Invalid input: negative movie ID
    EXPECT_EQ(rec.isVaildInput("1 -100", users), INVALID_INPUT);

    // Invalid input: user does not exist
    EXPECT_EQ(rec.isVaildInput("3 100", users), INVALID_LOGIC_INPUT);

    // Invalid input: more than one movie ID
    EXPECT_EQ(rec.isVaildInput("1 100 101", users), INVALID_INPUT);
}