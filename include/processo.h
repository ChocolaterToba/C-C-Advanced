#pragma once

#include <stdlib.h>
#include <stdio.h>

//  Write 2 arrays from outputArray to outfile with specific formatting
//  in: outputArray - array containing 2 arrays:
//                    outputArray[0] - ponters to numbers
//                    outputArray[1] - pointers to frequences
//      outputSize - size of outputArray[0] and outputArray[1]
//  out: outfile
//  Function returns EXIT_SUCCESS on success, EXIT_FAILURE on failure
int Processo (FILE* outfile, int** outputArray[2], size_t outputSize);