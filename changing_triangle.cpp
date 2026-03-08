#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;

void framebuffer_resize_callback(GLFWwindow* window, int width, int height);
void handle_input(GLFWwindow* window);

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Changing Triangle", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Fail to initialize window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    
    // glad setup
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "glad fail to initialize\n";
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, WIDTH, HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);
    
    float vertices[]
    {
        -0.5f, -0.5f, 0.0f,
        -0.5f,0.5f, 0.0f,
        0.5f, 0.0f, 0.0f,
    };

    // VAO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // VBO
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Copy vbo into vao
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

}
