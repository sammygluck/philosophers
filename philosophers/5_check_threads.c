#include "philosophers.h"

int check_each_philo(t_philo **philos)
{
    int i;
    time max_gap;

    max_gap = (time)(philos[0]->data->time_to_die);
    i = 0;
    while (i < philos[0]->data->philo_nr)
    {
        if (!philos[i]->last_eat)
        {
            if ((time_now(void) - philos[i]->start_routine) > max_gap)
                return (0);
        }
        else if (philos[i]->last_eat > 0)
        {
            if((time_now(void) - philos[i]->last_eat) > max_gap)
            return (0);
        }
        else 
            return (0);

        i++;
    }
    return (1);
}

void *monitor(void ***philosophers)
{
    t_philo **philos;

    philos = *philosophers;
    while (1)
    {
        usleep(100000);
        if (!check_each_philo(philos))
            break;
    }

}