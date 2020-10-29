#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "multi_thread.h"

#define TRUE 1
#define FALSE 0

#ifdef _WIN32
#include <windows.h>
#elif MACOS
#include <sys/param.h>
#include <sys/sysctl.h>
#else
#include <unistd.h>
#endif

int getNumCores() {
#ifdef WIN32
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    return sysinfo.dwNumberOfProcessors;
#elif MACOS
    int nm[2];
    size_t len = 4;
    uint32_t count;

    nm[0] = CTL_HW;
    nm[1] = HW_AVAILCPU;
    sysctl(nm, 2, &count, &len, NULL, 0);

    if (count < 1) {
        nm[1] = HW_NCPU;
        sysctl(nm, 2, &count, &len, NULL, 0);
        if (count < 1) {
            count = 1;
        }
    }
    return count;
#else
    return sysconf(_SC_NPROCESSORS_ONLN);
#endif
}

typedef struct {
    int* start;
    size_t batch_size;
    int starting_data;
} thread_info;

void* fill_batch(void* arg) {
    if (arg == NULL) {
        return (void*) EXIT_FAILURE;
    }

    thread_info* info = arg;
    if (info->start == NULL) {
        return (void*) EXIT_FAILURE;
    }

    int data = info->starting_data;
    for (size_t i = 0; i < info->batch_size; ++i) {
        info->start[i] = data;

        if (data != 3) {
            ++data;
        } else {
            data = 0;
        }
    }

    free(info);
    info = NULL;
    return (void*) EXIT_SUCCESS;
}

int multi_thread_fill(int* array, size_t array_len) {
    if (array == NULL) {
        return EXIT_FAILURE;
    }
    unsigned threads_amount = getNumCores();



    size_t batch_size = 0;
    batch_size = array_len / threads_amount;

    pthread_t* threads = calloc(threads_amount, sizeof(pthread_t));
    for (size_t i = 0; i < threads_amount; ++i) {
        thread_info* info = (thread_info*) malloc(sizeof(thread_info));
        if (info == NULL) {
            fprintf(stderr, "Could not create a thread\n");
            free(threads);
            return EXIT_FAILURE;
        }

        info->start = array + i * batch_size;
        if (i < threads_amount - 1) {
            info->batch_size = batch_size;
        } else {
            info->batch_size = array_len - i * batch_size;
        }

        info->starting_data = (i * batch_size) % 4;

        if (pthread_create(threads + i, NULL, fill_batch, (void*) info) != 0) {
            for (size_t j = 0; j < i; ++j) {
                pthread_join(threads[j], NULL);
            }

            fprintf(stderr, "Could not create a thread\n");
            free(threads);
            return EXIT_FAILURE;
        }
    }

    int status = 0;
    int return_value = EXIT_SUCCESS;
    for (size_t i = 0; i < threads_amount; ++i) {
        if (pthread_join(threads[i], (void*) &status) != 0) {
            fprintf(stderr, "Could not join a thread\n");
            return_value = EXIT_FAILURE;
        }
        if (status == EXIT_FAILURE) {
            fprintf(stderr, "Thread returned with failure\n");
            return_value = EXIT_FAILURE;
        }
    }

    free(threads);
    return return_value;
}
