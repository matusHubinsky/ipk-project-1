
#ifndef MAIN_H_
#define MAIN_H_

#include <iostream>
#include <cstring>

    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN64)
        #define OS "windows"
    #elif defined(__linux__) || defined(__gnu_linux__)
        #define OS "linux"
    #else 
        #define OS "unknown"
    #endif

#define BUFFER_SIZE 512

extern std::string buffer[BUFFER_SIZE];
extern int client_socket;

#endif