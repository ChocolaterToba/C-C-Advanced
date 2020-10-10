#include <stdlib.h>
#include <stdio.h>

int Processi(FILE* infile, int** inputArray, size_t* inputSize) {
    if (infile == NULL || inputArray == NULL || inputSize == NULL) {
        return EXIT_FAILURE;
    }
    if (*inputArray != NULL) {  //  Array is already initialised.
        return EXIT_FAILURE;
    }

    if (fscanf(infile, "%lu", inputSize) != 1) {
        return EXIT_FAILURE;
    }

    *inputArray = (int*) calloc(*inputSize, sizeof(int));
    if (*inputArray == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < *inputSize; ++i) {
        if (fscanf(infile, "%d", *inputArray + i) != 1) {
            free(*inputArray);
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}