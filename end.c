/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 10:01:15 by scastagn          #+#    #+#             */
/*   Updated: 2023/03/29 10:04:19 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_killer(t_rules *general)
{
	int	i;

	i = 0;
	while (i < general->n_philo)
	{
		pthread_mutex_destroy(&general->forks[i]);
		pthread_mutex_destroy(&general->philos[i].write);
		i++;
	}
	pthread_mutex_destroy(&general->lock);
	free(general->philos);
	free(general->forks);
	return ;
}
