/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_check_threads.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 12:27:21 by sgluck            #+#    #+#             */
/*   Updated: 2023/08/10 12:31:04 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int all_eaten(t_philo **philos)
{
	int i;
	int eat_count;

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
	long long	last_eat;

	pthread_mutex_lock(&philos->last_meal_mtx);
	last_eat = philos->last_eat;
	pthread_mutex_unlock(&philos->last_meal_mtx);
	max_gap = (long long)(philos->data->time_to_die);
	if (!last_eat)
		time_to_sub = philos->data->start_routine;
	else if (last_eat > 0)
		time_to_sub = last_eat;
	if (time_now() - time_to_sub > max_gap)
	{
		//conditional: only if there is more than one philo
		log_action(philos, "has died");
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
	if (all_eaten(philos))
		return (0);
	return (1);
}

void	*monitor(void *philosophers)
{
	t_philo	**philos;

	philos = *(t_philo ***)philosophers;

	while (1)
	{
		//add sleeping
		usleep(1000);
		if (!check_philos_status(philos))
			break ;
	}
    //shut down operation
	pthread_mutex_lock(&philos[0]->data->alive_mutex);
    philos[0]->data->all_alive = 0;
	pthread_mutex_unlock(&philos[0]->data->alive_mutex);
	//printing and exiting correctly
	return (NULL);
}
