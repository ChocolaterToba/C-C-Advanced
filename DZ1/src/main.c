#include <stdlib.h>
#include <stdio.h>

int main() {
    printf("Please input array's length: ");
    size_t inputSize = 0;
    if (scanf("%lu", &inputSize) != 1) {
        perror("Error when reading array's length\n");
        return EXIT_FAILURE;
    }

    int* inputArray = (int*) calloc(inputSize, sizeof(int));
    if (inputArray == NULL) {
        perror("Could not allocate memory for input array\n");
        return EXIT_FAILURE;
    }

    printf("Please input array's elements, separated by space or enter\n");
    for (size_t i = 0; i < inputSize; ++i) {
        if (scanf("%u", inputArray + i) != 1) {
            perror("Error when reading array's element\n");
            free(inputArray);
            return EXIT_FAILURE;
        }
    }

    int** outputArray[2];
    size_t outputSize = 0;
    if (MakeHistogram(inputArray, inputSize,
                      outputArray, &outputSize) == EXIT_FAILURE) {
        free(inputArray);
        return EXIT_FAILURE;
    }

    printf("Numbers: [");
    for (size_t i = 0; i < outputSize; ++i) {
        printf("%d ,", *outputArray[0][i]);
    }
    printf("\b\b] \n");

    printf("Frequences: [");
    for (size_t i = 0; i < outputSize; ++i) {
        printf("%d ,", *outputArray[1][i]);
    }
    printf("\b\b] \n");

    free(inputArray);
    free(outputArray[0]);
    NestingFree(outputArray[1], outputSize);
    return EXIT_SUCCESS;
}