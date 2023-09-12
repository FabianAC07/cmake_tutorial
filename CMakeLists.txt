# Add the minumum version for CMake
cmake_minimum_required(VERSION 3.16.3)

# Create project name
project(cmake_tutorial VERSION 0.1)

# Adding options to add or not libraries 
option(USE_ADDER "A simple library for adding 2 float numbers." ON)

if(USE_ADDER)
    # Adding subdirectories to the project (see CMakeLists.txt to see what will do in the subfolder)
    add_subdirectory(Adder)

    list(APPEND EXTRA_LIB_DIRS "Adder")
    list(APPEND EXTRA_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/Adder")
    list(APPEND EXTRA_LINKS "adder")
endif()

# This will configure the version of the code
configure_file(cmake_tutorial_Config.h.in cmake_tutorial_Config.h)

# Create a name for the executable (project_name, tarjet)
add_executable(${PROJECT_NAME} main.cpp)

# This includes the binary directory as an include, 
# thus it will include it and create a version of the code
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})

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
    PUBLIC external/glfw/include
    ${EXTRA_INCLUDE_DIRS}
)

# This tells cmake where to find the adder 
target_link_directories(${PROJECT_NAME} 
    PRIVATE external/glfw/src/
    ${EXTRA_LIB_DIRS}
)

# Link the new library to the project 
target_link_libraries(${PROJECT_NAME} 
    ${EXTRA_LINKS}
    glfw   
)