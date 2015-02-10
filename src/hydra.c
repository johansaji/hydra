#include <stdio.h>
#include <pthread.h>


#include "hydra.h"

typedef enum {
    HYDRA_NOT_STARTED = 0,
    HYDRA_STARTED,
    HYDRA_RUNNING,
    HYDRA_STOPPING,
    HYDRA_STOPPED,
    HYDRA_REMOVED
    }hydra_state;

static live_thread_count = 0;

typedef struct hydra_thread_{
    uint8_t id;
    pthread_t thread_id;
    } hydra_threads;

struct hydra_task_{
    
    } hydra_task_t;

struct hydra

/*
 *  Function : hydra_init
 *  Args     : 
 *             worker_count :- Max number of worker thread allowed
 *  Return   :
 *             HYDRA_SUCCESS :- Sucessfully initialised the library
 *             HYDRA_FAILED  :- Error occured while initialization
 */
HYDRA_RET hydra_init(uint8_t worker_count){
    if (MAX_WORKER_COUNT > worker_count){
        return HYDRA_FAILED;
    }
    
    return HYDRA_SUCCESS;
}
