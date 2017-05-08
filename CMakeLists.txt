cmake_minimum_required(VERSION 3.6)
project(ft_ls)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c ft_ls.h ft_ls.c test.c)
add_executable(ft_ls ${SOURCE_FILES})