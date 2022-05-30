cmake_minimum_required(VERSION 3.20)
include_directories("/include")
include_directories("glad/")
add_executable(LearnOpenGL "main.cpp" "mesh.cpp" "shader.cpp" "glad/glad.c")

find_package(glfw3 REQUIRED HINTS $ENV{GLFW_DIR})

target_link_libraries(LearnOpenGL PRIVATE glfw)
