#include <stdlib.h>
#include <stdio.h>
#include "process_input.h"
#include "process_output.h"
#include "make_histogram.h"
#include "nesting_free.h"

int main() {
    int* inputArray = NULL;
    size_t inputSize = 0;
    if (process_input(stdin, &inputArray, &inputSize) == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }

    int** outputArray[2] = {NULL, NULL};
    size_t outputSize = 0;
    if (make_histogram(inputArray, inputSize, outputArray, &outputSize) ==
        EXIT_FAILURE) {
        free(inputArray);
        return EXIT_FAILURE;
    }

    if (process_output(stdout, outputArray, outputSize) == EXIT_FAILURE) {
        free(inputArray);
        free(outputArray[0]);
        nesting_free(outputArray[1], outputSize);
        return EXIT_FAILURE;
    }

    free(inputArray);
    free(outputArray[0]);
    nesting_free(outputArray[1], outputSize);
    return EXIT_SUCCESS;
}
