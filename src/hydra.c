#include <stdio.h>
#include <pthread.h>


#include "hydra.h"
#include "types.h"

typedef enum {
    HYDRA_NOT_STARTED = 0,
    HYDRA_STARTED,
    HYDRA_RUNNING,
    HYDRA_STOPPING,
    HYDRA_STOPPED,
    HYDRA_REMOVED
} hydra_state;

/*
 * Contextual information for each task
 */
typedef struct hydra_task{
    hydra_state state;
    hydra_priority priority;
    hydra_routine routine;
    void *routine_args;
} hydra_task_t;

typedef struct hydra_tasks{
    hydra_task_t *task;
    struct hydra_task *next_task;
} hydra_tasks_t;

/*
 * Contextual information for master and reaper thread
 */
typedef struct hydra_controller_thread{
    pthread_t master_thred, reaper_thread;
    uint8_t shutdown;
    hydra_tasks_t *high_priority, *medium_priority, *low_priority;
    int live_thread_count = 0;
    pthread_mutex_t lock;
    pthread_cond_t condition;
}hydra_controller_thread_t;


typedef struct hydra_worker_thread{
    uint8_t id;
    pthread_t thread_id;
    hydra_task_t *task;
} hydra_worker_thread_t;


static void *hydra_master_thread(void *data){
    return NULL;
}

static void *hydra_reaper_thread(void *data){
    return NULL;
}

static HYDRA_RET create_task_queue(){
    
}

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
        return HYDRA_MAX_THREAD;
    }
    hydra_task_t test;    
    return HYDRA_SUCCESS;
}
