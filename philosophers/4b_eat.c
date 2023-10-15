/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4b_eat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 12:23:42 by sgluck            #+#    #+#             */
/*   Updated: 2023/08/10 12:25:12 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//It might be functional, but I don't like it. 
//In my opinion, lonely_philo should be handled seperately,
//mainly because of the logging as there might be double logging
void lonely_philo(t_philo *philo)
{
	long long time_of_death;

	pthread_mutex_lock(philo->right_fork);
	log_action(philo, "has taken a fork");
	time_of_death = philo->data->start_routine + philo->data->time_to_die;
	while (time_now() < time_of_death)
		usleep(10000);
	pthread_mutex_unlock(philo->right_fork);
	log_action(philo, "has died");
	shut_down(philo->data);
}

int	pick_up_forks(t_philo *philo)
{
	if (philo->data->philo_nr == 1)
	{
		lonely_philo(philo);
		return (0);
	}
	pthread_mutex_lock(philo->left_fork);
	log_action(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	log_action(philo, "has taken a fork");
	return (1);
}

void	put_forks_down(t_philo *philo)
{
	//error-notes
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_t *mutex_ptr;

	mutex_ptr = &philo->eat_count_mtx;
	//if there is only one philo => starve and die; location note
	if (!pick_up_forks(philo))
		return ;
	//does this need a mutex?
	philo->last_eat = time_now();
	log_action(philo, "is eating");
	optimized_sleep(philo->data->time_to_eat);
	put_forks_down(philo);
	if (philo->data->max_eats >= 0)
	{
		pthread_mutex_lock(mutex_ptr);
		philo->eat_count += 1;
		pthread_mutex_unlock(mutex_ptr);
	}
	return ;
}
