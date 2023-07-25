#include "philosophers.h"

static void free_philos(t_philo **philos, int i)
{
    int j;

    j = 0;
    while (j < i)
    {
        if (philos[j])
            free(philos[j]);
        j++;
    }
    free(philos);
    //error note
    exit(EXIT_FAILURE);
}

static int create_philo(t_philo **philos, t_data data, int i)
{
    t_philo *philo;

    philo = malloc(sizeof(t_philo));
    if (!philo)
        return (0);
    //these are just the a few of more
    philo->id = i;
    philo->eat_count = 0;
    philos[i] = philo;
    return (1);
    
}

void init_philos(t_philo **philosophers, t_data data)
{
    t_philo **philos;
    int i;

    philos = philosophers;
    philos = malloc(data.philo_nr * sizeof(t_philo *));
    //error note
    if (!philos)
        exit(1);
    i = 0;
    while (i < data.philo_nr)
    {
        if (!create_philo(philos, data, i))
            free_philos(philos, i);
        i++;
    }

}
