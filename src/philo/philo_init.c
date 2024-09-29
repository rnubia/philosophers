/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnubia <rnubia@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 22:51:11 by rnubia            #+#    #+#             */
/*   Updated: 2022/07/09 12:55:25 by rnubia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include "philo.h"

static void	destroy_forks(t_mutex *forks, int cnt)
{
	int	i;

	i = 0;
	while (i < cnt)
	{
		pthread_mutex_destroy(forks + i);
		i ++;
	}
	free(forks);
}

void	existence_destroy(t_exist *exist)
{
	int	i;

	i = 0;
	while (i < exist->philo_count)
	{
		pthread_mutex_destroy(&(exist->philos + i)->tcheck);
		pthread_mutex_destroy(&(exist->philos + i)->dcheck);
		i ++;
	}
	free(exist->philos);
	destroy_forks(exist->forks, exist->philo_count);
	destroy_mutexes(exist);
}

static t_bool	forks_init(t_exist *exist, int ph_cnt)
{
	t_mutex	*forks;
	int		i;

	forks = (t_mutex *)malloc(sizeof(*forks) * ph_cnt);
	if (forks == NULL)
		return (false);
	exist->forks = forks;
	i = 0;
	while (i < ph_cnt)
	{
		if (pthread_mutex_init(forks + i, NULL) != 0)
		{
			destroy_forks(forks, i - 1);
			return (false);
		}
		i ++;
	}
	return (true);
}

static t_bool	philos_init(t_exist *exist, t_mutex *forks, int ph_cnt)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)malloc(sizeof(*philos) * ph_cnt);
	if (philos == NULL)
		return (false);
	exist->philos = philos;
	i = 0;
	while (i < ph_cnt)
	{
		(philos + i)->phid = i + 1;
		(philos + i)->eating_count = 0;
		(philos + i)->time_to_die.tv_sec = UINT_MAX;
		if (i % 2 == 0)
			(philos + i)->left_fork = (forks + i);
		else
			(philos + i)->right_fork = (forks + i);
		if (i % 2 == 0)
			(philos + i)->right_fork = (forks + (i + 1) % ph_cnt);
		else
			(philos + i)->left_fork = (forks + (i + 1) % ph_cnt);
		(philos + i)->death = false;
		(philos + i ++)->exist = exist;
	}
	return (true);
}

t_bool	existence_init(t_exist *exist, int *args)
{
	exist->philo_count = args[0];
	exist->time_to_die = args[1] * 1000;
	exist->time_to_eat = args[2] * 1000;
	exist->time_to_sleep = args[3] * 1000;
	exist->eating_times = args[4];
	exist->eaten = false;
	if (pthread_mutex_init(&exist->lprint, NULL) != 0)
		return (false);
	if (pthread_mutex_init(&exist->echeck, NULL) != 0)
	{
		pthread_mutex_destroy(&exist->lprint);
		return (false);
	}
	if (forks_init(exist, exist->philo_count) == false)
	{
		destroy_mutexes(exist);
		return (false);
	}
	if (philos_init(exist, exist->forks, exist->philo_count) == false)
	{
		destroy_mutexes(exist);
		destroy_forks(exist->forks, exist->philo_count);
		return (false);
	}
	return (true);
}
