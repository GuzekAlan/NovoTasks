# First command. Must be on top
cmake_minimum_required(VERSION 3.15.0)

# Setting project name
project(task_2)

# C/C++ options (Use CXX for C++)
set(CMAKE_BUILD_TYPE Debug) # can be Release
set(CMAKE_CXX_STANDARD 17) # C++ standard
set(CMAKE_CXX_STANDARD_REQUIRED ON) # requires user to have compiler which can compile in set standard

# Flags to use in compiling
set(CMAKE_CXX_FLAGS_DEBUG_INIT -Wall -Wextra)
set(CMAKE_CXX_FLAGS_RELEASE_INIT -Wall -Wextra)

# Use set to add one folder to INCLUDES
set(INCLUDES ${PROJECT_SOURCE_DIR}/include)
# Adds directories (allows to omit relative path and only pass names of headers)
include_directories(${INCLUDES})    # REMEMBER TO USE ${XXXXX} FOR VARIABLE NAMES

# Use Glob to add multiple files to name SOURCE
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

# Adding .cpp files (relative from where CMake file is)
add_executable(${PROJECT_NAME} ${SOURCES})


option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)

# Adding SFML as subdirectory (Found in the internet)
include(FetchContent)

FetchContent_Declare(
  SFML
  URL "https://github.com/SFML/SFML/archive/2.5.1.zip"
)
FetchContent_GetProperties(SFML)

if(NOT SFML_POPULATED)
  if (LINK_DEPS_STATIC)
    set(SFML_STATIC_LIBRARIES TRUE CACHE BOOL "Use static libraries")
  endif()

  set(SFML_INSTALL_PKGCONFIG_FILES OFF CACHE BOOL "Install pkgconfig files")

  if (USE_SYSTEM_DEPS)
    find_package(SFML ${SFML_VERSION} COMPONENTS graphics QUIET)
  else()
    FetchContent_Populate(SFML)

    # No need to build audio and network modules
    set(SFML_BUILD_AUDIO FALSE CACHE BOOL "Build audio")
    set(SFML_BUILD_NETWORK FALSE CACHE BOOL "Build network")
    add_subdirectory(${sfml_SOURCE_DIR} ${sfml_BINARY_DIR} EXCLUDE_FROM_ALL)
  endif()
endif()

target_link_libraries(
  task_2 PRIVATE
        sfml-graphics
        sfml-system
        sfml-window
)

set_property(TARGET task_2 PROPERTY
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")