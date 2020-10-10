#include <stdlib.h>
#include <stdio.h>

int Processo (FILE* outfile, int** const outputArray[2], size_t outputSize) {
    if (outfile == NULL || outputArray == NULL) {
        return EXIT_FAILURE;
    }

    if (fprintf(outfile, "Numbers: [") != 10) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < outputSize - 1; ++i) {
        if (fprintf(outfile, "%d ,", *outputArray[0][i]) < 0) {
            return EXIT_FAILURE;
        }
    }
    if (fprintf(outfile, "%d]\n", *outputArray[0][outputSize - 1]) < 0) {
        return EXIT_FAILURE;
    }

    if (fprintf(outfile, "Frequences: [") != 13) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < outputSize - 1; ++i) {
        if (fprintf(outfile, "%d ,", *outputArray[1][i]) < 0) {
            return EXIT_FAILURE;
        }
    }
    if (fprintf(outfile, "%d]\n", *outputArray[1][outputSize - 1]) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}