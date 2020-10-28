#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <pthread.h>

#include "thread_options.h"

int process_input(int argc, char* argv[],
                  thread_options* thread_option, size_t* array_len) {
    if (!argc || argv == NULL || thread_option == NULL || array_len == NULL) {
        fprintf(stderr, "Incorrect arguments for process_input.\n");
        return EXIT_FAILURE;
    }

    char* opts = "-:";

    int opt = 0;
    int option_index = 0;

    static struct option long_options[] = {
        {"thread", required_argument, NULL, 't'},
        {NULL, 0, NULL, 0}
    };

    int optin = 1;

    while ((opt = getopt_long(argc, argv, opts, long_options,
                               &option_index)) != -1) {
        switch (opt) {
            case 't':
                if (optarg == 0) {
                    fprintf(stderr, "Parameter thread must have an option\n");
                    printf("Usage: DZ2 [--thread=single|multi] [array_len]\n");
                    return EXIT_FAILURE;
                }
                if (strcasecmp(optarg, "single") == 0) {
                    *thread_option = SINGLE_THREAD;
                } else if (strcasecmp(optarg, "multi") == 0) {
                    *thread_option = MULTI_THREAD;
                } else {
                    fprintf(stderr, "Incorrect thread option\n");
                    printf("Usage: DZ2 [--thread=single|multi] [array_len]\n");
                    return EXIT_FAILURE;
                }
                break;

            case 1:
                if (sscanf(optarg, "%zu", array_len) != 1) {
                    fprintf(stderr, "Incorrect array size\n");
                    printf("Usage: DZ2 [--thread=single|multi] [array_len]\n");
                    return EXIT_FAILURE;
                }
                break;

            case '?':
                fprintf(stderr, "Unknown option\n");
                printf("Usage: DZ2 [--thread=single|multi] [array_len]\n");
                return EXIT_FAILURE;

            default:
                break;
        }
    }

    return EXIT_SUCCESS;
}
