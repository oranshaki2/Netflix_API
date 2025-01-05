# Minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Project name
project(Netflix_API)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

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

# Define BUILD_SERVER_MAIN for the server executable
target_compile_definitions(server PRIVATE BUILD_SERVER_MAIN) 