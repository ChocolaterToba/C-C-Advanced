#include <stdlib.h>
#include <stdio.h>

int process_output(FILE* outfile, int** output_array[2], size_t output_size) {
    if (!outfile || !output_array) {
        return EXIT_FAILURE;
    }
    if (!output_array[0] || !output_array[1]) {
        return EXIT_FAILURE;
    }

    if (fprintf(outfile, "Numbers: [") != 10) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < output_size - 1; ++i) {
        if (fprintf(outfile, "%d, ", *output_array[0][i]) < 0) {
            return EXIT_FAILURE;
        }
    }
    if (fprintf(outfile, "%d]\n", *output_array[0][output_size - 1]) < 0) {
        return EXIT_FAILURE;
    }

    if (fprintf(outfile, "Frequences: [") != 13) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < output_size - 1; ++i) {
        if (fprintf(outfile, "%d, ", *output_array[1][i]) < 0) {
            return EXIT_FAILURE;
        }
    }
    if (fprintf(outfile, "%d]\n", *output_array[1][output_size - 1]) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
