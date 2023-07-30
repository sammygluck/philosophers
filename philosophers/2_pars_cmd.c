#include "philosophers.h"

static int validate_cmd(int argc, char **argv)
{
    int i;

    if (argc != 5 && argc != 6)
        return (0);
    i = 1;
    while (i < argc)
        if (!is_str_all_digit(argv[i++]))
            return (0);
    return (1);
}

static void set_data(t_data *data, int argc, char **argv)
{
    data->philo_nr = ft_atoi(argv[1]);
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        data->max_eats = ft_atoi(argv[5]);
    else
        data->max_eats = -1;
    //error note + location note
    data->log_mutex = malloc(sizeof(pthread_mutex_t));  // Allocate memory
    if (!data->log_mutex)
        // Handle allocation error
        exit(EXIT_FAILURE);
    pthread_mutex_init(data->log_mutex, NULL);
}

void init_data(t_data *data, int argc, char **argv)
{
    //error note
    if (!validate_cmd(argc, argv))
        exit(EXIT_FAILURE);
    set_data(data, argc, argv);
}
