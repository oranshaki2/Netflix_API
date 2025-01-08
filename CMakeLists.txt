# Minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Project name
project(Netflix_API)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories for header files
include_directories(${CMAKE_SOURCE_DIR}/cppServer/src)

# Define the data directory
add_definitions(-DDATA_DIR="${CMAKE_SOURCE_DIR}/data")

# Add the main application source files, with Server.cpp as the entry point
add_executable(server
    cppServer/src/commands/add.cpp
    cppServer/src/commands/deleteCommand.cpp
    cppServer/src/commands/help.cpp
    cppServer/src/commands/recommend.cpp
    cppServer/src/fileData/saveToFile.cpp
    cppServer/src/fileData/loadData.cpp
    cppServer/src/dataUser/movie.cpp
    cppServer/src/dataUser/user.cpp
    cppServer/src/tcp/Server.cpp
)

# Define BUILD_SERVER_MAIN for the server executable
target_compile_definitions(server PRIVATE BUILD_SERVER_MAIN) 