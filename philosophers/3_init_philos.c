/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_init_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 12:11:45 by sgluck            #+#    #+#             */
/*   Updated: 2023/08/10 12:16:54 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	set_philo_mutex(t_philo ***philosophers, t_data *data)
{
	t_philo	**philos;
	int		i;

	philos = *philosophers;
	i = 0;
	while (i < data->philo_nr - 1)
	{
		philos[i]->left_fork = &data->fork_mutexes[i];
		//error check if ! (???what did I mean, maybe lonely philo?)
		philos[i]->right_fork = &data->fork_mutexes[(i + 1) % data->philo_nr];
		i++;
	}
	if (i == data->philo_nr - 1)
	{
		philos[i]->left_fork = &data->fork_mutexes[(i + 1) % data->philo_nr];
		philos[i]->right_fork = &data->fork_mutexes[i];	
	}
}

static void	free_philos_and_exit(t_data *data, t_philo **philos, int i)
{
	int	j;

	j = 0;
	destroy_mutexes(data);
	while (j < i)
	{
		if (philos[j])
		{
			pthread_mutex_destroy(&philos[j]->last_meal_mtx);
			pthread_mutex_destroy(&philos[j]->eat_count_mtx);
			free(philos[j]);
		}
		j++;
	}
	free(philos);
	printf("couldn't malloc philo_array individuals\n");
	exit(EXIT_FAILURE);
}

static int	create_philo(t_philo ***philos, t_data *data, int i)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (0);
	philo->id = i + 1;
	philo->eat_count = 0;
	philo->last_eat = 0;
	philo->data = data;
	//error note
	pthread_mutex_init(&philo->last_meal_mtx, NULL);
	//error note
	pthread_mutex_init(&philo->eat_count_mtx, NULL);
	(*philos)[i] = philo;
	return (1);
}

void	init_philos(t_philo ***philos, t_data *data)
{
	int	i;

	*philos = malloc(data->philo_nr * sizeof(t_philo *));
	if (!*philos)
	{
		destroy_mutexes(data);
		printf("couldn't malloc philo_array\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < data->philo_nr)
	{
		//error note, also free mutexes, print error
		if (!create_philo(philos, data, i))
			free_philos_and_exit(data, *philos, i);	
		i++;
	}
	set_philo_mutex(philos, data);
}
