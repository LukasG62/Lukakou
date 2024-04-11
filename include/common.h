/**
 * @file common.h
 * @brief Common header file
 * This file contains common macros and definitions used throughout the project.
 */

#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef DEBUG
    #define UNUSED(x) (void)(x) //!< Macro to suppress unused variable warnings
    #define UNIMPLEMENTED(string) fprintf(stderr, "Unimplemented: %s\n", string) //!< Macro to print unimplemented function name
    #define DEBUG_PRINT(...) fprintf(stderr, __VA_ARGS__) //!< Macro to print debug message
#else
    #define UNUSED(x) (void)(x) //!< Macro to suppress unused variable warnings
    #define UNIMPLEMENTED(string) //!< Macro to print unimplemented function name
    #define DEBUG_PRINT(...) //!< Macro to print debug message
#endif

#define CHECK_ALLOC(ptr) if (!ptr) { ERROR("Memory allocation failed\n"); exit(EXIT_FAILURE); } //!< Macro to check memory allocation


#endif // COMMON_H