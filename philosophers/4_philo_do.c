#include "philosophers.h"

void *test_function(void *arg)
{
    int id;
    t_philo *philo;

    philo = (t_philo *) arg;
    id = philo->id;
    pthread_mutex_lock(philo->data->log_mutex);
    //note
    printf("this is my id %i\n", id);
    pthread_mutex_unlock(philo->data->log_mutex);
    return (NULL);
}

void print_action(pthread_mutex_t *mutex, char *str)
{
    pthread_mutex_lock(mutex);
    //note
    printf("%s\n", str);
    pthread_mutex_unlock(mutex);
}

void *think_eat_sleep(void *arg)
{  
    t_philo *philo;
    
    philo = (t_philo *) arg;
    //A. As long as all alive && the max eating times hasn't been reached
    //1. Think
    //  a. print thinking unto the screen
    print_action(philo->data->log_mutex, "THINK");
    //2. Eat
    print_action(philo->data->log_mutex, "EAT");
    //3. Sleep
    print_action(philo->data->log_mutex, "SLEEP");
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
        pthread_create(&philos[i]->tid, NULL, think_eat_sleep, philos[i]); 
        i++;
    }
    i = 0;
    while (i < data->philo_nr)
    {
        pthread_join(philos[i]->tid, NULL);
        i++;
    }
}