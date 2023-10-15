/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4c_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 12:25:23 by sgluck            #+#    #+#             */
/*   Updated: 2023/10/15 08:18:57 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// this function will return the current time in ms
long long	time_now(void)
{
	t_timeval	now;
	long long	now_ms;

	gettimeofday(&now, NULL);
	now_ms = ((long long)now.tv_sec * 1000) + (now.tv_usec / 1000);
	return (now_ms);
}

void	philo_sleep(t_philo *philo)
{
	log_action(philo, "sleeping");
	optimized_sleep(philo->data->time_to_sleep);
}

void	optimized_sleep(int to_sleep)
{
	long long	start_time;

	start_time = time_now();
	while ((time_now() - start_time) < to_sleep)
		usleep(500);
}
