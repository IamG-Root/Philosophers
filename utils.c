/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 10:02:03 by scastagn          #+#    #+#             */
/*   Updated: 2023/03/29 10:08:29 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

u_int64_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (printf("gettimeofday() FAILURE\n"));
	return ((time.tv_sec * (u_int64_t)1000) + (time.tv_usec / 1000));
}

void	ft_usleep(u_int64_t time)
{
	u_int64_t	start_count;

	start_count = get_time();
	while (get_time() - start_count < time)
		usleep(time / 10);
	return ;
}

int	ft_atoi(char *s)
{
	int					sign;
	int					i;
	unsigned long int	result;

	sign = 1;
	result = 0;
	i = 0;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == 32)
		i++;
	if (s[i] == '-')
			sign = -1;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i])
	{
		result = (result * 10) + (s[i] - 48);
		i++;
	}
	if ((result > 2147483648 && sign == -1)
		|| (result > 2147483647 && sign == 1))
		return (-1);
	return (result * sign);
}
