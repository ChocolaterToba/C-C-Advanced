#include <stdlib.h>
#include <stdio.h>
#include "single_thread.h"

int single_thread_fill(int* array, size_t array_len) {
    if (array == NULL) {
        return EXIT_FAILURE;
    }

    int data = 0;
    for (size_t i = 0; i < array_len; ++i) {
        array[i] = data;

        if (data != 3) {
            ++data;
        } else {
            data = 0;
        }
    }

    return EXIT_SUCCESS;
}
