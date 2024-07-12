cmake_minimum_required(VERSION 3.10)

project(dotnote VERSION 0.1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(.note
    src/main.cpp
    src/impl/CommandInterpreter.cpp
)
target_include_directories(.note PRIVATE src/headers)
