cmake_minimum_required(VERSION 3.14)
project(maze-game LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    sfml
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        3.1.0
)

set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)

set(SFML_BUILD_EXAMPLES OFF CACHE INTERNAL "")
set(SFML_BUILD_DOC OFF CACHE INTERNAL "")

FetchContent_MakeAvailable(sfml)

file(GLOB_RECURSE SRC_FILES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE 
    sfml-graphics
    sfml-audio
)

target_include_directories(${PROJECT_NAME} PRIVATE src)