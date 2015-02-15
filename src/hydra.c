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

struct shutdown_controller{
    uint8_t shutdown_service;
    uint8_t shutdown_reaper;
};

typedef struct hydra_controller_thread{
    pthread_t service_thread, reaper_thread;
    struct shutdown_controller shutdown;
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


static void *hydra_service_thread(void *flag){
    struct shutdown_controller *shutdown = (struct shutdown_controller *)flag;
    while (0 == shutdown->shutdown_service){
      //TODO: Service functionality implementation
    }
    shutdown->shutdown_reaper = 1;
    printf("hydra_service_thread shutdown\n");

    return NULL;
}

static void *hydra_reaper_thread(void *flag){
    struct shutdown_controller *shutdown = (struct shutdown_controller *)flag;
    while (0 == shutdown->shutdown_reaper){
      //TODO: Reaper functionality implementation
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
    ret = pthread_create(&(context->reaper_thread), NULL, hydra_reaper_thread, &(context->shutdown));
    if (0 != ret){
      //TODO:Log here
      goto controll_thred_failed;
    }

    //Creating service thread
    ret = pthread_create(&(context->service_thread), NULL, hydra_service_thread, &(context->shutdown));
    if (0 != ret){
      context->shutdown.shutdown_service = 1;
      context->shutdown.shutdown_reaper = 0;
      //TODO:Log here
      goto controll_thred_failed;
    }

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
    
    context->shutdown.shutdown_service = 0;
    ret = create_controll_threads(context);
    if (ret != HYDRA_SUCCESS){
        //TODO:Log here
        return ret;
    }
    return HYDRA_SUCCESS;
}

HYDRA_RET hydra_destroy(){
    //TODO: stop service and reaper thread
}
