cmake_minimum_required(VERSION 3.20)
project(device_driver CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(${PROJECT_NAME}_SOURCES 
    ${CMAKE_CURRENT_LIST_DIR}/tf/FrameDriver.cpp
)

add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_SOURCES})

# Set the include directories for the hal_driver library
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)

# target_include_directories(${PROJECT_NAME} PRIVATE
#    ${CMAKE_CURRENT_LIST_DIR}/utilities
# )

target_link_libraries(${PROJECT_NAME} PRIVATE
    tf
)
