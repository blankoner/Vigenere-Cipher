cmake_minimum_required(VERSION 3.27.7)

project(Viegenere)
add_executable(${PROJECT_NAME} cpp/main.cpp cpp/cipher.cpp)
target_compile_options(${PROJECT_NAME} PRIVATE -g)
