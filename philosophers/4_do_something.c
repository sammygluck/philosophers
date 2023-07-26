#include "philosophers.h"

static void *thread_function(void *arg)
{
    printf("hello\n");
}

static void *second_function(void *arg)
{
    printf("world\n");
}

void dual_thread(t_philo *philo)
{
    //one thread that will block a resource for a few seconds
    pthread_t id_one;
    pthread_t id_two;
    //pthread_mutex_t mutex_one;
    pthread_create(&id_one, NULL, thread_function, NULL);
    pthread_create(&id_two, NULL, second_function, NULL);
    pthread_join(&id_one, NULL);
    pthread_join(&id_two, NULL);
    //another thread of something trying to reach that resource
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