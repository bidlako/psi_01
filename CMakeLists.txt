cmake_minimum_required(VERSION 3.26)
project(psi_01 C)

set(CMAKE_C_STANDARD 99)

add_executable(psi_01 main.c
        tcp_server.h
        tcp_server.c)
