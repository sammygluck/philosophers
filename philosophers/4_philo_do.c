#include "philosophers.h"

void *print_id(void *arg)
{
    int id;
    t_philo *philo;

    philo = (t_philo *) arg;
    id = philo->id;
    //note
    printf("this is my id %i", id);
    return (NULL);
}

void run_philos(t_philo ***philosophers, t_data *data)
{
    t_philo **philos;
    int i;

    i = 0;
    philos = *philosophers;
    while (i < data->philo_nr)
    {
        //create thread for each philo
        pthread_create(&philos[i]->tid, NULL, print_id, philos[i]);
        i++;
    }
}