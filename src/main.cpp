/*
* Lab 1 - Triangles Galore!
* 
* Requirements:
* 1. Make a window with some background color.
* 2. Create a scene with some triangles.
* 3. Write a shader to apply colors set in the code to the triangles.
* 4. When a button is pressed, change the color of each triangle.
* 5. On ESC, exit.
*/

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include "shader.hpp"
#include "mesh.hpp"

void setViewportSizeCallback(GLFWwindow* window, int width, int height);

std::vector<Mesh> initScene(ShaderProgram* shaderProgram);

void processInput(GLFWwindow* window);

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW.\n";
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(640, 480, "Lab 1", NULL, NULL);
    if (window == NULL) {
        std::cerr << "Failed to create window.\n";
        return -1;
    }

    glfwMakeContextCurrent(window);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD.\n";
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, setViewportSizeCallback);

    ShaderProgram shaderProgram("Vec3.vert", "Vec3.frag");
    auto scene = initScene(&shaderProgram);

    while (!glfwWindowShouldClose(window)) {
        // process input
        processInput(window);

        // fun rendering things
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        for (Mesh& mesh : scene) {
            mesh.draw();
        }

        // poll events
        glfwPollEvents();

        // swap buffers
        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}

void setViewportSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

std::vector<Mesh> initScene(ShaderProgram* shaderProgram) {
    std::vector<Mesh> scene;

    std::vector<f32> aVerts{
        -0.5f, -0.5f, 0.0f,    1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f,    1.0f, 0.0f, 0.0f,
         0.5f, 0.25f, 0.0f,    0.5f, 0.0f, 0.5f,
         0.0f, 0.75f, 0.0f,    0.0f, 0.0f, 1.0f,
        -0.5f, 0.25f, 0.0f,    0.0f, 0.0f, 1.0f
    };
    std::vector<u32> aIndices{
        0, 1, 2,
        0, 4, 2,
        2, 3, 4
    };
    scene.push_back(Mesh(aVerts, aIndices, shaderProgram));

    std::vector<f32> bVerts{
        0.5f, 0.5f, 0.0f,   1.0, 0.0, 0.0,
        0.7f, 0.7f, 0.0f,   0.0, 1.0, 0.0,
        0.9f, 0.5f, 0.0f,   0.0, 0.0, 1.0
    };
    std::vector<u32> bIndices{
        0, 1, 2
    };
    scene.push_back(Mesh(bVerts, bIndices, shaderProgram));

    return scene;
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}
