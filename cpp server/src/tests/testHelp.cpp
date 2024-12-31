#include "commands/help.h"
#include "gtest/gtest.h"
#include <iostream>
#include <sstream>

using namespace std;

// Redirect cout to a stringstream to capture the output
class CoutRedirect {
public:
    CoutRedirect(streambuf* new_buffer) : old(cout.rdbuf(new_buffer)) {}
    ~CoutRedirect() { cout.rdbuf(old); }
private:
    std::streambuf* old;
};

// Test to verify that the execute function is called when the input is exactly "help"
TEST(TestHelp, ExecuteCalledOnExactHelp) {
    stringstream buffer;
    CoutRedirect redirect(buffer.rdbuf());
    help helpCommand;
    string command = "";
    if (helpCommand.isVaildInput(command)) {
        string output = helpCommand.execute();
        ASSERT_NE(output.find("DELETE, arguments: [userid] [movieid1] [movieid2] ..."), string::npos);
        ASSERT_NE(output.find("GET, arguments: [userid] [movieid]"), string::npos);
        ASSERT_NE(output.find("PATCH, arguments: [userid] [movieid1] [movieid2] ..."), string::npos);
        ASSERT_NE(output.find("POST, arguments: [userid] [movieid1] [movieid2] ..."), string::npos);
        ASSERT_NE(output.find("help"), string::npos);
    }
}

// Test to verify that the execute function is not called when the input is not exactly "help"
TEST(TestHelp, ExecuteNotCalledOnNonExactHelp) {
    stringstream buffer;
    CoutRedirect redirect(buffer.rdbuf());
    help helpCommand;
    string command = "5";
    if (helpCommand.isVaildInput(command)) {
        string output = helpCommand.execute();
        ASSERT_EQ(output.find("DELETE, arguments: [userid] [movieid1] [movieid2] ..."), string::npos);
        ASSERT_EQ(output.find("GET, arguments: [userid] [movieid]"), string::npos);
        ASSERT_EQ(output.find("PATCH, arguments: [userid] [movieid1] [movieid2] ..."), string::npos);
        ASSERT_EQ(output.find("POST, arguments: [userid] [movieid1] [movieid2] ..."), string::npos);
        ASSERT_EQ(output.find("help"), string::npos);
    }
}
