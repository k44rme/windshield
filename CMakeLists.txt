cmake_minimum_required(VERSION 4.0)
set(CMAKE_CXX_STANDART 23)

set(NAME windshield)
set(VERSION 1.0.0)

project(${NAME} VERSION ${VERSION})
add_executable(${NAME}
                src/main.cpp
                src/file_handler.cpp
                src/cli_manager.cpp)
target_include_directories(${NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
