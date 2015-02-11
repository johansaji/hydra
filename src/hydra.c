#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


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
    pthread_t service_thread, reaper_thread;
    uint8_t shutdown;
    hydra_tasks_t *high_priority, *medium_priority, *low_priority;
    uint8_t live_thread_count;
    pthread_mutex_t lock;
    pthread_cond_t notify;
}hydra_controller_thread_t;


typedef struct hydra_worker_thread{
    uint8_t id;
    pthread_t thread_id;
    hydra_task_t *task;
} hydra_worker_thread_t;


static void *hydra_service_thread(void *data){
    while (1){
      printf("hydra_service_thread\n");
      sleep (10);
    }
    return NULL;
}

static void *hydra_reaper_thread(void *data){
    while (1){
      printf("hydra_reaper_thread\n");
      sleep (10);
    }
    return NULL;
}

static HYDRA_RET create_controll_threads(hydra_controller_thread_t *context){
    int ret = ~0;
    ret = pthread_mutex_init(&(context->lock), NULL);
    if (0 != ret){
      //TODO:Log here
      goto lock_failed; 
    }

    ret = pthread_cond_init(&(context->notify), NULL);
    if (0 != ret){
      //TODO:Log here
      goto cond_failed;
    }

    //Creating reaper thread
    printf("reaper\n");
    ret = pthread_create(&(context->reaper_thread), NULL, hydra_reaper_thread, NULL);
    if (0 != ret){
      //TODO:Log here
      goto controll_thred_failed;
    }
    printf("reaper\n");

    //Creating service thread
    printf("service\n");
    ret = pthread_create(&(context->service_thread), NULL, hydra_service_thread, NULL);
    if (0 != ret){
      context->shutdown = 1;
      //TODO:Log here
      goto controll_thred_failed;
    }
    printf("service\n");

    return HYDRA_SUCCESS;

controll_thred_failed:
    pthread_cond_destroy(&(context->notify));
cond_failed:
    pthread_mutex_destroy(&(context->lock));
lock_failed:
    return HYDRA_FAILED; 
    
}

static hydra_controller_thread_t *context = NULL;

/*
 *  Function : hydra_init
 *  Args     : 
 *             worker_count :- Max number of worker thread allowed
 *  Return   :
 *             HYDRA_SUCCESS :- Sucessfully initialised the library
 *             HYDRA_FAILED  :- Error occured while initialization
 */

HYDRA_RET hydra_init(uint8_t worker_count){
    HYDRA_RET ret = HYDRA_FAILED;
    if (MAX_WORKER_COUNT < worker_count){
        //TODO:Log here
        return HYDRA_MAX_THREAD;
    }

    context = (hydra_controller_thread_t *)malloc(sizeof(hydra_controller_thread_t));
    if (NULL == context){
        //TODO:Log here
        return HYDRA_OOM;
    }
    memset(context, 0, sizeof(hydra_controller_thread_t));
    
    context->shutdown = 0;
    ret = create_controll_threads(context);
    if (ret != HYDRA_SUCCESS){
        //TODO:Log here
        return ret;
    }

    return HYDRA_SUCCESS;
}
