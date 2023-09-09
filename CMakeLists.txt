# Add the minumum version for CMake
cmake_minimum_required(VERSION 3.16.3)

# Create project name
project(cmake_tutorial)

# Create a name for the executable (project_name, tarjet)
add_executable(${PROJECT_NAME} main.cpp)