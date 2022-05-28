cmake_minimum_required(VERSION 3.20)
include_directories("include/")
include_directories("/include")
add_executable(LearnOpenGL "main.cpp" "glad.c"  "mesh.cpp" "shader.cpp")

find_package(glfw3 REQUIRED HINTS $ENV{GLFW_DIR})

target_link_libraries(LearnOpenGL PRIVATE glfw)
