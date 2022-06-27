cmake_minimum_required(VERSION 3.17)
project(ProjetoPPP C)

set(CMAKE_C_STANDARD 11)

add_compile_options(-Wall -Wextra -Werror)

add_executable(ProjetoPPP main.c structure.c lib-utf8.c)