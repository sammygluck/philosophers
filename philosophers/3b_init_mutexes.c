#include "philosophers.h"

void init_mutexes(t_data *data)
{
    int i;
    //malloc the space for the mutexes array
    data->fork_mutexes = malloc(sizeof(pthread_mutex_t *) * data->philo_nr);
    //error-note
    if (!data->fork_mutexes)
        exit(EXIT_FAILURE);
    i = 0;
    while (i < data->philo_nr)
    {
        data->fork_mutexes[i] = malloc(sizeof(pthread_mutex_t));
        //error-note
        //if (!data->fork_mutexes[i])
        //error-note
        pthread_mutex_init(data->fork_mutexes[i], NULL);
        i++;
    }
}

void set_philo_mutex(t_philo ***philosophers, t_data *data)
{
    t_philo **philos;
    int i;

    //give each philosopher the right mutex for the fork
    philos = *philosophers;
    i = 0;
    while (i < data->philo_nr)
    {
        philos[i]->left_fork = data->fork_mutexes[i];
        //error check if !
        philos[i]->right_fork = data->fork_mutexes[(i + 1) % data->philo_nr];
        i++;
    }
}