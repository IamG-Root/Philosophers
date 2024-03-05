/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 10:01:48 by scastagn          #+#    #+#             */
/*   Updated: 2023/03/29 10:06:47 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_rules *general)
{
	int	i;

	i = 0;
	while (i < general->n_philo)
	{
		if (pthread_create(&general->philos[i].act, NULL,
				&routine, &general->philos[i]))
			return (printf("Error while creating the thread\n"));
		ft_usleep(1);
		i++;
	}
	return (0);
}

int	join_threads(t_rules *general)
{
	int	i;

	i = 0;
	while (i < general->n_philo)
	{
		if (pthread_join(general->philos[i].act, NULL))
			return (printf("Error while joining the thread\n"));
		i++;
	}
	return (0);
}

int	run_simulation(t_rules *general)
{
	int			i;
	pthread_t	meals_checker;

	i = 0;
	general->start_time = get_time();
	if (general->meals > 0)
	{
		if (pthread_create(&meals_checker, NULL, &check_meals, general))
			return (printf("Error while creating the thread\n"));
	}
	if (create_threads(general))
		return (1);
	if (join_threads(general))
		return (1);
	if (general->meals > 0)
	{
		if (pthread_join(meals_checker, NULL))
			return (printf("Error while joining the thread\n"));
	}
	return (0);
}
