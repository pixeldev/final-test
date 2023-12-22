cmake_minimum_required(VERSION 3.27)
project(final_test C)

set(CMAKE_C_STANDARD 23)

add_executable(final_test main.c
        double_circular_linked_list.c
        double_circular_linked_list.h
        queue.c
        queue.h
        huffman.c
        huffman.h
        definitions.h)
