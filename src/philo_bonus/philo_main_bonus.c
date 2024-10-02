/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnubia <rnubia@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 09:21:46 by rnubia            #+#    #+#             */
/*   Updated: 2022/07/11 03:02:52 by rnubia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include "philo_bonus.h"

static t_bool	ft_stoi(char *str, int *inbr)
{
	long long int	llnbr;
	int				sgn;

	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str ++;
	sgn = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sgn = -1;
		str ++;
	}
	if (*str == '\0')
		return (false);
	llnbr = 0;
	while (*str != '\0')
	{
		if (*str < '0' || *str > '9')
			return (false);
		llnbr = llnbr * 10 + ((long long int)(*(str ++) - '0')) * sgn;
		if (llnbr < INT_MIN || llnbr > INT_MAX)
			return (false);
	}
	*inbr = (int)llnbr;
	return (true);
}

static t_bool	check_args(int argc, char **argv, int *args)
{
	int	i;

	if (argc != ARGS_COUNT && argc != ARGS_COUNT + 1)
	{
		printf("Arguments: number_of_philosophers time_to_die time_to_eat ");
		printf("time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (false);
	}
	i = 1;
	while (i < argc)
	{
		if (ft_stoi(*(argv + i), &args[i - 1]) == false || args[i - 1] <= 0)
		{
			printf("Error: all arguments must be positive integers\n");
			return (false);
		}
		i ++;
	}
	return (true);
}

static t_bool	philos_origin(t_exist *exist, t_philo *philo)
{
	int	i;

	i = -1;
	gettimeofday(&exist->inception, NULL);
	while (++ i < exist->philo_count)
	{
		*(exist->pids + i) = fork();
		if (*(exist->pids + i) == -1)
		{
			philos_kill(exist, i - 1);
			existence_destroy(exist);
			return (false);
		}
		if (*(exist->pids + i) == 0)
		{
			philo->phid = i + 1;
			if (philo_cycle(exist, philo) == false)
			{
				philos_kill(exist, i - 1);
				existence_destroy(exist);
				exit(EXIT_FAILURE);
			}
		}
	}
	return (true);
}

static void	philos_wait(t_exist *exist)
{
	int	status;
	int	i;

	i = 0;
	while (i < exist->philo_count)
	{
		waitpid(*(exist->pids + i), &status, 0);
		i ++;
	}
}

int	main(int argc, char **argv)
{
	t_exist	exist;
	t_philo	philo;
	int		args[ARGS_COUNT];

	args[ARGS_COUNT - 1] = -1;
	if (check_args(argc, argv, args) == false)
		return (RETURN_FAILURE);
	if (existence_init(&exist, args) == false)
		return (RETURN_FAILURE);
	if (philos_origin(&exist, &philo) == false)
		return (RETURN_FAILURE);
	philos_wait(&exist);
	existence_destroy(&exist);
	return (RETURN_SUCCESS);
}
