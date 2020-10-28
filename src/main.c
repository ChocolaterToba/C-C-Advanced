#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <getopt.h>
#include "single_thread.h"
#include "multi_thread.h"

typedef enum {
    SINGLE_THREAD,
    MULTI_THREAD
} thread_options;

int main(int argc, char* argv[]) {
    thread_options thread_option = SINGLE_THREAD;
    size_t array_len = 1 << 20;

    char* opts = "-:";

    int opt = 0;
    int option_index = 0;

    static struct option long_options[] = {
        {"thread", required_argument, NULL, 't'},
        {NULL, 0, NULL, 0}
    };

    while ((opt = getopt_long(argc, argv, opts, long_options,
                               &option_index)) != -1) {
        switch (opt) {
            case 't':
                if (optarg == 0) {
                    printf("Parameter thread must have an option\n");
                    printf("Usage: DZ2 [--thread=single|multi] [array_len]\n");
                    return EXIT_FAILURE;
                }
                if (strcasecmp(optarg, "single")) {
                    thread_option = SINGLE_THREAD;
                } else if (strcasecmp(optarg, "multi")) {
                    thread_option = MULTI_THREAD;
                } else {
                    printf("Incorrect thread option\n");
                    printf("Usage: DZ2 [--thread=single|multi] [array_len]\n");
                    return EXIT_FAILURE;
                }
                break;

            case 1:
                if (sscanf(optarg, "%zu", &array_len) != 1) {
                    printf("Incorrect array size\n");
                    printf("Usage: DZ2 [--thread=single|multi] [array_len]\n");
                    return EXIT_FAILURE;
                }
                break;

            case '?':
                printf("Unknown option\n");
                printf("Usage: DZ2 [--thread=single|multi] [array_len]\n");
                return EXIT_FAILURE;

            default:
                break;
        }
    }

    int* array = calloc(array_len, sizeof(int));
    if (array == NULL) {
        printf("Could not allocate memory for array\n");
        return EXIT_FAILURE;
    }

    clock_t start = clock();
    clock_t end;
    switch (thread_option) {
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
    printf("Filling time: %f seconds\n\n",
           (double)(end - start) / CLOCKS_PER_SEC);
    free(array);
    return EXIT_SUCCESS;
}
