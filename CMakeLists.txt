# Add the minumum version for CMake
cmake_minimum_required(VERSION 3.16.3)

# Create project name
project(cmake_tutorial)

# Create a name for the executable (project_name, tarjet)
add_executable(${PROJECT_NAME} main.cpp)

# Adding subdirectories to the project (see CMakeLists.txt to see what will do in the subfolder)
add_subdirectory(Adder)

# This tells cmake to include these directories into the project
target_include_directories(${PROJECT_NAME} PUBLIC Adder)

# This tells cmake where to find the adder 
target_link_directories(${PROJECT_NAME} PUBLIC Adder/)

# Link the new library to the project 
target_link_libraries(${PROJECT_NAME} adder)