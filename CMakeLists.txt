cmake_minimum_required(VERSION 3.16)
project(Music-Visualizer VERSION 1.0)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)

set(CMAKE_REQUIRED_FLAGS "-lSDL2 -lSDL2_ttf")

find_library(SDL2_LIBRARY NAMES SDL2)
find_library(SDL2_TTF_LIBRARY NAMES SDL2_ttf)

message("")
if(NOT SDL2_LIBRARY)
  message(FATAL_ERROR "SDL2 not found, please install it via your package manager!")
else()
  message(STATUS "SDL2 found at ${SDL2_LIBRARY}")
endif()

if(NOT SDL2_TTF_LIBRARY)
  message(FATAL_ERROR "SDL2_ttf not found, please install it via your package manager!")
else()
  message(STATUS "SDL2_ttf found at ${SDL2_TTF_LIBRARY}")
endif()
message("")

file(GLOB SOURCES "src/*.c")

add_executable(Vis ${SOURCES})

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  target_compile_options(Vis PRIVATE -Wall -Wextra -pedantic)
endif()

target_link_libraries(Vis ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARY})



