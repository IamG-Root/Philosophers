/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 10:01:40 by scastagn          #+#    #+#             */
/*   Updated: 2023/03/29 11:01:46 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>

typedef struct s_philo
{
	struct s_rules	*general;
	pthread_t		act;
	pthread_t		monitor;
	pthread_mutex_t	*rfrk;
	pthread_mutex_t	*lfrk;
	pthread_mutex_t	write;
	u_int64_t		mydeath;
	int				mymeals;
	int				eating;
	int				index;
}	t_philo;

typedef struct s_rules
{
	int				n_philo;
	u_int64_t		start_time;
	u_int64_t		death_time;
	u_int64_t		eat_time;
	u_int64_t		sleep_time;
	int				meals;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	int				dead;
	int				finished;
}	t_rules;

/* --- start.c --- */
void		set_values(t_rules *general);
int			assign_forks(t_rules *general);
int			check_input(char **argv);
int			initializer(t_rules *general, char **argv);
int			init_philos(t_rules *general);
/* --- end.c --- */
void		philo_killer(t_rules *general);
/* --- utils.c --- */
u_int64_t	get_time(void);
void		ft_usleep(u_int64_t time);
int			ft_atoi(char *s);
/* --- simulation.c --- */
int			create_threads(t_rules *general);
int			join_threads(t_rules *general);
int			run_simulation(t_rules *general);
/* --- philo_actions.c --- */
void		manage_forks(t_philo *philo, char action);
void		philos_eat(t_philo *philo);
void		*check_meals(void *general);
void		*monitor(void *philo);
void		*routine(void *philo);
/* --- case_one.c --- */
void		*life(void *general);
int			one_philo(t_rules *general);
#endif
