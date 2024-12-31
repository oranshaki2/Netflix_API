# Minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Project name
project(Netflix_TCP)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Include directories for header files
include_directories(${CMAKE_SOURCE_DIR}/src)

# Define the data directory
add_definitions(-DDATA_DIR="${CMAKE_SOURCE_DIR}/data")

# Add the main application source files, with Server.cpp as the entry point
add_executable(server
    src/commands/add.cpp
    src/commands/deleteCommand.cpp
    src/commands/help.cpp
    src/commands/recommend.cpp
    src/fileData/saveToFile.cpp
    src/fileData/loadData.cpp
    src/dataUser/movie.cpp
    src/dataUser/user.cpp
    src/tcp/Server.cpp
)

add_custom_target(client
    COMMAND python3 ${CMAKE_SOURCE_DIR}/src/tcp/tcpClient.py $ENV{IP} $ENV{PORT}
)

# Add the test executable for unit tests
add_executable(runNetflixTests
    src/commands/recommend.cpp
    src/commands/add.cpp
    src/commands/deleteCommand.cpp
    src/commands/help.cpp
    src/fileData/saveToFile.cpp
    src/fileData/loadData.cpp
    src/dataUser/movie.cpp
    src/tcp/Server.cpp
    src/dataUser/user.cpp
    src/tests/testAdd.cpp
    src/tests/testRecommend.cpp
    src/tests/testHelp.cpp
    src/tests/testDelete.cpp
    src/tests/testServer.cpp
)

# Define BUILD_SERVER_MAIN for the server executable
target_compile_definitions(server PRIVATE BUILD_SERVER_MAIN) 

# Link Google Test with the test executable
target_link_libraries(runNetflixTests gtest gtest_main)