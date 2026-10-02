cmake_minimum_required(VERSION 3.14)

set(NAME windshield)
set(VERSION 1.0.0)
set(CMAKE_CXX_STANDART 23)

project(${NAME} VERSION ${VERSION})
add_executable(${NAME}
                src/main.cpp
                src/file_handler.cpp)
target_include_directories(${NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
