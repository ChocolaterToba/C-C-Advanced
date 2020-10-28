#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "multi_thread.h"

int MultiThreadFill(int* array, size_t array_len) {
    if (array == NULL) {
        return EXIT_FAILURE;
    }

    int data = 1;
    for (size_t i = 0; i < array_len; ++i) {
        array[i] = data;

        if (data != 3) {
            ++data;
        } else {
            data = 1;
        }
    }

    return EXIT_SUCCESS;
}
