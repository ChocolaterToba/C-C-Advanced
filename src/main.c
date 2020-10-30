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

    struct timespec start;
    clock_gettime(CLOCK_REALTIME, &start);
    size_t loops_amount = 100;
    for (size_t i = 0; i < loops_amount; ++i) {
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
    }

    struct timespec end;
    clock_gettime(CLOCK_REALTIME, &end);
    printf("Average filling time: %f seconds\n\n",
           ((double)(end.tv_sec - start.tv_sec) +
            (double)(end.tv_nsec - start.tv_nsec) / 1000000000L)
            / loops_amount);
    free(array);
    return EXIT_SUCCESS;
}
