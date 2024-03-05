/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 10:01:28 by scastagn          #+#    #+#             */
/*   Updated: 2023/03/29 10:21:11 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	manage_forks(t_philo *philo, char action)
{
	if (action == 't')
	{
		pthread_mutex_lock(philo->lfrk);
		pthread_mutex_lock(&philo->general->lock);
		if (philo->general->dead == 0)
			printf("%llu %d has taken a fork\n",
				get_time() - philo->general->start_time, philo->index);
		pthread_mutex_unlock(&philo->general->lock);
		pthread_mutex_lock(philo->rfrk);
		pthread_mutex_lock(&philo->general->lock);
		if (philo->general->dead == 0)
			printf("%llu %d has taken a fork\n",
				get_time() - philo->general->start_time, philo->index);
		pthread_mutex_unlock(&philo->general->lock);
	}
	else if (action == 'd')
	{
		pthread_mutex_unlock(philo->lfrk);
		pthread_mutex_unlock(philo->rfrk);
	}
	return ;
}

void	philos_eat(t_philo *philo)
{
	manage_forks(philo, 't');
	pthread_mutex_lock(&philo->write);
	philo->mydeath = get_time() + philo->general->death_time;
	philo->eating = 1;
	pthread_mutex_lock(&philo->general->lock);
	if (philo->general->dead == 0)
		printf("%llu %d is eating\n",
			get_time() - philo->general->start_time, philo->index);
	pthread_mutex_unlock(&philo->general->lock);
	philo->mymeals++;
	ft_usleep(philo->general->eat_time);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->write);
	manage_forks(philo, 'd');
	pthread_mutex_lock(&philo->general->lock);
	if (philo->general->dead == 0)
		printf("%llu %d is sleeping\n",
			get_time() - philo->general->start_time, philo->index);
	pthread_mutex_unlock(&philo->general->lock);
	ft_usleep(philo->general->sleep_time);
	return ;
}

void	*check_meals(void *general)
{
	t_rules	*general_ptr;

	general_ptr = (t_rules *)general;
	while (!general_ptr->dead)
	{
		pthread_mutex_lock(&general_ptr->lock);
		if (general_ptr->finished >= general_ptr->n_philo)
			general_ptr->dead = 1;
		pthread_mutex_unlock(&general_ptr->lock);
	}
	return ((void *)0);
}

void	*monitor(void *philo)
{
	t_philo	*philo_ptr;

	philo_ptr = (t_philo *)philo;
	while (!philo_ptr->general->dead)
	{
		pthread_mutex_lock(&philo_ptr->write);
		if (get_time() >= philo_ptr->mydeath && philo_ptr->eating == 0)
		{
			pthread_mutex_lock(&philo_ptr->general->lock);
			if (philo_ptr->general->dead == 0)
			{
				printf("%llu %d is dead\n", get_time()
					- philo_ptr->general->start_time, philo_ptr->index);
				philo_ptr->general->dead = 1;
			}
			pthread_mutex_unlock(&philo_ptr->general->lock);
		}
		if (philo_ptr->mymeals == philo_ptr->general->meals)
		{
			philo_ptr->general->finished++;
			philo_ptr->mymeals++;
		}
		pthread_mutex_unlock(&philo_ptr->write);
	}
	return ((void *)0);
}

void	*routine(void *philo)
{
	t_philo		*philo_ptr;
	u_int64_t	time;

	philo_ptr = (t_philo *)philo;
	philo_ptr->mydeath = philo_ptr->general->death_time + get_time();
	if (pthread_create(&philo_ptr->monitor, NULL, &monitor, philo))
		return ((void *)1);
	while (!philo_ptr->general->dead)
	{
		philos_eat(philo_ptr);
		time = get_time() - philo_ptr->general->start_time;
		if (!philo_ptr->general->dead)
		{
			pthread_mutex_lock(&philo_ptr->general->lock);
			printf("%llu %d is thinking\n", time, philo_ptr->index);
			pthread_mutex_unlock(&philo_ptr->general->lock);
		}
	}
	if (pthread_join(philo_ptr->monitor, NULL))
		return ((void *)1);
	return ((void *)0);
}
