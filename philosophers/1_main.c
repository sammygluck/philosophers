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

//void	print_philos(t_philo **philosophers, int count);

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	**philosophers;

	philosophers = NULL;
	init_data(&data, argc, argv);
	init_philos(&philosophers, &data);
	run_philos(&philosophers, &data);
	//print_philos(philosophers, data.philo_nr);
	//free everything
}

//tmp
// void	print_philos(t_philo **philosophers, int count)
// {
// 	int	i;

// 	i = 0;
// 	while (i < count)
// 	{
// 		//note
// 		printf("%i\n", philosophers[i]->id);
// 		i++;
// 	}
// }
