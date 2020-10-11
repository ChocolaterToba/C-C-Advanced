#include <stdlib.h>
#include <stdio.h>
#include "processi.h"
#include "processo.h"
#include "make_histogram.h"
#include "nesting_free.h"

int main() {
    int* inputArray = NULL;
    size_t inputSize = 0;
    if (Processi(stdin, &inputArray, &inputSize) == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }

    int** outputArray[2] = {NULL, NULL};
    size_t outputSize = 0;
    if (MakeHistogram(inputArray, inputSize, outputArray, &outputSize) == EXIT_FAILURE) {
        free(inputArray);
        return EXIT_FAILURE;
    }

    if (Processo(stdout, outputArray, outputSize) == EXIT_FAILURE) {
        free(inputArray);
        free(outputArray[0]);
        NestingFree(outputArray[1], outputSize);
        return EXIT_FAILURE;
    }

    free(inputArray);
    free(outputArray[0]);
    NestingFree(outputArray[1], outputSize);
    return EXIT_SUCCESS;
}