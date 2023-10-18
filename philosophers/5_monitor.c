/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_monitor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 12:27:21 by sgluck            #+#    #+#             */
/*   Updated: 2023/10/17 11:37:40 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	all_eaten(t_philo **philos)
{
	int	i;
	int	eat_count;

	i = 0;
	while (i < philos[0]->data->philo_nr)
	{
		pthread_mutex_lock(&philos[i]->eat_count_mtx);
		eat_count = philos[i]->eat_count;
		pthread_mutex_unlock(&philos[i]->eat_count_mtx);
		if (eat_count < philos[i]->data->max_eats)
			return (0);
		i++;
	}
	return (1);
}

int	check_if_died(t_philo *philos)
{
	long long	max_gap;
	long long	time_to_sub;

	pthread_mutex_lock(&philos->last_meal_mtx);
	time_to_sub = philos->last_eat;
	pthread_mutex_unlock(&philos->last_meal_mtx);
	max_gap = (long long)(philos->data->time_to_die);
	if (time_now() - time_to_sub > max_gap)
	{
		log_action(philos, "has died");
		shut_down(philos->data);
		return (0);
	}
	return (1);
}

int	check_philos_status(t_philo **philos)
{
	int			i;

	i = 0;
	while (i < philos[0]->data->philo_nr)
	{
		if (!check_if_died(philos[i]))
			return (0);
		i++;
	}
	if (philos[0]->data->max_eats >= 0)
	{
		if (all_eaten(philos))
		{
			shut_down(philos[0]->data);
			return (0);
		}
	}
	return (1);
}

void	monitor(t_philo ***philosophers)
{
	t_philo	**philos;

	philos = *philosophers;
	while (1)
	{
		if (!check_philos_status(philos))
			break ;
	}
	return ;
}
