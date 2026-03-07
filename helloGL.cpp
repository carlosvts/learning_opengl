#include <cstdio>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;

// resize viewport when window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main()
{
    glfwInit(); // Initializes glfw
    // glfwWindowHint is a way to configure glfw
    // first argument: which option to config, second argument big enum
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Setting major and minor version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // to 3, so GLFW 3.3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Set to use core profile

    // Creating a window object
    // Monitor NULL  and Share NULL means default
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Hello Window", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Fail to initialize window " << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); // changes context of glfw to the current window

    // ------------------
    // glad setup
    // ------------------

    if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress)))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // set viewport for opengl
    // first two parameters are location
    glViewport(0, 0, WIDTH, HEIGHT);

    // tells glfw to call our function when window is resized
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);    
}

// resize viewport when window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

