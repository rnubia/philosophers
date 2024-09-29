/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnubia <rnubia@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 18:00:06 by rnubia            #+#    #+#             */
/*   Updated: 2022/07/09 16:04:42 by rnubia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philo.h"

long long	time_sub(t_timeval *min, t_timeval *sub)
{
	long long	diff_us;

	diff_us = ((long long)min->tv_sec - (long long)sub->tv_sec)
		* 1000000 + ((long long)min->tv_usec - (long long)sub->tv_usec);
	return (diff_us);
}

t_timeval	time_add(t_timeval *time, long long add_us)
{
	t_timeval	sum;

	sum.tv_sec = time->tv_sec + (long)((time->tv_usec + add_us) / 1000000);
	sum.tv_usec = (time->tv_usec + add_us) % 1000000;
	return (sum);
}

t_bool	time_less(t_timeval *time1, t_timeval *time2)
{
	if (time1->tv_sec == time2->tv_sec)
	{
		if (time1->tv_usec < time2->tv_usec)
			return (true);
		else
			return (false);
	}
	else if (time1->tv_sec < time2->tv_sec)
		return (true);
	else
		return (false);
}

t_bool	usleep_till(t_philo *philo, t_timeval *time)
{
	t_timeval	current_time;

	gettimeofday(&current_time, NULL);
	while (time_less(&current_time, time) == true)
	{
		pthread_mutex_lock(&philo->dcheck);
		if (philo->death == true)
		{
			pthread_mutex_unlock(&philo->dcheck);
			return (false);
		}
		pthread_mutex_unlock(&philo->dcheck);
		usleep(TIMER);
		gettimeofday(&current_time, NULL);
	}
	return (true);
}
