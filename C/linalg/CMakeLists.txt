cmake_minimum_required(VERSION 3.23)
project(linalg C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_FLAGS "-Wall -Wextra -O0 -lm")

include_directories(include)

set(sources src/vector.c src/matrix.c)

add_library(linalg SHARED ${sources})
add_executable(test test/test.c test/munit/munit.c ${sources})
