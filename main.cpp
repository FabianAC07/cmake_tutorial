#include <iostream>
#include <GLFW/glfw3.h>
#include <cmake_tutorial_Config.h>

#ifdef USE_ADDER
    #include "adder.h"
#endif

int main(int argc, char* argv[])
{
    std::cout << "Hello world!\n" << std::endl;

#ifdef USE_ADDER
    std::cout << "Using libAdder: " << add(72.1f, 73.8f) << std::endl;
#else
    std::cout << "NOT using libAdder: " << 72.1f + 73.8f << std::endl;
#endif

    // Print version of the builded code...
    std::cout << argv[0] << " Version " << cmake_tutorial_VERSION_MAJOR << "." << cmake_tutorial_VERSION_MINOR << "\n" << std::endl;

    GLFWwindow* window;
    int width, height;

    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        exit( EXIT_FAILURE );
    }


    window = glfwCreateWindow( 300, 300, "Gears", NULL, NULL );
    if (!window)
    {
        fprintf( stderr, "Failed to open GLFW window\n" );
        glfwTerminate();
        exit( EXIT_FAILURE );
    }

    // Main loop
    while( !glfwWindowShouldClose(window) )
    {
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();


    return 0;
}