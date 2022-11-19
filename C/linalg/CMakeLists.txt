cmake_minimum_required(VERSION 3.23)
project(linalg C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_FLAGS "-Wall -Wextra -Werror")

add_library(linalg SHARED library.c)
