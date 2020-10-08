#include <stdlib.h>

void NestingFree(int** array, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        free(array[i]);  //  Freeing nested arrays with single numbers in them.
    }
    free(array);
}