#pragma once

#include <stdlib.h>

//  Make array consisting of input's numbers and their frequences
//  in: inputArray
//  out: outputArray[0] - pointers to unique numbers from input
//       outputArray[1] - pointers to unique numbers' frequences
//  Function returns EXIT_SUCCESS on success, EXIT_FAILURE on failure
//  outputArray[0] and outputArray[1] are guaranteed to be freed in case of failure
int MakeHistogram(int* inputArray, size_t inputSize,
                  int** outputArray[2], size_t* outputSize);