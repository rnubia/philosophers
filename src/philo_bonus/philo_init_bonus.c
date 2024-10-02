/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnubia <rnubia@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 20:01:46 by rnubia            #+#    #+#             */
/*   Updated: 2022/07/11 02:56:35 by rnubia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include "philo_bonus.h"

void	philo_destroy(t_philo *philo)
{
	pthread_join(philo->dmon, NULL);
	sem_close(philo->tcheck);
	sem_close(philo->echeck);
	sem_unlink("/time_check");
	sem_unlink("/eatins_check");
}

t_bool	philo_init(t_exist *exist, t_philo *philo)
{
	philo->eating_count = 0;
	philo->time_to_die.tv_sec = UINT_MAX;
	philo->death = false;
	philo->exist = exist;
	sem_unlink("/time_check");
	philo->tcheck = sem_open("/time_check", O_CREAT, 0644, 1);
	if (philo->tcheck == SEM_FAILED)
		return (false);
	sem_unlink("/eatins_check");
	philo->echeck = sem_open("/eatins_check", O_CREAT, 0644, 1);
	if (philo->echeck == SEM_FAILED)
	{
		sem_close(philo->tcheck);
		sem_unlink("/time_check");
		return (false);
	}
	if (pthread_create(&philo->dmon, NULL, death_monitor, philo) != 0)
	{
		sem_close(philo->tcheck);
		sem_close(philo->echeck);
		sem_unlink("/time_check");
		sem_unlink("/eatins_check");
		return (false);
	}
	return (true);
}

void	existence_destroy(t_exist *exist)
{
	destroy_sems(exist);
	free(exist->pids);
}

t_bool	existence_init(t_exist *exist, int *args)
{
	exist->philo_count = args[0];
	exist->time_to_die = args[1] * 1000;
	exist->time_to_eat = args[2] * 1000;
	exist->time_to_sleep = args[3] * 1000;
	exist->eating_times = args[4];
	sem_unlink("/log_print");
	exist->lprint = sem_open("/log_print", O_CREAT, 0644, 1);
	if (exist->lprint == SEM_FAILED)
		return (false);
	sem_unlink("/forks");
	exist->forks = sem_open("/forks", O_CREAT, 0644, exist->philo_count);
	if (exist->forks == SEM_FAILED)
	{
		sem_close(exist->lprint);
		sem_unlink("/log_print");
		return (false);
	}
	exist->pids = (pid_t *)malloc(sizeof(*exist->pids) * exist->philo_count);
	if (exist->pids == NULL)
	{
		destroy_sems(exist);
		return (false);
	}
	return (true);
}

void	destroy_sems(t_exist *exist)
{
	sem_close(exist->lprint);
	sem_close(exist->forks);
	sem_unlink("/log_print");
	sem_unlink("/forks");
}
