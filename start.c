/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 10:01:55 by scastagn          #+#    #+#             */
/*   Updated: 2023/03/29 10:26:36 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_values(t_rules *general)
{
	int	i;

	i = 0;
	while (i < general->n_philo)
	{
		general->philos[i].eating = 0;
		general->philos[i].mymeals = 0;
		general->philos[i].index = i + 1;
		general->philos[i].general = general;
		pthread_mutex_init(&general->philos[i].write, NULL);
		i++;
	}
	general->dead = 0;
	general->finished = 0;
	return ;
}

int	assign_forks(t_rules *general)
{
	int	i;

	i = -1;
	while (++i < general->n_philo)
		pthread_mutex_init(&general->forks[i], NULL);
	i = 0;
	general->philos[0].rfrk = &general->forks[i];
	general->philos[0].lfrk = &general->forks[general->n_philo - 1];
	i = 1;
	while (i < general->n_philo)
	{
		general->philos[i].rfrk = &general->forks[i];
		general->philos[i].lfrk = &general->forks[i - 1];
		i++;
	}
	return (0);
}

int	init_philos(t_rules *general)
{
	general->philos = malloc (sizeof(t_philo) * general->n_philo);
	if (!general->philos)
		return (printf("Allocation error\n"));
	general->forks = malloc (sizeof(pthread_mutex_t) * general->n_philo);
	if (!general->forks)
		return (printf("Allocation error\n"));
	if (assign_forks(general))
		return (printf("Error while assigning forks\n"));
	set_values(general);
	return (0);
}

int	initializer(t_rules *general, char **argv)
{
	general->n_philo = (int) ft_atoi(argv[0]);
	general->death_time = (u_int64_t) ft_atoi(argv[1]);
	general->eat_time = (u_int64_t) ft_atoi(argv[2]);
	general->sleep_time = (u_int64_t) ft_atoi(argv[3]);
	if (argv[4])
		general->meals = (int) ft_atoi(argv[4]);
	if (general->n_philo < 1 || general->n_philo > 200
		|| general->death_time < 1 || general->eat_time < 1
		|| general->sleep_time < 1)
		return (1);
	if (argv[4] && general->meals < 1)
		return (1);
	pthread_mutex_init(&general->lock, NULL);
	return (0);
}

int	check_input(char **argv)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (argv[i])
	{
		while (argv[i][j])
		{
			while (argv[i][j] == ' ')
				j++;
			if (argv[i][j] < 48 || argv[i][j] > 57)
				return (1);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}
