#include <stdlib.h>
#include <stdio.h>

int Processo (FILE* outfile, int** const outputArray[2], size_t outputSize) {
    if (outfile == NULL || outputArray == NULL) {
        return EXIT_FAILURE;
    }

    if (fprintf(outfile, "Numbers: [") != 10) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < outputSize; ++i) {
        if (fprintf(outfile, "%d ,", *outputArray[0][i]) != 1) {
            return EXIT_FAILURE;
        }
    }

    if (fprintf(outfile, "\b\b]\nFrequences: [") != 17) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < outputSize; ++i) {
        if (fprintf(outfile, "%d ,", *outputArray[1][i]) != 1) {
            return EXIT_FAILURE;
        }
    }

    if (fprintf(outfile, "\b\b]\n") !=4) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}