/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnubia <rnubia@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 18:56:14 by rnubia            #+#    #+#             */
/*   Updated: 2022/07/11 03:18:05 by rnubia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "philo_bonus.h"

t_bool	check_eatings(t_philo *philo)
{
	sem_wait(philo->echeck);
	if (philo->eaten == true)
	{
		sem_post(philo->echeck);
		return (true);
	}
	sem_post(philo->echeck);
	return (false);
}

void	philo_log(t_exist *exist, t_philo *philo, char *mess, t_timeval *time)
{
	long long	time_diff;

	time_diff = time_sub(time, &exist->inception) / 1000;
	sem_wait(exist->lprint);
	printf("%lld %d %s\n", time_diff, philo->phid, mess);
	sem_post(exist->lprint);
}

void	philos_kill(t_exist *exist, int cnt)
{
	int	i;

	i = 0;
	while (i < cnt)
	{
		kill(*(exist->pids + i), SIGKILL);
		i ++;
	}
	free(exist->pids);
}

void	*death_monitor(void *data)
{
	long long	time_diff;
	t_timeval	curr_time;
	t_exist		*exist;
	t_philo		*philo;

	philo = (t_philo *)data;
	exist = philo->exist;
	while (21)
	{
		if (check_eatings(philo) == true)
			break ;
		sem_wait(philo->tcheck);
		gettimeofday(&curr_time, NULL);
		if (time_less(&philo->time_to_die, &curr_time) == true)
		{
			time_diff = time_sub(&curr_time, &exist->inception) / 1000;
			sem_wait(exist->lprint);
			printf("%lld %d %s\n", time_diff, philo->phid, "died");
			philos_kill(exist, exist->philo_count);
			exit(EXIT_FAILURE);
		}
		sem_post(philo->tcheck);
		usleep(TIMER);
	}
	return (NULL);
}
