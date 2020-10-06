#include <stdlib.h>
#include <stdio.h>

void NestingFree(int** array, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        free(array[i]);  //  Freeing nested arrays with single numbers in them.
    }
    free(array);
}

int MakeHistogram(int* inputArray, size_t inputSize,
                  int** outputArray[2], size_t* outputSize) {
    if (inputArray == NULL) {
        return EXIT_SUCCESS;
    }

    *outputSize = 0;
    size_t actualSize = 8;
    outputArray[0] = (int**) calloc(actualSize, sizeof(int*));
    if (outputArray[0] == NULL) {
        perror("Could not allocate memory for output numbers array\n");
        return EXIT_FAILURE;
    }

    outputArray[1] = (int**) calloc(actualSize, sizeof(int*));
    if (outputArray[1] == NULL) {
        perror("Could not allocate memory for output frequences array\n");
        free(outputArray[0]);
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < inputSize; ++i) {
        size_t j = 0;
        for (j; j < *outputSize; j++) {
            if (*outputArray[0][j] == inputArray[i]) {
                ++*outputArray[1][j];
                break;
            }
        }
        if (j == *outputSize) {
            if (j == actualSize) {
                int** newOutputNumbers = realloc(outputArray[0], actualSize * 2);
                int** newOutputFrequences = realloc(outputArray[1], actualSize * 2);

                if (newOutputNumbers == NULL || newOutputFrequences == NULL) {
                    free(outputArray[0]);
                    NestingFree(outputArray[1], j);
                    perror("Could not reallocate memory for output arrays\n");
                    return EXIT_FAILURE;
                }

                outputArray[0] = newOutputNumbers;
                outputArray[1] = newOutputFrequences;
                actualSize *= 2;
            }

            outputArray[1][j] = (int*) malloc(sizeof(int));
            if (outputArray[1][j] == NULL) {
                free(outputArray[0]);
                NestingFree(outputArray[1], j);
                perror("Could not allocate memory for single frequency\n");
                return EXIT_FAILURE;
            }

            outputArray[0][j] = inputArray + i;
            *outputArray[1][j] = 1;
            ++*outputSize;
        }
    }
    
    return EXIT_SUCCESS;
}

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