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

int	check_each_philo(t_philo **philos)
{
	int			i;
	long long	max_gap;

	max_gap = (long long)(philos[0]->data->time_to_die);
	i = 0;
	while (i < philos[0]->data->philo_nr)
	{
		if (!philos[i]->last_eat)
		{
			if ((time_now() - philos[i]->start_routine) > max_gap)
				return (0);
		}
		else if (philos[i]->last_eat > 0)
		{
			if ((time_now() - philos[i]->last_eat) > max_gap)
				return (0);
		}
		else
			return (0);
		i++;
	}
	return (1);
}

void	*monitor(void *philosophers)
{
	t_philo	**philos;

	philos = *(t_philo ***)philosophers;

	while (1)
	{
        //checking each philo includes:
		// 		1. did all of them eat enough
		// 		2. did anyone die
		// if one of these conditions is yes, then we must stop our simulation
		// i.e. set the flag to 0 and exit everything gracefully     
		if (!check_each_philo(philos))
			break ;
	}
    //shut down operation
    philos[0]->data->all_alive = 0;
	return (NULL);
}
