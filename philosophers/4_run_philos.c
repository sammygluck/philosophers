/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_run_philos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 12:20:24 by sgluck            #+#    #+#             */
/*   Updated: 2023/10/17 11:40:30 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	log_action(t_philo *philo, char *str)
{
	pthread_mutex_t	*mutex_ptr;
	long long		relative_time;
	int				all_alive;

	pthread_mutex_lock(&philo->data->alive_mutex);
	all_alive = philo->data->all_alive;
	pthread_mutex_unlock(&philo->data->alive_mutex);
	if (all_alive == 0)
		return ;
	relative_time = time_now() - philo->data->start_routine;
	mutex_ptr = &philo->data->log_mutex;
	pthread_mutex_lock(mutex_ptr);
	printf("%llu %i %s\n", relative_time, philo->id, str);
	pthread_mutex_unlock(mutex_ptr);
}

void	*think_eat_sleep(void *arg)
{
	t_philo	*philo;
	int		all_alive;

	philo = (t_philo *) arg;
	if (philo->id % 2 == 0)
		optimized_sleep((philo->data->time_to_eat / 2));
	while (1)
	{
		pthread_mutex_lock(&philo->data->alive_mutex);
		all_alive = philo->data->all_alive;
		pthread_mutex_unlock(&philo->data->alive_mutex);
		if (!all_alive)
			break ;
		log_action(philo, "is thinking");
		philo_eat(philo);
		philo_sleep(philo);
	}
	return (NULL);
}

void	run_philos(t_philo ***philosophers, t_data *data)
{
	t_philo	**philos;
	int		i;

	i = 0;
	philos = *philosophers;
	while (i < data->philo_nr)
	{
		if (pthread_create(&philos[i]->tid, NULL, think_eat_sleep, philos[i]))
		{
			shut_down(data);
			while (i > 0)
				pthread_join(philos[--i]->tid, NULL);
			free_stuff(data, philos);
			printf("pthread_create routine failure\n");
			exit(EXIT_FAILURE);
		}
		//destroy all mutexes ??besides for the forks??
		i++;
	}
	monitor(philosophers);
	i = 0;
	while (i < data->philo_nr)
	{
		pthread_join(philos[i]->tid, NULL);
		i++;
	}
}
