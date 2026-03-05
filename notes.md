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