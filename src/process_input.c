#include <stdlib.h>
#include <stdio.h>

int process_input(FILE* infile, int** input_array, size_t* input_size) {
    if (!infile || !input_array || !input_size) {
        return EXIT_FAILURE;
    }
    if (*input_array) {  //  Array is already initialised.
        return EXIT_FAILURE;
    }

    if (fscanf(infile, "%lu", input_size) != 1) {
        return EXIT_FAILURE;
    }

    *input_array = (int*) calloc(*input_size, sizeof(int));
    if (!*input_array) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < *input_size; ++i) {
        if (fscanf(infile, "%d", *input_array + i) != 1) {
            free(*input_array);
            *input_array = NULL;
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
