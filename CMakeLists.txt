cmake_minimum_required(VERSION 3.15)

project(KanbanCli LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Add third party headers
include_directories(${CMAKE_SOURCE_DIR}/third_party)

add_executable(kanban-tool
    src/main.cpp
    src/storage.cpp
)
