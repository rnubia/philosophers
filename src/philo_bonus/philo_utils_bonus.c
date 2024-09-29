/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnubia <rnubia@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 18:56:14 by rnubia            #+#    #+#             */
/*   Updated: 2022/07/10 10:00:26 by rnubia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo_bonus.h"

t_bool	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->dcheck);
	if (philo->death == true)
	{
		pthread_mutex_unlock(&philo->dcheck);
		return (true);
	}
	pthread_mutex_unlock(&philo->dcheck);
	return (false);
}

t_bool	check_eatings(t_exist *exist)
{
	pthread_mutex_lock(&exist->echeck);
	if (exist->eaten == true)
	{
		pthread_mutex_unlock(&exist->echeck);
		return (true);
	}
	pthread_mutex_unlock(&exist->echeck);
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

void	philo_died(t_exist *exist, t_philo *philo_died, t_timeval *time)
{
	long long	time_diff;
	int			i;

	i = 0;
	while (i < exist->philo_count)
	{
		pthread_mutex_lock(&(exist->philos + i)->dcheck);
		(exist->philos + i)->death = true;
		pthread_mutex_unlock(&(exist->philos + i)->dcheck);
		i ++;
	}
	time_diff = time_sub(time, &exist->inception) / 1000;
	pthread_mutex_lock(&exist->lprint);
	printf("%lld %d %s\n", time_diff, philo_died->phid, "died");
	pthread_mutex_unlock(&exist->lprint);
}

void	destroy_mutexes(t_exist *exist)
{
	pthread_mutex_destroy(&exist->lprint);
	pthread_mutex_destroy(&exist->echeck);
}
