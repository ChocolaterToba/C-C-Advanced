#pragma once

#include <stdlib.h>
#include "thread_options.h"

int process_input(int argc, char* argv[],
                  thread_options* thread_option, size_t* array_len);
