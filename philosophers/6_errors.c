#include "philosophers.h"

/*
When thinking about errors, we have to realize that there are different potential type of errors in this code

The first point, we must consider:
Malloced memory. An error occuring during different stages of the program, must be considered differently regarding 
our malloced memory.
1. Before any malloced memory has occured, in this stage we just need to exit the program gracefully, perhaps also print an
appropriate message.
2. After having malloced some memory, but not all. There are two options:
    a. Create a generalized freeing function that can detect if our functions exists
    b. Or create an intermediary freeing function that will free all necessary pointers at this stage
3. After having malloced all the necessary memory for this code, we can have the full mature version of the freeing function

A second point to consider:
What is the error message we're going to give when the error occurs? i.e. how specific to the error is our error message going to be?

A third point:
When working with threads, we would like to make sure that all is joined when wrapping up our code

A fourth point:
Besides for memory failures, we also have the possibility of having failure in functions.
We must isolate these potential functions and deal with them appropriately.
*/


/*
Malloced stuff, chronological order

1. data->fork_mutexes
2. data->fork_mutexes[i]
3. **philos
4. philos[i]
*/

void destroy_mutexes(t_data *data)
{
    int philo_nr;
    int i;

    philo_nr = data->philo_nr;
    i = 0;
    while (i < philo_nr)
    {
        //error note
        pthread_mutex_destroy(&data->fork_mutexes[i]);
        //free(data->fork_mutexes[i]);
        i++;
    }
    free(data->fork_mutexes);
    pthread_mutex_destroy(&data->log_mutex);
    pthread_mutex_destroy(&data->alive_mutex);
}

void free_philos(t_data *data, t_philo **philosophers)
{
    int philo_nr;
    int i;

    philo_nr = data->philo_nr;
    i = 0;
    while (i < philo_nr)
    {
        pthread_mutex_destroy(&philosophers[i]->last_meal_mtx);
        pthread_mutex_destroy(&philosophers[i]->eat_count_mtx);
        free(philosophers[i]);
        i++;
    }

}

void free_stuff(t_data *data, t_philo **philosophers)
{
    destroy_mutexes(data);
    free_philos(data, philosophers);
    free(philosophers);
}

void shut_down(t_data *data)
{
    pthread_mutex_lock(&data->alive_mutex);
    data->all_alive = 0;
    pthread_mutex_unlock(&data->alive_mutex);
}