/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnubia <rnubia@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 11:53:14 by rnubia            #+#    #+#             */
/*   Updated: 2022/07/09 13:34:50 by rnubia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <limits.h>
#include "philo.h"

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

	i = 0;
	while (i < exist->philo_count)
	{
		if (pthread_mutex_init(&(philo + i)->tcheck, NULL) != 0
			|| pthread_mutex_init(&(philo + i)->dcheck, NULL) != 0)
		{
			existence_destroy(exist);
			return (false);
		}
		i ++;
	}
	i = 0;
	gettimeofday(&exist->inception, NULL);
	while (i < exist->philo_count)
	{
		if (pthread_create(&(philo + i)->ptid, NULL, philo_cycle, philo + i))
		{
			existence_destroy(exist);
			return (false);
		}
		i ++;
	}
	return (true);
}

static void	death_monitor(t_exist *exist, t_philo *philo)
{
	t_timeval	curr_time;
	int			i;

	i = 0;
	while (21)
	{
		if (check_eatings(exist) == true)
			break ;
		pthread_mutex_lock(&(philo + i)->tcheck);
		gettimeofday(&curr_time, NULL);
		if (time_less(&(philo + i)->time_to_die, &curr_time) == true)
		{
			philo_died(exist, philo + i, &curr_time);
			pthread_mutex_unlock(&(philo + i)->tcheck);
			break ;
		}
		pthread_mutex_unlock(&(philo + i)->tcheck);
		i = (i + 1) % exist->philo_count;
	}
	i = 0;
	while (i < exist->philo_count)
		pthread_join((philo + i ++)->ptid, NULL);
}

int	main(int argc, char **argv)
{
	t_exist	exist;
	int		args[ARGS_COUNT];

	args[ARGS_COUNT - 1] = -1;
	if (check_args(argc, argv, args) == false)
		return (RETURN_FAILURE);
	if (existence_init(&exist, args) == false)
		return (RETURN_FAILURE);
	if (philos_origin(&exist, exist.philos) == false)
		return (RETURN_FAILURE);
	death_monitor(&exist, exist.philos);
	existence_destroy(&exist);
	return (RETURN_SUCCESS);
}
