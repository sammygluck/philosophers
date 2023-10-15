/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_init_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 12:01:38 by sgluck            #+#    #+#             */
/*   Updated: 2023/10/15 15:34:10 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_mutexes(t_data *data)
{
	int	i;

	data->fork_mutexes = malloc(sizeof(pthread_mutex_t) * data->philo_nr);
	//error-note
	if (!data->fork_mutexes)
	{
		printf("malloc failure mutex array\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < data->philo_nr)
	{
		//error-note
		//data->fork_mutexes[i] = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(&data->fork_mutexes[i], NULL);
		i++;
	}	
}

static void	set_data(t_data *data, int argc, char **argv)
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
	//error notes return non-0 upon failure to be handled in parent
	pthread_mutex_init(&data->log_mutex, NULL);
	pthread_mutex_init(&data->alive_mutex, NULL);
	//error note
	init_mutexes(data);
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

void	init_data(t_data *data, int argc, char **argv)
{
	//error note + nothing malloced yet, just print message 
	if (!validate_cmd(argc, argv))
	{
		printf("validate command args error\n");
		exit(EXIT_FAILURE);
	}
	//error note here for pthread_mutex_init failure
	set_data(data, argc, argv);

}
