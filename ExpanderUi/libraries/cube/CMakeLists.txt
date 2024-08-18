cmake_minimum_required(VERSION 3.16)
project(cube_programmer CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create the interface library
add_library(${PROJECT_NAME} INTERFACE)

# Set the include directories
target_include_directories(${PROJECT_NAME} INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/.
)
