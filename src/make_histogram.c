#include <stdlib.h>
#include "nesting_free.h"

int MakeHistogram(int* inputArray, size_t inputSize,
                  int** outputArray[2], size_t* outputSize) {
    if (inputArray == NULL || outputArray == NULL || outputSize == NULL) {
        return EXIT_FAILURE;
    }
    if (outputArray[0] != NULL || outputArray[1] != NULL) {
        return EXIT_FAILURE;
    }

    *outputSize = 0;
    size_t actualSize = 8;
    outputArray[0] = (int**) calloc(actualSize, sizeof(int*));
    if (outputArray[0] == NULL) {
        return EXIT_FAILURE;
    }

    outputArray[1] = (int**) calloc(actualSize, sizeof(int*));
    if (outputArray[1] == NULL) {
        free(outputArray[0]);
        outputArray[0] = NULL;
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < inputSize; ++i) {
        size_t j = 0;
        for (; j < *outputSize; ++j) {
            if (*outputArray[0][j] == inputArray[i]) {
                ++*outputArray[1][j];
                break;
            }
        }
        if (j == *outputSize) {
            if (j == actualSize) {
                int** newOutputNumbers = realloc(outputArray[0],
                                                 sizeof(int*) * actualSize * 2);
                int** newOutputFreq = realloc(outputArray[1],
                                              sizeof(int*) * actualSize * 2);

                if (newOutputNumbers == NULL || newOutputFreq == NULL) {
                    free(outputArray[0]);
                    NestingFree(outputArray[1], j);
                    outputArray[0] = NULL;
                    outputArray[1] = NULL;
                    return EXIT_FAILURE;
                }

                outputArray[0] = newOutputNumbers;
                outputArray[1] = newOutputFreq;
                actualSize *= 2;
            }

            outputArray[1][j] = (int*) malloc(sizeof(int));
            if (outputArray[1][j] == NULL) {
                free(outputArray[0]);
                NestingFree(outputArray[1], j);
                outputArray[0] = NULL;
                outputArray[1] = NULL;
                return EXIT_FAILURE;
            }

            outputArray[0][j] = inputArray + i;
            *outputArray[1][j] = 1;
            ++*outputSize;
        }
    }

    return EXIT_SUCCESS;
}
