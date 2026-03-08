# Learn OpenGL
> Version 3.3, the foundation. All post versions can be used if you know how to code on 3.3

## Concepts

Using GLFW instead of SDL, to be easier to follow learnopengl.com tutorial/book

`GLFW:` Library written in C specifically targeted by OpenGL

### Building GLFW

- Download GLFW (google glfw donwload, but linux usually already have installed)

### Compiling 

Use this headers:

`-lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl.`

Links (in order): glfw, opengl, x11, thread, xrandr (resize and rotate), xi (input), and dl (dynamic loader)

### GLAD

Library that users a web server to help connecting the graphics card with the operating system

#### Setuping GLAD

For setuping GLAD, we need to connect to the webserver glad.dav1d.de/ and:

- specify the OpenGL version (at least 3.3)
- set profile to Core
- ensure the Generate a loader option is ticked

Glad then will generate a zip file including two folders and a single `glad.c` file

Unzip them into the working directory

After that, we can `include <glad/glad.h>` into our code

> Hint: if we add glad.h inside our local include, we should also compile with the tag `Include` 

## Graphics Pipeline

What is the graphics pipeline?

Everything in OpenGL works on 3D space, but screen is 2D, so the pipeline is:

3D coordinates --> 2D coordinates --> colored pixels

- `shaders:` small process that runs on GPU cores for each step of the pipeline

`Vertex Data:` list of three 3D coordinates that maps to a triangle. Each vertex data contain a `vertex atributte`, that can be whatever we want (eg a particle), but it can be just a 3D position and a color

Our collection of coordinates needs to be known for OpenGL, so we need to pass a hint for its `primitive` type: `GL_POINTS`, `GL_TRIANGLES`, `GL_LINE_STRIP`

In modern OpenGL we are required to make a `vertex` and a `fragment shader` (check book)

### Vertex Shader 

Vertex shader is written in GLSL (OpenGL Shader Language)

More info in book

### EBO (Element Buffer Object)

We can create a EBO when we have figures that reuses points, eg a rectangle is made by two triangles, but we actually need just 4 points and not 6

### GLSL

GL Shaders Language is pretty similar as C, just some tricks

they have vectors and matrices

also `uniforms`, aka global variables
