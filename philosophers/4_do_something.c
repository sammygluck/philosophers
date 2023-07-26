#include "philosophers.h"

static void *thread_function(void *mutex_arg)
{
    int i;

    i = 0;
    while (i < 10)
    {
        pthread_mutex_t *mutex = (pthread_mutex_t *) mutex_arg;
        pthread_mutex_lock(mutex);
        printf("hello world: %i\n", i);
        i++;
        pthread_mutex_unlock(mutex);
       
    }
   

    return (NULL);
}

static void *second_function(void *mutex_arg)
{
    pthread_mutex_t *mutex = (pthread_mutex_t *) mutex_arg;
    while (1)
    {
        pthread_mutex_lock(mutex);
        printf("thread is running.....\n");
        sleep(5);
        pthread_mutex_unlock(mutex);
    }
    return (NULL);
}

void dual_thread(void)
{
    //one thread that will block a resource for a few seconds
    pthread_t id_one;
    pthread_t id_two;
    pthread_mutex_t mutex_one;

    pthread_mutex_init(&mutex_one, NULL);
    pthread_create(&id_one, NULL, thread_function, &mutex_one);
    pthread_create(&id_two, NULL, second_function, &mutex_one);
    pthread_join(id_one, NULL);
    pthread_cancel(id_two);
    pthread_join(id_two, NULL);
    //another thread of something trying to reach that resource
    pthread_mutex_destroy(&mutex_one);
}

/*
gitlens
better comments
prettier
peacock
live server
vscode pets
bookmarks
*/