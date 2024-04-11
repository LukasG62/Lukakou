/**
 * @file lukac.c
 * @brief Compiler program
 */

#include "common.h"

/**
 * @brief main
 * Entry point of the compiler program
 * @return 0 on success, 1 on failure
*/
int main(int argc, char *argv[]) {
    DEBUG_PRINT("Compiler program\n");

    if(argc < 2) {
        fprintf(stderr, "Usage: %s <source file>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
