/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnubia <rnubia@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 18:27:22 by rnubia            #+#    #+#             */
/*   Updated: 2022/07/09 14:09:27 by rnubia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"

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

t_bool	philo_log(t_exist *exist, t_philo *philo, char *mess, t_timeval *time)
{
	long long	time_diff;

	time_diff = time_sub(time, &exist->inception) / 1000;
	pthread_mutex_lock(&philo->dcheck);
	if (philo->death == false)
	{
		pthread_mutex_lock(&exist->lprint);
		printf("%lld %d %s\n", time_diff, philo->phid, mess);
		pthread_mutex_unlock(&exist->lprint);
	}
	else
	{
		pthread_mutex_unlock(&philo->dcheck);
		return (false);
	}
	pthread_mutex_unlock(&philo->dcheck);
	return (true);
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
