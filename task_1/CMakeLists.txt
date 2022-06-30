# First command. Must be on top
cmake_minimum_required(VERSION 3.1.0)

# Setting project name
project(task_1)

# C/C++ options (Use CXX for C++)
set(CMAKE_BUILD_TYPE Debug) # can be Release
set(CMAKE_CXX_STANDARD 17) # C++ standard
set(CMAKE_CXX_STANDARD_REQUIRED ON) # requires user to have compiler which can compile in set standard

# Flags to use in compiling
set(CMAKE_CXX_FLAGS_DEBUG_INIT -Wall -Wextra)
set(CMAKE_CXX_FLAGS_RELEASE_INIT -Wall -Wextra)

# Use set to add one folder to INCLUDES
set(INCLUDES ${PROJECT_SOURCE_DIR}/include)
# Adds directories (allows to ommit relative path and only pass names of headers)
include_directories(${INCLUDES})    # REMEMBER TO USE ${XXXXX} FOR VARIABLE NAMES

# Use Glob to add mutliple files to name SOURCE
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

# Adding .cpp files (relative from where CMake file is)
add_executable(${PROJECT_NAME} ${SOURCES})
