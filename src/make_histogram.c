#include <stdlib.h>
#include "nesting_free.h"

int make_histogram(int* input_array, size_t input_size,
                  int** output_array[2], size_t* output_size) {
    if (!input_array || !output_array || !output_size) {
        return EXIT_FAILURE;
    }
    if (output_array[0] || output_array[1]) {
        return EXIT_FAILURE;
    }

    *output_size = 0;
    size_t actual_size = 8;
    output_array[0] = (int**) calloc(actual_size, sizeof(int*));
    if (!output_array[0]) {
        return EXIT_FAILURE;
    }

    output_array[1] = (int**) calloc(actual_size, sizeof(int*));
    if (!output_array[1]) {
        free(output_array[0]);
        output_array[0] = NULL;
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < input_size; ++i) {
        size_t j = 0;
        for (; j < *output_size; ++j) {
            if (*output_array[0][j] == input_array[i]) {
                ++*output_array[1][j];
                break;
            }
        }
        if (j == *output_size) {
            if (j == actual_size) {
                int** new_output_numbers = realloc(output_array[0],
                                                   sizeof(int*) *
                                                   actual_size * 2);
                int** new_output_freq = realloc(output_array[1],
                                              sizeof(int*) * actual_size * 2);

                if (!new_output_numbers || !new_output_freq) {
                    free(output_array[0]);
                    nesting_free(output_array[1], j);
                    output_array[0] = NULL;
                    output_array[1] = NULL;
                    return EXIT_FAILURE;
                }

                output_array[0] = new_output_numbers;
                output_array[1] = new_output_freq;
                actual_size *= 2;
            }

            output_array[1][j] = (int*) malloc(sizeof(int));
            if (!output_array[1][j]) {
                free(output_array[0]);
                nesting_free(output_array[1], j);
                output_array[0] = NULL;
                output_array[1] = NULL;
                return EXIT_FAILURE;
            }

            output_array[0][j] = input_array + i;
            *output_array[1][j] = 1;
            ++*output_size;
        }
    }

    return EXIT_SUCCESS;
}
