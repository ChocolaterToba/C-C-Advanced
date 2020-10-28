#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <getopt.h>

#include "thread_options.h"
#include "process_input.h"

#include "single_thread.h"
#include "multi_thread.h"

int main(int argc, char* argv[]) {
    thread_options thread_option = SINGLE_THREAD;
    size_t array_len = 1 << 24;

    if (process_input(argc, argv, &thread_option, &array_len) == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }

    int* array = calloc(array_len, sizeof(int));
    if (array == NULL) {
        fprintf(stderr, "Could not allocate memory for array\n");
        return EXIT_FAILURE;
    }

    clock_t start = clock();
    clock_t end;
    switch (thread_option) {
        case SINGLE_THREAD:
            if (single_thread_fill(array, array_len) == EXIT_FAILURE) {
                free(array);
                return EXIT_FAILURE;
            }
            break;
        case MULTI_THREAD:
            if (multi_thread_fill(array, array_len) == EXIT_FAILURE) {
                free(array);
                return EXIT_FAILURE;
            }
            break;
    }

    end = clock();
    printf("Filling time: %f seconds\n\n",
           (double)(end - start) / CLOCKS_PER_SEC);
    free(array);
    return EXIT_SUCCESS;
}
