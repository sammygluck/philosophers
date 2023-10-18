/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_errors.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:44:08 by sgluck            #+#    #+#             */
/*   Updated: 2023/10/17 11:46:02 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_mutexes(t_data *data)
{
	int	philo_nr;
	int	i;

	philo_nr = data->philo_nr;
	i = 0;
	while (i < philo_nr)
	{
		pthread_mutex_destroy(&data->fork_mutexes[i]);
		i++;
	}
	free(data->fork_mutexes);
	pthread_mutex_destroy(&data->log_mutex);
	pthread_mutex_destroy(&data->alive_mutex);
}

void	free_philos(t_data *data, t_philo **philosophers)
{
	int	philo_nr;
	int	i;

	philo_nr = data->philo_nr;
	i = 0;
	while (i < philo_nr)
	{
		pthread_mutex_destroy(&philosophers[i]->last_meal_mtx);
		pthread_mutex_destroy(&philosophers[i]->eat_count_mtx);
		free(philosophers[i]);
		i++;
	}
}

void	free_stuff(t_data *data, t_philo **philosophers)
{
	destroy_mutexes(data);
	free_philos(data, philosophers);
	free(philosophers);
}

void	shut_down(t_data *data)
{
	pthread_mutex_lock(&data->alive_mutex);
	data->all_alive = 0;
	pthread_mutex_unlock(&data->alive_mutex);
}
