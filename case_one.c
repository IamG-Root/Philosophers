/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 10:54:43 by scastagn          #+#    #+#             */
/*   Updated: 2023/03/29 10:56:45 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*life(void *general)
{
	t_rules	*general_ptr;

	general_ptr = (t_rules *)general;
	while (!general_ptr->dead)
	{
		if (get_time() >= general_ptr->start_time + general_ptr->death_time)
		{
			general_ptr->dead = 1;
			printf("%llu %d is dead\n", get_time()
				- general_ptr->start_time, 1);
		}
	}
	return ((void *)0);
}

int	one_philo(t_rules *general)
{
	general->philos = malloc (sizeof(t_philo) * 1);
	general->forks = malloc (sizeof(pthread_mutex_t) * 1);
	general->dead = 0;
	pthread_mutex_init(&general->forks[0], NULL);
	general->start_time = get_time();
	printf("%llu %d has taken a fork\n",
		get_time() - general->start_time, 1);
	if (pthread_create(&general->philos[0].act, NULL, &life, (void *)general))
		return (printf("Error while creating the thread\n"));
	if (pthread_join(general->philos[0].act, NULL))
		return (printf("Error while joining the thread\n"));
	philo_killer(general);
	return (0);
}
