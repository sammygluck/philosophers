/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_init_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 12:01:38 by sgluck            #+#    #+#             */
/*   Updated: 2023/10/17 11:48:45 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_mutexes_failure(t_data *data, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		pthread_mutex_destroy(&data->fork_mutexes[j]);
		j++;
	}
	free (data->fork_mutexes);
	return (0);
}

int	init_mutexes(t_data *data)
{
	int	i;

	data->fork_mutexes = malloc(sizeof(pthread_mutex_t) * data->philo_nr);
	if (!data->fork_mutexes)
	{
		printf("malloc failure mutex array\n");
		return (0);
	}
	i = 0;
	while (i < data->philo_nr)
	{
		if (pthread_mutex_init(&data->fork_mutexes[i], NULL))
			return (init_mutexes_failure(data, i));
		i++;
	}
	return (1);
}

static int	set_data(t_data *data, int argc, char **argv)
{
	data->philo_nr = ft_atoi(argv[1]);
	if (data->philo_nr <= 0)
		exit(EXIT_FAILURE);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->max_eats = ft_atoi(argv[5]);
	else
		data->max_eats = -1;
	data->all_alive = 1;
	data->start_routine = time_now();
	if (pthread_mutex_init(&data->log_mutex, NULL))
		return (set_data_failure(data, 0));
	if (pthread_mutex_init(&data->alive_mutex, NULL))
		return (set_data_failure(data, 1));
	if (!init_mutexes(data))
		return (set_data_failure(data, 2));
	return (1);
}

static int	validate_cmd(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
		return (0);
	i = 1;
	while (i < argc)
		if (!is_str_all_digit(argv[i++]))
			return (0);
	return (1);
}

int	init_data(t_data *data, int argc, char **argv)
{
	if (!validate_cmd(argc, argv))
	{
		printf("validate command args error\n");
		return (0);
	}
	if (!set_data(data, argc, argv))
		return (0);
	return (1);
}
