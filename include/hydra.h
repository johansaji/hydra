#ifndef HYDRA_H
#define HYDRA_H

#include "types.h"

#define MAX_WORKER_COUNT 10

typedef void *(*hydra_routine) (void *);

typedef enum {
    HYDAR_HIGH = 0,
    HYDAR_MEDIUM,
    HYDAR_LOW
} hydra_priority;

typedef enum {
    HYDRA_SUCCESS = 0,  /* Sucess */
    HYDRA_FAILED,       /* Unknown Failure */
    HYDRA_MAX_THREAD,   /* Max number of worker thread reached */
    HYDRA_OOM           /* Out Of Memory */
    }HYDRA_RET;

HYDRA_RET hydra_init(uint8_t );

#endif
