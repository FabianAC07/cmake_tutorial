# Add the minumum version for CMake
cmake_minimum_required(VERSION 3.16.3)

# Create project name
project(cmake_tutorial)

# Create a name for the executable (project_name, tarjet)
add_executable(${PROJECT_NAME} main.cpp)

# Adding subdirectories to the project (see CMakeLists.txt to see what will do in the subfolder)
add_subdirectory(Adder)

# ------------------- DOWNLOAD ALL THE SUBMODULES -----------------------
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    # Update submodules as needed...
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT_GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with $(GIT_SUBMOD_RESULT), please check submodules")
        endif()
    endif()
endif()
# ------------------- END DOWNLOAD ALL THE SUBMODULES -------------------

# ---------------------- CHECK ALL THE SUBMODULES -----------------------
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/external/glfw/CMakeLists.txt")
   message(FATAL_ERROR "The glfw submodules was not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()
# -------------------- END CHECK ALL THE SUBMODULES ---------------------

add_subdirectory(external/glfw)

# This tells cmake to include these directories into the project
target_include_directories(${PROJECT_NAME} 
    PUBLIC Adder PUBLIC 
    external/glfw/include
)

# This tells cmake where to find the adder 
target_link_directories(${PROJECT_NAME} 
    PRIVATE Adder/
    PRIVATE external/glfw/src/
)

# Link the new library to the project 
target_link_libraries(${PROJECT_NAME} 
    adder
    glfw   
)