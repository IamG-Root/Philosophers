/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 10:00:53 by scastagn          #+#    #+#             */
/*   Updated: 2023/03/29 10:10:23 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_rules	general;

	if (argc != 5 && argc != 6)
		return (printf("Too few or too many arguments!\n"));
	argv++;
	if (check_input(argv))
		return (printf("Input arguments must be positive numbers\n"));
	if (initializer(&general, argv))
		return (printf("Invalid input arguments\n"));
	if (general.n_philo == 1)
		return (one_philo(&general));
	if (init_philos(&general))
		return (0);
	if (run_simulation(&general))
		return (0);
	philo_killer(&general);
	return (0);
}
