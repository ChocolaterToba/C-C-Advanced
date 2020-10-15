#pragma once

#include <stdlib.h>
#include <stdio.h>

//  Write 2 arrays from output_array to outfile with specific formatting
//  in: output_array - array containing 2 arrays:
//                    output_array[0] - ponters to numbers
//                    output_array[1] - pointers to frequences
//      output_size - size of output_array[0] and output_array[1]
//  out: outfile
//  Function returns EXIT_SUCCESS on success, EXIT_FAILURE on failure
int process_output(FILE* outfile, int** output_array[2], size_t output_size);
