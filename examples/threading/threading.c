#include "threading.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// Optional: use these functions to add debug or error prints to your application
#define DEBUG_LOG(msg,...)
//#define DEBUG_LOG(msg,...) printf("threading: " msg "\n" , ##__VA_ARGS__)
#define ERROR_LOG(msg,...) printf("threading ERROR: " msg "\n" , ##__VA_ARGS__)

void* threadfunc(void* thread_param)
{
    bool fail = false;
    int x;
    struct thread_data* t_data=(struct thread_data *)thread_param;
    usleep(t_data->wait_to_obtain_ms * 1000);
    x = pthread_mutex_lock(t_data->mutex);
    if (x != 0)
    {
        fail = true;
    }
    usleep(t_data->wait_to_release_ms * 1000);
    x = pthread_mutex_unlock(t_data->mutex);
    if (x != 0)
    {
        fail = true;
    }
    if(fail){
    t_data->thread_complete_success=false;
    }
        
    else{
    t_data->thread_complete_success=true;
    }
    return thread_param;
    // TODO: wait, obtain mutex, wait, release mutex as described by thread_data structure
}


bool start_thread_obtaining_mutex(pthread_t *thread, pthread_mutex_t *mutex,int wait_to_obtain_ms, int wait_to_release_ms)
{
    /**
     * TODO: allocate memory for thread_data, setup mutex and wait arguments, pass thread_data to created thread
     * using threadfunc() as entry point.
     *
     * return true if successful.
     *
     * See implementation details in threading.h file comment block
     */
    struct thread_data *t_data = (struct thread_data *)malloc(sizeof(struct thread_data *));
    t_data->mutex = mutex;
    t_data->wait_to_obtain_ms = wait_to_obtain_ms;
    t_data->wait_to_release_ms = wait_to_release_ms;
    if(pthread_create(thread, NULL, threadfunc, t_data)== 0){
    return true;
    }
    else return false;
}

