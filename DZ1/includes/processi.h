#pragma once

#include <stdlib.h>
#include <stdio.h>

//  Write array from infile to inputArray
//  in: infile
//  out: inputArray - pointer to pointer to format array
//                    p to p because we need to change external pointer to array
//       inputSize - pointer to variable with array's size
//  Function returns EXIT_SUCCESS on success, EXIT_FAILURE on failure
//  InputArray is guaranteed to be freed in case of failure
int Processi(FILE* infile, int** inputArray, size_t* inputSize);