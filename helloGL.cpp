#include <cstdio>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;

// resize viewport when window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// process input
void process_input(GLFWwindow* window);
// triangle
void draw_triangle(unsigned int shader_program);
// rectangle
void draw_rect(unsigned int shader_program);

// compiling
const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "out vec3 vertexColor;"
    "void main()\n"
    "{\n"
    " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    " vertexColor = aColor;"
    "}\0";

const char* fragmentShaderSource = "#version 330 core\n"
    "in vec3 vertexColor;\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    " FragColor = vec4(vertexColor, 1.0);\n"
    "}\0";


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
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    // set viewport for opengl
    // first two parameters are location
    glViewport(0, 0, WIDTH, HEIGHT);
    
    // tells glfw to call our function when window is resized
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);

    float vertices[] = 
    {
        // x   y  
        // z=0 (cause we rendering on 2d)        colors
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,

        // other triangle
        0.5, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
    };
    
    // creating Vertex Array Object - VAO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // buffer for our vertex data that will be sent to GPU
    // VBO vertex buffer object
    // unsignedt int, ie, large buffer ie we can add many vertex
    // VBO is a OpenGL object
    unsigned int VBO;
    // generate a unique ID for VBO
    glad_glGenBuffers(1, &VBO);
    // binds a buffer type to our buffer
    glad_glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // copy previously defined vertex data into buffers memory
    // • GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times.
    // • GL_STATIC_DRAW: the data is set only once and used many times.
    // • GL_DYNAMIC_DRAW: the data is changed a lot and used many times.
    glad_glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // compiling vertex shader
    unsigned int vertex_shader;
    vertex_shader = glad_glCreateShader(GL_VERTEX_SHADER);
    glad_glShaderSource(vertex_shader, 1, &vertexShaderSource, NULL);
    glad_glCompileShader(vertex_shader);

    // checks if compile shaders worked
    int success;
    char infoLog[512];
    glad_glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Fragment Shader - calculating colors (RGBA)
    unsigned int fragment_shader;
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragment_shader);

    // Shader Program - creating a shader object (linking vertex and fragment)
    unsigned int shader_program;
    shader_program = glCreateProgram(); // returns an id
    // linking
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    
    if (!success) 
    {
        glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
        std::cout << "error linking shader\n" << infoLog << std::endl;
    }

    
    // linking vertex attribute position
    // 0 defined in layout = 0
    // 3 size of vertex attribute (a vec3)
    // type of data of vec3
    // normalize: GL_FALSE
    // stride, space between  consecutive vertex elements
    // (offset in bytes)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // linking vertex attribute color          6 cause skipping position
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    while (!glfwWindowShouldClose(window))
    {
        // input
        process_input(window);
        
        // rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT); // fill the buffer with color configured by glClearColor
        // draw_triangle(shader_program);
        draw_rect(shader_program);
        
        // displaying (swap buffers)
        glfwSwapBuffers(window); // swap color 2d buffer (basically screen)
        glfwPollEvents();        // check for input events
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    glfwTerminate();
    return 0;
}

// resize viewport when window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void draw_triangle(unsigned int shader_program)
{
    // set opengl to use shader program
    glUseProgram(shader_program);
    
    // draw triangle
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void draw_rect(unsigned int shader_program)
{
    glUseProgram(shader_program);

    glDrawArrays(GL_TRIANGLES, 0, 6);
}