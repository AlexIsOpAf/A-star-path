cmake_minimum_required(VERSION 3.1)

# if(${CMAKE_VERSION} VERSION_LESS 3.14)
#     cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
# else()
#     cmake_policy(VERSION 3.14)
# endif()
# project(apath LANGUAGES CXX)

# add_compile_options(-Wall -Wextra -Wpedantic)

# add_library(alib includes/Node.h includes/Matrix.h)
# target_include_directories(alib PUBLIC inclu)

# add_executable(arun src/Node.cpp src/Matrix.cpp src/main.cpp) 

# set(HEADER_FILES includes/Matrix.h includes/file2.h)

# add_library(mylib libsrc.cpp HEADER_FILES)
# target_include_directories(mylib PRIVATE includes)
# add_executable(myexec src/Node.cpp src/Matrix.cpp src/main.cpp HEADER_FILES)
# target_include_directories(myexec PRIVATE ${YOUR_DIRECTORY})

# target_include_directories(test PRIVATE includes)
set(SOURCES src/main.cpp src/Node.cpp src/Matrix.cpp includes/Node.h includes/Matrix.h)
add_executable(test ${SOURCES})









