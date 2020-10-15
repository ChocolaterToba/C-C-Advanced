#include <stdlib.h>

void NestingFree(int** array, size_t size) {
    if (!array) {
        for (size_t i = 0; i < size; ++i) {
            free(array[i]);  //  Freeing nested arrays of length 1.
        }
        free(array);
        array = NULL;
    }
}
