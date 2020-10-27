#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "single_thread_lib.h"
#include "multi_thread_lib.h"

typedef enum {
    SINGLE_THREAD,
    MULTI_THREAD
} run_options;

int main(int argc, char* argv[]) {
    run_options option = SINGLE_THREAD;
    size_t array_len = 1 << 20;
    if (argc >= 1) {
        if (argv[1] == "-multi-thread") {
            option = MULTI_THREAD;
        } else if (argv[1] != "-single-thread") {
            printf("Unknown option -%s\n", argv[1]);
            printf("Usage: DZ2 [-multi-thread | -single-thread] [length]\n\n");
            return EXIT_FAILURE;
        }

        if (argc == 2) {
            if (sscanf(argv[2], "%zu", &array_len) != 1) {
                printf("Error: length should be a positive integer.\n\n");
                return EXIT_FAILURE;
            }
        } else {
            printf("%d options passed. Should be 2 or less", argc);
            printf("Usage: DZ2 [-multi-thread | -single-thread] [length]\n\n");
            return EXIT_FAILURE;
        }
    }

    int* array = calloc(array_len, sizeof(int));

    clock_t start = clock();
    clock_t end;
    switch (option) {
        case SINGLE_THREAD:
            if (SingleThreadFill(array, array_len) == EXIT_FAILURE) {
                free(array);
                return EXIT_FAILURE;
            }
            break;
        case MULTI_THREAD:
            if (MultiThreadFill(array, array_len) == EXIT_FAILURE) {
                free(array);
                return EXIT_FAILURE;
            }
            break;
    }
    end = clock();
    printf("Total time: %f seconds\n\n", (end - start) / CLOCKS_PER_SEC);
    return EXIT_SUCCESS;
}
