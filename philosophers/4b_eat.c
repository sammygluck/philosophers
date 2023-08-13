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

void lonely_philo(t_philo *philo)
{
	long long time_of_death;


	time_of_death = philo->data->start_routine + philo->data->time_to_die;
	while (time_now() < time_of_death)
		usleep(10000)
	pthread_mutex_unlock(philo->right_fork);
	log_action(philo, "has died");
	pthread_mutex_lock(&philo->data->alive_mutex);
	philo->data->all_alive = 0;
	pthread_mutex_unlock(&philo->data->alive_mutex);
}

void	pick_up_forks(t_philo *philo)
{
	if (philo->id == philo->data->philo_nr)
	{
		pthread_mutex_lock(philo->right_fork);
		log_action(philo, "has taken a fork");
		if (philo->data->philo_nr == 1)
		{
			lonenly_philo(philo);
			return ;
		}
		pthread_mutex_lock(philo->left_fork);
		log_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		log_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		log_action(philo, "has taken a fork");
	}
}

void	put_forks_down(t_philo *philo)
{
	//error-notes
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_t mutex;

	mutex = philo->eat_count_mtx;
	//if there is only one philo => starve and die; location note
	pick_up_forks(philo);
	//does this need a mutex?
	philo->last_eat = time_now();
	log_action(philo, "is eating");
	usleep(philo->data->time_to_eat * 1000);
	put_forks_down(philo);
	//mutex?
	if (philo->eat_count >= 0)
	{
		pthread_mutex_lock(&mutex);
		philo->eat_count += 1;
		pthread_mutex_unlock(&mutex);
	}
}
