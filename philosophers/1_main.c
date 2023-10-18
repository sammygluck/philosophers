/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 11:59:21 by sgluck            #+#    #+#             */
/*   Updated: 2023/08/10 12:01:21 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	**philosophers;

	philosophers = NULL;
	if (!init_data(&data, argc, argv))
		return (-1);
	if (!init_philos(&philosophers, &data))
		return (-1);
	run_philos(&philosophers, &data);
	free_stuff(&data, philosophers);
}