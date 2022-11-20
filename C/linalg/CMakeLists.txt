cmake_minimum_required(VERSION 3.23)
project(linalg C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -O2")

include_directories(include)

add_library(linalg SHARED src/library.c)
add_executable(test test/test.c test/munit/munit.c)
