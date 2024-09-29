/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnubia <rnubia@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 20:01:46 by rnubia            #+#    #+#             */
/*   Updated: 2022/07/10 11:43:21 by rnubia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>///
#include "philo_bonus.h"

void	philo_kill(t_exist *exist,  int cnt)
{
	int	i;

	i = 0;
	while (i < cnt)
	{
		kill(exist->(pids + i), SIGKILL);
		i ++;
	}
	free(exist->pids);
}

void	existence_destroy(t_exist *exist)
{
	sem_unlink("/log_print");
	sem_unlink("/forks");
	sem_close(exist->lprint);
	sem_close(exist->forks);
	free(exist->pids);
/*	int	i;

	i = 0;
	while (i < exist->philo_count)
	{
		pthread_mutex_destroy(&(exist->philos + i)->tcheck);
		pthread_mutex_destroy(&(exist->philos + i)->dcheck);
		i ++;
	}
	free(exist->philos);
	destroy_forks(exist->forks, exist->philo_count);
	destroy_mutexes(exist); */
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

static t_bool	philo_init(t_exist *exist, t_philo philo)
{
	philo->eating_count = 0;
	philos->time_to_die.tv_sec = UINT_MAX;
	philos->death = false;
	philo->exist = exist;
	sem_unlink("/time_check");
	sem_unlink("/eatins_check");
	philo->tcheck = sem_open("/time_check", O_CREAT, 0644, 1);
	if (philo->tcheck == SEM_FAILED)
		return (false);
	philo->echeck = sem_open("/eatins_check", O_CREAT, 0644, 1);
	if (exist->echeck == SEM_FAILED)
	{
		sem_close(philo->tcheck);
		sem_unlink("/time_check");
		return (false);
	}
	if (pthread_create(&philo->dmon, NULL, death_monitor, philo))///
	{
		existence_destroy(exist);
		sem_unlink("/time_check");
		sem_unlink("/eatins_check");
		return (false);
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
	sem_unlink("/log_print");
	sem_unlink("/forks");
	exist->lprint = sem_open("/log_print", O_CREAT, 0644, 1);
	if (exist->lprint == SEM_FAILED)
		return (false);
	exist->forks = sem_open("/forks", O_CREAT, 0644, exist->philo_count);
	if (exist->forks == SEM_FAILED)
	{
		sem_close(exist->lprint);
		sem_unlink("/forks");
		return (false);
	}
	exist->pids = (pid_t *)malloc(sizeof(*exist->pids) * exist->philo_count);
	if (pids == NULL)
	{
		sem_close(exist->lprint);
		sem_close(exist->fork);
		sem_unlink("/log_print");
		sem_unlink("/forks");
		return (false);
	}
	return (true);
}
