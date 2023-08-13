/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_philo_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 12:20:24 by sgluck            #+#    #+#             */
/*   Updated: 2023/08/10 13:15:08 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	log_action(t_philo *philo, char *str)
{
	pthread_mutex_t	mutex;

	mutex = philo->data->log_mutex;
	pthread_mutex_lock(mutex);
	//note
	printf("%llu %i %s\n", time_now(), philo->id, str);
	pthread_mutex_unlock(mutex);
}

void	*think_eat_sleep(void *arg)
{
	t_philo	*philo;
    int i;

	philo = (t_philo *) arg;
	//add the even/uneven division (if even pick move otherwise sleep)
	//create a variable holding the all_alive data and initially read by using a mutex
	
	//A. As long as all alive && the max eating times hasn't been reached
    i = 0;
	
    while (philo->data->all_alive)
   { 
        philo_think(philo);
        philo_eat(philo);
        philo_sleep(philo);
        i++;
    }
    return (NULL);
}

void	run_philos(t_philo ***philosophers, t_data *data)
{
	t_philo	**philos;
	int		i;
    pthread_t monitor_tid;

	i = 0;
	philos = *philosophers;
	while (i < data->philo_nr)
	{
		//create thread for each philo
		pthread_create(&philos[i]->tid, NULL, think_eat_sleep, philos[i]);
		i++;
	}
    pthread_create(&monitor_tid, NULL, monitor, philosophers);
	i = 0;
	while (i < data->philo_nr)
	{
		pthread_join(philos[i]->tid, NULL);
	i++;
	}
    pthread_join(monitor_tid, NULL);
}
