#pragma once

#include <stdlib.h>
#include <stdio.h>

//  Write array from infile to input_array
//  in: infile
//  out: input_array - pointer to pointer to format array
//                    p to p because we need to change external pointer to array
//       input_size - pointer to variable with array's size
//  Function returns EXIT_SUCCESS on success, EXIT_FAILURE on failure
//  input_array is guaranteed to be freed in case of failure
int process_input(FILE* infile, int** input_array, size_t* input_size);
