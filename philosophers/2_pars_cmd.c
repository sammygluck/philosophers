#include "philosophers.h"

void init_data(t_data *data, int argc, char **argv)
{
    data->philo_nr = argv[1];
    data->time_to_die = argv[2];
    data->time_to_eat = argv[3];
    data->time_to_sleep = argv[4];
    if (argc == 5)
        data->max_eats = argv[5];
    else
        data->max_eats = 0;
}