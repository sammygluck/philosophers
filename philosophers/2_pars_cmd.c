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
        data->max_eats = 0;
}

void init_data(t_data *data, int argc, char **argv)
{
    if (!validate_cmd(argc, argv))
        printf("error");
    set_data(data, argc, argv);
}